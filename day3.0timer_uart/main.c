#include "config.h"
#include "GPIO.h"
#include "timer.h"
#include "UART.h"
#include "delay.h"
#include <stdio.h>
/*
1.串口：通过PC给串口发消息
2.如果收到0x01，timer中就去打印Hello Word
3.如果收到其他的，就不打印
*/

u8 tmp=0x00;

//GPIO初始化
void GPIO_config(void) {
    GPIO_InitTypeDef GPIO_InitStructure;//结构定义
    GPIO_InitStructure.Mode=GPIO_PullUp;//IO模式，GPIO_PullUp,GPIO_HighZ,GPIO_OUT_OD,GPIO_OUT_PP
    GPIO_InitStructure.Pin=GPIO_Pin_3;//指定要初始化的IO
    GPIO_Inilize(GPIO_P5, &GPIO_InitStructure);//初始化
}

//UART初始化
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

//Timer初始化
void TIMER_config(void) {
    TIM_InitTypeDef        TIM_InitStructure;                        //结构定义
    TIM_InitStructure.TIM_Mode      = TIM_16BitAutoReload;    //指定工作模式,   TIM_16BitAutoReload,TIM_16Bit,TIM_8BitAutoReload,TIM_16BitAutoReloadNoMask
    TIM_InitStructure.TIM_Priority    = Priority_0;            //指定中断优先级(低到高) Priority_0,Priority_1,Priority_2,Priority_3
    TIM_InitStructure.TIM_Interrupt = ENABLE;                    //中断是否允许,   ENABLE或DISABLE
    TIM_InitStructure.TIM_ClkSource = TIM_CLOCK_1T;        //指定时钟源,     TIM_CLOCK_1T,TIM_CLOCK_12T,TIM_CLOCK_Ext
    TIM_InitStructure.TIM_ClkOut    = DISABLE;                //是否输出高速脉冲, ENABLE或DISABLE
    TIM_InitStructure.TIM_Value     = 65536UL - (MAIN_Fosc / 1000UL);        //初值,>367
    TIM_InitStructure.TIM_Run       = ENABLE;                    //是否初始化后启动定时器, ENABLE或DISABLE
    Timer_Inilize(Timer0,&TIM_InitStructure);                    //初始化Timer0      Timer0,Timer1,Timer2,Timer3,Timer4
}

//使用Printf
char putchar (char dat){
	TX1_write2buff(dat);
}

void timer0_call() {
    if(tmp == 0x01) {
       // PrintString1("Hello Word\r\n"); // 写字符串
			printf("Hello Word\r\n");
    }
}

int main() {
    u8 i;
    //引用
    GPIO_config();
    UART_config();
    TIMER_config();

    //中断总开关
    EA=1;

    while(1) {
        delay_ms(10);
        //接收PC发来的消息
        if(COM1.RX_TimeOut > 0)        //超时计数
        {
            if(--COM1.RX_TimeOut == 0)
            {
                if(COM1.RX_Cnt > 0)
                {
                    for(i=0; i<COM1.RX_Cnt; i++)    {
                        // TODO: RX1_Buffer[i]存的是接收的数据
                        // TODO: 做具体的逻辑
                        tmp=RX1_Buffer[i];
                        TX1_write2buff(RX1_Buffer[i]);// 写一个byte
                    }
                }
                COM1.RX_Cnt = 0;
            }
        }
    }
}