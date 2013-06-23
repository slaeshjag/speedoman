#include "ai.h"
#include "player.h"

static int ypos_delta[] = {
	-15, -15, -15, -15, -15, -15, -15, -15, -17, -17
};


int playerDirection(MOVABLE_ENTRY *p_e) {
	int shooting;

	shooting = ((p.shoot_start - d_last_frame_time()) > 0) ? 1 : 0;
		
	if (p.sliding)
		/* TODO: Insert sliding sprite directions */
		return p_e->x_velocity > 0 ? 0 : 0;
	if (p_e->y_velocity)
		/* Jumping. TODO: Insert jumping sprite directions */
		return p.last_walk_dir + ((shooting) ? /* TODO: Insert jump shoot sprite */ 6 : 6);
	if (p_e->x_velocity)
		/* Running */
		return p.last_walk_dir + ((shooting) ? 4 : 2);
	
	return p.last_walk_dir + ((shooting) ? 8 : 0);
}

void playerShoot(SPEEDOMAN *s, MOVABLE_ENTRY *self) {
	int dir, y_pos, x_pos, hit_w, hit_h;

	d_sprite_hitbox(self->sprite, &x_pos, &y_pos, &hit_w, &hit_h);
	x_pos += self->x / 1000;
	y_pos = self->y / 1000;

	dir = playerDirection(self);
	y_pos += (d_sprite_height(self->sprite) + ypos_delta[dir]);
	p.shoot_start = 500;

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


void playerFixHitbox(SPEEDOMAN *s, MOVABLE_ENTRY *self) {
	int dir, box1_x, box2_x, box1_y, box2_y, box1_w, box2_w, box1_h, box2_h, diff;

	dir = playerDirection(self);
	if (dir == p.last_dir)
		return;
	p.last_dir = dir;
	d_sprite_hitbox(self->sprite, &box1_x, &box1_y, &box1_w, &box1_h);
	d_sprite_direction_set(self->sprite, dir);
	d_sprite_hitbox(self->sprite, &box2_x, &box2_y, &box2_w, &box2_h);
	diff = (((box2_y + box2_h) - (box1_y + box1_h)));
	self->x -= (((box2_x - box1_x) + (box2_w - box1_w)) * 1000);
	self->y -= (diff * 1000);

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
			p.last_dir = 1;
			self->gravity_effect = 1;
			s->var.camera_follow(self);
			self->hp_max = s->cfg.speedoman_hp;
			self->hp = s->cfg.speedoman_hp;
			self->hit = 0;
			self->type = 0;
			p.shoot_start = 0;
			s->var.meter_watch(s->var.meter.player_health, 1, &self->hp, self->hp_max);
			s->player = (int) (self - s->movable.movable) / sizeof(MOVABLE_ENTRY);
			p.coll_test = malloc(s->movable.movables * sizeof(int));
			break;
		case MOVABLE_MSG_LOOP:
			playerFixHitbox(s, self);
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

			p.shoot_start -= d_last_frame_time();
			playerCollisionCheck(s, self);

			if (d_keys_get().l) {
				playerShoot(s, self);
				keys.l = 1;
				d_keys_set(keys);
			}
			break;
		case MOVABLE_MSG_DESTROY:
			s->var.meter_watch(s->var.meter.player_health, 0, NULL, 1);
			free(p.coll_test);
		default:
			break;
	}
	return;
}
