/*
 * units_scale.h
 *
 *  Created on: 6 марта 2019 г.
 *      Author: zloy-virus
 */

#ifndef GFM_TOOLS_UNITS_SCALE_H_
#define GFM_TOOLS_UNITS_SCALE_H_

gboolean	gfm_units_init_default();
void 		gfm_units_free_data();
double 		gfm_units_get_scale(const char8 *units_name);

#endif /* GFM_TOOLS_UNITS_SCALE_H_ */
