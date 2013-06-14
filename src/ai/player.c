#include "ai.h"
#include "player.h"


int playerDirection(MOVABLE_ENTRY *p_e) {
	if (p.sliding)
		/* TODO: Insert sliding sprite directions */
		return p_e->x_velocity > 0 ? 0 : 0;
	if (p_e->y_velocity)
		/* Jumping. TODO: Insert jumping sprite directions */
		return (p.last_walk_dir);
	if (p_e->x_velocity)
		/* Running */
		return p.last_walk_dir + 2;
	return p.last_walk_dir;
}



void player(SPEEDOMAN *s, MOVABLE_ENTRY *self, MOVABLE_MSG msg) {
	switch (msg) {
		case MOVABLE_MSG_INIT:
			p.sliding = 0;
			p.last_walk_dir = 1;
			break;
		case MOVABLE_MSG_LOOP:
			if (d_keys_get().x && !self->y_velocity)
				self->y_velocity = atoi(d_stringtable_entry(s->config, "JUMP_ACCELERATION"));

			if (d_keys_get().left) {
				self->x_velocity = -20;
				p.last_walk_dir = 0;
			} else if (d_keys_get().right) {
				p.last_walk_dir = 1;
				self->x_velocity = 20;
			} else if (!p.sliding)
				self->x_velocity = 0;

			d_sprite_direction_set(self->sprite, playerDirection(self));
			break;
		default:
			break;
	}
	return;
}
