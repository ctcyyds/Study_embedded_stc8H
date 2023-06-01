#include "config.h"
#include "GPIO.h"
#include "delay.h"
#include "PWM.h"

//P0.1
#define PERIOD	(MAIN_Fosc / 1000 - 1)

void GPIO_config(void) {
    GPIO_InitTypeDef	GPIO_InitStructure;		//结构定义
    GPIO_InitStructure.Pin  = GPIO_Pin_1;		//指定要初始化的IO,
    GPIO_InitStructure.Mode = GPIO_OUT_PP;	//指定IO的输入或输出方式,GPIO_PullUp,GPIO_HighZ,GPIO_OUT_OD,GPIO_OUT_PP
    GPIO_Inilize(GPIO_P0, &GPIO_InitStructure);//初始化
}

void PWM_config(void) {

    PWMx_InitDefine		PWMx_InitStructure;
    // 总配置
    // (MAIN_Fosc / 1000 - 1) 周期计数值
    PWMx_InitStructure.PWM_Period   		= PERIOD;	//周期时间,   0~65535
    PWMx_InitStructure.PWM_DeadTime 		= 0;								//死区发生器设置, 0~255
    PWMx_InitStructure.PWM_EnoSelect		= ENO6P;	//输出通道选择,	ENO1P,ENO1N,ENO2P,ENO2N,ENO3P,ENO3N,ENO4P,ENO4N / ENO5P,ENO6P,ENO7P,ENO8P
    PWMx_InitStructure.PWM_PS_SW    		= PWM6_SW_P01;//切换端口

    // 具体PWM端口配置
    // pwm6
    PWMx_InitStructure.PWM6_Mode    		=	CCMRn_PWM_MODE2;	//模式,		CCMRn_FREEZE,CCMRn_MATCH_VALID,CCMRn_MATCH_INVALID,CCMRn_ROLLOVER,CCMRn_FORCE_INVALID,CCMRn_FORCE_VALID,CCMRn_PWM_MODE1,CCMRn_PWM_MODE2
    PWMx_InitStructure.PWM6_Duty    		= 0;			//PWM4占空比时间, 0~Period

    // pwm6
    PWMx_InitStructure.PWM_CC6Enable   = ENABLE;				//开启PWM6P输入捕获/比较输出,  ENABLE,DISABLE

    // PWM启动配置
    PWMx_InitStructure.PWM_MainOutEnable= ENABLE;				//主输出使能, ENABLE,DISABLE
    PWMx_InitStructure.PWM_CEN_Enable   = ENABLE;				//使能计数器, ENABLE,DISABLE
    PWM_Configuration(PWMB, &PWMx_InitStructure);				//初始化PWM,  PWMA,PWMB

}

int main() {
    PWMx_Duty duty;
    u8 d = 0;// 百分比值
    GPIO_config();
    PWM_config();
    EA = 1;

    while(1) {

        d ++;
				if(d >= 100) {
					d = 0;
				}
        // 占空比。（高电平的 计数值） 【0 - 100】
        duty.PWM6_Duty = d * PERIOD / 100 ;
        UpdatePwm(PWMB, &duty);
        delay_ms(10);
    }
}