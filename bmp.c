#include <stdio.h>
#include "bmp.h"

uint32_t main(uint32_t argc, uint8_t **argv){
	FILE *fd;
	bmp_header_t *bmp;

	

	fd = fopen("1.bmp", "r");
	if(fd == NULL){
		printf("Cant open file\n");
	}

	fseek(fd, 18, SEEK_SET);

	uint8_t buff[4];
	buff[0] = getc(fd);

	uint32_t width;
	width = (buff[3]<< 24) + (buff[2] << 16) + (buff[1] << 8) + buff[0];
	printf("Width: %d\n", buff[0]);

	fclose(fd);
}

