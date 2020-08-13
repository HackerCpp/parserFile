#include <string.h>
#include <gtk/gtk.h>

#include "top_bottom.h"

#include "datablock.h"
#include "save_export_curves.h"

//#include "ui/top_bottom_ui.h"
#include <program_h>
//BUILDER_XML(tb_str)


bool32		is_tif_block = TRUE;
float64		invalid_value = -999.5;

static GtkWidget	*tb_dlg = NULL;
static GtkListStore	*param_store = NULL;
static int			selected_count = 0;
static ExportMode	*l_mode = NULL;

static void process_param_selection();
EXTERN bool32 run(){
    //printf("%s","f_fileName");
}
static void more_toggled(GtkToggleButton *togglebutton, GtkWidget *area )
{
	static gint width = -1;
	static gint height = -1;

	if( gtk_toggle_button_get_active( togglebutton ) == TRUE ){
		gtk_window_set_resizable( GTK_WINDOW(tb_dlg), TRUE );
		gtk_window_resize( GTK_WINDOW(tb_dlg), width, height );
		gtk_widget_show( area );
	}
	else{
		gtk_window_get_size( GTK_WINDOW(tb_dlg), &width, &height );
		gtk_window_set_resizable( GTK_WINDOW(tb_dlg), FALSE );
		gtk_widget_hide( area );
	}
}

static void on_response( GtkButton *button, gpointer data )
{
	gtk_dialog_response( GTK_DIALOG(tb_dlg), GPOINTER_TO_INT(data) );
}

enum _Labels{ UNIT_STEP, UNIT_START, UNIT_STOP, LABEL_COUNT, ENTRY_STEP, ENTRY_START, ENTRY_STOP, ENTRY_COUNT }Labels;
static void on_change_export_by_depth(GtkToggleButton *togglebutton, GtkWidget **widgets );
/* id for stopping update on export type change */
gulong	on_step_changed_id = 0;
static void on_step_changed( GtkEntry *entry, gpointer user_data);

static void create_parameter_list( GtkWidget *, GPtrArray *data_blocks );
static void on_select_deselect( GtkButton *button, gboolean *is_selected_all );

