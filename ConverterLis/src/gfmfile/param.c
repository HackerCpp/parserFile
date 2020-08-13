#include <string.h>
#include <glib.h>
#include <gio/gio.h>

#include "datablock.h"

typedef ParamData ParamSlice[POINT_CONTINUE_SIZE];
#define POINT_SLICE_SHIFT	8
#define POINT_SLICE_MASK	255

/* reserved count of ParamSlice */
#define RESERVED_COUNT_SLICES	1024

struct _ParamArray{
};

/* store ParamPoint in array of slices for optimal memory using,
 * use depth slices for fast searching ParamPoint by depth */
typedef struct _ParamArrayPrivate {
	ParamArray	parr;

	size_t		count;		/* ParamPoint count in all slices */
	GPtrArray	*data;		/* array of pointers to ParamSlice */
	ParamData	*last;		/* pointer to last ParamPoint in ParamArray */
	GPtrArray	*dslices;	/* array of pointers of DepthSlice */
	DepthSlice	*dlast;		/* pointer to last DepthSlice in dslices */
} ParamArrayPrivate;

#ifdef __GNUC__
#define INLINE __inline
#else
#ifdef __cplusplus
#define INLINE inline
#else
#undef INLINE
#endif
#endif
static ParamData* parr_get_data_int( ParamArrayPrivate *parr, size_t index )
{
	return (ParamData*)g_ptr_array_index( parr->data, index>>POINT_SLICE_SHIFT) + (index&POINT_SLICE_MASK);
}

static void parr_depth_slice_int( ParamArrayPrivate *parr, size_t numslice,
		fixed32_5 begin_m_5, fixed32_5 end_m_5, size_t *ibeg, size_t *iend );

EXTERN ParamArray* parr_create()
{
	ParamArrayPrivate *res;
	res = g_slice_new( ParamArrayPrivate );
	res->count = 0;
	res->data = g_ptr_array_sized_new( RESERVED_COUNT_SLICES );
	res->last = NULL;
	res->dslices = g_ptr_array_new();
	res->dlast = NULL;
	return &res->parr;
}

EXTERN void parr_dup_data( const ParamArray *src, ParamArray *dest )
{
	ParamArrayPrivate *res, *priv;
	int i;

	g_return_if_fail( src != NULL );
	g_return_if_fail( dest != NULL );

	priv = (ParamArrayPrivate*)src;
	res = (ParamArrayPrivate*)dest;

	res->count = priv->count;

	for( i = 0; i < priv->data->len; ++i )
		g_ptr_array_add( res->data, g_slice_dup(ParamSlice, g_ptr_array_index(priv->data, i)) );
	if( res->count > 0 )
		res->last = parr_get_data_int( res, res->count-1  );

	for( i = 0; i < priv->dslices->len; ++i )
		g_ptr_array_add( res->dslices, g_slice_dup(DepthSlice, g_ptr_array_index(priv->dslices, i)) );
	if( i > 0 )
		res->dlast = g_ptr_array_index(res->dslices, i-1 );
}

static void slice_free( gpointer data, gpointer user_data )
{
	g_slice_free1( GPOINTER_TO_SIZE(user_data), data );
}

EXTERN void parr_clear( ParamArray *parr )
{
	ParamArrayPrivate *priv;

	if( parr != NULL ){
		priv = (ParamArrayPrivate*)parr;
		priv->count = 0;
		priv->last = NULL;
		g_ptr_array_foreach( priv->dslices, slice_free, GSIZE_TO_POINTER(sizeof(DepthSlice)) );
		priv->dslices->len = 0;
		priv->dlast = NULL;
	}
}

EXTERN void parr_destroy( ParamArray *parr )
{
	ParamArrayPrivate *priv;

	if( parr != NULL ){
		priv = (ParamArrayPrivate*)parr;
		g_ptr_array_foreach( priv->data, slice_free, GSIZE_TO_POINTER(sizeof(ParamSlice)) );
		g_ptr_array_free( priv->data, TRUE );
		g_ptr_array_foreach( priv->dslices, slice_free, GSIZE_TO_POINTER(sizeof(DepthSlice)) );
		g_ptr_array_free( priv->dslices, TRUE );
		g_slice_free( ParamArrayPrivate, priv );
	}
}

