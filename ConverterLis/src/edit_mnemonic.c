/*
 * edit_mnemonic.c
 *
 *  Created on: 27.09.2016
 *      Author: Andrey
 */
#include "edit_mnemonic.h"

static GArray *arr_mnemonics = NULL;
uint16 size_of_mnem = DEFAULT_SIZE_MNEM;

EXTERN void edit_mnemonic(gchar *in_mnem, gchar *in_unit){

	gchar *pos;
	int len_buf;
	int len_buf_nums;
	gchar	buf_skob[100];//буфер для инфы из скобок
	gchar	buf_nums[100];//буфер для цифр
	int i;
	int k;
//	int j;
	uint16 offset = 0;
//	Replay_names item;

	if(arr_mnemonics == NULL)
		arr_mnemonics = g_array_sized_new (FALSE, FALSE, sizeof (Replay_names), 1);

	//выделяем единицы измерения
	if( in_unit[0] == 0 && in_mnem != NULL ){
		pos = strchr(in_mnem, '(');
		if(pos != NULL){
			pos++;
			i = 0;
			while(*pos != ')')
				in_unit[i++] = *pos++;
			in_unit[i] = 0;

		}
		else
			in_unit[0] = 0;
		pos = NULL;
	}

	pos = strchr(in_mnem, '(');
	if(pos != NULL)
		*pos = 0;

	if(strlen(in_mnem) > size_of_mnem){
		//выделяем полезную инфу из квадратных скобок
		i = 0;
		pos = strchr(in_mnem,'[');
		while(pos != NULL){
			pos += 1;
			//берем первый символ из скобки если слово большое, если есть цифры то сохраняем их полностью
			buf_skob[i++] = *pos++;
			while(*pos != ']'){
				if(strchr("0123456789", *pos))
					buf_skob[i++] = *pos;
				pos++;
			}
			pos = strchr(pos,'[');
		}
		buf_skob[i] = 0;
		len_buf = i;

		char8	*new_mnem;
		new_mnem = g_strdup(in_mnem);
		pos = strchr(new_mnem, '[');
		if(pos)
			*pos = 0;

		//выделяем цифры если они есть
		if(new_mnem != NULL ){
			pos = &new_mnem[0];
			offset = 0;
			for(;*pos; ++pos){
				if(strchr("0123456789", *pos)){
					buf_nums[offset] = *pos;
					offset++;
				}
				else
					*(pos - offset) = *pos;
			}
			*(pos - offset) = 0;
		}
		buf_nums[offset] = 0;
		len_buf_nums = offset;

		//соединям два буфера со скобками и цифрами
		for(i = len_buf_nums, k = 0; k < len_buf; k++, i++ )
			buf_nums[i] = buf_skob[k];
		buf_nums[i] = 0;
		len_buf_nums = i;

		// берем по одной букве в слове с '_'
		if(strlen(new_mnem) > size_of_mnem){
			pos = &in_mnem[0];
			k = 1;
			while(1){
				pos = strchr(pos,'_');
				if(pos + 1 == NULL || pos == NULL || strchr("0123456789", *(pos + 1))){
					if(k > 1)
						new_mnem[k] = 0;
	//				if(k > 1){
	//					for(i = k; k < size_of_mnem; k++)
	//						new_mnem[k] = ' ';
	//					new_mnem[k] = 0;
	//				}
					break;
				}
				new_mnem[k] = *(pos + 1);
				k++;
				pos = pos + 1;
			}
		}

		// если букв получилось больше size_of_mnem удаляем гласные начиная со 2 -ой
		if(new_mnem != NULL && strlen(new_mnem) > size_of_mnem){
			pos = &new_mnem[1];
			offset = 0;
			for(;*pos; ++pos){
				if(strchr("AEIOUY", *pos))
					offset++;
				else
					*(pos - offset) = *pos;
			}
			*(pos - offset) = 0;
		}

		if( new_mnem != NULL && strlen(new_mnem) > size_of_mnem )
			new_mnem[size_of_mnem] = 0;

//		if( in_unit != NULL && strlen(in_unit) > size_of_mnem )
//			in_unit[size_of_mnem] = 0;

		//добавляем полезную информацию
		char8	*concat_mnem = g_strconcat(new_mnem, buf_nums, NULL);
		g_free(new_mnem);
		new_mnem = g_strdup(concat_mnem);
		g_free(concat_mnem);
/*
			if(len_buf_nums != 0 && len_buf_nums < size_of_mnem + 1){
				k = 0;
				if(strlen(new_mnem) < size_of_mnem){
					for(i = strlen(new_mnem); i<size_of_mnem; i++)
						new_mnem[i] = buf_nums[k++];
				}
				else
					for(i = size_of_mnem - len_buf_nums; i < size_of_mnem; i++){
						new_mnem[i] = buf_nums[k];
						k++;
					}
				new_mnem[i] = 0;
			}
*/
			//	pos = strchr(in_mnem,'[');
			//	if(pos)
			//		new_mnem = g_strconcat(new_mnem, pos, NULL);

				for(k = 0; k < strlen(new_mnem); k++)
					in_mnem[k] = new_mnem[k];
				in_mnem[k] = 0;

				if(new_mnem)
					g_free(new_mnem);

	}

	//удаляем скобки, если они есть
	pos = &in_mnem[0];
	offset = 0;
	for(;*pos; ++pos){
		if(strchr("[]()_", *pos))
			offset++;
		else
			*(pos - offset) = *pos;
	}
	*(pos - offset) = 0;

	//сравниваем полученную мнемонику с предыдущими, если такая же попалась то добавляем вместо последнего символа число повторов этой мнемоники
	cmp_mnem_with_arr(in_mnem, in_unit);
}

