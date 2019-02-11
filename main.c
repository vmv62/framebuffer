#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include "fbsh.h"
#include "get_conf.h"
#include "bmp.h"

int main(int argc, char **argv){
	screen_t *scr;
	resurses_t *res;
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


#ifdef DEBUG_MAIN
	printf("%s\n%s\n", res->object[0]->on_bitmap, res->object[0]->off_bitmap);
#endif
	free(res);
	free(scr);
	return 0;
}
