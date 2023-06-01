#ifndef __NIXIE_H__
#define __NIXIE_H__

//如果要做移植

#include "config.h"

// 数据
#define NIX_DI	P44
// 锁存 byte
#define NIX_RCK  P43
// 移位 bit
#define NIX_SCK  P42

// 模式：pullup
#define NIXIE_PIN_INIT()	{P4M1 &= ~0x10,P4M0 &= ~0x10,P4M1 &= ~0x08,P4M0 &= ~0x08,P4M1 &= ~0x04,P4M0 &= ~0x04;}
//#define NOP2()	_nop_(),_nop_()

// 初始化
void Nixie_init();

// 显示数字
// index: 位置
// dat: 内容. 寄存器要的数据，人的认知有偏差。
// dat: 改为人能理解的值，人的值转成寄存器要的值
void Nixie_show(u8 index, u8 dat);


#endif