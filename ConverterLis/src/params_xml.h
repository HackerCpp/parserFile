/*
 * params_xml.h
 *
 *  Created on: 29 нояб. 2019 г.
 *      Author: zloy-virus
 */

#ifndef PARAMS_XML_H_
#define PARAMS_XML_H_

void params_xml_hash_table_new();
void params_xml_table_free_data();
void params_xml_table_set_new_element(const char8 *key, const char8* lis_mnem);

const char8* params_xml_table_get_lis_mnem(const char8 *key);

#endif /* PARAMS_XML_H_ */
