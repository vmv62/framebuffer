#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include "fbsh.h"
#include "get_conf.c"
//#include "bmp.h"

int main(int argc, char **argv){
	screen_t *scr;
	resurses_t *res;
	object_t *obj_zero;;

	if(2 < atoi(argv[1])){
		printf("Wrong number!\n");
		return 0;
	}

	//Читаем файл конфигурации.
	res = read_conf("monitor.conf");
	//Определяем параметры экрана на который будем выводть изображения
	scr = init_screen("/dev/fb0");
	//Загружаем ресурсы программы.

//	res->object[0]->bmp[0] = read_pict(res->object[0]->on_bitmap);
	obj_zero = res->object[atoi(argv[1])];

#ifdef DEBUG_MAIN
	printf("%s\n", res->object[atoi(argv[1])]->on_bitmap);
	printf("Resurses:\n\tObject 1 name: %s;\n\tObject 1 x coord: %d;\n\tObject 1 y coord: %d;\n\n", obj_zero->obj_name, obj_zero->xcoord, obj_zero->ycoord);
	printf("Screen information:\n\tX resolution: %d;\n\tY resolution: %d;\n\tBPP: %d\n", scr->xres, scr->yres, scr->screen_bpp);
#endif

	free(res);
	free(scr);
	return 0;
}
