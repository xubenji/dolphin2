#include <stdio.h>
//#include <../boot/init_boot.h>
#include <audio.h>
#include <hardisk.h>
#include <usb.h>


void main(){
    //init_boot();
    audio();
    hardisk();
    usb();
}