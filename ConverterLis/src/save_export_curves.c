#include "save_export_curves.h"
#include "top_bottom.h"
#include "program.h"

static const char8* cut_shortcut( const char8 *str )
{
	char8	*out;

	if( str == NULL )
		return NULL;
	out = strstr( str, ":" );
	if( out != NULL )
		return out + 1;

	return str;
}

EXTERN void	save_default_select_params(GtkListStore *param_store, ExportMode *l_mode){

	GtkTreeIter	iter;
	gboolean	valid;
	gboolean	checked;
	ParamDesc	*desc;
	const char *prop_str;
	char8	*mode_name = NULL;
	const char8	*param_name;
	char8	*pos;

	if(param_store == NULL)
		return;

	valid = gtk_tree_model_get_iter_first( GTK_TREE_MODEL(param_store), &iter );
	while( valid ){

		gtk_tree_model_get( GTK_TREE_MODEL(param_store), &iter, COLUMN_CHECKED,
				&checked, COLUMN_DESC_POINTER, &desc, -1 );

		if(desc == NULL){
			valid = gtk_tree_model_iter_next( GTK_TREE_MODEL(param_store), &iter );
			continue;
		}

		pos = strchr(desc->entmnem, '.');
		if(pos != NULL){
			mode_name = g_strdup(pos + 1);
			pos = strchr(mode_name, '[');
			if(pos != NULL)
				*pos = 0;
			else{
				pos = strchr(mode_name,':');
				if(pos != NULL)
					*pos = 0;
			}

		}

		param_name = cut_shortcut( desc->entmnem );

		if(mode_name){
			if(l_mode->is_time_mode)
				prop_str = prog_str_printf(PROP_TIME_STR, param_name);
			else
				prop_str = prog_str_printf(PROP_DEPTH_STR, param_name);
			prog_set_default_module_prop_int32(mode_name, prop_str, checked);
			g_free(mode_name);
			mode_name = NULL;
		}
		valid = gtk_tree_model_iter_next( GTK_TREE_MODEL(param_store), &iter );
	}

}

EXTERN void	read_default_select_params(GtkListStore *param_store, ExportMode *l_mode){
	GtkTreeIter	iter;
	gboolean	valid;
	int32		checked;
	ParamDesc	*desc;

	char8	*mode_name = NULL;
	const char8	*param_name;
	char8	*pos;
	bool32 status;
	const char *prop_str;

	if(param_store){
		valid = gtk_tree_model_get_iter_first( GTK_TREE_MODEL(param_store), &iter );
		while( valid ){
			gtk_tree_model_get( GTK_TREE_MODEL(param_store), &iter, COLUMN_DESC_POINTER, &desc, -1 );
			if(desc == NULL){
				valid = gtk_tree_model_iter_next( GTK_TREE_MODEL(param_store), &iter );
				continue;
			}
			param_name = cut_shortcut( desc->entmnem );

			pos = strchr(desc->entmnem, '.');
			if(pos != NULL){
				mode_name = g_strdup(pos + 1);
				pos = strchr(mode_name, '[');
				if(pos != NULL)
					*pos = 0;
				else{
					pos = strchr(mode_name,':');
					if(pos != NULL)
						*pos = 0;
				}
			}

			if(mode_name){
				if(l_mode->is_time_mode)
					prop_str = prog_str_printf(PROP_TIME_STR, param_name);
				else
					prop_str = prog_str_printf(PROP_DEPTH_STR, param_name);
				status = prog_get_default_module_prop_int32(mode_name, prop_str, &checked);
				g_free(mode_name);
				mode_name = NULL;
				if(status == TRUE)
					gtk_list_store_set( param_store, &iter, COLUMN_CHECKED, checked, -1 );
			}

			valid = gtk_tree_model_iter_next( GTK_TREE_MODEL(param_store), &iter );
		}
	}
}
