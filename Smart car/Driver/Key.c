#include "Key.h"

static u8 state = 1;

void Key_init() {
	KEY_PIN_INIT();
}

void Key_scan() {
	if(KEY == KEY_DOWN && state == KEY_UP) {
		//°´ÏÂ
		state = KEY_DOWN;
		Key_on_keydown();
	} else if(KEY == KEY_UP && state == KEY_DOWN){
		//Ì§Æð
		state = KEY_UP;
		Key_on_keyup();
	}
}