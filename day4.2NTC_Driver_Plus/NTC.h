/*
热敏电阻驱动
*/
#ifndef __NTC_H__
#define __NTC_H__
//STC8H平台的库函数
#include "ADC.h"


//引脚用的是P04
#define NTC_PIN P04
#define NTC_CHN 12
//设置状态为高阻输入
#define NTC_PIN_INIT() {P0M1 |= 0x10,	P0M0 &= ~ 0x10;}

//不同芯片更改处
u16 NTC_Get_ADCResult(u8 chn);

//初始化操作
void NTC_init();


//提供温度获取的方法：方法名，参数，返回值
int NTC_get_temperature();




#endif