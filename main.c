#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include "fbsh.h"
#include "get_conf.h"
#include "bmp.h"

int main(int argc, char **argv){
	screen_t *scr;
	resurses_t *res;

	char default_config[] = {"monitor.conf"};

	typedef struct{
		bmp_struct_t *bitmap[10];
		uint32_t x_coord;
		uint32_t y_coord;
		uint32_t state;
	}disp_object_t;

	disp_object_t *object[100];


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

	for(uint8_t i =0; i < res->obj_count; i++){
		uint32_t param = res->object[i]->params;
//		bmp_struct_t *tmp_bmp;

		object[i] = (disp_object_t *)malloc(sizeof(disp_object_t));
//		object[i] = (screen_object_t *)malloc(sizeof(screen_object_t));

		object[i]->x_coord = res->object[i]->xcoord;
		object[i]->y_coord = res->object[i]->ycoord;
		object[i]->state = 0;

		if(param & ON_IMAGE){
			object[i]->bitmap[1] = read_pict(res->object[i]->on_bitmap);
		}

		if(param & OFF_IMAGE){
         object[i]->bitmap[0] = read_pict(res->object[i]->off_bitmap);
      }

	}
#ifdef DEBUG_MAIN
	for(uint32_t i = 0; i < res->obj_count; i++){
		printf("X coord: %d; Y coord: %d;\n", object[i]->x_coord, object[i]->y_coord);
	}

//	printf("%d\n%d\n", object[0]->x_coord, object[0]->y_coord);
#endif

	for(uint32_t i = 0; i < res->obj_count; i++){
		show_object(scr, object[i]->bitmap[1]->byte_field, object[i]->bitmap[1]->height, object[i]->bitmap[1]->width, object[i]->x_coord, object[i]->y_coord);
	}


	free(res);
	free(scr);
/*	for(uint32_t i = 0; i < res->obj_count; i++){
		free(object[i]);
	}
*/
	return 0;
}
