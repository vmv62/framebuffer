/*
Описание файла.
	Функция prg_dat_t *read_conf(char *file) принимает строку с адресом конфигурационного файла.
	Читает строки, выбирает параметры объектов, и заполняет структуры этих объектов.
	Создает массив указателей на структуры объектов и счетчик этих объектов.
	Каждый объект может содержать до OBJECT_BITMAP_COUNT изображений

*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bmp.h"
#include "get_conf.h"


resurses_t *read_conf(char *file){
	FILE *fd;
	char buff[BUFF_LEN];
	resurses_t *res;

	res = (resurses_t *)malloc(sizeof(resurses_t));

	if(NULL == (fd = fopen(file, "r"))){
		printf("Error file open\n");
		exit(0);
	}
/*
#ifdef DEBUG_GET_CONF
		else{
			outs("File opened");
		}
#endif
*/

	//Перебор строк файла с настройками и извлечение необходимой информации из них.
	while(NULL != fgets(buff, BUFF_LEN, fd)){

/*
#ifdef DEBUG_GET_CONF
		outs("Read string!\n");
#endif
*/

		if((res->object[res->obj_count] = is_a_object(buff))){
			res->obj_count++;
			res->object[res->obj_count - 1]->params = 0;
		}else{
			parse_string(buff, res->object[res->obj_count - 1]);
		}
	}
	fclose(fd);
	return res;
}

uint32_t parse_string(char *string, object_t *obj){
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

	memcpy(key, string, (key_pos - string));
	key[key_pos - string] = 0;
	strcpy(argument, key_pos+1);

#ifdef DEBUG_GET_CONF
	outs(key);
	outs(argument);
#endif


	if(!strcmp(key, "on_bitmap")){
//		obj->bmp[1] = read_pict(argument);
		obj->params |= IMAGE_1;
	}

	if(!strcmp(key, "off_bitmap")){
//		obj->bmp[0] = read_pict(argument);
		obj->params |= IMAGE_2;
	}

	if(!strcmp(key, "xcoord")){
		obj->xcoord = atoi(argument);
		obj->params |= XCOORD;
	}

	if(!strcmp(key, "ycoord")){
		obj->ycoord = atoi(argument);
		obj->params |= YCOORD;
	}

	if(!strcmp(key, "register")){
		obj->reg = atoi(argument);
		obj->params |= YCOORD;
	}

	return 0;
}



/*------------Готово работает------------*/
//Определение начала объектов в конфигурационном файле и выделение память под данный объект.

object_t *is_a_object(char *string){
	char *open_brace = 0, *close_brace = 0, *cursor = string;
	object_t *object;
//	char bf[50];
/*
#ifdef DEBUG_GET_CONF
	outs("Before while in is_a_jbject!\n");
	outs(string);
#endif
*/
	while(*cursor != (0 || '\n')){
		if((*cursor) == '['){
			open_brace = cursor;
/*
#ifdef DEBUG_GET_CONF
	outs("Find [!\n");
#endif
*/
		}
		if(*cursor == ']'){
			close_brace = cursor;
/*
#ifdef DEBUG_GET_CONF
	outs("Find ]!\n");
#endif
*/
		}
		cursor++;
	}

	if((open_brace && close_brace) == 0){
		return 0;
	}

	//Если чередование квадратных скобок верное, считаем что это объект и выделяем для него место.
	if(open_brace < close_brace){
		//размещаем указатель в массив объектов.

#ifdef DEBUG_STEPS
		outs("Find object!\n");
#endif

		object = (object_t *)malloc(sizeof(object_t));
		memcpy(object->obj_name, open_brace + 1, close_brace - string - 1);
		object->obj_name[close_brace - string - 1] = 0;
		return object;
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
		if((*in_ptr != ' ') && (*in_ptr != '"') && (*in_ptr != '\n')){
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

