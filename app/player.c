#include <stdio.h>
#include "usb.h"
#include "media.h"
#include "lcd.h"

int main(){
    printf("mp3 init....");
    media_init();
    usb_init();
    lcd_init();
    return 0;
}