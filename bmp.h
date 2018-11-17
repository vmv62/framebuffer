#define OFFSET_SIZE	2
#define OFFSET_WIDTH	18
#define OFFSET_HEIGHT	22
#define OFFSET_BITCOUNT	28
#define OFFSET_IMAGESIZE	34

typedef unsigned char uint8_t;
typedef unsigned short uint16_t;
typedef unsigned int uint32_t;

typedef struct{
	uint8_t signature[2];
	uint32_t size;
	uint32_t reserved;
	uint32_t offset;
	uint32_t header_size;
	uint32_t width;
	uint32_t height;
	uint8_t planes;
	uint8_t bit_count;
	uint32_t compression;
	uint32_t size_image;
	uint32_t xpels_per_meter;
	uint32_t ypels_per_meter;
	uint32_t colors_used;
	uint32_t colors_impotant;
}bmp_header_t;
