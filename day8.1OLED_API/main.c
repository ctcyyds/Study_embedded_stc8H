//////////////////////////////////////////////////////////////////////////////////
//本程序只供学习使用，未经作者许可，不得用于其它任何用途
//中景园电子
//店铺地址：http://shop73023976.taobao.com/?spm=2013.1.0.0.M4PqC2
//
//  文 件 名   : main.c
//  版 本 号   : v2.0
//  作    者   : HuangKai
//  生成日期   : 2014-0101
//  最近修改   :
//  功能描述   : OLED 4接口演示例程(51系列)
//              说明:
//              ----------------------------------------------------------------
//              GND    电源地
//              VCC  接5V或3.3v电源
//              SCL  P10（SCL）
//              SDA  P11（SDA）
//              RES  P12 注：SPI接口显示屏改成IIC接口时需要接RES引脚
//                           IIC接口显示屏用户请忽略
//              ----------------------------------------------------------------
// 修改历史   :
// 日    期   :
// 作    者   : HuangKai
// 修改内容   : 创建文件
//版权所有，盗版必究。
//Copyright(C) 中景园电子2014/3/16
//All rights reserved
//******************************************************************************/
//#include "REG51.h"
#include "config.h"
#include "oled.h"
#include "bmp.h"

int main(void)
{
    //GPIO初始化
    P0M1 = 0;
    P0M0 = 0;
    P1M1 = 0;
    P1M0 = 0;
    P2M1 = 0;
    P2M0 = 0;
    P3M1 = 0;
    P3M0 = 0;
    P4M1 = 0;
    P4M0 = 0;
    P5M1 = 0;
    P5M0 = 0;
    P6M1 = 0;
    P6M0 = 0;
    P7M1 = 0;
    P7M0 = 0;
    EA = 1;
    OLED_Init();//初始化OLED
    OLED_ColorTurn(0);//0正常显示，1 反色显示
    OLED_DisplayTurn(0);//0正常显示 1 屏幕翻转显示
    while(1)
    {
        /**OLED_ShowChar(0,0,'a',16);
        OLED_ShowNum(0,2,2023,4,16);
        OLED_ShowString(0,4,"Hello word!",16);
        OLED_DrawBMP(0,0,128, 64,BMP2);**/
        OLED_ShowChinese(0,2,0,16);
        OLED_ShowChinese(10,2,1,16);
        OLED_ShowChinese(36,2,2,16);
        OLED_ShowChinese(56,2,3,16);
        OLED_ShowChinese(76,2,4,16);
        OLED_ShowChar(30,4,'Y',16);
        OLED_ShowChar(50,4,'Y',16);
        OLED_ShowChar(70,4,'D',16);
        OLED_ShowChar(90,4,'S',16);
    }

}

