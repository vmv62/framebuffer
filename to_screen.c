
/*
To test that the Linux framebuffer is set up correctly, and that the device permissions
are correct, use the program below which opens the frame buffer and draws a gradient-
filled red square:

retrieved from:
Testing the Linux Framebuffer for Qtopia Core (qt4-x11-4.2.2)

http://cep.xor.aps.anl.gov/software/qt4-x11-4.2.2/qtopiacore-testingframebuffer.html
*/

#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <linux/fb.h>
#include <sys/mman.h>
#include <sys/ioctl.h>
#include "bmp.h"

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
    printf("The framebuffer device was opened successfully.\n");

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

    printf("%dx%d, %dbpp\n", vinfo.xres, vinfo.yres, vinfo.bits_per_pixel);

    // Figure out the size of the screen in bytes
    screensize = vinfo.xres * vinfo.yres * vinfo.bits_per_pixel / 8;

    // Map the device to memory
    fbp = (char *)mmap(0, screensize, PROT_READ | PROT_WRITE, MAP_SHARED, fbfd, 0);
    if ((int)fbp == -1) {
        perror("Error: failed to map framebuffer device to memory");
        exit(4);
    }
    printf("The framebuffer device was mapped to memory successfully.\n");

	img_data_t *img;
	img = (img_data_t *)malloc(sizeof(img_data_t));

	get_pic_param("1.bmp", img);

	printf("Wigth: %d, Height: %d, BPP: %d\n", img->width, img->height, img->bit_pp);

	FILE *fd;

	fd = fopen("1.bmp", "r");

	fseek(fd , img->pixel_offset, SEEK_SET);

	int xn=1024, yn=768;
	int cur = xn * yn * 4;
	while(yn--){
		for(int i = 0; i < xn; i++){
			*(fbp) = fgetc(fd);
			*(fbp) = fgetc(fd);
			*(fbp) = fgetc(fd);
			*(fbp) = 0;
		}
		
	}

/*
	uint32_t *cursor = (vinfo.xres * (vinfo.yres - 1)) * 4; //	bytes
	for(uint32_t i = 0; i < vinfo.yres ; i++){		//pixel
		for(uint32_t t = 0; t < vinfo.xres; t++){
			*(cursor) = fgetc(fd);
			*(cursor + 1) = fgetc(fd);
			*(cursor + 2) = fgetc(fd);
			*(cursor + 3) = 0;
			cursor +=4;
		}
		cursor -= vinfo.xres * 4;		//bytes
	}
*/

   	munmap(fbp, screensize);
	fclose(fd);
   	close(fbfd);
   	return 0;
}
