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

#include "compare.h"

//========================================================================
// 函数:void	CMP_Inilize(CMP_InitDefine *CMPx)
// 描述: 定时器初始化程序.
// 参数: CMPx: 结构参数,请参考compare.h里的定义.
// 返回: 成功返回0, 空操作返回1,错误返回2.
// 版本: V1.0, 2012-10-22
//========================================================================
void	CMP_Inilize(CMP_InitDefine *CMPx)
{
	CMPCR1 = 0;
	CMPCR2 = CMPx->CMP_OutDelayDuty & 0x3f;										//比较结果变化延时周期数, 0~63
	if(CMPx->CMP_EN == ENABLE)				CMPCR1 |= CMPEN;				//允许比较器		ENABLE,DISABLE
	if(CMPx->CMP_RiseInterruptEn == ENABLE)	CMPCR1 |= PIE;		//允许上升沿中断	ENABLE,DISABLE
	if(CMPx->CMP_FallInterruptEn == ENABLE)	CMPCR1 |= NIE;		//允许下降沿中断	ENABLE,DISABLE
	if(CMPx->CMP_P_Select  == CMP_P_ADC)	CMPCR1 |= PIS;			//比较器输入正极性选择, CMP_P_P37: 选择内部P3.7做正输入, CMP_P_ADC: 由ADCIS[2:0]所选择的ADC输入端做正输入.
	if(CMPx->CMP_N_Select  == CMP_N_P36)	CMPCR1 |= NIS;			//比较器输入负极性选择, CMP_N_GAP: 选择内部BandGap电压BGv做负输入, CMP_N_P36: 选择外部P3.6做输入.
	if(CMPx->CMP_Outpt_En == ENABLE)		CMPCR1 |= CMPOE;			//允许比较结果输出到P3.4/P4.1,   ENABLE,DISABLE
	if(CMPx->CMP_InvCMPO     == ENABLE)		CMPCR2 |= INVCMPO;	//比较器输出取反, 	ENABLE,DISABLE
	if(CMPx->CMP_100nsFilter == DISABLE)	CMPCR2 |= DISFLT;		//内部0.1uF滤波,  	ENABLE,DISABLE
	P_SW2 = (P_SW2 & ~(0x08)) | CMPx->CMP_P_SW;
	if(CMPx->CMP_Priority > Priority_3)	return;		//错误
	CMP_Priority(CMPx->CMP_Priority);		//指定中断优先级(低到高) Priority_0,Priority_1,Priority_2,Priority_3
}

/********************* UART1中断函数************************/
void CMP_int (void) interrupt CMP_VECTOR
{
	CMPCR1 &= ~CMPIF;			//清除中断标志
	P47 = CMPCR1 & 0x01;	//中断方式读取比较器比较结果
}
