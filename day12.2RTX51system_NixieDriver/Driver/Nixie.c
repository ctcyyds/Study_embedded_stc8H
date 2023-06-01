#include "Nixie.h"


u8 code LED_TABLE[] = 
{
	0xC0,0xF9,0xA4,0xB0,0x99,0x92,0x82,0xF8,0x80,0x90,0x7F,0xBF,
    0x79,0x24,0x30,0x19,0x12,0x02,0x78,0x00,0x10,
	0x88,0x83,0xC6,0xA1,0x86,0x8E,0x89,0xF1,0xC7,0x8C,0x98,0xC1
};

// 初始化
void Nixie_init() {
    NIXIE_PIN_INIT();
}

// 显示数字
// index: 位置
// dat: 内容
void Nixie_show(u8 index, u8 dat) {
	  u8 i;
    for(i = 0; i < 8; i++) {
        // 1 0 1 0 1 0 1 0
        // 操作了一个bit

        //printf("%d \r\n", (int)(a & 0x80));
        if(LED_TABLE[dat] & (1 << (7 - i))) {
            // 高电平
            NIX_DI = 1;
        } else {
            // 低电平
            NIX_DI = 0;
        }
        // 1 0 1 0 1 0 1 0
        // 0 1 0 1 0 1 0 0
        // a = a << 1;
        //a <<= 1;
        NIX_SCK = 0;
        NOP2();
        NIX_SCK = 1;
        NOP2();
    }
		
		// 0x01	0			1 << 0	 0x01
		// 0x02	1			1 << 1	 0x02
		// 0x04	2			1 << 2	 0x04
		//	?   n			1 << n		
		// 
    for(i = 0; i < 8; i++) {
        // 1 0 1 0 1 0 1 0
        // 操作了一个bit
        if((1 << index) & (1 << (7 - i))) {
            // 高电平
            NIX_DI = 1;
        } else {
            // 低电平
            NIX_DI = 0;
        }

        // 1 0 1 0 1 0 1 0
        // 0 1 0 1 0 1 0 0
        //b = b << 1;
        //b <<= 1;
        NIX_SCK = 0;
        NOP2();
        NIX_SCK = 1;
        NOP2();
    }

    // 锁存
    NIX_RCK = 0;
    NOP2();
    NIX_RCK = 1;
    NOP2();
}