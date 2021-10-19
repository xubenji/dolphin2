#ifndef	_PRINTK_H
#define	_PRINTK_H

#define LINE_SIZE 160

struct ScreenBuffer{
    char * buffer;
    int column;
    int row;
};

void puts();

#endif