EXTERN void destroy_arr_mnemonics(){
	int i;

	if(arr_mnemonics == NULL)
		return;

	for(i = 0 ; i < arr_mnemonics->len; i++){
		if(g_array_index(arr_mnemonics,Replay_names, i).mnem != NULL)
			g_free(g_array_index(arr_mnemonics,Replay_names, i).mnem);
		if(g_array_index(arr_mnemonics,Replay_names, i).unit != NULL)
			g_free(g_array_index(arr_mnemonics,Replay_names, i).unit);
	}
	g_array_free(arr_mnemonics, TRUE);
	arr_mnemonics = NULL;
}

EXTERN void cmp_mnem_with_arr(char8	*in_mnem, char8	*in_unit){
	int i;
	char8	*new_mnem;
	Replay_names *item;

	if(arr_mnemonics == NULL)
		return;

	if(in_mnem == NULL)
		return;
	if(in_unit == NULL)
		return;

	//сравниваем полученную мнемонику с предыдущими, если такая же попалась то добавляем вместо последнего символа число повторов этой мнемоники
	for(i = 0; i < arr_mnemonics->len; i++ )
		if(strcmp(in_mnem, g_array_index(arr_mnemonics, Replay_names, i).mnem) == 0 &&
			strcmp(in_unit, g_array_index(arr_mnemonics, Replay_names, i).unit) == 0){
			g_array_index(arr_mnemonics, Replay_names, i).num_replay += 1;
			gchar *suffix = g_strdup_printf("%d", g_array_index(arr_mnemonics, Replay_names, i).num_replay);

			new_mnem = g_strconcat(in_mnem, suffix, NULL);
/*			len_buf = strlen(suffix);

			if(strlen(in_mnem) < size_of_mnem){
				k = 0;
				for(j = strlen(in_mnem); j<size_of_mnem; j++)
					in_mnem[j] = suffix[k++];
				in_mnem[j] = 0;
			}
			else
				if(len_buf != 0 && len_buf < size_of_mnem + 1){
					k = 0;
				for(j = size_of_mnem - len_buf; j<size_of_mnem; j++)
					in_mnem[j] = suffix[k++];
				in_mnem[j] = 0;
			}
*/
			g_free(in_mnem);
			in_mnem = g_strdup(new_mnem);
			g_free(new_mnem);

			if(suffix != NULL)
				g_free(suffix);

			return;
		}

	item = g_new0(Replay_names, 1);
	item->mnem = g_strdup(in_mnem);
	item->unit = g_strdup(in_unit);
	item->num_replay = 0;
	g_array_append_vals (arr_mnemonics, item, 1);
}
