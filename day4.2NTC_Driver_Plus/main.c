#include "config.h"
#include "GPIO.h"
#include "delay.h"
#include "ADC.h"
#include "UART.h"
#include "stdio.h"
#include "NTC.h"

void GPIO_config(void) {
    GPIO_InitTypeDef GPIO_InitStructure;//结构定义
    GPIO_InitStructure.Mode=GPIO_PullUp;//IO模式，GPIO_PullUp,GPIO_HighZ,GPIO_OUT_OD,GPIO_OUT_PP
    GPIO_InitStructure.Pin=GPIO_Pin_0 | GPIO_Pin_1;//指定要初始化的IO
    GPIO_Inilize(GPIO_P3, &GPIO_InitStructure);//初始化
}

void ADC_config(void)
{
    ADC_InitTypeDef		ADC_InitStructure;		//结构定义
    ADC_InitStructure.ADC_SMPduty   = 31;		//ADC 模拟信号采样时间控制, 0~31（注意： SMPDUTY 一定不能设置小于 10）
    ADC_InitStructure.ADC_CsSetup   = 0;		//ADC 通道选择时间控制 0(默认),1
    ADC_InitStructure.ADC_CsHold    = 1;		//ADC 通道选择保持时间控制 0,1(默认),2,3
    ADC_InitStructure.ADC_Speed     = ADC_SPEED_2X1T;		//设置 ADC 工作时钟频率	ADC_SPEED_2X1T~ADC_SPEED_2X16T
    ADC_InitStructure.ADC_Power     = ENABLE;				//ADC功率允许/关闭	ENABLE,DISABLE
    ADC_InitStructure.ADC_AdjResult = ADC_RIGHT_JUSTIFIED;	//ADC结果调整,	ADC_LEFT_JUSTIFIED,ADC_RIGHT_JUSTIFIED
    ADC_InitStructure.ADC_Priority    = Priority_0;			//指定中断优先级(低到高) Priority_0,Priority_1,Priority_2,Priority_3
    ADC_InitStructure.ADC_Interrupt = DISABLE;			//中断允许	ENABLE,DISABLE
    ADC_Inilize(&ADC_InitStructure);					//初始化
    ADC_PowerControl(ENABLE);							//单独的ADC电源操作函数, ENABLE或DISABLE
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

char putchar (char dat) {
    TX1_write2buff(dat);
    return dat;
}

int main() {
	int t;
    GPIO_config();
    UART_config();
		ADC_config();
		//初始化驱动
		NTC_init();
    EA = 1;
    while(1) {
				//获取温度，调用方法
				t = NTC_get_temperature();
				
        printf("%d\r\n",t);

        delay_ms(250);
        delay_ms(250);
        delay_ms(250);
        delay_ms(250);
    }
}