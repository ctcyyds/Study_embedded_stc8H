//////////////////////////////////////////////////////////////////////////////////
//������ֻ��ѧϰʹ�ã�δ���������ɣ��������������κ���;
//�о�԰����
//���̵�ַ��http://shop73023976.taobao.com/?spm=2013.1.0.0.M4PqC2
//
//  �� �� ��   : main.c
//  �� �� ��   : v2.0
//  ��    ��   : HuangKai
//  ��������   : 2014-0101
//  ����޸�   :
//  ��������   : OLED 4�ӿ���ʾ����(51ϵ��)
//              ˵��:
//              ----------------------------------------------------------------
//              GND    ��Դ��
//              VCC  ��5V��3.3v��Դ
//              SCL  P10��SCL��
//              SDA  P11��SDA��
//              RES  P12 ע��SPI�ӿ���ʾ���ĳ�IIC�ӿ�ʱ��Ҫ��RES����
//                           IIC�ӿ���ʾ���û������
//              ----------------------------------------------------------------
// �޸���ʷ   :
// ��    ��   :
// ��    ��   : HuangKai
// �޸�����   : �����ļ�
//��Ȩ���У�����ؾ���
//Copyright(C) �о�԰����2014/3/16
//All rights reserved
//******************************************************************************/
//#include "REG51.h"
#include "config.h"
#include "oled.h"
#include "bmp.h"

int main(void)
{
    //GPIO��ʼ��
    P0M1 = 0;
    P0M0 = 0;
    P1M1 = 0;
    P1M0 = 0;
    P2M1 = 0;
    P2M0 = 0;
    P3M1 = 0;
    P3M0 = 0;
    P4M1 = 0;
    P4M0 = 0;
    P5M1 = 0;
    P5M0 = 0;
    P6M1 = 0;
    P6M0 = 0;
    P7M1 = 0;
    P7M0 = 0;
    EA = 1;
    OLED_Init();//��ʼ��OLED
    OLED_ColorTurn(0);//0������ʾ��1 ��ɫ��ʾ
    OLED_DisplayTurn(0);//0������ʾ 1 ��Ļ��ת��ʾ
    while(1)
    {
        /**OLED_ShowChar(0,0,'a',16);
        OLED_ShowNum(0,2,2023,4,16);
        OLED_ShowString(0,4,"Hello word!",16);
        OLED_DrawBMP(0,0,128, 64,BMP2);**/
        OLED_ShowChinese(0,2,0,16);
        OLED_ShowChinese(10,2,1,16);
        OLED_ShowChinese(36,2,2,16);
        OLED_ShowChinese(56,2,3,16);
        OLED_ShowChinese(76,2,4,16);
        OLED_ShowChar(30,4,'Y',16);
        OLED_ShowChar(50,4,'Y',16);
        OLED_ShowChar(70,4,'D',16);
        OLED_ShowChar(90,4,'S',16);
    }

}
