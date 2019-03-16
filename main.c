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


	//Определяем параметры экрана на который будем выводть изображения
	scr = init_screen("/dev/fb0");

#ifdef DEBUG_MAIN
    printf("Params:\t%d\n", res->object[0]->params);
#endif

#ifdef DEBUG_MAIN
	for(uint32_t i = 0; i < res->obj_count; i++){
		printf("X coord: %d; Y coord: %d;\n", res->object[i]->xcoord, res->object[i]->ycoord);
	}

#endif

	point_t start = {100, 200};
	point_t end = {400, 201};
	make_line(scr, start, end);

	uint32_t counter =0;
	while(1){
		for(uint32_t i = 0; i < res->obj_count; i++){
			if(res->object[i]->state == 1){
				show_object(scr, res->object[i]->on_bitmap, res->object[i]->yres, res->object[i]->xres, res->object[i]->xcoord, res->object[i]->ycoord);
			}else{
				show_object(scr, res->object[i]->off_bitmap, res->object[i]->yres, res->object[i]->xres, res->object[i]->xcoord, res->object[i]->ycoord);
			}
		}

		sleep(1);
		if(res->object[0]->state == 1){
			res->object[0]->state = 0;
		}else{
			res->object[0]->state = 1;
		}

		switch(counter){
			case 3: 	res->object[1]->state = 1;
						break;
			case 9: 	res->object[1]->state = 0;
						break;
			case 15: 	counter = 0;
						break;
		}
		counter++;
#ifdef DEBUG_MAIN
    printf("Iteration!\n");
#endif
	}


	free(res);
	free(scr);
	return 0;
}
