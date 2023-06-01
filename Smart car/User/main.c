
#include "GPIO.h"
#include "UART.h"
#include <stdio.h>
#include "Key.h"
#include "Motors.h"
#include "Track.h"


u8 flag = 0;
char putchar (char dat) {
    TX1_write2buff(dat);
    return dat;
}

void GPIO_config(void) {
	GPIO_InitTypeDef	GPIO_InitStructure;		//结构定义
	GPIO_InitStructure.Pin  = GPIO_Pin_0 | GPIO_Pin_1;		//指定要初始化的IO,
	GPIO_InitStructure.Mode = GPIO_PullUp;	//指定IO的输入或输出方式,GPIO_PullUp,GPIO_HighZ,GPIO_OUT_OD,GPIO_OUT_PP
	GPIO_Inilize(GPIO_P3, &GPIO_InitStructure);//初始化
}

void UART_config(void) {
    COMx_InitDefine		COMx_InitStructure;					//结构定义
    COMx_InitStructure.UART_Mode      = UART_8bit_BRTx;	//模式, UART_ShiftRight,UART_8bit_BRTx,UART_9bit,UART_9bit_BRTx
    COMx_InitStructure.UART_BRT_Use   = BRT_Timer1;			//选择波特率发生器, BRT_Timer1, BRT_Timer2 (注意: 串口2固定使用BRT_Timer2)
    COMx_InitStructure.UART_BaudRate  = 115200ul;			//波特率, 一般 110 ~ 115200
    COMx_InitStructure.UART_RxEnable  = ENABLE;				//接收允许,   ENABLE或DISABLE
    COMx_InitStructure.BaudRateDouble = DISABLE;			//波特率加倍, ENABLE或DISABLE
    COMx_InitStructure.UART_Interrupt = ENABLE;				//中断允许,   ENABLE或DISABLE
    COMx_InitStructure.UART_Priority  = Priority_0;			//指定中断优先级(低到高) Priority_0,Priority_1,Priority_2,Priority_3
    COMx_InitStructure.UART_P_SW      = UART1_SW_P30_P31;	//切换端口,   UART1_SW_P30_P31,UART1_SW_P36_P37,UART1_SW_P16_P17,UART1_SW_P43_P44
    UART_Configuration(UART1, &COMx_InitStructure);		//初始化串口1 UART1,UART2,UART3,UART4
}



void sys_init() {
    GPIO_config();
    UART_config();

    Key_init();
    Motors_init();
    Track_init();
    EA = 1;
}

// 定义我的程序入口
void start() _task_ 0 {
    sys_init();

    os_create_task(1);
    os_delete_task(0);
}

void Key_on_keyup() {
    if(flag == 0) {
				printf("启动巡线\r\n");
        // 按一下启动巡线任务
				os_create_task(2);
    } else {
			printf("停止巡线\r\n");
				os_delete_task(2);
        // 再按停止
        Motors_stop();
    }
		flag = !flag;
}
void Key_on_keydown() {

}

// 扫描按键状态
void task1() _task_ 1 {
    while(1) {
        Key_scan();
        os_wait2(K_TMO, 4);
    }
}

// 实时获取线的坐标信息
void task2() _task_ 2 {
		int pos;
		printf("task2 start\r\n");
    while(1) {
				Track_get_position(&pos);
				
				// 判断坐标
				if(pos == 0) {
					// 直行
					Motors_forward(80);
				} else if(pos < 0) {
					// 左拐
					Motors_left(50);
				} else if(pos > 0) {
					Motors_right(50);
				}
        os_wait2(K_TMO, 1);
    }
}
