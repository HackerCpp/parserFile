#include <gio/gio.h>

#include "compress.h"

void compress_data( const void *in_data, uint32 in_len, void **out_data, uint32 *out_len )
{
	GZlibCompressor	*gzip;
    GConverterResult res;
	GByteArray		*arr;

#define		ZIPBUF_SIZE		1000
	uint8	zip_buf[ZIPBUF_SIZE];
	gsize	written;
	gsize	read;
	int		count;

    g_return_if_fail( out_data != NULL || out_len != NULL );

    arr = g_byte_array_new();
    gzip = g_zlib_compressor_new( G_ZLIB_COMPRESSOR_FORMAT_GZIP, 9 );
    count = 0;
    do{
		res = g_converter_convert( G_CONVERTER(gzip), in_data + count, in_len - count,
				zip_buf, ZIPBUF_SIZE, G_CONVERTER_INPUT_AT_END, &read, &written, NULL );
		g_byte_array_append( arr, zip_buf, written );
		count += read;
	}while( res == G_CONVERTER_CONVERTED );

    if( res == G_CONVERTER_FINISHED ){
		if( out_data != NULL )
			*out_data = g_memdup( arr->data, arr->len );
		if( out_len != NULL )
			*out_len = arr->len;
	}
	else{
		if( out_data != NULL )
			*out_data = NULL;
		if( out_len != NULL )
			*out_len = 0;
	}

	g_byte_array_free( arr, TRUE );
    g_object_unref( G_OBJECT(gzip) );
}

void decompress_data( const void *in_data, uint32 in_len, void **out_data, uint32 *out_len )
{
	GZlibDecompressor	*guzip;
	GConverterResult	res;
	GByteArray			*arr;

#define		ZIPBUF_SIZE		1000
	uint8	zip_buf[ZIPBUF_SIZE];
	gsize	written;
	gsize	read;
	int		count;

	g_return_if_fail( out_data != NULL || out_len != NULL );

	arr = g_byte_array_new();
	guzip = g_zlib_decompressor_new( G_ZLIB_COMPRESSOR_FORMAT_GZIP );
	count = 0;
	do{
		res = g_converter_convert( G_CONVERTER(guzip), in_data + count, in_len - count,
				zip_buf, ZIPBUF_SIZE, G_CONVERTER_INPUT_AT_END, &read, &written, NULL );
		g_byte_array_append( arr, zip_buf, written );
		count += read;
	}while( res == G_CONVERTER_CONVERTED );

	if( res == G_CONVERTER_FINISHED ){
		if( out_data != NULL )
			*out_data = g_memdup( arr->data, arr->len );
		if( out_len != NULL )
			*out_len = arr->len;
	}
	else{
		if( out_data != NULL )
			*out_data = NULL;
		if( out_len != NULL )
			*out_len = 0;
	}

	g_byte_array_free( arr, TRUE );
	g_object_unref( G_OBJECT(guzip) );
}