EXTERN bool32 top_bottom_run( ExportMode *mode )
{
	GtkBuilder		*builder;
	GError			*builder_err;

	GtkWidget		*button;
	GtkWidget		*more_area;
	GtkWidget		*nonvalid;
	GtkWidget		*param_list;
	GtkWidget		*widgets[ ENTRY_COUNT ];
	gboolean		is_selected_all;
	GtkWidget		*by_depth;
	GtkWidget		*tif_block;
	gint			ans;
	const char8		*str_const;
	double			l_start;
	double			l_stop;
	double			l_step;

	l_mode = mode;

	builder_err = NULL;
	builder = gtk_builder_new();
    gtk_builder_set_translation_domain( builder, PACKAGE );
    //gtk_builder_add_from_string( builder, tb_str(), strlen( tb_str() ), &builder_err);
    const char* f_fileName = "E:\\MyQtProgram\\parserGfm\\ConverterLis\\src\\ui\\top_bottom.ui";
    gtk_builder_add_from_file(builder,f_fileName,&builder_err);
	if( builder_err != NULL ){
		g_printerr( "\n** ERROR: %s\n", builder_err->message );
		g_return_val_if_reached( 0 );
	}

    tb_dlg = GTK_WIDGET( gtk_builder_get_object( builder, "top_bottom_dialog" ) );

    //gtk_widget_hide( gtk_dialog_get_action_area(GTK_DIALOG(tb_dlg)) );
	gtk_window_set_transient_for( GTK_WINDOW(tb_dlg), GTK_WINDOW( prog_get_top_window_pointer("GTK") ) );

	// TODO add export LIS by time
    gtk_widget_hide( GTK_WIDGET( gtk_builder_get_object( builder, "frame_time_depth" ) ) );

	more_area = GTK_WIDGET( gtk_builder_get_object( builder, "more_area" ) );
	button = GTK_WIDGET( gtk_builder_get_object( builder, "more_button" ) );
	g_signal_connect( G_OBJECT(button), "toggled", G_CALLBACK(more_toggled), more_area );

	button = GTK_WIDGET( gtk_builder_get_object( builder, "button_select" ) );
	is_selected_all = 1;
	g_signal_connect( G_OBJECT(button), "clicked", G_CALLBACK(on_select_deselect), &is_selected_all );

	button = GTK_WIDGET( gtk_builder_get_object( builder, "button_ok" ) );
	g_signal_connect( G_OBJECT(button), "clicked", G_CALLBACK(on_response), GINT_TO_POINTER(GTK_RESPONSE_OK) );
	button = GTK_WIDGET( gtk_builder_get_object( builder, "button_cancel" ) );
	g_signal_connect( G_OBJECT(button), "clicked", G_CALLBACK(on_response), GINT_TO_POINTER(GTK_RESPONSE_CANCEL) );

	widgets[ UNIT_STEP ] = GTK_WIDGET( gtk_builder_get_object( builder, "unit_step" ) );
	widgets[ UNIT_START ] = GTK_WIDGET( gtk_builder_get_object( builder, "unit_start" ) );
	widgets[ UNIT_STOP ] = GTK_WIDGET( gtk_builder_get_object( builder, "unit_stop" ) );
	widgets[ ENTRY_STEP ] = GTK_WIDGET( gtk_builder_get_object( builder, "entry_step" ) );
	widgets[ ENTRY_START ] = GTK_WIDGET( gtk_builder_get_object( builder, "entry_start" ) );
	widgets[ ENTRY_STOP ] = GTK_WIDGET( gtk_builder_get_object( builder, "entry_stop" ) );
	on_step_changed_id = g_signal_connect( G_OBJECT(widgets[ ENTRY_STEP ]), "changed", G_CALLBACK(on_step_changed), widgets );

    by_depth = GTK_WIDGET( gtk_builder_get_object( builder, "bydepth" ) );

    g_signal_connect( G_OBJECT(by_depth), "toggled", G_CALLBACK(on_change_export_by_depth), widgets );
    gtk_toggle_button_set_active( GTK_TOGGLE_BUTTON(by_depth), !mode->is_time_mode );



    nonvalid = GTK_WIDGET( gtk_builder_get_object( builder, "invalid_value" ) );
	str_const = prog_get_pref6s( "invalid_value" );
	if( str_const != NULL )
		gtk_entry_set_text( GTK_ENTRY(gtk_bin_get_child( GTK_BIN(nonvalid) )), str_const );
	else
		gtk_combo_box_set_active( GTK_COMBO_BOX(nonvalid), 1 );

    tif_block = GTK_WIDGET( gtk_builder_get_object( builder, "is_tif_block" ) );
	is_tif_block = TRUE;
	prog_get_pref6s_int32( "is_tif_block", &is_tif_block );
    gtk_toggle_button_set_active( GTK_TOGGLE_BUTTON(tif_block), is_tif_block );

    param_list = GTK_WIDGET( gtk_builder_get_object( builder, "parameters_list" ) );
    create_parameter_list( param_list, data_blocks );

    read_default_select_params( param_store, mode);

	gtk_widget_show( tb_dlg );

    while( 1 ){
		ans = gtk_dialog_run( GTK_DIALOG(tb_dlg) );
		if( ans == GTK_RESPONSE_DELETE_EVENT || ans == GTK_RESPONSE_CANCEL )
			break;
		if( ans == GTK_RESPONSE_OK ){
			if( selected_count == 0 ){
				g_printerr( "\n** NO PARMETERS SELECTED!" );
				continue;
			}
			l_start = prog_strtod( gtk_entry_get_text( GTK_ENTRY(widgets[ ENTRY_START ]) ), NULL );
			l_stop = prog_strtod( gtk_entry_get_text( GTK_ENTRY(widgets[ ENTRY_STOP ]) ), NULL );
			l_step = prog_strtod( gtk_entry_get_text( GTK_ENTRY(widgets[ ENTRY_STEP ]) ), NULL );
			if( l_step < 0 && l_mode->is_time_mode == 1 ){
				g_printerr( "\n** TIME STEP MUST BE POSITIVE!!!" );
				continue;
			}
			if( (l_stop - l_start) * l_step == 0 ){
				g_printerr( "\n** EMPTY DATA!!!" );
				continue;
			}
			if( (l_stop - l_start) * l_step < 0 ){
				g_printerr( "\n** START, STOP, STEP ARE NOT CONFORM" );
				continue;
			}
			if( l_mode->is_time_mode == 0 ){
				l_mode->start_m_5 = l_start * 1e+5;
				l_mode->stop_m_5 = l_stop * 1e+5;
				l_mode->step_m_5 = l_step * 1e+5;
			}
			else{
				l_mode->begin_sec_3 = l_start * 1e+3;
				l_mode->end_sec_3 = l_stop * 1e+3;
				l_mode->step_sec_3 = l_step * 1e+3;
			}

			is_tif_block = gtk_toggle_button_get_active( GTK_TOGGLE_BUTTON(tif_block) );
			prog_put_pref6s_int32( "is_tif_block", is_tif_block );

			invalid_value = prog_strtod( gtk_entry_get_text( GTK_ENTRY(gtk_bin_get_child( GTK_BIN(nonvalid) )) ), NULL );
			prog_put_pref6s_float64( "invalid_value", invalid_value );

			process_param_selection();
			break;
		}
	}

	mode->is_time_mode = gtk_toggle_button_get_active( GTK_TOGGLE_BUTTON(by_depth) ) == FALSE;
	save_default_select_params(param_store, mode);
	gtk_widget_destroy( tb_dlg );
	g_object_unref( G_OBJECT(builder) );
	gtk_list_store_clear (param_store);
	param_store = NULL;
    return ( ans == GTK_RESPONSE_OK );
}