EXTERN size_t parr_param_count( ParamArray *parr )
{
	ParamArrayPrivate *priv;

	g_return_val_if_fail( parr != NULL, 0 );

	priv = (ParamArrayPrivate*)parr;
	g_return_val_if_fail( priv->data != NULL, 0 );

	return priv->count;
}

EXTERN size_t parr_add_data( ParamArray *parr, ParamData data )
{
	ParamArrayPrivate *priv;
	size_t 		res;
	DSDirection	newd;

	g_return_val_if_fail( parr != NULL, -1 );

	priv = (ParamArrayPrivate*)parr;
	g_return_val_if_fail( priv->data != NULL, -1 );

	res = priv->count;
	++priv->count;
	if( priv->last == NULL ){
		g_ptr_array_add( priv->dslices, g_slice_new0(DepthSlice) );
		priv->dlast = g_ptr_array_index( priv->dslices, 0 );
	}
	else{
		if( priv->last->position.depth_m_5 > data.position.depth_m_5 )
			newd = DS_UP;
		else if( priv->last->position.depth_m_5 < data.position.depth_m_5 )
			newd = DS_DOWN;
		else
			newd = DS_UNKNOWN;
		if( priv->dlast->dir == DS_UNKNOWN )
			priv->dlast->dir = newd;
		if( priv->dlast->dir == newd || newd == DS_UNKNOWN )
			priv->dlast->end = res;
		else{
			priv->dlast = g_slice_new(DepthSlice);
			priv->dlast->dir = DS_UNKNOWN;
			priv->dlast->end = priv->dlast->begin = res;
			g_ptr_array_add( priv->dslices, priv->dlast );
		}
	}

	if( (priv->count)>>POINT_SLICE_SHIFT >= priv->data->len )
		g_ptr_array_add( priv->data, g_slice_new(ParamSlice) );
	priv->last = parr_get_data_int( priv, res );
	memcpy( priv->last, &data, sizeof(ParamData) );

	return res;
}

EXTERN ParamData*	parr_get_data( ParamArray *parr, size_t index )
{
	ParamArrayPrivate *priv;

	g_return_val_if_fail( parr != NULL, NULL );

	priv = (ParamArrayPrivate*)parr;
	g_return_val_if_fail( priv->data != NULL, NULL );

	if( index >= priv->count ){
		g_printerr( "\n** INDEX %d OUT OF RANGE %d", index, priv->count );
		g_return_val_if_reached( NULL );
	}
	return parr_get_data_int( priv, index );
}

EXTERN ParamData*	parr_get_last_data( ParamArray *parr )
{
	ParamArrayPrivate *priv;

	g_return_val_if_fail( parr != NULL, NULL );

	priv = (ParamArrayPrivate*)parr;
	g_return_val_if_fail( priv->data != NULL, NULL );

	if( priv->count == 0 )
		return NULL;

	return priv->last;
}

EXTERN size_t parr_depth_slice( ParamArray *parr, fixed32_5 begin_m_5, fixed32_5 end_m_5, DepthSlice **arr )
{
	ParamArrayPrivate *priv;
	DepthSlice		ds;
	size_t 			i, ibeg, iend;

	static GArray	*darr = NULL;

	g_return_val_if_fail( arr != NULL, 0 );

	*arr = NULL;

	g_return_val_if_fail( parr != NULL, 0 );

	priv = (ParamArrayPrivate*)parr;

	if( priv->count == 0 )
		return 0;

	g_return_val_if_fail( priv->data != NULL, 0 );
	g_return_val_if_fail( priv->dslices != NULL, 0 );
	g_return_val_if_fail( begin_m_5 <= end_m_5, 0 );

	if( darr == NULL )
		darr = g_array_new( FALSE, FALSE, sizeof( DepthSlice) );
	g_array_set_size( darr, 0 );
	for( i = 0; i < priv->dslices->len; ++i ){
		parr_depth_slice_int( priv, i, begin_m_5, end_m_5, &ibeg, &iend );
		if( ibeg != -1 && iend != -1 ){
			ds.dir = ((DepthSlice*)g_ptr_array_index( priv->dslices, i))->dir;
			ds.begin = ibeg;
			ds.end = iend;
			g_array_append_val( darr, ds );
		}
	}
	if( darr->len != 0 ){
		*arr = g_new( DepthSlice, darr->len );
		memcpy( *arr, darr->data, sizeof(DepthSlice) * darr->len );
	}
	return darr->len;
}

