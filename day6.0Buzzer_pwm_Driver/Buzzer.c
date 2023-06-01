#include "Buzzer.h"

u16 HZS[] = {
    1047, 1175, 1319, 1397, 1568, 1760, 1976, 2093};

void Buzzer_init()
{
    BUZZER_PIN_INIT();
}

void Buzzer_music(u8 note)
{ // 确定PWM的周期
    // 确定PWM的占空比
    // note --> hz
    u16 hz = HZS[note - 1];
    u16 PERIOD = (MAIN_Fosc / hz - 1);
    PWMx_InitDefine PWMx_InitStructure;
    // 总配置
    PWMx_InitStructure.PWM_Period =PERIOD; // 周期时间,   0~65535
    PWMx_InitStructure.PWM_DeadTime = 0;                  // 死区发生器设置, 0~255
    PWMx_InitStructure.PWM_EnoSelect = ENO5P;             // 输出通道选择,	ENO1P,ENO1N,ENO2P,ENO2N,ENO3P,ENO3N,ENO4P,ENO4N / ENO5P,ENO6P,ENO7P,ENO8P
    PWMx_InitStructure.PWM_PS_SW = PWM5_SW_P00;           // 切换端口
    // 具体PWM端口配置 PWM6
    PWMx_InitStructure.PWM5_Mode = CCMRn_PWM_MODE1; // 模式,		CCMRn_FREEZE,CCMRn_MATCH_VALID,CCMRn_MATCH_INVALID,CCMRn_ROLLOVER,CCMRn_FORCE_INVALID,CCMRn_FORCE_VALID,CCMRn_PWM_MODE1,CCMRn_PWM_MODE2
    PWMx_InitStructure.PWM5_Duty = PERIOD / 2;      // PWM6占空比时间, 0~Period

    // PWM6
    PWMx_InitStructure.PWM_CC5Enable = ENABLE; // 开启PWM4P输入捕获/比较输出,  ENABLE,DISABLE

    // PWM启动配置
    PWMx_InitStructure.PWM_MainOutEnable = ENABLE; // 主输出使能, ENABLE,DISABLE
    PWMx_InitStructure.PWM_CEN_Enable = ENABLE;    // 使能计数器, ENABLE,DISABLE
    PWM_Configuration(PWMB, &PWMx_InitStructure);  // 初始化PWM,  PWMA,PWMB
}