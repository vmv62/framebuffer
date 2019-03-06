#include <stdint.h>
#include "debug.h"

#define OFFSET_SIZE	0x02
#define OFFSET_PIXEL_DATA 0xA
#define OFFSET_WIDTH	0x12
#define OFFSET_HEIGHT	0x16
#define OFFSET_BITCOUNT	0x1C
#define OFFSET_IMAGESIZE	34

//#define DEBU


//Ошибки при работе с картинкой
enum{
	FILE_NOT_BMP_FORMAT = 0x01,
	ERROR_WHILE_READ_FILE,
	CANT_OPEN_FILE,
};

enum{
	BMP_BPP = 0x01,
	BMP_XRES,
	BMP_YRES,
	BMP_BFS,
	BMP_BFO,
	BMP_BF,
};

//screen_object_t load_objects();
uint32_t get_from_pict(FILE *file, uint32_t cmd);
uint32_t get_int_from_file(FILE **fd, uint32_t offset, uint32_t size);


