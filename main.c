#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <unistd.h>
#include "fbsh.h"
#include "get_conf.h"
//#include "bmp.h"

int main(int argc, char **argv){
	screen_t *scr;
	resurses_t *res;

	char default_config[] = {"monitor.conf"};
/*
	typedef struct{
//		bmp_struct_t *bitmap[10];
		uint32_t x_coord;
		uint32_t y_coord;
		uint32_t state;
	}disp_object_t;
*/
//	disp_object_t *object[100];
/*
	if(fork()){
		return 0;
	}
*/
//	screen_object_t *object[100];

//	object_t *cur_obj;
/*
	if(2 < atoi(argv[1])){
		printf("Wrong number!\n");
		return 0;
	}
*/
	//Читаем файл конфигурации.
	res = read_conf(default_config);


#ifdef DEBUG_MAIN
    printf("Program parametrs is read!\n");
#endif

	//Определяем параметры экрана на который будем выводть изображения
	scr = init_screen("/dev/fb0");
	//Считываем ресурсы изображения.

#ifdef DEBUG_MAIN
    printf("Params:\t%d\n", res->object[0]->params);
#endif

#ifdef DEBUG_MAIN
	for(uint32_t i = 0; i < res->obj_count; i++){
		printf("X coord: %d; Y coord: %d;\n", res->object[i]->xcoord, res->object[i]->ycoord);
	}

#endif


	while(1){
		for(uint32_t i = 0; i < res->obj_count; i++){
			if(res->object[i]->def_state == 1){
				show_object(scr, res->object[i]->on_bitmap, res->object[i]->yres, res->object[i]->xres, res->object[i]->xcoord, res->object[i]->ycoord);
			}else{
				show_object(scr, res->object[i]->off_bitmap, res->object[i]->yres, res->object[i]->xres, res->object[i]->xcoord, res->object[i]->ycoord);
			}
		}

		sleep(1);
		if(res->object[0]->def_state == 1){
			res->object[0]->def_state = 0;
		}else{
			res->object[0]->def_state = 1;
		}
#ifdef DEBUG_MAIN
    printf("Iteration!\n");
#endif
	}

//show_object(scr, object[3]->bitmap[1]->byte_field, object[3]->bitmap[1]->height, object[3]->bitmap[1]->width, object[3]->x_coord, object[3]->y_coord);

	free(res);
	free(scr);
/*	for(uint32_t i = 0; i < res->obj_count; i++){
		free(object[i]);
	}
*/
	return 0;
}
