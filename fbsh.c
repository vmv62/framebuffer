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
//#include "bmp.c"

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
	if ((signed int)fbp == -1) {
		perror("Error: failed to map framebuffer device to memory");
		exit(4);
	}

	//Заполняем структуру экрана.
	scr->xres = vinfo.xres;
	scr->yres = vinfo.yres;
	scr->screen_bpp = vinfo.bits_per_pixel;
	scr->fbp = fbp;

#ifdef DEBUG_FBC
	printf("Display BPP: %d\n", vinfo.bits_per_pixel);
#endif

	memset(fbp, 0x00, screensize);
   return scr;
}


int show_object(screen_t *scr, uint8_t *byte_field, uint32_t height, uint32_t width, uint32_t x_coord, uint32_t y_coord){

	//Находим положение последней строки файла в рамках экрана.
	uint8_t *cursor = scr->fbp + (4 * x_coord) + ((y_coord + height) * (scr->xres * 4));	//В байтах
	uint8_t *byte_field_cur = byte_field;
	uint8_t *line_cursor;

	for(uint32_t i = 0; i < height; i++){		//pixel
		line_cursor = cursor;

#ifdef DEBUG_FBC
        printf("Line %d\n", i);
#endif

		for(uint32_t t = 0; t < width * 4; t++){
#ifdef DEBUG_FBC
        printf("Line of image %d\n", t);
#endif
			*line_cursor = *byte_field_cur;
			byte_field_cur++;
			line_cursor++;
		}
		cursor -= (scr->xres ) * 4;					//bytesi
	}

  	return 0;
}

uint32_t make_line(screen_t *scr, point_t start, point_t end){
	uint8_t *cursor;
	uint32_t x_coef, y_coef = 0;
	uint32_t x_pixel = 0, y_pixel = 0;

	x_coef = end.x / end.y;
	y_coef = end.y / end.x;

	x_pixel = end.x - start.x;
	y_pixel = end.y - start.y;

	printf("x_pixels: %d; y_pixels: %d; x_coef: %d; y_coef: %d\n", x_pixel, y_pixel, x_coef, y_coef);



//	if(x_pixel > y_pixel){
//		x_coef = x_pixel / y_pixel;
//	}

	

/*
	int count = 0;
	while((start.x != end.x) && (start.y != end.y)){
		cursor = scr->fbp + (scr->xres * start.y * 4) + (start.x * 4);  //set curcor to start point of the line
		memset(cursor, 0xFF, 4);
		count++;

		if(start.x < end.x){
			start.x ++;
		}else{
				start.x--;
			}


		if(start.y < end.y){
			start.y++;
		}else{
				start.y--;
			}

//		printf("%d:%d\n", start.x, start.y);
	}
*/

	return 0;
}
