#include "UART.h"
#include "config.h"
#include "GPIO.h"
#include "MatrixKeys.h"
#include <stdio.h>
#include "Nixie.h"

u8 leds[8] = {0};
void GPIO_config(void) {

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

void All_init() {
    GPIO_config();
    UART_config();
    MK_init();
    Nixie_init();
    EA = 1;
}

char putchar (char dat) {
    TX1_write2buff(dat);
    return dat;
}

void MK_on_keyup(u8 row, u8 col) {
    printf("%d行，%d列 UP\r\n",(int)row,(int)col);
    if(row == 0 && col == 0) {
        leds[0]++;
    } else if(row == 0 && col == 1) {
        leds[0]--;
    } else if(row == 0 && col == 2) {
        os_send_signal(3);
    }
}
void MK_on_keydown(u8 row, u8 col) {
    printf("%d行，%d列 Down\r\n",(int)row,(int)col);
}

//定义我的程序入口
void start() _task_ 0{
    All_init();

    os_create_task(1);
    os_create_task(2);
    os_create_task(3);
    os_delete_task(0);
}

void task1() _task_ 1{
    while(1) {
        u16 state;
        MK_scan(&state);
        os_wait2(K_TMO,4);
    }
}

void task2() _task_ 2{
    u8 i;
    while(1) {
        for(i = 0; i < 8; i++) {
            Nixie_show(i, leds[i]);
        }
    }
}

void task3() _task_ 3{
    while(1) {
        //OLED显示
        printf("task_3 start\r\n");
        os_wait1(K_SIG);
        printf("task_3 end\r\n");
    }
}
