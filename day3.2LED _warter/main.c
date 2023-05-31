#include "config.h"
#include "GPIO.h"
#include "delay.h"

/*
LED顺序点亮
*/
//声明/替换
#define LED1 P27
#define LED2 P26
#define LED3 P15
#define LED4 P14
#define LED5 P23
#define LED6 P22
#define LED7 P21
#define LED8 P20
#define LED_SW P45

//GPIO初始化
void GPIO_config(void) {
    GPIO_InitTypeDef GPIO_InitStructure;//结构定义
    GPIO_InitStructure.Mode=GPIO_PullUp;//IO模式，GPIO_PullUp,GPIO_HighZ,GPIO_OUT_OD,GPIO_OUT_PP
    GPIO_InitStructure.Pin=GPIO_Pin_5;//指定要初始化的IO
    GPIO_Inilize(GPIO_P4, &GPIO_InitStructure);//初始化

    GPIO_InitStructure.Mode=GPIO_PullUp;//IO模式，GPIO_PullUp,GPIO_HighZ,GPIO_OUT_OD,GPIO_OUT_PP
    GPIO_InitStructure.Pin=GPIO_Pin_7 | GPIO_Pin_6 | GPIO_Pin_3| GPIO_Pin_2 | GPIO_Pin_1 | GPIO_Pin_0;//指定要初始化的IO
    GPIO_Inilize(GPIO_P2, &GPIO_InitStructure);//初始化

    GPIO_InitStructure.Mode=GPIO_PullUp;//IO模式，GPIO_PullUp,GPIO_HighZ,GPIO_OUT_OD,GPIO_OUT_PP
    GPIO_InitStructure.Pin=GPIO_Pin_5 | GPIO_Pin_4;//指定要初始化的IO
    GPIO_Inilize(GPIO_P1, &GPIO_InitStructure);//初始化
}

int main() {
    int i;
    //引用
    GPIO_config();

    LED_SW = 0;

    while(1) {
        for(i = 0; i < 8; i++) {
            LED1 = i==0 ? 0 : 1;
            LED2 = i==1 ? 0 : 1;
            LED3 = i==2 ? 0 : 1;
            LED4 = i==3 ? 0 : 1;
            LED5 = i==4 ? 0 : 1;
            LED6 = i==5 ? 0 : 1;
            LED7 = i==6 ? 0 : 1;
            LED8 = i==7 ? 0 : 1;
						delay_ms(250);
        }
				
				for(i = 8; i >= 0; i--) {
            LED1 = i==0 ? 0 : 1;
            LED2 = i==1 ? 0 : 1;
            LED3 = i==2 ? 0 : 1;
            LED4 = i==3 ? 0 : 1;
            LED5 = i==4 ? 0 : 1;
            LED6 = i==5 ? 0 : 1;
            LED7 = i==6 ? 0 : 1;
            LED8 = i==7 ? 0 : 1;
						delay_ms(250);
        }
    }
}