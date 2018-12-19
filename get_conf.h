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

sconf_t files[20];

uint32_t read_conf(char *file, sconf_t *conf);
uint32_t parse_string(char *string, sconf_t pict);
