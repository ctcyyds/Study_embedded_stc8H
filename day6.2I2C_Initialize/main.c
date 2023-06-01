#include "config.h"
#include "GPIO.h"
#include "delay.h"
#include "I2C.h"

// 引脚初始化
// P32 P33 GPIO_OUT_OD
void GPIO_config(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;              // 结构定义
    GPIO_InitStructure.Mode = GPIO_OUT_OD;            // IO模式，GPIO_PullUp,GPIO_HighZ,GPIO_OUT_OD,GPIO_OUT_PP
    GPIO_InitStructure.Pin = GPIO_Pin_3 | GPIO_Pin_2; // 指定要初始化的IO
    GPIO_Inilize(GPIO_P3, &GPIO_InitStructure);       // 初始化
}

// I2C配置
void I2C_config(void)
{
    I2C_InitTypeDef I2C_InitStructure;
    I2C_InitStructure.I2C_Mode = I2C_Mode_Master; // 主从选择   I2C_Mode_Master, I2C_Mode_Slave
    I2C_InitStructure.I2C_Enable = ENABLE;        // I2C功能使能,   ENABLE, DISABLE
    I2C_InitStructure.I2C_MS_WDTA = DISABLE;      // 主机使能自动发送,  ENABLE, DISABLE
    I2C_InitStructure.I2C_MS_Interrupt = DISABLE; // 使能主机模式中断,  ENABLE, DISABLE
    I2C_InitStructure.I2C_Speed = 13;             // 总线速度=Fosc/2/(Speed*2+4),      0~63
    I2C_InitStructure.I2C_IoUse = I2C_P33_P32;    // IO口切换   I2C_P14_P15, I2C_P24_P25, I2C_P33_P32

    I2C_Init(&I2C_InitStructure);
}

int main()
{
    u8 number;
    u8 p[2];
    u8 addr;
    u8 reg;
    EA = 1;
    GPIO_config();
    I2C_config();
    /**
     * 从设备的两个地址
     * 1.设备地址 0xA2
     * 1.1读地址0xA3  1读
     * 1.2写地址0XA2  0写
     * 2.寄存器地址
     */
    while (1)
    {
        // 这里的addr为寄存器地址
        // ReadNbyte(addr, p, 2);
        addr = 0x51;
        reg = 0x02;
        number = 1;
        I2C_ReadNbyte(addr, reg, p, 1);
        P[0];
        P[1];
    }
}
