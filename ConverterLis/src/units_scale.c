/*
 * units_scale.c
 *
 *  Created on: 6 марта 2019 г.
 *      Author: zloy-virus
 */

#include "gtk/gtk.h"

static GData*	units = 0; 					/* list of unit's scales */

typedef struct _GfmUnits{
	gchar	*name;
	gchar	*scale;
} GfmUnits;

gboolean gfm_units_init_default()
{
	int 		i;
	char		*name_brackets;

	GfmUnits units_default[] = {
			{.name = "PIX", .scale = "2.1928571428571428571428571428571"},
			{.name = "CMM", .scale = "0.1"},
			{.name = "DMM", .scale = "1"},
			{.name = "MM",	.scale = "10"},
			{.name = "CM",	.scale = "100"},
			{.name = "M",	.scale = "10000"},
			{.name= "FT",	.scale = "3048"},
			{.name="FOOT",	.scale ="3048"},
			{.name="IN",	.scale="254"},
			{.name="INCH",	.scale="254"},
			{.name="MSEC",	.scale="1"},
			{.name="MKSEC", .scale="0.001"},
			{.name="USEC",	.scale="0.001"},
			{.name="SEC",	.scale="1000"},
			{.name="MIN",	.scale="60000"},
			{.name="HR",	.scale="3600000"},
			{.name="GRAM",	.scale="0.001"},
			{.name="KG",	.scale="1"},
			{.name="TONNE", .scale="1000"},
			{.name="LB", 	.scale="0.45359237"}
	};

	if( units )
		g_datalist_clear( &units );
	else
		g_datalist_init( &units );

	for(i = 0; i < G_N_ELEMENTS(units_default); i++){
		double	*d = g_new( double, 1 );
		*d = g_strtod( (const gchar*)units_default[i].scale, NULL );
		name_brackets = g_strdup_printf( "(%s)", (gchar*)units_default[i].name );
		g_datalist_set_data_full( &units, (const gchar*)units_default[i].name, d, g_free );
		g_datalist_set_data_full( &units, (const gchar*)name_brackets, d, g_free );
		g_free(name_brackets);
	}

	return TRUE;

}

void gfm_units_free_data()
{
	if(units){
		g_datalist_clear( &units );
		units = NULL;
	}
}

double gfm_units_get_scale(const gchar *units_name)
{
	GQuark id;
	gpointer data;

	g_return_val_if_fail(units_name != NULL, 1);
	g_return_val_if_fail( units != NULL, 1 );

	id = g_quark_from_string(units_name);
	data = g_datalist_id_get_data( &units, id );
	if( data == NULL ){
		g_printerr( "\n** UNIT '%s' NOT FOUND", g_quark_to_string( id ) );
		g_return_val_if_reached( 0.0 );
	}
	return *(double*)data;
}
