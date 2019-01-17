#include <stdint.h>

#define BUFF_LEN 200
#define OBJ_CNT 100


//Show modes
enum{
	BLINK = 1,
	STATIC,
	REG_STATE,
	SHOW_ONCE,
};

typedef struct{
	char obj_name[64];
	char file_name_1[64];
	char file_name_2[64];
	uint8_t show_mode;
	uint32_t xcoord;
	uint32_t ycoord;
}oconf_t;


typedef struct{
	int obj_count;
	oconf_t *object[OBJ_CNT];
}prg_dat_t;

uint32_t read_conf(char *file, prg_dat_t *p_conf);			//Читаем конфигурационный файл.
uint32_t is_a_object(char *string, prg_dat_t *pict);							//Определяем заголовок объекта
uint32_t parse_string(char *string, oconf_t *pict);		//Парсим строку, Заполняя парасетры в структуре
char *clear_string(char *in_string);						//Чистим строку от ненужных символов.
