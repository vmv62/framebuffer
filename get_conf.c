#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "get_conf.h"
#include "bmp.h"

int main(int argc, char **argv){
	sconf_t *conf;
	prg_dat_t *p_conf;

	conf = (sconf_t *)malloc(sizeof(sconf_t));
	p_conf = (prg_dat_t *)malloc(sizeof(prg_dat_t));
	read_conf(argv[1], conf, p_conf);

	printf("Object count == %d\n", p_conf->obj_count);

	free(conf);
	free(p_conf);
	return 0;
}

uint32_t read_conf(char *file, sconf_t *conf, prg_dat_t *p_conf){
	FILE *fd;
	char buff[BUFF_LEN];

	if(NULL == (fd = fopen(file, "r"))){
		printf("Error file open\n");
	}

	//Перебор строк файла с настройками и извлечение необходимой информации из нихщ

	int i = 0;
	while(NULL != fgets(buff, BUFF_LEN, fd)){
		i++;
		if(is_a_object(buff, conf)){
			p_conf->obj_count++;
		}else{
			parse_string(buff, conf);
		}

	}
	printf("obj_name - %s\n", conf->obj_name);
	fclose(fd);
	return 0;
}

uint32_t parse_string(char *string, sconf_t *pict){
	char *key_pos = string, *cursor;
	char key[64], argument[64];
	while(*key_pos){
		if(*key_pos == '='){
//			key_pos = string;
			break;
		}
		key_pos++;
	}
	printf("%d", string - key_pos - 1);
	memcpy(key, string, string - key_pos - 1);
//	memcpy(argument, key_pos, strlen(string) - (key_pos - string));

	printf("Key: %s\n", key);
//	printf("Argument: %s\n", argument);
	return 0;
}


//Счетчик объектов в конфигурационном файле.
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

	if(open_brace < close_brace){
		memcpy(pict->obj_name, open_brace + 1, close_brace - string - 1);
		return close_brace - string - 1;
	}

	return 0;
}
/*
char *clear_string(char *in_string){
	int str_len;
	str_len = strlen(string);
	char tmp_str[str_len];


}
*/
