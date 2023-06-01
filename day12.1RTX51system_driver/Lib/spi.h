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

#ifndef	__SPI_H
#define	__SPI_H

#include	"config.h"

#define	SPI_BUF_LENTH	128
#define	SPI_BUF_type	xdata


#define	SPI_Mode_Master		1
#define	SPI_Mode_Slave		0
#define	SPI_CPOL_High		1
#define	SPI_CPOL_Low		0
#define	SPI_CPHA_1Edge		1
#define	SPI_CPHA_2Edge		0
#define	SPI_Speed_4			0
#define	SPI_Speed_16		1
#define	SPI_Speed_64		2
#define	SPI_Speed_128		3
#define	SPI_MSB				0
#define	SPI_LSB				1
#define	SPI_P12_P13_P14_P15	(0<<2)
#define	SPI_P22_P23_P24_P25	(1<<2)
#define	SPI_P54_P40_P41_P43	(2<<2)
#define	SPI_P35_P34_P33_P32	(3<<2)

typedef struct
{
	u8	SPI_Module;		//ENABLE,DISABLE
	u8	SPI_SSIG;		//ENABLE, DISABLE
	u8	SPI_FirstBit;	//SPI_MSB, SPI_LSB
	u8	SPI_Mode;		//SPI_Mode_Master, SPI_Mode_Slave
	u8	SPI_CPOL;		//SPI_CPOL_High,   SPI_CPOL_Low
	u8	SPI_CPHA;		//SPI_CPHA_1Edge,  SPI_CPHA_2Edge
	u8	SPI_Interrupt;		//ENABLE,DISABLE
	u8	SPI_Speed;		//SPI_Speed_4,      SPI_Speed_16,SPI_Speed_64,SPI_Speed_128
	u8	SPI_IoUse;		//SPI_P12_P13_P14_P15, SPI_P22_P23_P24_P25, SPI_P54_P40_P41_P43, SPI_P35_P34_P33_P32
} SPI_InitTypeDef;



extern	u8 	SPI_RxCnt;
extern	u8 	SPI_RxTimerOut;
extern	u8 	SPI_BUF_type SPI_RxBuffer[SPI_BUF_LENTH];


void	SPI_Init(SPI_InitTypeDef *SPIx);
void	SPI_SetMode(u8 mode);
void	SPI_WriteByte(u8 dat);

#endif

