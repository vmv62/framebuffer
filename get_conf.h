#include <stdint.h>

#define BUFF_LEN 100

typedef struct{
	int obj_count;
}prg_dat_t;

//Show modes
enum{
	BLINK = 1,
	STATIC,
	REG_STATE,
	SHOW_ONCE,
};

typedef struct{
	uint8_t file_name_1[64];
	uint8_t file_name_2[64];
	uint8_t show_mode;
	uint8_t reserved;
	char obj_name[64];
	uint32_t xcoord;
	uint32_t ycoord;
}sconf_t;

sconf_t files[20];

uint32_t read_conf(char *file, sconf_t *pict, prg_dat_t *p_conf);			//Читаем конфигурационный файл.
uint32_t is_a_object(char *string, sconf_t *pict);							//Определяем заголовок объекта
uint32_t parse_string(char *string, sconf_t *pict);		//Парсим строку, Заполняя парасетры в структуре
