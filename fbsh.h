#include "debug.h"
//#define DEBUG


enum{
	WRONG_RESOLUTION_OF_THE_PICTURE = 1,
};


typedef struct{
	uint32_t xres;
	uint32_t yres;
	uint32_t screen_bpp;
	uint8_t *fbp;
}screen_t;


screen_t *init_screen(char *device);
//int send_to(screen_t *scr, bm);
//int set_color(uint32_t color, uint32_t shape, uint32_t xcoord, uint32_t ycoord, uint8_t *fbp);
