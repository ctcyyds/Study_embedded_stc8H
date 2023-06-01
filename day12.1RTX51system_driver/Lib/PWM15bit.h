/*---------------------------------------------------------------------*/
/* --- STC MCU Limited ------------------------------------------------*/
/* --- STC 1T Series MCU Demo Programme -------------------------------*/
/* --- Mobile: (86)13922805190 ----------------------------------------*/
/* --- Fax: 86-0513-55012956,55012947,55012969 ------------------------*/
/* --- Tel: 86-0513-55012928,55012929,55012966 ------------------------*/
/* --- Web: www.STCMCU.com --------------------------------------------*/
/* --- Web: www.STCMCUDATA.com  ---------------------------------------*/
/* --- QQ:  800003751 -------------------------------------------------*/
/* 如果要在程序中使用此代码,请在程序中注明使用了STC的资料及程序            */
/*---------------------------------------------------------------------*/

#ifndef	__PWM15BIT_H
#define	__PWM15BIT_H

#include	"config.h"

#define	PWM0				0
#define	PWM1				1
#define	PWM2				2
#define	PWM3				3
#define	PWM4				4
#define	PWM5				5

#define	PWM00				0
#define	PWM01				1
#define	PWM02				2
#define	PWM03				3
#define	PWM04				4
#define	PWM05				5
#define	PWM06				6
#define	PWM07				7
#define	PWM10				8
#define	PWM11				9
#define	PWM12				10
#define	PWM13				11
#define	PWM14				12
#define	PWM15				13
#define	PWM16				14
#define	PWM17				15
#define	PWM20				16
#define	PWM21				17
#define	PWM22				18
#define	PWM23				19
#define	PWM24				20
#define	PWM25				21
#define	PWM26				22
#define	PWM27				23
#define	PWM30				24
#define	PWM31				25
#define	PWM32				26
#define	PWM33				27
#define	PWM34				28
#define	PWM35				29
#define	PWM36				30
#define	PWM37				31
#define	PWM40				32
#define	PWM41				33
#define	PWM42				34
#define	PWM43				35
#define	PWM44				36
#define	PWM45				37
#define	PWM46				38
#define	PWM47				39
#define	PWM50				40
#define	PWM51				41
#define	PWM52				42
#define	PWM53				43
#define	PWM54				44
#define	PWM55				45
#define	PWM56				46
#define	PWM57				47

#define	PWMn_CLK_SYS			0
#define	PWMn_CLK_TM2			1

typedef struct
{
	u8	PWM_Enable;	//PWM使能,  ENABLE, DISABLE
	
	u8	PWM_Interrupt;	//计数器归零中断使能,  ENABLE, DISABLE
	u8	PWM_Counter;		//计数器使能,  ENABLE, DISABLE
	u8	PWM_Clock_Sel;	//时钟源选择,  PWMn_CLK_SYS, PWMn_CLK_TM2
	u8	PWM_Clock_PS;		//系统时钟分频参数,  0~15
	u16	PWM_Period;			//PWM周期,  0~0x7fff
} PWM15_InitTypeDef;

void	PWM15_Init(u8 PWM_id, PWM15_InitTypeDef *PWMx);
u8	PWMChannelCtrl(u8 PWM_id, u8 pwm_eno, u8 pwm_ini, u8 pwm_eni, u8 pwm_ent2i, u8 pwm_ent1i);
u8	PWMLevelSet(u8 PWM_id, u8 pwm_hldl, u8 pwm_hldh);
u8	PWM15Duty(u8 PWM_id, u16 dutyL, u16 dutyH);

#endif

