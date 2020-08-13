#ifndef EDIT_MNEMONIC_H_
#define EDIT_MNEMONIC_H_

#include "gtk/gtk.h"
#include "common.h"

typedef struct _replay_names{
	gchar		*mnem;
	gchar		*unit;
	uint16		num_replay;
} Replay_names;

#define DEFAULT_SIZE_MNEM 4

EXTERN void edit_mnemonic(gchar *in_mnem, gchar *in_unit);
EXTERN void cmp_mnem_with_arr(char8	*in_mnem, char8	*in_unit);
EXTERN void destroy_arr_mnemonics();

#endif /* EDIT_MNEMONIC_H_ */
