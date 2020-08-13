#include <gtk/gtk.h>
#include "basic_types.h"

typedef struct _ParamsXML{
	char8*	lis_mnem;
} ParamsXML;

static GHashTable *hash_table_params_xml = NULL;

static void params_xml_free(ParamsXML *ptr)
{
	if(ptr == NULL)
		return;

	if(ptr->lis_mnem != NULL)
		g_free(ptr->lis_mnem);

	g_free(ptr);
}

void params_xml_hash_table_new()
{
	if(hash_table_params_xml != NULL)
		g_hash_table_destroy(hash_table_params_xml);

	hash_table_params_xml =  g_hash_table_new_full(g_str_hash, g_str_equal, g_free, (GDestroyNotify)params_xml_free);
}

void params_xml_table_set_new_element(const char8 *key, const char8* lis_mnem)
{

	ParamsXML *param;
	if(hash_table_params_xml == NULL)
		return;

	if(key == NULL)
		return;

	if(lis_mnem == NULL)
		return;

	param = g_new0(ParamsXML, 1);
	if(param == NULL)
		return;

	param->lis_mnem = g_strdup(lis_mnem);
	g_hash_table_insert(hash_table_params_xml, g_strdup(key), param);
}

const char8* params_xml_table_get_lis_mnem(const char8 *key)
{
	if(hash_table_params_xml == NULL)
		return NULL;

	if(key == NULL)
		return NULL;

	return (const char8*)g_hash_table_lookup(hash_table_params_xml, key);
}

void params_xml_table_free_data()
{
	if(hash_table_params_xml == NULL)
		return;

	g_hash_table_destroy(hash_table_params_xml);
	hash_table_params_xml = NULL;
}
