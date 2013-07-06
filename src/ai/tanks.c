#include "../speedoman.h"


void player(SPEEDOMAN *, MOVABLE_ENTRY *, MOVABLE_MSG);

void tank_collision_check(SPEEDOMAN *s, MOVABLE_ENTRY *self, int w) {
	int box_x, box_y, box_w, box_h, i, match;

	d_sprite_hitbox(self->sprite, &box_x, &box_y, &box_w, &box_h);
	match = d_bbox_test(s->movable.bbox, self->x/1000 + box_x, self->y/1000 + box_y, box_w, box_h, s->movable.ai_coll_buf, ~0);

	for (i = 0; i < match; i++) {
		if (s->movable.movable[s->movable.ai_coll_buf[i]].ai != (void *) player)
			continue;
		self->hp = 0;
		if (w)
			s->var.progress.w_tank++;
		else
			s->var.progress.e_tank++;
		self->prevent_respawn = 1;
	}

	return;
}



void e_tank(SPEEDOMAN *s, MOVABLE_ENTRY *self, MOVABLE_MSG msg) {
	
	switch (msg) {
		case MOVABLE_MSG_INIT:
			self->gravity_effect = 1;
			self->type = 0;
			self->hp = 100;
			self->hp_max = 100;
			self->touch_dmg = 0;
			break;
		case MOVABLE_MSG_LOOP:
			self->hit = 1;
			tank_collision_check(s, self, 0);
			break;
		case MOVABLE_MSG_DESTROY:
			break;
		default:
			break;
	}

	return;
}


void w_tank(SPEEDOMAN *s, MOVABLE_ENTRY *self, MOVABLE_MSG msg) {
	
	switch (msg) {
		case MOVABLE_MSG_INIT:
			self->gravity_effect = 1;
			self->type = 0;
			self->hp = 100;
			self->hp_max = 100;
			self->touch_dmg = 0;
			break;
		case MOVABLE_MSG_LOOP:
			self->hit = 1;
			tank_collision_check(s, self, 1);
			break;
		case MOVABLE_MSG_DESTROY:
			break;
		default:
			break;
	}

	return;
}
