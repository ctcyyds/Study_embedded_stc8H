#ifndef __MATRIX_KEYS__
#define __MATRIX_KEYS__
#include "config.h"
//===============================
// 定义行
#define ROW1 P34
#define ROW2 P35
#define ROW3 P40
#define ROW4 P41
// 定义列
#define COL1 P03
#define COL2 P06
#define COL3 P07
#define COL4 P17
// 初始化所有引脚

// #define KEYS_PIN_INIT() {P0M0 &= ~0xc8, P0M1 &= ~0xc8, P1M0 &= ~0x80, P1M1 &= ~0x80, P3M0 &= ~0x30, P3M1 &= ~0x30,P4M0 &= ~0x03,P4M1 &= ~0x03;}
#define KEYS_PIN_INIT()                                                                                                                 \
        {                                                                                                                               \
                P0M0 &= ~0xc8, P0M1 &= ~0xc8, P3M0 &= ~0x30, P3M1 &= ~0x30, P4M0 &= ~0x03, P4M1 &= ~0x03, P1M0 &= ~0x80, P1M1 &= ~0x80; \
        }

//===============================

// 开关状态对应的电平
#define KEY_DOWN 0
#define KEY_UP 1

// 定义行列长度
#define ROW_NUM 4
#define COL_NUM 4

void MK_init();
void MK_scan(u16 *state);

extern void MK_on_keyup(u8 row, u8 col);
extern void MK_on_keydown(u8 row, u8 col);

#endif