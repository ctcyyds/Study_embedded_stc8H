#include "config.h"
#include "GPIO.h"
#include "delay.h"
#include "UART.h"
#include <stdio.h>
#include "PCF8563.h"
#include "I2C.h"
#include "oled.h"

char putchar (char dat) {
    TX1_write2buff(dat);
    return dat;
}

void GPIO_config(void) {
    GPIO_InitTypeDef GPIO_InitStructure;//结构定义
    GPIO_InitStructure.Mode=GPIO_PullUp;//IO模式，GPIO_PullUp,GPIO_HighZ,GPIO_OUT_OD,GPIO_OUT_PP
    GPIO_InitStructure.Pin=GPIO_Pin_3 | GPIO_Pin_2;//指定要初始化的IO
    GPIO_Inilize(GPIO_P3, &GPIO_InitStructure);//初始化
}

void UART_config(void) {
    COMx_InitDefine        COMx_InitStructure;                    //结构定义
    COMx_InitStructure.UART_Mode      = UART_8bit_BRTx;    //模式, UART_ShiftRight,UART_8bit_BRTx,UART_9bit,UART_9bit_BRTx
    COMx_InitStructure.UART_BRT_Use   = BRT_Timer1;            //选择波特率发生器, BRT_Timer1, BRT_Timer2 (注意: 串口2固定使用BRT_Timer2)
    COMx_InitStructure.UART_BaudRate  = 115200ul;            //波特率, 一般 110 ~ 115200
    COMx_InitStructure.UART_RxEnable  = ENABLE;                //接收允许,   ENABLE或DISABLE
    COMx_InitStructure.BaudRateDouble = DISABLE;            //波特率加倍, ENABLE或DISABLE
    COMx_InitStructure.UART_Interrupt = ENABLE;                //中断允许,   ENABLE或DISABLE
    COMx_InitStructure.UART_Priority  = Priority_0;            //指定中断优先级(低到高) Priority_0,Priority_1,Priority_2,Priority_3
    COMx_InitStructure.UART_P_SW      = UART1_SW_P30_P31;    //切换端口,   UART1_SW_P30_P31,UART1_SW_P36_P37,UART1_SW_P16_P17,UART1_SW_P43_P44
    UART_Configuration(UART1, &COMx_InitStructure);        //初始化串口1 UART1,UART2,UART3,UART4
}

void I2C_config(void)
{
    I2C_InitTypeDef		I2C_InitStructure;
    I2C_InitStructure.I2C_Mode      = I2C_Mode_Master;	//主从选择   I2C_Mode_Master, I2C_Mode_Slave
    I2C_InitStructure.I2C_Enable    = ENABLE;						//I2C功能使能,   ENABLE, DISABLE
    I2C_InitStructure.I2C_MS_WDTA   = DISABLE;					//主机使能自动发送,  ENABLE, DISABLE
    I2C_InitStructure.I2C_MS_Interrupt = DISABLE;				//使能主机模式中断,  ENABLE, DISABLE
    I2C_InitStructure.I2C_Speed     = 13;								//总线速度=Fosc/2/(Speed*2+4),      0~63
    I2C_InitStructure.I2C_IoUse     = I2C_P33_P32;			//IO口切换   I2C_P14_P15, I2C_P24_P25, I2C_P33_P32

    I2C_Init(&I2C_InitStructure);
}

int main() {
    Clock_t c;
    u8 row1_offset_x;
    u8 row2_offset_x;
    GPIO_config();
    UART_config();
    I2C_config();
    PCF8563_init();

    OLED_Init();//初始化OLED
    OLED_ColorTurn(0);//0正常显示，1 反色显示
    OLED_DisplayTurn(0);//0正常显示 1 屏幕翻转显示
    EA = 1;

    //获取时间，显示
    //clock
    c.year = 2023;
    c.month = 4;
    c.day = 20;
    c.weekday =4;
    c.hour = 9;
    c.minute = 13;
    c.second = 12;
    PCF8563_set_clock(c);
    row1_offset_x=20;
    row2_offset_x=26;
    while(1) {
        PCF8563_get_clock(&c);
        printf("%d-%d-%d %d", (int)c.year, (int)c.month, (int)c.day, (int)c.weekday);
        printf(" %d:%d:%d \r\n", (int)c.hour, (int)c.minute, (int)c.second);
        //年-月-日
        OLED_ShowNum(row1_offset_x+0,0,c.year,4,16);
        OLED_ShowChar(row1_offset_x+32,0,'.',16);
        if(c.month < 10) {
            OLED_ShowNum(row1_offset_x+36,0,0,1,16);
            OLED_ShowNum(row1_offset_x+44,0,c.month,1,16);
        } else {
            OLED_ShowNum(row1_offset_x+36,0,c.month,2,16);
        }
        OLED_ShowChar(row1_offset_x+54,0,'.',16);
        if(c.day < 10) {
            OLED_ShowNum(row1_offset_x+60,0,0,1,16);
            OLED_ShowNum(row1_offset_x+72,0,c.day,1,16);
        } else {
            OLED_ShowNum(row1_offset_x+60,0,c.day,2,16);
        }

        //时：分：秒
        if(c.hour < 10) {
            OLED_ShowNum(row2_offset_x+0,4,0,1,16);
            OLED_ShowNum(row2_offset_x+8,4,c.hour,1,16);
        } else {
            OLED_ShowNum(row2_offset_x+0,4,c.hour,2,16);
        }

        OLED_ShowChar(row2_offset_x+16,4,':',16);
        if(c.minute < 10) {
            OLED_ShowNum(row2_offset_x+24,4,0,1,16);
            OLED_ShowNum(row2_offset_x+32,4,c.minute,1,16);
        } else {
            OLED_ShowNum(row2_offset_x+24,4,c.minute,2,16);
        }
        OLED_ShowChar(row2_offset_x+40,4,':',16);
        if(c.second < 10) {
            OLED_ShowNum(row2_offset_x+48,4,0,1,16);
            OLED_ShowNum(row2_offset_x+56,4,c.second,1,16);
        } else {
            OLED_ShowNum(row2_offset_x+48,4,c.second,2,16);
        }
        delay_ms(250);
        delay_ms(250);
        delay_ms(250);
        delay_ms(250);
    }
}