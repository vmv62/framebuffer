#include <stdint.h>

#define OFFSET_SIZE	0x02
#define OFFSET_PIXEL_DATA 0xA
#define OFFSET_WIDTH	0x12
#define OFFSET_HEIGHT	0x16
#define OFFSET_BITCOUNT	0x1C
#define OFFSET_IMAGESIZE	34

/*
typedef char uint8_t;
typedef unsigned short uint16_t;
typedef unsigned int uint32_t;
*/

typedef struct{
	uint8_t 	bpp;
	uint8_t	reserved1;
	uint8_t	reserved2;
	uint8_t	reserved3;
	uint32_t width;
	uint32_t height;
	uint32_t bytes_field_size;
	uint8_t 	*byte_field;
}bmp_struct_t;


//Ошибки при работе с картинкой
enum{
	FILE_NOT_BMP_FORMAT = 0x01,
	ERROR_WHILE_READ_FILE,
	CANT_OPEN_FILE,
};

uint32_t get_int_from_file(FILE **fd, uint32_t offset, uint32_t size);
uint32_t read_pict(uint8_t *file, bmp_struct_t *bmp);
