#include "config.h"
#include "GPIO.h"
#include "PWM.h"
#include "delay.h"
//�滻
#include LED_SW P45
#define LED3 P15

//GPIO��ʼ��
void GPIO_config(void) {
    GPIO_InitTypeDef GPIO_InitStructure;//�ṹ����
    GPIO_InitStructure.Mode=GPIO_PullUp;//IOģʽ��GPIO_PullUp,GPIO_HighZ,GPIO_OUT_OD,GPIO_OUT_PP
    GPIO_InitStructure.Pin=GPIO_Pin_5;//ָ��Ҫ��ʼ����IO
    GPIO_Inilize(GPIO_P4, &GPIO_InitStructure);//��ʼ��

    GPIO_InitStructure.Mode=GPIO_PullUp;//IOģʽ��GPIO_PullUp,GPIO_HighZ,GPIO_OUT_OD,GPIO_OUT_PP
    GPIO_InitStructure.Pin=GPIO_Pin_5;//ָ��Ҫ��ʼ����IO
    GPIO_Inilize(GPIO_P1, &GPIO_InitStructure);//��ʼ��
}

//PWM
void	PWM_config(void)
{
    PWMx_InitDefine		PWMx_InitStructure;
		//PWM������
    PWMx_InitStructure.PWM_Period   		= MAIN_Fosc / 1000 - 1;	//����ʱ��,   0~65535
    PWMx_InitStructure.PWM_DeadTime 		= 0;								//��������������, 0~255
    PWMx_InitStructure.PWM_EnoSelect		= ENO4P | ENO4N;	//���ͨ��ѡ��,	ENO1P,ENO1N,ENO2P,ENO2N,ENO3P,ENO3N,ENO4P,ENO4N / ENO5P,ENO6P,ENO7P,ENO8P
		//PWM�˿�����
    PWMx_InitStructure.PWM4_Mode    		=	CCMRn_PWM_MODE1;	//ģʽ,		CCMRn_FREEZE,CCMRn_MATCH_VALID,CCMRn_MATCH_INVALID,CCMRn_ROLLOVER,CCMRn_FORCE_INVALID,CCMRn_FORCE_VALID,CCMRn_PWM_MODE1,CCMRn_PWM_MODE2
    PWMx_InitStructure.PWM4_SetPriority	= Priority_0;			//ָ���ж����ȼ�(�͵���) Priority_0,Priority_1,Priority_2,Priority_3
    PWMx_InitStructure.PWM_PS_SW    		=	PWM4_SW_P26_P27;//�л��˿�
    PWMx_InitStructure.PWM4_Duty    		= PWMA_Duty.PWM4_Duty;	//PWM4ռ�ձ�ʱ��, 0~Period

    PWMx_InitStructure.PWM_CC4Enable   = ENABLE;				//����PWM4P���벶��/�Ƚ����,  ENABLE,DISABLE
    PWMx_InitStructure.PWM_CC4NEnable  = ENABLE;				//����PWM4N���벶��/�Ƚ����,  ENABLE,DISABLE
		//��������
    PWMx_InitStructure.PWM_MainOutEnable= ENABLE;				//�����ʹ��, ENABLE,DISABLE
    PWMx_InitStructure.PWM_CEN_Enable   = ENABLE;				//ʹ�ܼ�����, ENABLE,DISABLE
    PWM_Configuration(PWMA, &PWMx_InitStructure);				//��ʼ��PWM,  PWMA,PWMB
}

int main() {
    EA = 1;
    P45 = 0;
    //����
    GPIO_config();
    while(1) {

    }
}