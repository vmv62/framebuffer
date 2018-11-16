#include <stdio.h>
#include "bmp.h"

uint32_t main(uint32_t argc, uint8_t **argv){
	FILE *fd;
	bmp_header_t *bmp;

	

	fd = fopen("1.bmp", "r");
	if(fd == NULL){
		printf("Cant open file\n");
	}

	fseek(fd, SEEK_SET, 18);

	uint8_t buff[4];
	for(uint8_t i=0; i < 4; i++){
		buff[i] = getc(fd);
	}

	uint32_t width = buff[3]<< 24 | buff[2]4F?buff[0]
	printf("Width: %d\n", );

	fclose(fd);
}

