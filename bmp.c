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
		uint32_t bfs;
		uint32_t bfo;
		uint8_t *bfp;
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
	obj->yres = (uint32_t)get_from_pict(fd, BMP_YRES);
	obj->bfs = (uint32_t)get_from_pict(fd, BMP_BFS);
	obj->bfo = (uint32_t)get_from_pict(fd, BMP_BFO);
	obj->bfp = (uint8_t *)get_from_pict(fd, BMP_BF);

	printf("BPP = %d \nXRES = %d \nYRES = %d \nBFSIZE = %d \nBFOFFSET = %d\n", obj->bpp, obj->xres, obj->yres, obj->bfs, obj->bfo);

	fclose(fd);

	return 0;
}

/*
screen_object_t load_objects(){

}
*/

//read picture to memory
uint32_t get_from_pict(FILE *file, uint32_t cmd){
	uint32_t bfs;
	uint8_t *bfp;

	switch(cmd){
		case BMP_BPP: 		return (get_int_from_file(&file, OFFSET_BITCOUNT, 1));
		case BMP_XRES: 	return (get_int_from_file(&file, OFFSET_WIDTH, 4));
		case BMP_YRES: 	return (get_int_from_file(&file, OFFSET_HEIGHT, 4));
		case BMP_BFS: 		return (get_int_from_file(&file, OFFSET_SIZE, 4) - get_int_from_file(&file, OFFSET_PIXEL_DATA, 4));
		case BMP_BFO: 		return (get_int_from_file(&file, OFFSET_PIXEL_DATA, 4));
		case BMP_BF:		bfs = get_int_from_file(&file, OFFSET_SIZE, 4) - get_int_from_file(&file, OFFSET_PIXEL_DATA, 4);
								bfp = (uint8_t *)malloc(bfs);
								fseek(file, get_int_from_file(&file, OFFSET_PIXEL_DATA, 4), SEEK_SET);
								fread(bfp, 1, bfs, file);
								return *bfp;
	}
/*
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
