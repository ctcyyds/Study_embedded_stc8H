#include "config.h"
#include "GPIO.h"
#include "timer.h"
/*
LED呼吸灯
*/
//声明/替换
#define LED3 P15
#define LED_SW P45
	
	u8 freq = 10;
	u8 duty = 1;
	u8 cont = 0;
	u8 total=0;
	
//GPIO初始化
void GPIO_config(void) {
    GPIO_InitTypeDef GPIO_InitStructure;//结构定义
    GPIO_InitStructure.Mode=GPIO_PullUp;//IO模式，GPIO_PullUp,GPIO_HighZ,GPIO_OUT_OD,GPIO_OUT_PP
    GPIO_InitStructure.Pin=GPIO_Pin_5;//指定要初始化的IO
    GPIO_Inilize(GPIO_P4, &GPIO_InitStructure);//初始化

    GPIO_InitStructure.Mode=GPIO_PullUp;//IO模式，GPIO_PullUp,GPIO_HighZ,GPIO_OUT_OD,GPIO_OUT_PP
    GPIO_InitStructure.Pin=GPIO_Pin_5;//指定要初始化的IO
    GPIO_Inilize(GPIO_P1, &GPIO_InitStructure);//初始化
}

//timer初始化
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
void timer0_call(){
	//LED3 = !LED3;
	if(cont < duty){
		LED3 = 0;
	}else{
		LED3 = 1;
	}
	cont++;
	if(cont == freq){
		cont = 0;
	}
	if(total == 100){
		duty++;
		total = 0;
	}
	total++;
	if(duty > 10){
		duty = 0;
	}
}

int main() {
    //引用
    GPIO_config();
		TIMER_config();
    //中断总开关
    EA=1;

    LED_SW = 0;
    LED3 = 0;
	
    while(1) {
       
    }
}