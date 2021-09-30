#ifndef _PRINTK_AMD64_H
#define _PRINTK_AMD64_H

#include "amd64/types.h"

#define BASE 0xb8000

#define CHAR_DISPLAY_ADDERSS 0Xb8000
#define LINE_MAX_CHAR 80
#define SCREEN_MODE 800*600


void put_int64(int64_t num_hex);
void put_int32(int32_t num_hex);
void put_int16(int16_t num_hex);
void put_int8(int8_t num_hex);

void print_char(uint8_t ch);
void init_display_info();
uint16_t new_line(uint16_t cursor_pos);
uint16_t backspace(uint16_t cursor_pos);
void get_cursor_pos(uint8_t ch);
void printk(uint8_t *str);
void print_char(uint8_t ch);
void put_dec_uint32(uint32_t num);
void fresh_screen();



typedef struct display_char{
	int8_t *vram;
	uint16_t cursor_pos;
	int8_t color; 
}DisPlay_Char;

#endif