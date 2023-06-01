//////////////////////////////////////////////////////////////////////////////////
//本程序只供学习使用，未经作者许可，不得用于其它任何用途
//中景园电子
//店铺地址：http://shop73023976.taobao.com/?spm=2013.1.0.0.M4PqC2
//
//  文 件 名   : main.c
//  版 本 号   : v2.0
//  作    者   : HuangKai
//  生成日期   : 2018-10-31
//  最近修改   :
//  功能描述   : OLED SPI接口演示例程(51系列)
//              说明:
//              ----------------------------------------------------------------
//              GND    电源地
//              VCC  3.3v电源
//              D0   P1^4（SCL）
//              D1   P1^3（SDA）
//              DC   P1^2
//              CS1  P1^1
//              FS0  P1^0
//              CS2  P0^0
//              ----------------------------------------------------------------
// 修改历史   :
// 日    期   :
// 作    者   : HuangKai
// 修改内容   : 创建文件
//版权所有，盗版必究。
//Copyright(C) 中景园电子2018-10-31
//All rights reserved
//******************************************************************************/
//#include "REG51.h"
#include "config.h"
#include "oled.h"
#include "bmp.h"
#include "GPIO.h"

void GPIO_config() {
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
}

int main(void)
{
    float t=0;
    GPIO_config();
    OLED_Init();
    OLED_ColorTurn(0);//0正常显示，1 反色显示
    OLED_DisplayTurn(0);//0正常显示 1 屏幕翻转显示
    OLED_Clear();
    while(1)
    {
////		t+=0.01;
////		OLED_ShowNum(0,0,t,5);//显示小数
        OLED_Display_128x64(bmp1);
        delay_ms(500);
        OLED_Display_GB2312_string(0,0,"12864,带中文字库");	/*在第1页，第1列，显示一串16x16点阵汉字或8x16的ASCII字*/
        OLED_Display_GB2312_string(0,2,"16X16简体汉字库,");  /*显示一串16x16点阵汉字或8x16的ASCII字.以下雷同*/
        OLED_Display_GB2312_string(0,4,"或8X16点阵ASCII,");
        OLED_Display_GB2312_string(0,6,"或5X7点阵ASCII码");
        delay_ms(500);
        OLED_Clear();
        OLED_Display_GB2312_string(24,0,"中景园电子");
        OLED_Display_GB2312_string(0,2,"主要生产OLED模块");
        OLED_Display_GB2312_string(0,4,"顾客至上真诚服务");
        OLED_Display_GB2312_string(0,6,"诚信与质量第一！");
        delay_ms(500);
        OLED_Clear();
        OLED_Display_GB2312_string(0,0,"GB2312简体字库及");
        OLED_Display_GB2312_string(0,2,"有图型功能，可自");
        OLED_Display_GB2312_string(0,4,"编大字或图像或生");
        OLED_Display_GB2312_string(0,6,"僻字，例如：");
        OLED_Display_16x16(97,6,jiong1);					/*在第7页，第81列显示单个自编生僻汉字“囧”*/
        OLED_Display_16x16(113,6,lei1);
        delay_ms(500);
        OLED_Clear();
        OLED_Display_GB2312_string(0,0,"<!@#$%^&*()_-+]/");	/*在第1页，第1列，显示一串16x16点阵汉字或8*16的ASCII字*/
        OLED_Display_string_5x7(0,2,"<!@#$%^&*()_-+]/;.,?[");/*在第3页，第1列，显示一串5x7点阵的ASCII字*/
        OLED_Display_string_5x7(0,3,"XY electronics Co., ");/*显示一串5x7点阵的ASCII字*/
        OLED_Display_string_5x7(0,4,"Ltd. established at  ");/*显示一串5x7点阵的ASCII字*/
        OLED_Display_string_5x7(0,5,"year 2010.Focus OLED ");/*显示一串5x7点阵的ASCII字*/
        OLED_Display_string_5x7(0,6,"Mobile:13265585975");/*显示一串5x7点阵的ASCII字*/
        OLED_Display_string_5x7(0,7,"Tel:0755-32910715");/*显示一串5x7点阵的ASCII字*/
        delay_ms(500);
        OLED_Clear();
        OLED_Display_GB2312_string(0,0,"啊阿埃挨哎唉哀皑");	/*在第1页，第1列，显示一串16x16点阵汉字或8x16的ASCII字*/
        OLED_Display_GB2312_string(0,2,"癌蔼矮艾碍爱隘鞍");  /*显示一串16x16点阵汉字或8x16的ASCII字.以下雷同*/
        OLED_Display_GB2312_string(0,4,"氨安俺按暗岸胺案");
        OLED_Display_GB2312_string(0,6,"肮昂盎凹敖熬翱袄");
        delay_ms(500);
        OLED_Clear();
        OLED_Display_GB2312_string(0,0,"鬟鬣麽麾縻麂麇麈");
        OLED_Display_GB2312_string(0,2,"麋麒鏖麝麟黛黜黝");
        OLED_Display_GB2312_string(0,4,"黠黟黢黩黧黥黪黯");
        OLED_Display_GB2312_string(0,6,"齄鼬鼹鼷鼽鼾鼢鼯");
        delay_ms(500);
        OLED_Clear();
    }
}