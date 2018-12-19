#include <stdio.h>
#include <stdlib.h>
#include "get_conf.h"
#include "bmp.h"

int main(int argc, char **argv){
	sconf_t *conf;

	conf = (sconf_t *)malloc(sizeof(sconf_t));
	read_conf(argv[1], conf);
	return 0;
}

uint32_t read_conf(char *file, sconf_t *conf){
	FILE *fd;
	char buff[BUFF_LEN];

	if(NULL == (fd = fopen(file, "r"))){
		printf("Error file open\n");
	}

	//Перебор строк файла с настройками и извлечение необходимой информации из нихщ

	int i = 0;
	while(NULL != fgets(buff, BUFF_LEN, fd)){
		i++;
		parse_string(buff, files[i]);
	}

	fclose(fd);
	return 0;
}

uint32_t parse_string(char *string, sconf_t pict){

	printf("%s\n", string);
	return 0;
}
