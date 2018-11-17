#include <stdio.h>
#include "bmp.h"

uint32_t main(uint32_t argc, uint8_t **argv){
	FILE *fd;
	bmp_header_t *bmp;

	fd = fopen("1.bmp", "r");
	if(fd == NULL){
		printf("Cant open file\n");
	}

	fseek(fd, OFSET_WIDTH, SEEK_SET);

	uint8_t buff[4];
	buff[0] = getc(fd);
	printf("Width: %d\n", buff[0]);

	fclose(fd);
}

