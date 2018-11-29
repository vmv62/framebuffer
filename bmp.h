#define OFFSET_SIZE	0x02
#define OFFSET_PIXEL_DATA 0xA
#define OFFSET_WIDTH	0x12
#define OFFSET_HEIGHT	0x16
#define OFFSET_BITCOUNT	0x1C
#define OFFSET_IMAGESIZE	34

typedef unsigned char uint8_t;
typedef unsigned short uint16_t;
typedef unsigned int uint32_t;

typedef struct{
	uint8_t type;
	uint32_t size;
	uint32_t reserved;
	uint32_t jffset_bits;
}bmp_header_t;

typedef struct{
	uint32_t width;
	uint32_t height;
	uint16_t bit_pp;
	uint32_t pixel_offset;
	uint8_t	*bit_field;
}img_data_t;


//-------------------------------------------------------------------
typedef struct{
	uint8_t 	bpp;
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

uint32_t get_int_value(FILE *fd, uint32_t offset, uint32_t size);
uint32_t open_pict(uint8_t *file, bmp_struct_t *bmp);
