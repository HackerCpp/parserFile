/*
 * getfunction.h
 *
 *  Created on: 30 нояб. 2019 г.
 *      Author: Денис
 */

#ifndef GFM_TOOLS_GETFUNCTION_H_
#define GFM_TOOLS_GETFUNCTION_H_

void* get_function( const char* name );

/*
 * void* get_function(char* name) is used by managers for receiving
 * main program function addresses by name
 */
typedef void* (*GetFunction)( const char* name );


#endif /* GFM_TOOLS_GETFUNCTION_H_ */
