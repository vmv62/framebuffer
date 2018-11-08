#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <linux/fb.h>
#include <sys/mman.h>
#include <sys/ioctl.h>


int main(int argc, char* argv[])
{
  int fbfd = 0;
  struct fb_var_screeninfo vinfo;
  struct fb_fix_screeninfo finfo;
  long int screensize = 0;
  char *fbp = 0;

	//Open bitmap file 
	int bitmap = open("./1.bmp", O_RDWR);
	
	fseek(&bitmap, 0x0A, SEEK_SET);
	int shift;
	for(char i=0; i<4; i++){
		shift += getc(bitmap)<<(i*4);
	}

	printf("Bitmap shift: %d", shift);
  // Open the framebuffer file for reading and writing
  fbfd = open("/dev/fb0", O_RDWR);
  if (!fbfd) {
    printf("Error: cannot open framebuffer device.\n");
    return(1);
  }
  printf("The framebuffer device was opened successfully.\n");

  // Get fixed screen information
  if (ioctl(fbfd, FBIOGET_FSCREENINFO, &finfo)) {
    printf("Error reading fixed information.\n");
  }

  // Get variable screen information
  if (ioctl(fbfd, FBIOGET_VSCREENINFO, &vinfo)) {
    printf("Error reading variable information.\n");
  }
  printf("%d\t%dx%d, %d bpp\n", finfo.smem_len, vinfo.xres, vinfo.yres, 
         vinfo.bits_per_pixel );

	printf("Bit per pixel: ", vinfo.bits_per_pixel);
  // map framebuffer to user memory 
  screensize = finfo.smem_len;

  fbp = (char*)mmap(0, 
                    screensize, 
                    PROT_READ | PROT_WRITE, 
                    MAP_SHARED, 
                    fbfd, 0);

  if ((int)fbp == -1) {
    printf("Failed to mmap.\n");
  }
  else {
    // draw...
	
  }

	// cleanup
	munmap(fbp, screensize);
	close(fbfd);
	close(bitmap);
	return 0;
}
