#ifndef ___MOTORS_H__
#define ___MOTORS_H__

#include "config.h"
#include "PWM.h"

#define LQF	P16
#define LQB	P17
#define LHF	P21
#define LHB	P20
#define RQF	P14
#define RQB	P15
#define RHF	P22
#define RHB	P23

#define PERIOD (MAIN_Fosc / 1000 - 1)

//pullup
#define MOTORS_PIN_INIT() { P1M0 &= ~0xf0; P1M1 &= ~0xf0; P2M0 &= ~0x0f; P2M1 &= ~0x0f;}


void Motors_init();


void Motors_forward(u8 speed);
void Motors_backward(u8 speed);
void Motors_left(u8 speed);
void Motors_right(u8 speed);
void Motors_around(u8 speed);
void Motors_stop();


#endif