EXTERN void parr_get_depth_interval( ParamArray *parr, fixed32_5 *top_m_5, fixed32_5 *bottom_m_5, DSDirection *dir )
{
	ParamArrayPrivate	*priv;
	fixed32_5		l_top_m_5, n_top_m_5;
	fixed32_5		l_bot_m_5, n_bot_m_5;
	fixed32_5		max_len_m_5;
	fixed32_5		cur_len_m_5;
	DSDirection		l_dir;
	DSDirection		prev_dir;
	DepthSlice		**ds;
	int i;

	g_return_if_fail( parr != NULL );

	priv = (ParamArrayPrivate*)parr;

	if( priv->count == 0 )
		return;

	l_top_m_5 = priv->last->position.depth_m_5;
	l_bot_m_5 = priv->last->position.depth_m_5;
	max_len_m_5 = 0;
	cur_len_m_5 = 0;
	l_dir = DS_UNKNOWN;
	prev_dir = DS_UNKNOWN;

	ds = (DepthSlice**)&g_ptr_array_index( priv->dslices, 0 );
	for( i = 0; i < priv->dslices->len; ++i, ++ds ){
		if( (*ds)->dir == DS_UP ){
			n_top_m_5 = parr_get_data_int( priv, (*ds)->end )->position.depth_m_5;
			n_bot_m_5 = parr_get_data_int( priv, (*ds)->begin )->position.depth_m_5;
		}
		else{
			n_top_m_5 = parr_get_data_int( priv, (*ds)->begin )->position.depth_m_5;
			n_bot_m_5 = parr_get_data_int( priv, (*ds)->end )->position.depth_m_5;
		}

		if( prev_dir == (*ds)->dir ){
			cur_len_m_5 += n_bot_m_5 - n_top_m_5;
		}
		else{
			if( cur_len_m_5 > max_len_m_5 ){
				max_len_m_5 = cur_len_m_5;
				l_dir = prev_dir;
			}
			prev_dir = (*ds)->dir;
			cur_len_m_5 = n_bot_m_5 - n_top_m_5;
		}

		if( l_top_m_5 > n_top_m_5 )
			l_top_m_5 = n_top_m_5;
		if( l_bot_m_5 < n_bot_m_5 )
			l_bot_m_5 = n_bot_m_5;
	}

	if( cur_len_m_5 > max_len_m_5 )
		l_dir = prev_dir;

	if( top_m_5 != NULL )
		*top_m_5 = l_top_m_5;
	if( bottom_m_5 != NULL )
		*bottom_m_5 = l_bot_m_5;
	if( dir != NULL )
		*dir = l_dir;
}


EXTERN void parr_time_slice( ParamArray *parr, ufixed32_3 begin_sec_3, ufixed32_3 end_sec_3, size_t *ibeg, size_t *iend )
{
	ParamArrayPrivate *priv;
	size_t			l, h, c;
	ufixed32_3		lt_sec_3, ht_sec_3, ct_sec_3;

	g_return_if_fail( parr != NULL );

	*ibeg = -1;
	*iend = -1;
	priv = (ParamArrayPrivate*)parr;
	if( priv->count == 0 )
		return;

	g_return_if_fail( priv->data != NULL );
	g_return_if_fail( begin_sec_3 <= end_sec_3 );

	lt_sec_3 = parr_get_data_int(priv, 0)->position.time_sec_3;
	h = priv->count -1;
	ht_sec_3 = parr_get_data_int(priv, h)->position.time_sec_3;
	if( begin_sec_3 > ht_sec_3 || end_sec_3 < lt_sec_3 )
		return;

	/* searching low bound for begin_sec_3 time */
	*ibeg = 0;
	if( begin_sec_3 > lt_sec_3 ){
		/* binary search */
		while( h - *ibeg > 1 ){
			c = ( h + *ibeg ) / 2;
			ct_sec_3 = parr_get_data_int(priv, c)->position.time_sec_3;
			if( ct_sec_3 > begin_sec_3 ){
				h = c;
				ht_sec_3 = ct_sec_3;
			}
			else{
				*ibeg = c;
				lt_sec_3 = ct_sec_3;
			}
		}
	}

	/* searching high bound for end_sec_3 time */
	*iend = priv->count - 1;
	ht_sec_3 = parr_get_data_int(priv, *iend)->position.time_sec_3;
	if( end_sec_3 < ht_sec_3  ){
		/* binary search starts from low bound */
		l = *ibeg;
		lt_sec_3 = parr_get_data_int(priv, l)->position.time_sec_3;
		while( *iend - l > 1 ){
			c = ( *iend + l ) / 2;
			ct_sec_3 = parr_get_data_int(priv, c)->position.time_sec_3;
			if( ct_sec_3 > end_sec_3 ){
				*iend = c;
				ht_sec_3 = ct_sec_3;
			}
			else{
				l = c;
				lt_sec_3 = ct_sec_3;
			}
		}
	}
}

