enum{
	WRONG_RESOLUTION_OF_THE_PICTURE = 1,
};


int send_to(uint32_t  xcoord, uint32_t ycoord, uint8_t *file, struct fb_var_screeninfo *vinfo, uint8_t *fbp);
