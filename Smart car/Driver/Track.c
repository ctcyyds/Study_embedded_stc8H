#include "Track.h"

static int last_pos;
void Track_init() {
	TRACK_PIN_INIT();
}

void Track_get_state(u8 *state) {
	if(TRACK_0 == 0) {
		// b0 1
		*state |= 0x01;
	} else {
		// b0 0
		*state &= ~0x01;
	}
	if(TRACK_1 == 0) {
		// b1 1
		*state |= 0x02;
	} else {
		// b1 0
		*state &= ~0x02;
	}
	if(TRACK_2 == 0) {
		// b2 1
		*state |= 0x04;
	} else {
		// b2 0
		*state &= ~0x04;
	}
	if(TRACK_3 == 0) {
		// b3 1
		*state |= 0x08;
	} else {
		// b3 0
		*state &= ~0x08;
	}
	if(TRACK_4 == 0) {
		// b4 1
		*state |= 0x10;
	} else {
		// b4 0
		*state &= ~0x10;
	}
}

void Track_get_position(int *pos) {
	int sum = 0;
	int cnt = 0;
	if(TRACK_0 == 1) {
		sum += 64;
		cnt++;
	}
	if(TRACK_1 == 1) {
		sum += 32;
		cnt++;
	}
	if(TRACK_2 == 1) {
		sum += 0;
		cnt++;
	}
	if(TRACK_3 == 1) {
		sum += -32;
		cnt++;
	}
	if(TRACK_4 == 1) {
		sum += -64;
		cnt++;
	}
	
	if(cnt == 0) {
		// pos, 位置为上一次的位置
		*pos = last_pos;
	} else {
		last_pos = sum / cnt;
		*pos = last_pos;
	}
}