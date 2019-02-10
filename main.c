#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include "fbsh.h"
#include "get_conf.c"
//#include "bmp.h"

int main(int argc, char **argv){
	screen_t *scr;
	resurses_t *res;
	object_t *cur_obj;
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

	//Загружаем ресурсы программы. Читаем изображения в память.
	for(uint32_t i = 0; i < res->obj_count; i++){
		cur_obj = res->object[i];
		if(cur_obj->params & ON_IMAGE){
			cur_obj->on_bmp = read_pict(cur_obj->on_bitmap);
		}

		if(cur_obj->params & OFF_IMAGE){
			cur_obj->on_bmp = read_pict(cur_obj->off_bitmap);
		}
	}

	//Пробуем вывести одно изображение на экран.
	show_object(res->object[0]->on_bmp);

#ifdef DEBUG_MAIN
	printf("Image bpp %d\n", res->object[0]->on_bmp->bpp);
#endif
	free(res);
	free(scr);
	return 0;
}
