#ifndef __TRACK_H__
#define __TRACK_H__

#include "config.h"

#define TRACK_0	P47
#define TRACK_1	P06
#define TRACK_2 P50
#define TRACK_3	P32
#define TRACK_4 P33

#define TRACK_PIN_INIT() { P4M0 &= ~0x80; P4M1 &= ~0x80; P5M0 &= ~0x01; P5M1 &= ~0x01; P0M0 &= ~0x40; P0M1 &= ~0x40; P3M0 &= ~0x0c; P3M1 &= ~0x0c; }

void Track_init();
void Track_get_state(u8 *state);
void Track_get_position(int *pos);


#endif