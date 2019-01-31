#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <string.h>
#include <linux/fb.h>
#include <sys/mman.h>
#include <sys/ioctl.h>
#include "bmp.h"
#include "fbsh.h"
#include "get_conf.h"

int main()
{
	int fbfd = 0;
	struct fb_var_screeninfo vinfo;
	struct fb_fix_screeninfo finfo;
	long int screensize = 0;
	char *fbp = 0;
	prg_dat_t *p_conf;

	p_conf = read_conf("monitor.conf");
/*
	if(fork()){
		return 0;
	}
*/
#ifdef DEBUG_FBC
		printf("%s", p_conf->object[0]->file_name_1);
		printf("%s", p_conf->object[1]->file_name_1);
#endif


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

	memset(fbp, 0x0, screensize);


	bmp_struct_t *bmps[100];
	bmps[0] = read_pict(p_conf->object[0]->file_name_1);
	bmps[1] = read_pict(p_conf->object[0]->file_name_2);
	bmps[2] = read_pict(p_conf->object[1]->file_name_1);
	bmps[3] = read_pict(p_conf->object[1]->file_name_2);
//	for(uint32_t i = 0; i < p_conf->obj_count - 1; i++){
//		bmps[i] = read_pict(p_conf->object[i]->file_name_1);
//	}

/*
	bmp_1 = (bmp_struct_t *)malloc(sizeof(bmp_struct_t));
	read_pict("pict/Red_pilot_light_1.bmp", bmp_1);

	bmp_struct_t *bmp_2;
	bmp_2 = (bmp_struct_t *)malloc(sizeof(bmp_struct_t));
	read_pict("pict/Yellow_pilot_light_1.bmp", bmp_2);
//	memset(bmp_2->byte_field, 0x0, bmp_2->bytes_field_size);
*/
	while(1){
		send_to(p_conf->object[0]->xcoord, p_conf->object[0]->ycoord, bmps[0], &vinfo, fbp);
		send_to(p_conf->object[0]->xcoord, p_conf->object[0]->ycoord, bmps[2], &vinfo, fbp);
		sleep(1);
		send_to(p_conf->object[1]->xcoord, p_conf->object[1]->ycoord, bmps[1], &vinfo, fbp);
		send_to(p_conf->object[1]->xcoord, p_conf->object[1]->ycoord, bmps[3], &vinfo, fbp);
		sleep(1);
	}

	free(bmps[0]);
	free(bmps[1]);
	free(bmps[2]);
	free(bmps[3]);
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

/*
int set_color(uint32_t color, bmp_struct_t *bmp, uint32_t xcoord, uint32_t y_coord, uint8_t *fbp){


}
*/
