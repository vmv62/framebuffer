#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
//#include "bmp.h"
#include "fbsh.h"
#include "get_conf.c"

int main(int argc, char **argv){
	screen_t *scr;
	resurses_t *res;
	object_t *obj_zero;;

	res = read_conf("monitor.conf");
	scr = init_screen("/dev/fb0");
/*
	printf("Programm find %d objects!\n", res->obj_count);

	if(3 > atoi(argv[1])){
		printf("Programm find %d objects!\n", res->obj_count);
		return 0;
	}
*/
	obj_zero = res->object[atoi(argv[1])];

#ifdef DEBUG_MAIN
	printf("Resurses:\n\tObject 1 name: %s;\n\tObject 1 x coord: %d;\n\tObject 1 y coord: %d;\n\n", obj_zero->obj_name, obj_zero->xcoord, obj_zero->ycoord);
	printf("Screen information:\n\tX resolution: %d;\n\tY resolution: %d;\n\tBPP: %d\n", scr->xres, scr->yres, scr->screen_bpp);
#endif

	free(res);
	free(scr);
	return 0;
}
