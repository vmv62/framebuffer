#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "bmp.h"


int main(int argc, char **argv){
	FILE *fd;

	typedef struct{
		uint8_t bpp;
		uint32_t xres;
		uint32_t yres;
	}pict_t;

	pict_t *obj;

	obj = (pict_t *)malloc(sizeof(pict_t));

	fd = fopen(argv[1], "r");
	if(fd == NULL){
		printf("Error open file!\n");
		exit(0);
	}

	obj->bpp = (uint8_t)get_from_pict(fd, BMP_BPP);
	obj->xres = (uint32_t)get_from_pict(fd, BMP_XRES);

	printf("BPP = %d \nXRES = %d\n", obj->bpp, obj->xres);

	fclose(fd);

	return 0;
}

/*
screen_object_t load_objects(){

}
*/

//read picture to memory
uint32_t get_from_pict(FILE *file, uint32_t cmd){

	switch(cmd){
		case BMP_BPP: 		return (get_int_from_file(&file, OFFSET_BITCOUNT, 4));
		case BMP_XRES: 	return (get_int_from_file(&file, OFFSET_WIDTH, 4));
	}
/*
	bmp->bpp = get_int_from_file(&fd, OFFSET_BITCOUNT, 4);
	bmp->width = get_int_from_file(&fd, OFFSET_WIDTH, 4);
	bmp->height = get_int_from_file(&fd, OFFSET_HEIGHT, 4);
	bmp->bytes_field_size = get_int_from_file(&fd, OFFSET_SIZE, 4) - get_int_from_file(&fd, OFFSET_PIXEL_DATA, 4);
	pixels_pointer = get_int_from_file(&fd, OFFSET_PIXEL_DATA, 4);

	bmp->byte_field = (uint8_t *)malloc(bmp->bytes_field_size);

#ifdef DEBUG_BMP
   printf("Start coping bitdield\n");
#endif


	if(bmp->bpp == 32){
		//Копируем битовое поле в память.
		fseek(fd, pixels_pointer, SEEK_SET);
		fread(bmp->byte_field, 1, bmp->bytes_field_size, fd);
	}

#ifdef DEBUG_BMP
   printf("Stop coping bitdield\n");
#endif


	fclose(fd);
*/
	return 0;
}

//Полностью рабочая функция.
uint32_t get_int_from_file(FILE **fd, uint32_t offset, uint32_t size){
	uint32_t ret_val;

	fseek(*fd, offset, SEEK_SET);

	uint32_t result_of_read = fread(&ret_val, 1, size, *fd);
	if(result_of_read == 0){
		printf("Cant read from file");
		return 0;
	}

	return ret_val;
}
