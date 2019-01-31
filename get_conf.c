#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "get_conf.h"

/*
int main(int argc, char **argv){
//	sconf_t *conf;
	prg_dat_t *p_conf;

//	p_conf = (prg_dat_t *)malloc(sizeof(prg_dat_t));
	p_conf = read_conf("monitor.conf");

#ifdef OUTPUTS
	outs(p_conf->object[0]->obj_name);
//	outs(p_conf->object[0]->file_name_1);
//	outs(p_conf->object[0]->file_name_2);
	outd(p_conf->object[0]->xcoord);
	outd(p_conf->object[0]->ycoord);

	outs(p_conf->object[1]->obj_name);
//	outs(p_conf->object[1]->file_name_1);
//	outs(p_conf->object[1]->file_name_2);
	outd(p_conf->object[1]->xcoord);
	outd(p_conf->object[1]->ycoord);

	outs(p_conf->object[2]->obj_name);
//	outs(p_conf->object[2]->file_name_1);
//	outs(p_conf->object[2]->file_name_2);
	outd(p_conf->object[2]->xcoord);
	outd(p_conf->object[2]->ycoord);
#endif

	for(int i = 0; i < p_conf->obj_count; i++){
		free(p_conf->object[i]);
	}
	free(p_conf);
	return 0;
}
*/


prg_dat_t *read_conf(char *file){
	FILE *fd;
	char buff[BUFF_LEN];
	prg_dat_t *p_conf;

	p_conf = (prg_dat_t *)malloc(sizeof(prg_dat_t));

	if(NULL == (fd = fopen(file, "r"))){
		printf("Error file open\n");
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

		if((p_conf->object[p_conf->obj_count] = is_a_object(buff))){
			p_conf->obj_count++;
			p_conf->object[p_conf->obj_count - 1]->params = 0;
		}else{
			parse_string(buff, p_conf->object[p_conf->obj_count - 1]);
		}

	}
	fclose(fd);
	return p_conf;
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

	memcpy(key, string, (key_pos - string));
	key[key_pos - string] = 0;
	strcpy(argument, key_pos+1);

#ifdef DEBUG_GET_CONF
	outs(key);
	outs(argument);
#endif


	if(!strcmp(key, "image_1")){
		strcpy(pict->file_name_1, argument);
		pict->params |= IMAGE_1;
	}

	if(!strcmp(key, "image_2")){
		strcpy(pict->file_name_2, argument);
		pict->params |= IMAGE_2;
	}

	if(!strcmp(key, "xcoord")){
		pict->xcoord = atoi(argument);
		pict->params |= XCOORD;
	}

	if(!strcmp(key, "ycoord")){
		pict->ycoord = atoi(argument);
		pict->params |= YCOORD;
	}

	return 0;
}



/*------------Готово работает------------*/
//Определение начала объектов в конфигурационном файле и выделение память под данный объект.

oconf_t *is_a_object(char *string){
	char *open_brace = 0, *close_brace = 0, *cursor = string;
	oconf_t *object;
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
/*
#ifdef DEBUG_STEPS
		outs("Find object!\n");
#endif
*/
		object = (oconf_t *)malloc(sizeof(oconf_t));
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

