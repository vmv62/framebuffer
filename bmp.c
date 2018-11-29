#include <stdio.h>
#include <stdlib.h>
#include "bmp.h"



int main(int argc, char **argv){
	bmp_struct_t *bmp;
	bmp = (bmp_struct_t *)malloc(sizeof(bmp_struct_t));

	read_pict("./pict/plug.bmp", bmp);
	return 0;
}

//read picture to memory
uint32_t read_pict(uint8_t *file, bmp_struct_t *bmp){
	FILE *fd;

	fd = fopen(file, "r");
	if(fd == NULL){
		printf("Error with file!\n");
	}

	bmp->bpp = get_int_from_file(&fd, OFFSET_BITCOUNT, 4);
	bmp->width = get_int_from_file(&fd, OFFSET_WIDTH, 4);
	bmp->height = get_int_from_file(&fd, OFFSET_HEIGHT, 4);
	bmp->bytes_field_size = get_int_from_file(&fd, OFFSET_SIZE, 4) - get_int_from_file(&fd, OFFSET_PIXEL_DATA, 4);;

	byte_field = (uint8_t *)malloc(bmp->bytes_field_size);
	

	printf("%dx%d, %d bpp; pixel info size: %d\n", bmp->width, bmp->height, bmp->bpp, bmp->bytes_field_size);

	fclose(fd);

	return 0;
}

uint32_t get_int_from_file(FILE **fd, uint32_t offset, uint32_t size){
	char buff[4];

	fseek(*fd, offset, SEEK_SET);
	if(NULL == fgets(buff, size, *fd)){
		printf("Error reading data from file\n");
	}
/*
	uint32_t ret_val;
	uint8_t shift = 0;
	for(uint32_t i = 0; i < size; i++){
		ret_val += (buff[i] << shift);
		shift = i * 8;
	}
*/
	return buff[0] + (buff[1]<<8) + (buff[2]<<16) + (buff[3]<<24);
//	return ret_val;
}
