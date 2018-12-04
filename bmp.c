#include <stdio.h>
#include <stdlib.h>
#include "bmp.h"



int main(int argc, char **argv){
	bmp_struct_t *bmp;
	bmp = (bmp_struct_t *)malloc(sizeof(bmp_struct_t));

	read_pict(argv[1], bmp);

	while(1);;

	free(bmp);
	return 0;
}

//read picture to memory
uint32_t read_pict(uint8_t *file, bmp_struct_t *bmp){
	FILE *fd;
	uint32_t pixels_pointer;

	fd = fopen(file, "r");
	if(fd == NULL){
		printf("Error with file!\n");
	}

	bmp->bpp = get_int_from_file(&fd, OFFSET_BITCOUNT, 4);
	bmp->width = get_int_from_file(&fd, OFFSET_WIDTH, 4);
	bmp->height = get_int_from_file(&fd, OFFSET_HEIGHT, 4);
	bmp->bytes_field_size = get_int_from_file(&fd, OFFSET_SIZE, 4) - get_int_from_file(&fd, OFFSET_PIXEL_DATA, 4);;
	pixels_pointer = get_int_from_file(&fd, OFFSET_PIXEL_DATA, 4);

	bmp->byte_field = (uint8_t *)malloc(bmp->bytes_field_size);

	//Копируем битовое поле в память.
	fseek(fd, pixels_pointer, OFFSET_PIXEL_DATA);

	printf("fread read: %d bytes\n", fread(bmp->byte_field, 1, bmp->bytes_field_size, fd));


	printf("%dx%d, %d bpp; pixel info size: %d, \t%d\n", bmp->width, bmp->height, bmp->bpp, bmp->bytes_field_size, pixels_pointer);

	fclose(fd);

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
