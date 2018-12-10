#include <stdint.h>

#define BUFF_LEN 100

//Show modes
enum{
	BLINK = 1,
	STATIC,
	REG_STATE,
	SHOW_ONCE,
};

typedef struct{
	uint8_t file_name_1[50];
	uint8_t file_name_2[50];
	uint8_t show_mode;
	uint8_t reserved;
	uint32_t xcoord;
	uint32_t ycoord;
}sconf_t;

sconf_t files[];

uint32_t read_conf(uint8_t *file, sconf_t *conf);
