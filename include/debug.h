/*
 * @Author: your name
 * @Date: 2021-10-16 15:24:57
 * @LastEditTime: 2021-11-16 21:18:30
 * @LastEditors: Please set LastEditors
 * @Description: 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 * @FilePath: /dolphin2/include/debug.h
 */
#ifndef __DEBUG_H
#define __DEBUG_H

#include "stdint.h"

#define ASSERT(e,infor) do {                  \
    if(!(e))                            \
        error_check(__FILE__,__LINE__,infor); \
} while (0)


void error_check(uint8_t *file, uint64_t line, uint8_t * infor);

#endif

