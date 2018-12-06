#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <linux/fb.h>
#include <sys/mman.h>
#include <sys/ioctl.h>
#include "bmp.h"
#include "fbsh.h"

int main()
{
    int fbfd = 0;
    struct fb_var_screeninfo vinfo;
    struct fb_fix_screeninfo finfo;
    long int screensize = 0;
    char *fbp = 0;
//    int x = 0, y = 0;
//    long int location = 0;

    // Open the file for reading and writing
    fbfd = open("/dev/fb0", O_RDWR);
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
    fbp = (char *)mmap(0, screensize, PROT_READ | PROT_WRITE, MAP_SHARED, fbfd, 0);
    if ((int)fbp == -1) {
        perror("Error: failed to map framebuffer device to memory");
        exit(4);
    }

	bmp_struct_t *bmp_1;
	bmp_1 = (bmp_struct_t *)malloc(sizeof(bmp_struct_t));
	read_pict("pict/plug.bmp", bmp_1);

	bmp_struct_t *bmp_2;
	bmp_2 = (bmp_struct_t *)malloc(sizeof(bmp_struct_t));
	read_pict("pict/460x460.bmp", bmp_2);

	while(1){
		send_to(900, 200, bmp_1, &vinfo, fbp);
		sleep(2);
		send_to(900, 700, bmp_2, &vinfo, fbp);
		sleep(2);
	}

	free(bmp_1);
	free(bmp_2);
   munmap(fbp, screensize);
	close(fbfd);
   return 0;
}

int send_to(uint32_t xcoord, uint32_t ycoord, bmp_struct_t *bmp, struct fb_var_screeninfo *vinfo, uint8_t *fbp){

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
