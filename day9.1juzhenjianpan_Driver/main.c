#include "config.h"
#include "GPIO.h"
#include "UART.h"
#include "delay.h"
#include <stdio.h>
#include "MatrixKeys.h"

char putchar(char dat)
{
    TX1_write2buff(dat);
    return dat;
}

// GPIO初始化
void GPIO_config(void)
{
    GPIO_InitTypeDef GPIO_InitStructure; // 结构定义
    // P34 P35
    GPIO_InitStructure.Mode = GPIO_PullUp;            // IO模式，GPIO_PullUp,GPIO_HighZ,GPIO_OUT_OD,GPIO_OUT_PP
    GPIO_InitStructure.Pin = GPIO_Pin_4 | GPIO_Pin_5; // 指定要初始化的IO
    GPIO_Inilize(GPIO_P3, &GPIO_InitStructure);       // 初始化
    // P40 P41
    GPIO_InitStructure.Mode = GPIO_PullUp;            // IO模式，GPIO_PullUp,GPIO_HighZ,GPIO_OUT_OD,GPIO_OUT_PP
    GPIO_InitStructure.Pin = GPIO_Pin_0 | GPIO_Pin_1; // 指定要初始化的IO
    GPIO_Inilize(GPIO_P4, &GPIO_InitStructure);       // 初始化
    // P03 P06 P07
    GPIO_InitStructure.Mode = GPIO_PullUp;                         // IO模式，GPIO_PullUp,GPIO_HighZ,GPIO_OUT_OD,GPIO_OUT_PP
    GPIO_InitStructure.Pin = GPIO_Pin_3 | GPIO_Pin_6 | GPIO_Pin_7; // 指定要初始化的IO
    GPIO_Inilize(GPIO_P0, &GPIO_InitStructure);                    // 初始化
    // P17
    GPIO_InitStructure.Mode = GPIO_PullUp;      // IO模式，GPIO_PullUp,GPIO_HighZ,GPIO_OUT_OD,GPIO_OUT_PP
    GPIO_InitStructure.Pin = GPIO_Pin_7;        // 指定要初始化的IO
    GPIO_Inilize(GPIO_P1, &GPIO_InitStructure); // 初始化
}

// UART初始化
void UART_config(void)
{
    COMx_InitDefine COMx_InitStructure;              // 结构定义
    COMx_InitStructure.UART_Mode = UART_8bit_BRTx;   // 模式, UART_ShiftRight,UART_8bit_BRTx,UART_9bit,UART_9bit_BRTx
    COMx_InitStructure.UART_BRT_Use = BRT_Timer1;    // 选择波特率发生器, BRT_Timer1, BRT_Timer2 (注意: 串口2固定使用BRT_Timer2)
    COMx_InitStructure.UART_BaudRate = 115200ul;     // 波特率, 一般 110 ~ 115200
    COMx_InitStructure.UART_RxEnable = ENABLE;       // 接收允许,   ENABLE或DISABLE
    COMx_InitStructure.BaudRateDouble = DISABLE;     // 波特率加倍, ENABLE或DISABLE
    COMx_InitStructure.UART_Interrupt = ENABLE;      // 中断允许,   ENABLE或DISABLE
    COMx_InitStructure.UART_Priority = Priority_0;   // 指定中断优先级(低到高) Priority_0,Priority_1,Priority_2,Priority_3
    COMx_InitStructure.UART_P_SW = UART1_SW_P30_P31; // 切换端口,   UART1_SW_P30_P31,UART1_SW_P36_P37,UART1_SW_P16_P17,UART1_SW_P43_P44
    UART_Configuration(UART1, &COMx_InitStructure);  // 初始化串口1 UART1,UART2,UART3,UART4
}

void MK_on_keyup(u8 row, u8 col)
{
    printf("Up %d行 %d列\r\n", (int)row, (int)col); // 按钮抬起电平为高
}

void MK_on_keydown(u8 row, u8 col)
{
    printf("Down %d行 %d列\r\n", (int)row, (int)col); // 按钮按下电平为低
}

int main()
{
		u16 state;
    GPIO_config();
    UART_config();
    MK_init();
    EA = 1;
    while (1)
    {
        delay_ms(20);
        MK_scan(&state);
    }
}