static void process_param_selection()
{
	GtkTreeIter	iter;
	gboolean	valid;
	gboolean	checked;
	ParamDesc	*desc;

	valid = gtk_tree_model_get_iter_first( GTK_TREE_MODEL(param_store), &iter );
	while( valid ){
		gtk_tree_model_get( GTK_TREE_MODEL(param_store), &iter, COLUMN_CHECKED,
				&checked, COLUMN_DESC_POINTER, &desc, -1 );
		if( checked == 0 )
			desc->flags = 0;
		valid = gtk_tree_model_iter_next( GTK_TREE_MODEL(param_store), &iter );
	}
}

static void param_toggled( GtkCellRendererToggle *cell, gchar *path_str, gpointer model )
{
	GtkTreeIter		iter;
	GtkTreePath		*path;
	gboolean		checked;
	ParamDesc		*desc;

	path = gtk_tree_path_new_from_string (path_str);
	gtk_tree_model_get_iter( GTK_TREE_MODEL(model), &iter, path );
	gtk_tree_path_free( path );

	gtk_tree_model_get( GTK_TREE_MODEL(model), &iter, COLUMN_CHECKED, &checked, COLUMN_DESC_POINTER, &desc, -1 );

	checked ^= 1;
	if( checked ){
//		desc->flags |= INTERPOLATE;
		++selected_count;
	}
	else{
//		desc->flags ^= INTERPOLATE;
		--selected_count;
	}

	gtk_list_store_set( GTK_LIST_STORE (model), &iter, COLUMN_CHECKED, checked, -1 );
}

