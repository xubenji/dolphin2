#include "amd64/print_amd64.h"

DisPlay_Char chs;

void print_char(uint8_t ch){
    chs.vram[chs.cursor_pos*2] = ch;
	chs.vram[chs.cursor_pos*2+1] = chs.color;
	chs.cursor_pos++;	
}

void init_print(){
	chs.vram=CHAR_DISPLAY_ADDERSS;
	chs.cursor_pos=0;
	chs.color=0x07;
}

void puts(uint8_t *str){
	while (*str!=0x00)
		{
		get_cursor_pos(*str);
		str++;
		}
}

void get_cursor_pos(uint8_t ch){
	//chs.cursor_pos = get_cursor();
	if(ch==0xd){
		chs.cursor_pos = new_line(chs.cursor_pos); //line feed
	}else if(ch==0xa){
		chs.cursor_pos = new_line(chs.cursor_pos);
	}else if(ch==0x8){
		chs.cursor_pos = backspace(chs.cursor_pos);
		
	}else{
		print_char(ch);
	}
	//set_cursor();
}

uint16_t new_line(uint16_t cursor_pos){
	cursor_pos -= cursor_pos%LINE_MAX_CHAR;
	cursor_pos += LINE_MAX_CHAR;
	return cursor_pos;
}

uint16_t backspace(uint16_t cursor_pos){
	cursor_pos=cursor_pos-1;
	chs.vram[chs.cursor_pos*2]=0;
	chs.vram[chs.cursor_pos*2-1]=0x07;
	return cursor_pos;
}