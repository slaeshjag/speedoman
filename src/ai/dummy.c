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
			s->var.meter_watch(s->var.meter.boss_health, 1, &self->hp, self->hp_max);
			break;
		case MOVABLE_MSG_LOOP:
			self->hit = 0;
			break;
		case MOVABLE_MSG_DESTROY:
			s->var.meter_watch(s->var.meter.boss_health, 0, NULL, 1);
			break;
		default:
			break;
	}

	return;
}
