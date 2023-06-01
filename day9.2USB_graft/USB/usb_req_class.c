/*---------------------------------------------------------------------*/
/* --- STC MCU Limited ------------------------------------------------*/
/* --- STC 1T Series MCU Demo Programme -------------------------------*/
/* --- Mobile: (86)13922805190 ----------------------------------------*/
/* --- Fax: 86-0513-55012956,55012947,55012969 ------------------------*/
/* --- Tel: 86-0513-55012928,55012929,55012966 ------------------------*/
/* --- Web: www.STCMCU.com --------------------------------------------*/
/* --- Web: www.STCMCUDATA.com  ---------------------------------------*/
/* --- QQ:  800003751 -------------------------------------------------*/
/* 如果要在程序中使用此代码,请在程序中注明使用了STC的资料及程序        */
/*---------------------------------------------------------------------*/

#include "stc.h"
#include "usb.h"
#include "usb_req_class.h"

BYTE bHidIdle;
BYTE bKeyCode = 0;
BYTE bKeyDebounce = 0;
BOOL fKeyOK;

sbit LED_NUM        = P6^7;
sbit LED_CAPS       = P6^6;
sbit LED_SCROLL     = P6^5;

void usb_req_class()
{
    switch (Setup.bRequest)
    {
    case GET_REPORT:
        usb_get_report();
        break;
    case SET_REPORT:
        usb_set_report();
        break;
    case GET_IDLE:
        usb_get_idle();
        break;
    case SET_IDLE:
        usb_set_idle();
        break;
    case GET_PROTOCOL:
        usb_get_protocol();
        break;
    case SET_PROTOCOL:
        usb_set_protocol();
        break;
    default:
        usb_setup_stall();
        return;
    }
}

void usb_get_report()
{
    if ((DeviceState != DEVSTATE_CONFIGURED) ||
        (Setup.bmRequestType != (IN_DIRECT | CLASS_REQUEST | INTERFACE_RECIPIENT)))
    {
        usb_setup_stall();
        return;
    }

    Ep0State.pData = UsbBuffer;
    Ep0State.wSize = Setup.wLength;

    usb_setup_in();
}

void usb_set_report()
{
    if ((DeviceState != DEVSTATE_CONFIGURED) ||
        (Setup.bmRequestType != (OUT_DIRECT | CLASS_REQUEST | INTERFACE_RECIPIENT)))
    {
        usb_setup_stall();
        return;
    }

    Ep0State.pData = UsbBuffer;
    Ep0State.wSize = Setup.wLength;

    usb_setup_out();
}

void usb_get_idle()
{
    if ((DeviceState != DEVSTATE_CONFIGURED) ||
        (Setup.bmRequestType != (IN_DIRECT | CLASS_REQUEST | INTERFACE_RECIPIENT)))
    {
        usb_setup_stall();
        return;
    }

    Ep0State.pData = &bHidIdle;
    Ep0State.wSize = 1;

    usb_setup_in();
}

void usb_set_idle()
{
    if ((DeviceState != DEVSTATE_CONFIGURED) ||
        (Setup.bmRequestType != (OUT_DIRECT | CLASS_REQUEST | INTERFACE_RECIPIENT)))
    {
        usb_setup_stall();
        return;
    }

    bHidIdle = Setup.wValueH;

    usb_setup_status();
}

void usb_get_protocol()
{
    usb_setup_stall();
}

void usb_set_protocol()
{
    usb_setup_stall();
}

void usb_class_out()
{
    BYTE led;
    
    if (usb_bulk_intr_out(UsbBuffer, 1) == 1)
    {
        P4M0 &= ~0x01;
        P4M1 &= ~0x01;
        P6M0 &= ~0xe0;
        P6M1 &= ~0xe0;
        P40 = 0;
        
        led = UsbBuffer[0];
        LED_NUM = !(led & 0x01);
        LED_CAPS = !(led & 0x02);
        LED_SCROLL = !(led & 0x04);
    }
}

void usb_class_in()
{
    BYTE key[8];
    BYTE i;
    
    if (DeviceState != DEVSTATE_CONFIGURED)
        return;

    if (!UsbInBusy && fKeyOK)
    {
        fKeyOK = 0;

        key[0] = 0;
        key[1] = 0;
        key[2] = 0;
        key[3] = 0;
        key[4] = 0;
        key[5] = 0;
        key[6] = 0;
        key[7] = 0;

        switch (bKeyCode)
        {
        case 0xfe:  key[2] = 0x1e; break;
        case 0xfd:  key[2] = 0x1f; break;
        case 0xfb:  key[2] = 0x20; break;
        case 0xf7:  key[2] = 0x21; break;
        case 0xef:  key[2] = 0x22; break;
        case 0xdf:  key[2] = 0x23; break;
        case 0xbf:  key[2] = 0x24; break;
        case 0x7f:  key[2] = 0x25; break;
        }
        
        IE2 &= ~0x80;   //EUSB = 0;
        UsbInBusy = 1;
        usb_write_reg(INDEX, 1);
        for (i=0; i<8; i++)
        {
            usb_write_reg(FIFO1, key[i]);
        }
        usb_write_reg(INCSR1, INIPRDY);
        IE2 |= 0x80;    //EUSB = 1;
    }
}

void scan_key()
{
    BYTE key;
    
    P0M0 = 0x00;
    P0M1 = 0x00;
    
    key = 0;
    P0 = 0xff;
    P06 = 0;
    _nop_();
    _nop_();
    key |= P0 & 0x0f;
    P06 = 1;
    P07 = 0;
    _nop_();
    _nop_();
    key |= (P0 & 0x0f) << 4;
    P07 = 1;
    
    if (key != bKeyCode)
    {
        bKeyCode = key;
        bKeyDebounce = 20;
    }
    else
    {
        if (bKeyDebounce)
        {
            bKeyDebounce--;
            if (bKeyDebounce == 0)
            {
                fKeyOK = 1;
            }
        }
    }
    
}

