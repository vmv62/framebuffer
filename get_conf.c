#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "get_conf.h"
#include "bmp.h"

int main(int argc, char **argv){
//	sconf_t *conf;
	prg_dat_t *p_conf;

//	conf = (sconf_t *)malloc(sizeof(sconf_t));
	p_conf = (prg_dat_t *)malloc(sizeof(prg_dat_t));
//	printf("%d\n", sizeof(prg_dat_t));
//	read_conf(argv[1], conf, p_conf);
	read_conf(argv[1], p_conf);

//	printf("Object count == %d\n", p_conf->obj_count);
	printf("Info about object 1: Name: %s, X coord: %d, Y coord: %d, File: \n", p_conf->object[0].file_name_1, &p_conf->object[0].xcoord, p_conf->object[0].ycoord);

//	free(conf);
	free(p_conf);
	return 0;
}

//uint32_t read_conf(char *file, sconf_t *conf, prg_dat_t *p_conf){
uint32_t read_conf(char *file, prg_dat_t *p_conf){
	FILE *fd;
	char buff[BUFF_LEN];

	if(NULL == (fd = fopen(file, "r"))){
		printf("Error file open\n");
	}

	//Перебор строк файла с настройками и извлечение необходимой информации из них.
	int i = 0;
	while(NULL != fgets(buff, BUFF_LEN, fd)){
		i++;
		if(is_a_object(buff, &p_conf->object[p_conf->obj_count])){
			p_conf->obj_count++;
		}else{
//			printf("%s", buff);
			parse_string(buff, &p_conf->object[p_conf->obj_count]);
		}

	}
	fclose(fd);
	return 0;
}

uint32_t parse_string(char *string, sconf_t *pict){
	char *key_pos, *cursor;
	char key[64], argument[64];

	cursor = clear_string(string);
//	printf("%s", cursor);
	while(*cursor){
		if(*cursor == '='){
			key_pos = (++cursor);
		}
		if(*cursor == '#'){
			return 0;
		}
		cursor++;
	}
	memcpy(key, string, (key_pos - string - 1));
	key[key_pos - string - 1] = 0;
//	printf("%s\n", key);
	if(!strcmp(key, "image_1")){
		memcpy(argument, key_pos, cursor - key_pos);
		argument[cursor - key_pos] = 0;
		strcpy(pict->file_name_1, argument);
		printf("%s", argument);
	}

	if(!strcmp(key, "image_2")){
		memcpy(argument, key_pos, cursor - key_pos);
		argument[cursor - key_pos] = 0;
		printf("%s", argument);
	}

	if(!strcmp(key, "xcoord")){
		pict->xcoord = atoi(key_pos);
		printf("%d\n", pict->xcoord);
	}

	if(!strcmp(key, "ycoord")){
		pict->ycoord = atoi(key_pos);
		printf("%d\n", pict->ycoord);
	}

	return 0;
}



/*------------Готово работает------------*/
//Определение начала объектов в конфигурационном файле.

uint32_t is_a_object(char *string, sconf_t *pict){
	char *open_brace = 0, *close_brace = 0, *cursor = string;

	while(*cursor != (0 | '\n')){
		if(*cursor == '['){
			open_brace = cursor;
		}
		if(*cursor == ']'){
			close_brace = cursor;
		}
		cursor++;
	}

	if((open_brace && close_brace) == 0){
		return 0;
	}

	if(open_brace < close_brace){
		memcpy(pict->obj_name, open_brace + 1, close_brace - string - 1);
		return close_brace - string - 1;
	}

	return 0;
}

/*------------Готово работает------------*/
//Чистит строку от пробелов и кавычек.
char *clear_string(char *in_string){
	char *in_ptr, *b_ptr;
	char buffer[200];
	int char_cntr = 0;

	in_ptr = in_string;
	b_ptr = buffer;
	while(*in_ptr){
		if((*in_ptr != ' ') && (*in_ptr != '"')){
			*b_ptr = *in_ptr;
			b_ptr++;
			in_ptr++;
			char_cntr++;
		}else{
			in_ptr++;
			}
	}
	*(b_ptr++) = 0;
	memcpy(in_string, buffer, ++char_cntr);
	return in_string;
}

