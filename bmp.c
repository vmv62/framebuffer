#include <stdio.h>
#include <stdlib.h>
#include "bmp.h"


int main(int argc, char **argv){
	FILE *fd;
//	bmp_struct_t *bmp;
//	bmp = (bmp_struct_t *)malloc(sizeof(bmp_struct_t));
//	int xres;

	fd = fopen("pict/debian.bmp", "r");
	if(fd == -1){
		printf("File not open!\n");
	}

#ifdef DEBUG_BMP
	printf("fd in main: %d\n", (int)fd);
#endif

	printf("x res: %d\n", (int)get_from_pict(fd, GXRES));
	printf("y rres: %d\n", (int)get_from_pict(fd, GYRES));

	while(1);;

	fclose(fd);
//	free(bmp);
	return 0;
}

/*
screen_object_t load_objects(){

}
*/

//read picture to memory
int *get_from_pict(FILE *fd, int command){
//	uint32_t pixels_pointer;
//	bmp_struct_t *bmp;

#ifdef DEBUG_BMP
	printf("fd in get_from_pict: %d\n", (int)fd);
#endif
#ifdef DEBUG_BMP
	printf("get_from_pict start\n");
#endif

/*
	bmp = (bmp_struct_t *)malloc(sizeof(bmp_struct_t));
*/
	if(command == GXRES){
		int res = get_int_from_file(fd, OFFSET_WIDTH, 4);
		return (int *)res;
	}

	if(command == GYRES){
		int res = get_int_from_file(fd, OFFSET_HEIGHT, 4);
		return (int *)res;
	}

	if(command == GBPP){
		int res = get_int_from_file(fd, OFFSET_PIXEL_DATA, 4);
		return (int *)res;
	}
/*
	if(command == GBPP){
		int res = get_int_from_file(fd, OFFSET_PIXEL_DATA, 4);
		return (int *)res;
	}

*/


/*
	bmp->bytes_field_size = get_int_from_file(&fd, OFFSET_SIZE, 4) - get_int_from_file(&fd, OFFSET_PIXEL_DATA, 4);
	pixels_pointer = get_int_from_file(&fd, OFFSET_PIXEL_DATA, 4);

	bmp->byte_field = (uint8_t *)malloc(bmp->bytes_field_size);
*/
/*
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
uint32_t get_int_from_file(FILE *fd, uint32_t offset, uint32_t size){
	uint32_t ret_val;

#ifdef DEBUG_BMP
	printf("before fseec\n");
#endif

	fseek(fd, offset, SEEK_SET);

#ifdef DEBUG_BMP
	printf("get_int_from_file fseec\n");
#endif

	uint32_t result_of_read = fread(&ret_val, 1, size, fd);

#ifdef DEBUG_BMP
	printf("get_int_from_freed fseec\n");
#endif
	if(result_of_read == 0){
		printf("Cant read from file");
		return 0;
	}

	return ret_val;
}
