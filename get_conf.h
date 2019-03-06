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
#include "debug.h"
//#include "bmp.h"

//Определение макросов для упрощения вывода отладочной информации.
#define outs(exp)	printf("%s\n", exp)
#define outd(exp)	printf("%d\n", exp)

#define BUFF_LEN 200
#define OBJ_CNT 100

#define ON_IMAGE	0x01
#define OFF_IMAGE	0x02
#define XCOORD		0x04
#define YCOORD		0x08
#define DEF_STATE 0x10

//Структура объекта.
typedef struct{
	char obj_name[64];
	uint8_t *on_bitmap;
	uint8_t *off_bitmap;
	char	def_state;
	char bpp;
	uint32_t xres;
	uint32_t yres;
	uint32_t params;
	uint32_t	reg;
	uint32_t xcoord;
	uint32_t ycoord;
}object_t;


typedef struct{
	uint32_t obj_count;
	object_t *object[OBJ_CNT];
}resurses_t;

resurses_t *read_conf(char *file);			//Читаем конфигурационный файл.
object_t *is_a_object(char *string);							//Определяем заголовок объекта
uint32_t parse_string(char *string, object_t *obj);		//Парсим строку, Заполняя парасетры в структуре
char *clear_string(char *in_string);						//Чистим строку от ненужных символов.
