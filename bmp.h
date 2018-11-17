#define OFFSET_SIZE	0x02
#define OFFSET_PIXEL_DATA 10
#define OFFSET_WIDTH	0x11
#define OFFSET_HEIGHT	0x15
#define OFFSET_BITCOUNT	0x1C
#define OFFSET_IMAGESIZE	34

typedef unsigned char uint8_t;
typedef unsigned short uint16_t;
typedef unsigned int uint32_t;

typedef struct{
	uint32_t width;
	uint32_t height;
	uint16_t bit_pp;
	uint32_t pixel_offset;
	uint8_t	*bit_field;
}img_data_t;

//Ошибки при работе с картинкой
enum{
	FILE_NOT_BMP_FORMAT = 0x01,
	ERROR_WHILE_READ_FILE,
	CANT_OPEN_FILE,
};

int get_int_value(uint8_t *buff);
int get_pic_param(uint8_t *file, img_data_t *img);
