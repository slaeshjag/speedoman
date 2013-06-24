#include "ai.h"
#include "dummy.h"



void shellthing(SPEEDOMAN *s, MOVABLE_ENTRY *self, MOVABLE_MSG msg) {

	switch (msg) {
		case MOVABLE_MSG_INIT:
			self->gravity_effect = 1;
			self->type = 0;
			self->hp = 100;
			self->hp_max = 100;
			self->touch_dmg = 100;
			self->x_velocity = -40;
			self->y_velocity = 0;
			d_sprite_direction_set(self->sprite, 0);
			break;
		case MOVABLE_MSG_LOOP:
			self->hit = 0;
			if (self->x_velocity < 0) {
				if (!(s->var.movable_tile_coll(self, -1, 1) & COLLISION_TOP)) {
					d_sprite_direction_set(self->sprite, 1);
					self->x_velocity = 40;
				}
			} else if (self->x_velocity > 0) {
				if (!(s->var.movable_tile_coll(self, 1, 1) & COLLISION_TOP)) {
					d_sprite_direction_set(self->sprite, 0);
					self->x_velocity = -40;
				}
			}


			break;
		case MOVABLE_MSG_DESTROY:
			break;
		default:
			break;
	}

	return;
}
