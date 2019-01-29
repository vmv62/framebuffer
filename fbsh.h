#define DEBUG


enum{
	WRONG_RESOLUTION_OF_THE_PICTURE = 1,
};
/*
enum{
	
};
*/
int send_to(uint32_t  xcoord, uint32_t ycoord, bmp_struct_t *bmp, struct fb_var_screeninfo *vinfo, uint8_t *fbp);
//int set_color(uint32_t color, uint32_t shape, uint32_t xcoord, uint32_t ycoord, uint8_t *fbp);
