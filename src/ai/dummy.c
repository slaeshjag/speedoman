#include "ai.h"
#include "dummy.h"



void dummy(SPEEDOMAN *s, MOVABLE_ENTRY *self, MOVABLE_MSG msg) {

	switch (msg) {
		case MOVABLE_MSG_INIT:
			self->gravity_effect = 1;
			self->type = 0;
			self->hp = 100;
			self->hp_max = 100;
			self->touch_dmg = 10;
			break;
		case MOVABLE_MSG_LOOP:
			self->hit = 0;
			break;
		default:
			break;
	}

	return;
}
