#include <stdio.h>
#include "get_conf.h"
#include "bmp.h"

uint32_t main(uint32_t argc, uint8_t **argv){
	sconf_t *conf;

	read_conf(argv[1], conf);
	return 0;
}

uint32_t read_conf(uint8_t *file, sconf_t *conf){
	FILE *fd;
	buff[BUFF_LEN];

	if(NULL == (fd = fopen(file, "r"))){
		printf("Error file open");
	}

	fgets(buff, BUFF_LEN, fd);
	printf("%s\n", buff);

	close(fd);
	return 0;
}
