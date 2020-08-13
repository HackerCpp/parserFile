#ifndef SAVE_EXPORT_CURVES_H_
#define SAVE_EXPORT_CURVES_H_
#include <string.h>
#include <gtk/gtk.h>

#include "common.h"
#include "top_bottom.h"
#include "datablock.h"
#include "program.h"

#define PROP_TIME_STR  "%s_time_select"
#define PROP_DEPTH_STR "%s_depth_select"

EXTERN void	save_default_select_params(GtkListStore *param_store, ExportMode *l_mode);
EXTERN void	read_default_select_params(GtkListStore *param_store, ExportMode *l_mode);

#endif /* SAVE_EXPORT_CURVES_H_ */
