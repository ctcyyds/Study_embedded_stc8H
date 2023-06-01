#include "stc.h"
#include "usb.h"
#include "usb_req_class.h"
#include "timer.h"
#include "config.h"

void sys_init();

void main()
{
    sys_init();
    usb_init();
    timer_init();

    EA = 1;
    
    while (1)
    {
        usb_class_in();
        
        if (f1ms)
        {
            f1ms = 0;
            scan_key();
        }
    }
}

void sys_init()
{
	P_SW2 |= 0x80;  //扩展寄存器(XFR)访问使能
	
    P3M0 &= ~0x03;
    P3M1 |= 0x03;
    
    IRC48MCR = 0x80;
    while (!(IRC48MCR & 0x01));
    
    USBCLK = 0x00;
    USBCON = 0x90;
}