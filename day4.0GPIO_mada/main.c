#include "config.h"
#include "GPIO.h"
#include "delay.h"

void GPIO_config(void) {
    GPIO_InitTypeDef GPIO_InitStructure;//结构定义
    GPIO_InitStructure.Mode=GPIO_OUT_PP;//IO模式，GPIO_PullUp,GPIO_HighZ,GPIO_OUT_OD,GPIO_OUT_PP
    GPIO_InitStructure.Pin=GPIO_Pin_1;//指定要初始化的IO
    GPIO_Inilize(GPIO_P0, &GPIO_InitStructure);//初始化
}

int main(){
	GPIO_config();
	EA = 1;
	while(1){
		P01 = 1;
		delay_ms(250);
		delay_ms(250);
		P01 = 0;
		delay_ms(250);
		delay_ms(250);
	}
}