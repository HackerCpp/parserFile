/*
 * string-transform.h
 *
 *  Created on: 9 марта 2019 г.
 *      Author: Денис
 */

#ifndef GFM_TOOLS_STRING_TRANSFORM_H_
#define GFM_TOOLS_STRING_TRANSFORM_H_

/* some transform types for curves names */
#define FULL_LOCAL		"FULL"
#define SHORT_LOCAL		"SHORT"
#define SMALL_LOCAL		"SMALL"
#define LAS_FORM		"LAS"
#define LIS_FORM		"LIS"

void 	string_transform_init(char8	*path_file_names_txt);
char8*	string_transform( const char8 *string, const char8 *type );

#endif /* GFM_TOOLS_STRING_TRANSFORM_H_ */
