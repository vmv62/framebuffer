#include <stdio.h>
#include <stdlib.h>
#include "bmp.h"



int main(int argc, char **argv){
	FILE *fd;

	fd = fopen("./pict/Black.bmp", "r");
	if(fd == NULL){
		printf("Error with file!\n");
	}

	uint32_t width = get_int_from_file(fd, 0x02, 4);
	printf("Width: %d\n", width);

	fclose(fd);
	return 0;
}


uint32_t get_int_from_file(FILE *fd, uint32_t offset, uint32_t size){
	char buff[4];

	fseek(fd, offset, SEEK_SET);
	if(NULL == fgets(buff, size, fd)){
		printf("Error reading data from file\n");
	}

	uint32_t ret_val;
	for(uint32_t i = 0; i < size; i++){
		ret_val |= (buff[i] << (i * 8));
	}

	printf("%d\n", ret_val);
//	return buff[0] + (buff[1]<<8) + (buff[2]<<16) + (buff[3]<<24);
	return ret_val;
}
