#include <stdio.h>
#include <stdlib.h>
#include "bmp.h"



uint32_t main(uint32_t argc, uint8_t **argv){
	//Указатель на тип данных картинки
//	img_data_t *img;

	//Выделяем память под информацию о картинке
//	img = (img_data_t *)malloc(sizeof(img_data_t));
	FILE *fd;
	fopen("pict/plug.bmp", "r");

	printf("Width: %d\n", get_int_value(fd, OFFSET_SIZE, 4));
//	printf("Height: %d\n", img->height);
//  	printf("Bit per pixel: %d\n", img->bit_pp);
//	printf("Bit field offset: %d\n", img->pixel_offset);

	fclose(fd);
	return 0;
}


uint32_t get_int_value(FILE *fd, uint32_t offset, uint32_t size){
	uint8_t buff[4];

	fseek(fd, offset, SEEK_SET);
	if(NULL == fgets(buff, size, fd)){
		printf("Error reading data from file\n");
	}

	uint32_t ret_val;
	for(uint32_t i = 0; i < size; i++){
		ret_val += buff[i] << (i * 8);
	}

//	return buff[0] + (buff[1]<<8) + (buff[2]<<16) + (buff[3]<<24);
	return ret_val;
}
