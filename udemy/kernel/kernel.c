#include <stdio.h>
//#include <../boot/init_boot.h>
#include </root/dolphin2/udemy/kernel/drives/audio/audio.h>
#include </root/dolphin2/udemy/kernel/drives/hardisk/hardisk.h>
#include </root/dolphin2/udemy/kernel/drives/usb/usb.h>


void main(){
    //init_boot();
    audio();
    hardisk();
    usb();
}