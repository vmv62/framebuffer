#include "debug.h"
#include "bmp.h"
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

typedef struct{
	bmp_stuct_t *on_bmp
	bmp_struct_t *off_bmp;
	uint32_t xcoord;
	uint32_t ycoord;
	uint8_t state;
}screen_object_t;

screen_t *init_screen(char *device);
//int chow_object(screen_t *scr, bmp_struct_t *bmp);
//int set_color(uint32_t color, uint32_t shape, uint32_t xcoord, uint32_t ycoord, uint8_t *fbp);