static void create_parameter_list( GtkWidget *treeview, GPtrArray *data_blocks )
{
	DataBlock		**db;
	const ParamDesc	**desc;
	GtkTreeIter		iter;
	GtkCellRenderer *renderer;
	GtkTreeViewColumn *column;
	char8			*str;
	int i;

	param_store = gtk_list_store_new( NUM_COLUMNS, G_TYPE_BOOLEAN, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_POINTER );

	selected_count = 0;
	db = (DataBlock**)&g_ptr_array_index( data_blocks, 0 );
    if(!db)
        return;
    for( i = 0; i < data_blocks->len; ++i, ++db ){
        if(!*db)
            continue;
        desc = data_block_get_paramdesc_array( *db );
        for( ; *desc != NULL; ++desc ){
			bool32 check_param = TRUE;

			gtk_list_store_append( param_store, &iter );
			str = prog_string_transform( (*desc)->entmnem, FULL_LOCAL );
			if((strstr((*desc)->entmnem, "SPEC[") != NULL))
				check_param = TRUE;
			if(strstr((*desc)->entmnem, "WF[") != NULL)
				check_param = TRUE;
			if(strstr((*desc)->entmnem, "SPEED") != NULL)
				check_param = TRUE;
			if(strstr((*desc)->entmnem, "[LEFT]") != NULL)
				check_param = FALSE;
			if(strstr((*desc)->entmnem, "[ZERO]") != NULL)
				check_param = FALSE;

			if(parr_get_last_data((*desc)->parr) == NULL)
				check_param = FALSE;

			if( (*desc)->no_lis ==  TRUE)
				check_param = FALSE;


			gtk_list_store_set( param_store, &iter,
					COLUMN_CHECKED, check_param,
					COLUMN_MNEMONIC, (*desc)->entmnem,
					COLUMN_COMMENT, str,
					COLUMN_DESC_POINTER, *desc,
					-1 );
			g_free( str );
			++selected_count;
        }
    }

    gtk_tree_view_set_model( GTK_TREE_VIEW(treeview), GTK_TREE_MODEL(param_store) );

	renderer = gtk_cell_renderer_toggle_new();
	g_signal_connect( renderer, "toggled", G_CALLBACK(param_toggled), param_store );
	column = gtk_tree_view_column_new_with_attributes( "", renderer, "active", COLUMN_CHECKED, NULL );
	gtk_tree_view_append_column( GTK_TREE_VIEW(treeview), column );

	renderer = gtk_cell_renderer_text_new();
	column = gtk_tree_view_column_new_with_attributes( _("LIS mnemonic"), renderer, "text", COLUMN_MNEMONIC, NULL );
	gtk_tree_view_append_column( GTK_TREE_VIEW(treeview), column );

	renderer = gtk_cell_renderer_text_new();
	column = gtk_tree_view_column_new_with_attributes( _("Comments"), renderer, "text", COLUMN_COMMENT, NULL );
    gtk_tree_view_append_column( GTK_TREE_VIEW(treeview), column );
}

static void on_select_deselect( GtkButton *button, gboolean *is_selected_all )
{
	GtkTreeIter	iter;
	gboolean	valid;
	gboolean	checked;
	ParamDesc	*desc;

	*is_selected_all ^= 1;
	selected_count = 0;
	if( *is_selected_all == 1 ){
		gtk_button_set_label( button, _("Deselect ALL") );
		valid = gtk_tree_model_get_iter_first( GTK_TREE_MODEL(param_store), &iter );
		while( valid ){
			gtk_tree_model_get( GTK_TREE_MODEL(param_store), &iter, COLUMN_CHECKED,
					&checked, COLUMN_DESC_POINTER, &desc, -1 );
			checked = 1;
//			desc->flags |= INTERPOLATE;

			gtk_list_store_set( param_store, &iter, COLUMN_CHECKED, checked, -1 );
			++selected_count;
			valid = gtk_tree_model_iter_next( GTK_TREE_MODEL(param_store), &iter );
		}
	}
	else{
		gtk_button_set_label( button, _("Select ALL") );
		valid = gtk_tree_model_get_iter_first( GTK_TREE_MODEL(param_store), &iter );
		while( valid ){
			gtk_tree_model_get( GTK_TREE_MODEL(param_store), &iter, COLUMN_CHECKED,
					&checked, COLUMN_DESC_POINTER, &desc, -1 );
			checked = 0;
//			desc->flags ^= INTERPOLATE;

			gtk_list_store_set( param_store, &iter, COLUMN_CHECKED, checked, -1 );
			valid = gtk_tree_model_iter_next( GTK_TREE_MODEL(param_store), &iter );
		}
	}
}

