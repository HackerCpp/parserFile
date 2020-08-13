#include "lis_data.h"
#include "lis.h"

static uint32		prev_file_pos = 0;
static TIFBlock		tif = { 0, 0, 0 };

static void swap_int16( int16 *p );
static void swap_int32( int32 *p );
static void float32_to_D( float32 *p );
static void D_to_float32( float32 *p );

static void extract_datum_v( char8 repr_code, va_list *args, Datum *datum, uint8 *size );

static ComponBlock* component_block_v( uint8 type_number, char8 repr_code, const char8 *mnemonic, const char8 *units, va_list *args );

EXTERN void lis_block_write_init()
{
	prev_file_pos = 0;
	tif = (TIFBlock){ 0, 0, 0 };
}

EXTERN void lis_block_add_data( LisBlock *block, const void *data, uint32 data_len )
{
	g_byte_array_append( block, data, data_len );
}

EXTERN void lis_block_add_datum( LisBlock *block, char8 repr_code, ... )
{
	Datum		datum;
	uint8		size;
	va_list		args;

	va_start( args, repr_code );
	extract_datum_v( repr_code, &args, &datum, &size );
	lis_block_add_data( block, &datum, size );
	va_end( args );
}

EXTERN void lis_block_add_compon_block( LisBlock *block, uint8 type_number, char8 repr_code, const char8 *mnemonic, const char8 *units, ... )
{
	ComponBlock		*cb;
	va_list			args;

	va_start( args, units );
	cb = component_block_v( type_number, repr_code, mnemonic, units, &args );
	va_end( args );

	lis_block_add_data( block, cb, sizeof(ComponBlock) - sizeof(cb->datum) + cb->size );

	g_free( cb );
}

EXTERN void lis_block_add_compon_block_list( LisBlock *block, const char8 *repr_codes, char8 **mnemonics, ... )
{
	ComponBlock		*cb;
	va_list			args;
	uint8			type_number;
	uint32			count, i;

	g_return_if_fail( g_strv_length( mnemonics ) == strlen( repr_codes ) );

	type_number = 0;

	va_start( args, mnemonics );
	count = strlen( repr_codes );
	for( i = 0; i < count; ++i ){
		cb = component_block_v( type_number, repr_codes[i], mnemonics[i], "", &args );
		if( cb == NULL ){
			g_warn_if_fail( cb != NULL );
			continue;
		}

		lis_block_add_data( block, cb, sizeof(ComponBlock) - sizeof(cb->datum) + cb->size );
		g_free( cb );

		type_number = 69;
	}
	va_end( args );
}

EXTERN void lis_block_add_entry_block( LisBlock *block, uint8 entry_type, char8 repr_code, ... )
{
	va_list			args;
	uint8			size;
	Datum			datum;
	EntryBlock		*eb;

	va_start( args, repr_code );
	size = 0;
	extract_datum_v( repr_code, &args, &datum, &size );

	if( size == 0 ){
		va_end( args );
		g_return_if_fail( size != 0 );
	}

	eb = g_malloc( sizeof(EntryBlock) - sizeof(eb->datum) + size );
	eb->entry_type = entry_type;
	eb->repr_code = repr_code;
	eb->size = size;
	if( repr_code == 'A' )
		memcpy( &eb->datum, datum.str, size );
	else
		memcpy( &eb->datum, &datum, size );
	va_end( args );

	lis_block_add_data( block, eb, sizeof(EntryBlock) - sizeof(eb->datum) + eb->size );
	g_free( eb );
}

EXTERN void lis_block_write( LisBlock *block, GOutputStream *out, TIFSave tif_save )
{
	PhRecHead		phrec;

	if( block->len == 0 ){
		/* if have no logical data, write TIF block only */
		if( tif_save == TIF_NOT_USE )
			return;

		tif.tif_type = tif_save ;
		tif.next_adr = prev_file_pos + sizeof(TIFBlock);

		g_output_stream_write( out, &tif, sizeof(tif), NULL, NULL );

		tif.prev_adr = prev_file_pos;
		prev_file_pos = tif.next_adr;

		return;
	}

	tif.tif_type = tif_save;
	tif.next_adr = prev_file_pos + sizeof(TIFBlock) + block->len + sizeof(PhRecHead);

	phrec.length = block->len + sizeof(phrec);
	swap_int16( (int16*)&phrec.length );
	phrec.header = 0;

	if( tif_save != TIF_NOT_USE )
		g_output_stream_write( out, &tif, sizeof(tif), NULL, NULL );

	g_output_stream_write( out, &phrec, sizeof(phrec), NULL, NULL );
	g_output_stream_write( out, block->data, block->len, NULL, NULL );

	tif.prev_adr = prev_file_pos;
	prev_file_pos = tif.next_adr;

	g_byte_array_set_size( block, 0 );
}



static void swap_int16( int16 *p )
{
    /*asm volatile(
			"movl		%0, %%edi\n\t"
			"movw		(%%edi), %%ax\n\t"
			"xchg		%%al, %%ah\n\t"
			"movw		%%ax, (%%edi)\n\t"
			::	"A" (p)
			:	"%edi", "%eax"
    );*/
}

static void swap_int32( int32 *p )
{
    /*asm volatile(
			"movl		%0, %%edi\n\t"
			"movl		(%%edi), %%eax\n\t"
			"bswap		%%eax\n\t"
			"movl		%%eax, (%%edi)\n\t"
			::	"A" (p)
			:	"%edi", "%eax"
    );*/
}

