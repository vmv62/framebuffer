#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <linux/fb.h>
#include <sys/mman.h>
#include <sys/ioctl.h>
#include "bmp.h"
#include "to_screen.h"

int main()
{
    int fbfd = 0;
    struct fb_var_screeninfo vinfo;
    struct fb_fix_screeninfo finfo;
    long int screensize = 0;
    char *fbp = 0;
    int x = 0, y = 0;
    long int location = 0;

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

	printf("Show gauge\n");
	send_to(100, 200, "Gauge.bmp", &vinfo, fbp);

   munmap(fbp, screensize);
	close(fbfd);
   return 0;
}

int send_to(uint32_t xcoord, uint32_t ycoord, uint8_t *file, struct fb_var_screeninfo *vinfo, uint8_t *fbp){
	FILE *fd;

	fd = fopen(file, "r");
	if (fd == NULL) {
        perror("Error: cannot open image file");
        exit(1);
    }


	img_data_t *img;
	img = (img_data_t *)malloc(sizeof(img_data_t));

	get_pic_param(fd, img);

	printf("height - %d\n", img->height);
	printf("width - %d\n", img->width);

	//Go to pixel field.
	fseek(fd , img->pixel_offset, SEEK_SET);

	//Находим положение последней строки файла в рамках экрана.
	uint8_t *cursor = fbp + (4 * xcoord) + ((ycoord + img->height) * vinfo->xres * 4);	//В байтах
	uint8_t *line_cursor;
	for(uint32_t i = 0; i < img->height ; i++){		//pixel
		line_cursor = cursor;
		for(uint32_t t = 0; t < img->width ; t++){
			*(line_cursor) = fgetc(fd);
			*(line_cursor + 1) = fgetc(fd);
			*(line_cursor + 2) = fgetc(fd);
			*(line_cursor + 3) = fgetc(fd);
			line_cursor +=4;
		}
		cursor -= vinfo->xres * 4;							//bytesi
	}

	free(img);
	fclose(fd);
  	return 0;
}