static void round_bounds( GtkWidget **widgets )
{
	GString	*str;

	str = g_string_new( NULL );
	if( l_mode->is_time_mode == 0 ){
		g_string_printf( str, "%8.2f", ((l_mode->start_m_5 / l_mode->step_m_5) * l_mode->step_m_5) * 1e-5 );
		gtk_entry_set_text( GTK_ENTRY(widgets[ENTRY_START]), str->str );
		g_string_printf( str, "%8.2f", ((l_mode->stop_m_5 / l_mode->step_m_5) * l_mode->step_m_5) * 1e-5 );
		gtk_entry_set_text( GTK_ENTRY(widgets[ENTRY_STOP]), str->str );
	}
	else{
		g_string_printf( str, "%8.2f", ((l_mode->begin_sec_3 / l_mode->step_sec_3) * l_mode->step_sec_3) * 1e-3 );
		gtk_entry_set_text( GTK_ENTRY(widgets[ENTRY_START]), str->str );
		g_string_printf( str, "%8.2f", ((l_mode->end_sec_3 / l_mode->step_sec_3) * l_mode->step_sec_3) * 1e-3 );
		gtk_entry_set_text( GTK_ENTRY(widgets[ENTRY_STOP]), str->str );
	}
	g_string_free( str, TRUE );
}

static void on_change_export_by_depth(GtkToggleButton *togglebutton, GtkWidget **widgets )
{
	GString	*str;
	int i;

    save_default_select_params(param_store, l_mode);

    str = g_string_new( NULL );
    if( gtk_toggle_button_get_active( togglebutton ) == TRUE ){
		for( i = UNIT_STEP; i < LABEL_COUNT; ++i )
			gtk_label_set_text( GTK_LABEL(widgets[i]), _("m") );

        g_signal_handler_block( G_OBJECT(widgets[ENTRY_STEP]), on_step_changed_id );
        g_string_printf( str, "%8.2f", l_mode->step_m_5 * 1e-5 );
        gtk_entry_set_text( GTK_ENTRY(widgets[ENTRY_STEP]), str->str );
        g_signal_handler_unblock( G_OBJECT(widgets[ENTRY_STEP]), on_step_changed_id );

        l_mode->is_time_mode = 0;
        //round_bounds( widgets );
	}
    else{
		for( i = UNIT_STEP; i < LABEL_COUNT; ++i )
			gtk_label_set_text( GTK_LABEL(widgets[i]), _("sec") );

		g_signal_handler_block( G_OBJECT(widgets[ENTRY_STEP]), on_step_changed_id );
			g_string_printf( str, "%8.2f", l_mode->step_sec_3 * 1e-3 );
			gtk_entry_set_text( GTK_ENTRY(widgets[ENTRY_STEP]), str->str );
		g_signal_handler_unblock( G_OBJECT(widgets[ENTRY_STEP]), on_step_changed_id );

		l_mode->is_time_mode = 1;
        //round_bounds( widgets );
    }
	g_string_free( str, TRUE );

    read_default_select_params(param_store, l_mode);
}

static void on_step_changed( GtkEntry *entry, gpointer user_data )
{
	double		step;
	const gchar	*str;

	str = gtk_entry_get_text( entry );
	if( str!= NULL ){
		step = prog_strtod( str, NULL );
		if( l_mode->is_time_mode == 0 ){
			if( (fixed32_5)(step * 1e+5) != 0 ){
				if( step > 0 )
					l_mode->step_m_5 = (fixed32_5)(step * 1e+5 + 0.5 );
				else
					l_mode->step_m_5 = (fixed32_5)(step * 1e+5 - 0.5 );
			}
		}
		else{
			if( step < 0 )
				step = -step;
			if( (ufixed32_3)(step * 1e+3) != 0 )
				l_mode->step_sec_3  = (ufixed32_3)(step * 1e+3 + 0.5 );
		}
		round_bounds( (GtkWidget**)user_data);
	}
}
