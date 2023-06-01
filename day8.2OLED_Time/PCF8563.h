#ifndef ___PCF8563_H__
#define ___PCF8563_H__

#include "config.h"
#include "I2C.h"

//#define PCF8563_ENABLE_ALARM
//#define PCF8563_ENABLE_TIMER
#define PCF8563_ADDR		0x51
#define PCF8563_REG_CS2	0x01
#define PCF8563_REG_TD	0x02

#define I2C_WRITE(a,r,p,n)	I2C_WriteNbyte(a, r, p, n)
#define I2C_READ(a,r,p,n)		I2C_ReadNbyte(a, r, p, n)

typedef struct {
    u16 year;
    u8 month;
    u8 day;
    u8 weekday;
    u8 hour;
    u8 minute;
    u8 second;
} Clock_t;

typedef struct {
    u8 day;
    u8 weekday;
    u8 hour;
    u8 minute;
    u8 enable_day;
    u8 enable_weekday;
    u8 enable_hour;
    u8 enable_minute;
} Alarm_t;

//enum TimerFreq{ HZ4096 = 0, HZ64 = 1, HZ1 = 2, HZ1_60 = 3};

typedef enum {
    HZ4096 = 0, HZ64 = 1, HZ1 = 2, HZ1_60 = 3
} TimerFreq;


typedef struct {
    TimerFreq src_clk;
    u8 countdown;
} Timer_t;


void PCF8563_init();

//读时间
//写时间
//获取时间：年月日星期时分秒
void PCF8563_set_clock(Clock_t c);

void PCF8563_get_clock(Clock_t *c);

// 设置闹钟
void PCF8563_enable_alarm();
void PCF8563_set_alarm(Alarm_t a);
void PCF8563_get_alarm(Alarm_t *a);
void PCF8563_disable_alarm();

// 设置定时器
void PCF8563_enable_timer();
void PCF8563_set_timer(Timer_t t);
void PCF8563_get_timer(Timer_t *t);
void PCF8563_disable_timer();


// 驱动中，alarm的触发了中断，在中断中需要去清理状态值，最好放到驱动中实现
// 1. 驱动中要写中断函数
// 2.

// 当触发了alarm时的回调
#ifdef 	PCF8563_ENABLE_ALARM
extern void PCF8563_on_alarm();
#endif

// 当触发了timer时的回调
#ifdef PCF8563_ENABLE_TIMER
extern void PCF8563_on_timer();
#endif

#endif