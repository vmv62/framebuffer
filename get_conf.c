#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "get_conf.h"
#include "bmp.h"

int main(int argc, char **argv){
//	sconf_t *conf;
	prg_dat_t *p_conf;

	p_conf = (prg_dat_t *)malloc(sizeof(prg_dat_t));
	read_conf("monitor.conf", p_conf);

	printf("%s\n", p_conf->object[0]->obj_name);
	printf("%s\n", p_conf->object[1]->obj_name);
//	printf("%d\n", p_conf->object[1]->xcoord);

	for(int i = 0; i < p_conf->obj_count; i++){
		free(p_conf->object[i]);
	}
	free(p_conf);
	return 0;
}

//uint32_t read_conf(char *file, sconf_t *conf, prg_dat_t *p_conf){
uint32_t read_conf(char *file, prg_dat_t *p_conf){
	FILE *fd;
	char buff[BUFF_LEN];
	int obj_cnt = 0;

	if(NULL == (fd = fopen(file, "r"))){
		printf("Error file open\n");
	}

	//Перебор строк файла с настройками и извлечение необходимой информации из них.
	while(NULL != fgets(buff, BUFF_LEN, fd)){
		if(is_a_object(buff, p_conf)){
			p_conf->object[obj_cnt] = (oconf_t *)malloc(sizeof(oconf_t));
			obj_cnt++;
		}else{
			parse_string(buff, p_conf->object[obj_cnt - 1]);
		}

	}
	fclose(fd);
	return 0;
}

uint32_t parse_string(char *string, oconf_t *pict){
	char *key_pos, *cursor;
	char key[64], argument[64];

	cursor = clear_string(string);
	while(*cursor){
		if(*cursor == '='){
			key_pos = cursor;
		}
		if(*cursor == '#'){
			return 0;
		}
		cursor++;
	}

//	printf("%d\n", key_pos - string);
	memcpy(key, string, (key_pos - string));
	key[key_pos - string] = 0;
	strcpy(argument, key_pos+1);
	if(!strcmp(key, "image_1")){
		strcpy(pict->file_name_1, argument);
	}

	if(!strcmp(key, "image_2")){
		strcpy(pict->file_name_2, argument);
	}

	if(!strcmp(key, "xcoord")){
		pict->xcoord = atoi(argument);
	}

	if(!strcmp(key, "ycoord")){
		pict->ycoord = atoi(argument);
	}

	return 0;
}



/*------------Готово работает------------*/
//Определение начала объектов в конфигурационном файле и выделение память под данный объект.

uint32_t is_a_object(char *string, prg_dat_t *pict){
	char *open_brace = 0, *close_brace = 0, *cursor = string;

	while(*cursor != (0 || '\n')){
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

	//Если чередование квадратных скобок верное, считаем что это объект и выделяем для него место.
	if(open_brace < close_brace){
		//размещаем указатель в массив объектов.
		pict->object[pict->obj_count] = (oconf_t *)malloc(sizeof(oconf_t));
		memcpy(pict->object[pict->obj_count]->obj_name, open_brace + 1, close_brace - string - 1);
		pict->obj_count++;
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

