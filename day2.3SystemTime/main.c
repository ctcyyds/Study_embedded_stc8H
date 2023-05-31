/*P53 高低变化*/
#include "config.h"
#include "GPIO.h"
/*
IO初始化
*/
void GPIO_config(void) {
    GPIO_InitTypeDef GPIO_InitStructure;//结构定义
    GPIO_InitStructure.Mode=GPIO_PullUp;//IO模式，GPIO_PullUp,GPIO_HighZ,GPIO_OUT_OD,GPIO_OUT_PP
    GPIO_InitStructure.Pin=GPIO_Pin_3;//指定要初始化的IO
    GPIO_Inilize(GPIO_P5, &GPIO_InitStructure);//初始化
}
int main() {
    GPIO_config();
    while(1) {
        P53 =! P53;
        NOP1();
    }
}