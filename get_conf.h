/*
Объект битовое отображение:
	Имя или номер объекта.
	Регистр опроса (определяет поведение - картинка или текст)
	Координаты отображения.
	Размеры изображения.
	Битовое поле для состояния включено.
	Битовое поле для состояния выключено.
*/

#include <stdint.h>
#include "bmp.h"
#include "debug.h"

//Определение макросов для упрощения вывода отладочной информации.
#define outs(exp)	printf("%s\n", exp)
#define outd(exp)	printf("%d\n", exp)

#define BUFF_LEN 200
#define OBJ_CNT 100

#define IMAGE_1	0x01
#define IMAGE_2	0x02
#define XCOORD		0x04
#define YCOORD		0x08

//#define OUTPUTS
//#define DEBUG_STEPS

//Show modes
enum{
	BLINK = 1,
	STATIC,
	REG_STATE,
	SHOW_ONCE,
};

typedef struct{
	uint32_t params;
	char obj_name[64];
	char file_name_1[64];
	char file_name_2[64];
	uint8_t show_mode;
	uint32_t xcoord;
	uint32_t ycoord;
	bmp_struct_t *bmp;
}object_t;


typedef struct{
	uint32_t obj_count;
	object_t *object[OBJ_CNT];
}prg_dat_t;

prg_dat_t *read_conf(char *file);			//Читаем конфигурационный файл.
object_t *is_a_object(char *string);							//Определяем заголовок объекта
uint32_t parse_string(char *string, object_t *pict);		//Парсим строку, Заполняя парасетры в структуре
char *clear_string(char *in_string);						//Чистим строку от ненужных символов.
