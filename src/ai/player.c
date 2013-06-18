#include "ai.h"
#include "player.h"

static int ypos_delta[] = {
	-15, -15, -15, -15
};


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

void playerShoot(SPEEDOMAN *s, MOVABLE_ENTRY *self) {
	int dir, y_pos, x_pos, hit_w, hit_h;

	d_sprite_hitbox(self->sprite, &x_pos, &y_pos, &hit_w, &hit_h);
	x_pos += self->x / 1000;
	y_pos = self->y / 1000;

	dir = playerDirection(self);
	y_pos += (d_sprite_height(self->sprite) + ypos_delta[dir]);

	if (dir & 1)
		x_pos += hit_w;

	s->var.bullet_spawn(0, (dir & 1) ? 1 : -1, self, x_pos, y_pos);

	return;
}


void playerHit(MOVABLE_ENTRY *self, int hp) {
	self->hit = 1;
	self->hit_time = 1000;
	self->hp -= hp;

	return;
}


void playerCollisionCheck(SPEEDOMAN *s, MOVABLE_ENTRY *self) {
	int box_x, box_y, box_w, box_h, i, match;
	
	if (self->hit)
		return;

	d_sprite_hitbox(self->sprite, &box_x, &box_y, &box_w, &box_h);
	match = d_bbox_test(s->movable.bbox, self->x/1000 + box_x, self->y/1000 + box_y, box_w, box_h, p.coll_test, ~0);

	for (i = 0; i < match && !self->hit; i++) {
		if (&s->movable.movable[p.coll_test[i]] == self)
			continue;
		playerHit(self, s->movable.movable[p.coll_test[i]].touch_dmg);
	}

	return;
}



void player(SPEEDOMAN *s, MOVABLE_ENTRY *self, MOVABLE_MSG msg) {
	DARNIT_KEYS keys = d_keys_zero();

	switch (msg) {
		case MOVABLE_MSG_INIT:
			p.sliding = 0;
			p.last_walk_dir = 1;
			self->gravity_effect = 1;
			s->var.camera_follow(self);
			self->hp_max = s->cfg.speedoman_hp;
			self->hp = s->cfg.speedoman_hp;
			self->hit = 0;
			self->type = 0;
			p.coll_test = malloc(s->movable.movables * sizeof(int));
			break;
		case MOVABLE_MSG_LOOP:
			d_sprite_direction_set(self->sprite, playerDirection(self));
			if (d_keys_get().x && !self->y_velocity)
				self->y_velocity = s->cfg.jump_acceleration;

			if (d_keys_get().left) {
				self->x_velocity = -s->cfg.speedoman_walk_speed;
				p.last_walk_dir = 0;
			} else if (d_keys_get().right) {
				p.last_walk_dir = 1;
				self->x_velocity = s->cfg.speedoman_walk_speed;
			} else if (!p.sliding)
				self->x_velocity = 0;
			if (self->hit) {
				self->hit_time -= d_last_frame_time();
				if (self->hit_time <= 0)
					self->hit_time = (self->hit = 0) - 1;
			}

			playerCollisionCheck(s, self);

			if (d_keys_get().l) {
				playerShoot(s, self);
				keys.l = 1;
				d_keys_set(keys);
			}
			break;
		case MOVABLE_MSG_DESTROY:
			free(p.coll_test);
		default:
			break;
	}
	return;
}
