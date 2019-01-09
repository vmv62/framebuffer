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
//	read_conf(argv[1], p_conf);
	read_conf("monitor.conf", p_conf);

//	printf("Object count == %d\n", p_conf->obj_count);
//	printf("Info about object 1: Name: %s\n", p_conf->object[0]->file_name_1);

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

//	printf("Read_conf before while\n");
	//Перебор строк файла с настройками и извлечение необходимой информации из них.
	while(NULL != fgets(buff, BUFF_LEN, fd)){
		if(is_a_object(buff, p_conf)){
			p_conf->obj_count++;
			printf("Increment obj count\n");
		} else{
			printf("Before string parse\n");
			parse_string(buff, p_conf);
			printf("Obj_cntr %d\n", p_conf->obj_count);
		}

	}
	fclose(fd);
	return 0;
}

uint32_t parse_string(char *string, prg_dat_t *pict){
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
//		printf("%d\n", pict->obj_count);
		strcpy(&pict->object[pict->obj_count]->file_name_1, argument);
		printf("%s", argument);
	}

	if(!strcmp(key, "image_2")){
		memcpy(argument, key_pos, cursor - key_pos);
		argument[cursor - key_pos] = 0;
		printf("%s", argument);
	}

	if(!strcmp(key, "xcoord")){
		pict->object[pict->obj_count]->xcoord = atoi(key_pos);
		printf("%d\n", pict->object[pict->obj_count]->xcoord);
	}

	if(!strcmp(key, "ycoord")){
		pict->object[pict->obj_count]->ycoord = atoi(key_pos);
		printf("%d\n", pict->object[pict->obj_count]->ycoord);
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
		pict->object[pict->obj_count] = (sconf_t *)malloc(sizeof(sconf_t));
		memcpy(pict->object, open_brace + 1, close_brace - string - 1);
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

