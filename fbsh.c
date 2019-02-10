#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <stdint.h>
#include <fcntl.h>
#include <string.h>
#include <linux/fb.h>
#include <sys/mman.h>
#include <sys/ioctl.h>
#include "fbsh.h"

screen_t *init_screen(char *device){
	int fbfd = 0;
	struct fb_var_screeninfo vinfo;
	struct fb_fix_screeninfo finfo;
	long int screensize = 0;
	uint8_t *fbp = 0;
	screen_t *scr;

	scr = (screen_t *)malloc(sizeof(screen_t));

    // Open the file for reading and writing
	fbfd = open(device, O_RDWR);
	if (fbfd == -1) {
		perror("Error: cannot open framebuffer device");
		exit(1);
	}

	// Get fixed screen information
	if (ioctl(fbfd, FBIOGET_FSCREENINFO, &finfo) == -1) {
		perror("Error reading fixed information");
		exit(2);
	}

	// Get variable screen information
	if (ioctl(fbfd, FBIOGET_VSCREENINFO, &vinfo) == -1) {
		perror("Error reading variable information");
		exit(3);
	}

    // Figure out the size of the screen in bytes
	screensize = vinfo.xres * vinfo.yres * vinfo.bits_per_pixel / 8;

    // Map the device to memory
	fbp = (uint8_t *)mmap(0, screensize, PROT_READ | PROT_WRITE, MAP_SHARED, fbfd, 0);
	if ((int)fbp == -1) {
		perror("Error: failed to map framebuffer device to memory");
		exit(4);
	}

	//Заполняем структуру экрана.
	scr->xres = vinfo.xres;
	scr->yres = vinfo.yres;
	scr->screen_bpp = vinfo.bits_per_pixel;
	scr->fbp = fbp;

   return scr;
}


int show_object(screen_t *scr, bmp_struct_t *bmp){

	//Находим положение последней строки файла в рамках экрана.
	uint8_t *cursor = fbp + (4 * xcoord) + ((ycoord + bmp->height) * (vinfo->xres * 4));	//В байтах
	uint8_t *byte_field_cur = bmp->byte_field;
	uint8_t *line_cursor;

	for(uint32_t i = 0; i < bmp->height; i++){		//pixel
		line_cursor = cursor;
		for(uint32_t t = 0; t < bmp->width * 4; t++){
			*line_cursor = *byte_field_cur;
			byte_field_cur++;
			line_cursor++;
		}
		cursor -= (vinfo->xres ) * 4;					//bytesi
	}

  	return 0;
}

/*
int show_object(screen_t *scr, bmp_struct_t *bmp){

	//Находим положение последней строки файла в рамках экрана.
	uint8_t *cursor = fbp + (4 * xcoord) + ((ycoord + bmp->height) * (vinfo->xres * 4));	//В байтах
	uint8_t *byte_field_cur = bmp->byte_field;
	uint8_t *line_cursor;

	for(uint32_t i = 0; i < bmp->height; i++){		//pixel
		line_cursor = cursor;
		for(uint32_t t = 0; t < bmp->width * 4; t++){
			*line_cursor = *byte_field_cur;
			byte_field_cur++;
			line_cursor++;
		}
		cursor -= (vinfo->xres ) * 4;					//bytesi
	}

  	return 0;
}

*/

/*
int set_color(uint32_t color, bmp_struct_t *bmp, uint32_t xcoord, uint32_t y_coord, uint8_t *fbp){


}
*/
