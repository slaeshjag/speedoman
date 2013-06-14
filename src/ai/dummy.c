#include "ai.h"
#include "dummy.h"



void dummy(SPEEDOMAN *s, MOVABLE_ENTRY *self, MOVABLE_MSG msg) {
	switch (msg) {
		case MOVABLE_MSG_INIT:
			self->gravity_effect = 1;
			break;
		default:
			break;
	}

	return;
}
