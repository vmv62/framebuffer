#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "bmp.h"


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
								return (uint32_t)bfp;
	}

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