/* searching indexes for given depth slice */
static void parr_depth_slice_int( ParamArrayPrivate *parr, size_t numslice,
		fixed32_5 begin_m_5, fixed32_5 end_m_5, size_t *ibeg, size_t *iend )
{
	DepthSlice	*ds;
	fixed32_5	ld_m_5, hd_m_5, cd_m_5;
	size_t		l, h, c;

	ds = (DepthSlice*)g_ptr_array_index( parr->dslices, numslice );
	if( ds->dir == DS_DOWN ){
		*ibeg = ds->begin;
		*iend = ds->end;
	}else{
		*ibeg = ds->end;
		*iend = ds->begin;
	}
	ld_m_5 = parr_get_data_int( parr, *ibeg )->position.depth_m_5;
	hd_m_5 = parr_get_data_int( parr, *iend )->position.depth_m_5;
	if( begin_m_5 > hd_m_5 || end_m_5 < ld_m_5 ){
		*ibeg = -1;
		*iend = -1;
		return;
	}
	if( begin_m_5 > ld_m_5 ){
		/* binary search */
		h = *iend;
		while( *ibeg != h+1 && *ibeg+1 != h ){
			c = (*ibeg + h) / 2;
			cd_m_5 = parr_get_data_int( parr, c )->position.depth_m_5;
			if( cd_m_5 > begin_m_5 ){
				h = c;
				hd_m_5 = cd_m_5;
			}
			else{
				*ibeg = c;
				ld_m_5 = cd_m_5;
			}
		}
		hd_m_5 = parr_get_data_int( parr, *iend )->position.depth_m_5;
	}
	if( end_m_5 < hd_m_5 ){
		/* binary search */
		l = *ibeg;
		while( *iend != l+1 && *iend+1 != l ){
			c = (*iend + l) / 2;
			cd_m_5 = parr_get_data_int( parr, c )->position.depth_m_5;
			if( cd_m_5 < end_m_5 ){
				l = c;
				ld_m_5 = cd_m_5;
			}
			else{
				*iend = c;
				hd_m_5 = cd_m_5;
			}
		}
	}
	if( ds->dir == DS_UP ){
		c = *ibeg;
		*ibeg = *iend;
		*iend = c;
	}
}


EXTERN void parr_remove_depth_overlap( ParamArray *parr )
{
	ParamArrayPrivate	*priv;
	ParamArray	*pnew;
	uint32		i;
	fixed32_5	depth_prev;
	ParamData	*pd;
	DepthSlice	**ds;
	DSDirection	dir;

	g_return_if_fail( parr != NULL );

	priv = (ParamArrayPrivate*)parr;
	if( priv->count == 0 )
		return;

	parr_get_depth_interval( parr, NULL, NULL, &dir );
	ds = (DepthSlice**)(&g_ptr_array_index( priv->dslices, 0 ) );

	depth_prev = 0xFFFFFFFF;

	pnew = parr_create();
	for( i = 0; i < priv->count; ++i ){
		if( i > (*ds)->end )
			++ds;
		if( (*ds)->dir != dir )
			continue;
		pd = parr_get_data_int( priv, i );
		if( depth_prev != 0xFFFFFFFF ){
			if( dir == DS_UP && depth_prev < pd->position.depth_m_5 )
				continue;
			if( dir == DS_DOWN && depth_prev > pd->position.depth_m_5 )
				continue;
		}
		depth_prev = pd->position.depth_m_5;
		parr_add_data( pnew, *pd );
	}

	parr_clear( parr );
	g_ptr_array_foreach( priv->data, slice_free, GSIZE_TO_POINTER(sizeof(ParamSlice)) );
	g_ptr_array_free( priv->data, TRUE );
	g_ptr_array_free( priv->dslices, TRUE );
	memcpy( priv, pnew, sizeof(ParamArrayPrivate) );
	g_slice_free1( sizeof(ParamArrayPrivate), pnew );
}
