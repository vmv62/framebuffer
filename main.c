#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include "fbsh.h"
#include "get_conf.h"
#include "bmp.h"

int main(int argc, char **argv){
	screen_t *scr;
	resurses_t *res;

	typedef struct{
		uint8_t *bit_field[10];
		uint32_t x_res;
		uint32_t y_res;
		uint32_t x_coord;
		uint32_t y_coord
		uint32_t state;
	}disp_object_t;

	disp_object_t *object[100];

//	object_t *cur_obj;
/*
	if(2 < atoi(argv[1])){
		printf("Wrong number!\n");
		return 0;
	}
*/
	//Читаем файл конфигурации.
	res = read_conf("monitor.conf");
	//Определяем параметры экрана на который будем выводть изображения
	scr = init_screen("/dev/fb0");

	//Считываем ресурсы изображения.
	for(uint8_t i =0; i < res->obj_count; i++){
		if(res->object[i]->params & ON_IMAGE){
			object[i]->bit_field[0] = 
		}
	}


#ifdef DEBUG_MAIN
	printf("%s\n%s\n", res->object[0]->on_bitmap, res->object[0]->off_bitmap);
#endif
	free(res);
	free(scr);
	return 0;
}
