#include <stdio.h>
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

	while(NULL != fgets(buff, BUFF_LEN, fd)){
		printf("%s\n", buff);
	}

	fclose(fd);
	return 0;
}

uint32_t parse_string(uint8_t *string, uint8_t *var, uint8_t *val){


	return 0;
}
