#include <stdio.h>
#include <stdlib.h>
#include "bmp.h"

uint32_t main(uint32_t argc, uint8_t **argv){
	//Указатель на тип данных картинки
	img_data_t *img;

	//Выделяем память под информацию о картинке
	img = (img_data_t *)malloc(sizeof(img_data_t));

	get_pic_param("1.bmp", img);
	printf("Width: %d\n", img->width);
	printf("Height: %d\n", img->height);

	free(img);
	return 0;
}

int get_pic_param(uint8_t *file, img_data_t *img){
	FILE *fd;
	uint8_t buff[4];

	fd = fopen(file, "r");
	if(fd == NULL){
		printf("Cant open file\n");
	}

	//Проверяем является ли файл БМП файлом.

	if(!((fgetc(fd) == 'B') && (fgetc(fd) == 'M'))){
		return FILE_NOT_BMP_FORMAT;
	}

	//Идем за шириной картинки
	fseek(fd, OFFSET_WIDTH, SEEK_SET);

	if(NULL == fgets(buff, 4, fd)){
		printf("errorw while reading file\n");
	}
	else{
		img->width = get_int_value(buff);
	}

	//Идем за высотой картинки.
	fseek(fd, OFFSET_HEIGHT, SEEK_SET);

	if(NULL == fgets(buff, 4, fd)){
		printf("errorw while reading file\n");
	}
	else{
		img->height = get_int_value(buff);
	}



	fclose(fd);
	return 1;
}

int get_int_value(uint8_t *buff){
	return buff[3] + (buff[2]<<8) + (buff[1]<<16) + (buff[0]<<24);
}
