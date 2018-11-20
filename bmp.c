#include <stdio.h>
#include <stdlib.h>
#include "bmp.h"

/*
uint32_t main(uint32_t argc, uint8_t **argv){
	//Указатель на тип данных картинки
	img_data_t *img;

	//Выделяем память под информацию о картинке
	img = (img_data_t *)malloc(sizeof(img_data_t));

	get_pic_param("1.bmp", img);
	printf("Width: %d\n", img->width);
	printf("Height: %d\n", img->height);
   	printf("Bit per pixel: %d\n", img->bit_pp);
	printf("Bit field offset: %d\n", img->pixel_offset);

	free(img);
	return 0;
}
*/

int get_pic_param(FILE *fd, img_data_t *img){
//	FILE *fd;
	uint8_t buff[4];
/*
	fd = fopen(file, "r");
	if(fd == NULL){
		return CANT_OPEN_FILE;
	}
*/
	//Проверяем является ли файл БМП файлом.
	if(!((fgetc(fd) == 'B') && (fgetc(fd) == 'M'))){
		return FILE_NOT_BMP_FORMAT;
	}

	//Идем за шириной картинки
	fseek(fd, OFFSET_WIDTH, SEEK_SET);
	if(NULL == fgets(buff, 4, fd)){
		return ERROR_WHILE_READ_FILE;
	}
	else{
		img->width = get_int_value(buff);
	}

	//Идем за высотой картинки.
	fseek(fd, OFFSET_HEIGHT, SEEK_SET);
	if(NULL == fgets(buff, 4, fd)){
		return ERROR_WHILE_READ_FILE;
	}
	else{
		img->height = get_int_value(buff);
	}

	//Читем сколько бит на каждый пиксель приходится.
	fseek(fd, OFFSET_BITCOUNT, SEEK_SET);
	if(NULL == fgets(buff, 2, fd)){
		return ERROR_WHILE_READ_FILE;
	}
	else{
		img->bit_pp = buff[0] + (buff[1]<<8);
	}

	//Находим смещение данных по поикселя от начала файла
	fseek(fd, OFFSET_PIXEL_DATA, SEEK_SET);
	if(NULL == fgets(buff, 4, fd)){
		return ERROR_WHILE_READ_FILE;
	}
	else{
		img->pixel_offset = buff[0];//get_int_value(buff);
	}

	return 0;
}

int get_int_value(uint8_t *buff){
	return buff[0] + (buff[1]<<8) + (buff[2]<<16) + (buff[3]<<24);
}