static void float32_to_D( float32 *p )
{
    /*if( *((int32*)p) == 0 )
		return;
	asm volatile(
			"movl		%0, %%edi \n\t"
			"movl		(%%edi), %%eax \n\t"
			"xorl		%%ecx, %%ecx \n\t"
			"movl		%%eax, %%ebx \n\t"
			"addl		$0x01000000, %%ebx \n\t"
			"orl		$0x00800000, %%eax \n\t"
			"sarl		$1, %%eax \n\t"
			"jns		p2 \n\t"
			"movl		$0x80000000, %%ecx \n\t"
			"negl		%%eax \n\t"
			"notl		%%ebx \n\t"
		"p2: \n\t"
			"andl		$0x007fffff, %%eax \n\t"
			"andl		$0x7f800000, %%ebx \n\t"
			"orl		%%ebx, %%eax \n\t"
			"orl		%%ecx, %%eax \n\t"
			"bswapl		%%eax \n\t"
			"movl		%%eax, (%%edi) \n\t"
			::	"A" (p)
			:	"%edi", "%eax", "%ebx", "%ecx"
    );*/
}

static void D_to_float32( float32 *p )
{
	bool32	err;

	if( *((int32*)p) == 0 )	/* don't use *p because it contains not float32 value */
		return;

    /*err = FALSE;

	asm volatile(
			"movl		%0, %%edi \n\t"
			"movl		(%%edi), %%eax \n\t"

			"bswapl		%%eax \n\t"
			"movl		%%eax, %%ebx \n\t"
			"xorl		%%ecx, %%ecx \n\t"
			"shll		$1, %%eax \n\t"
			"jnc		p1 \n\t"

			"negl		%%eax \n\t"
			"notl		%%ebx \n\t"
			"movl		$0x80000000, %%ecx \n\t"
		"p1: \n\t"

			"btl		$23, %%eax \n\t"
			"jc			norm \n\t"
			"movl		$1, %1 \n\t"
		"norm: \n\t"
			"subl		$0x01000000, %%ebx \n\t"
			"andl		$0x007fffff, %%eax \n\t"
			"andl		$0x7f800000, %%ebx \n\t"
			"orl		%%ebx, %%eax \n\t"
			"orl		%%ecx, %%eax \n\t"
			"movl		%%eax, (%%edi) \n\t"
			::	"A" (p), "m" (err)
			:	"%edi", "%eax", "%ebx", "%ecx", "memory"
	);
	if( err == TRUE ){
		g_printerr( "\n LIS file has non normalized float32" );
		g_warn_if_reached();
    }*/
}

EXTERN void copy_int16_and_swap_bytes( int16 *dst, const int16 *src, uint32 n )
{
    /*asm volatile(
			"movl		%0, %%esi \n\t"
			"movl		%1, %%edi \n\t"
			"movl		%2, %%ecx \n\t"
			"cld \n\t"
		"rp: \n\t"
			"lodsw \n\t"
			"xchg		%%al, %%ah \n\t"
			"stosw \n\t"
			"loop	rp \n\t"
			::	"g" (src), "g" (dst), "g" (n)
			:	"%edi", "%esi", "%eax", "%ecx"
    );*/

}

EXTERN void str_copy4( char8 *dest, const char8 *src )
{
	uint32	str_len;

	g_return_if_fail( dest != NULL );
	g_return_if_fail( src != NULL );

	str_len = strlen( src );
	if( str_len > 4 ){
		str_len = 4;
		g_printerr( "\n ** ERROR in function str_copy4 string '%s' is too big", src );
		g_warn_if_reached();
	}

	memcpy( dest, src, str_len );
	memset( dest + str_len, ' ', 4 - str_len);
}

static void extract_datum_v( char8 repr_code, va_list *args, Datum *datum, uint8 *size )
{
	*size = 0;
	if( repr_code == '8' ){
		*size = 1;
		datum->_8 = va_arg( *args, int );
	}
	else if( repr_code == 'A' ){
		datum->str = va_arg( *args, char8* );
		if( datum->str != NULL ){
			*size = strlen( datum->str );
			if( *size == 0 ){
				*size = 1;
				datum->str = " ";
			}
		}
	}
	else if( repr_code == 'B' ){
		*size = 1;
		datum->B = va_arg( *args, int );
	}
	else if( repr_code == 'D' ){
		*size = 4;
		datum->D = va_arg( *args, double );
		float32_to_D( &datum->D );
	}
	else if( repr_code == 'I' ){
		*size = 4;
		datum->I = va_arg( *args, int );
		swap_int32( &datum->I );
	}
	else if( repr_code == 'O' ){
		*size = 2;
		datum->O = va_arg( *args, int );
		swap_int16( &datum->O );
	}
}

static ComponBlock* component_block_v( uint8 type_number, char8 repr_code, const char8 *mnemonic, const char8 *units, va_list *args )
{
	uint8			size;
	Datum			datum;
	ComponBlock		*cb;

	size = 0;
	extract_datum_v( repr_code, args, &datum, &size );

	g_return_val_if_fail( size != 0, NULL );

	cb = g_malloc( sizeof(ComponBlock) - sizeof(cb->datum) + size );
	cb->type_number = type_number;
	cb->repr_code = repr_code;
	cb->size = size;
	cb->category = 0;
	str_copy4( cb->mnemonic, mnemonic );
	str_copy4( cb->units, units );
	if( repr_code == 'A' )
		memcpy( &cb->datum, datum.str, size );
	else
		memcpy( &cb->datum, &datum, size );

	return cb;
}
