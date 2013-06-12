#include "speedoman.h"


int movableInit() {
	s->movable.movable = NULL;
	s->movable.movables = 0;

	s->movable.ai = d_dynlib_open(d_stringtable_entry(s->config, "AI_LIB"));
	s->movable.ai_table = d_stringtable_open(d_stringtable_entry(s->config, "AI_TABLE"));
	
	if (!s->movable.ai || !s->movable.ai_table)
		return -1;
	d_stringtable_section_load(s->movable.ai, "INDEX");

	return 0;
}


int movableLoad() {
	int i;
	MOVABLE_ENTRY *entry;

	for (i = 0; i < s->movable.movables; i++)
		d_sprite_free(s->movable.movable[i].sprite);
	if (!(entry = realloc(s->movable.movable, sizeof(MOVABLE_ENTRY) * s->active_level->objects))) {
		free(s->movable.movable);
		d_dynlib_close(s->movable.ai);
		movableInit();
		return -1;
	}

	s->movable.movable = entry;
	s->movable.movables = s->active_level->objects;

	for (i = 0; i < s->movable.movables; i++) {
		s->movable.movable[i].sprite = d_sprite_load(d_map_prop(s->active_level->object[i].ref, "sprite"), 0, DARNIT_PFORMAT_RGB5A1);
		s->movable.movable[i].ai = d_dynlib_get(s->movable.ai, d_stringtable_entry(s->movable.ai_table, d_map_prop(s->active_level->object[i].ref, "ai")));
		s->movable.movable[i].x = s->active_level->object[i].x * 1000;
		s->movable.movable[i].y = s->active_level->object[i].y * 1000;
		s->movable.movable[i].l = s->active_level->object[i].l;
		s->movable.movable[i].direction = 0;
		s->movable.movable[i].gravity_effect = 1;
		s->movable.movable[i].x_velocity = 0;
		s->movable.movable[i].y_velocity = 0;
	}

	return 0;
}


int movableGravity(MOVABLE_ENTRY *entry) {
	int gravity;
	int delta_x, delta_y, r, t, u;
	int hit_x, hit_y, hit_w, hit_h;

	DARNIT_MAP_LAYER *layer = &(s->active_level->layer[entry->l]);

	d_sprite_hitbox(entry->sprite, &hit_x, &hit_y, &hit_w, &hit_h);
	hit_w--;
	hit_h--;

	/* Y-axis */
	if (entry->gravity_effect == 0)
		gravity = 0;
	else
		gravity = (entry->gravity_effect == 2) ? s->cfg.gravity_strong : s->cfg.gravity_weak;

	if (entry->y_velocity + (gravity * d_last_frame_time()) / 1000 > s->cfg.terminal_velocity)
		entry->y_velocity = s->cfg.terminal_velocity;
	else
		entry->y_velocity += gravity * d_last_frame_time() / 1000;
	delta_y = (entry->y_velocity * d_last_frame_time());

	/* X-axis */
	delta_x = 0;
	//final_x = entry->x;
	/* TODO: STUB */

	while (delta_x || delta_y) {
		if (!delta_y /*|| (delta_x / (delta_y / 1000) > 1000)*/) {
		} else {	/* delta_y måste vara != 0 */
			r = entry->y % 1000;
			if (r + delta_y < 1000 && r + delta_y >= 0) {
				entry->y += delta_y;
				delta_y = 0;
				continue;
			}

			if (delta_y > 0) {
				r = 1000 - r;
				u = entry->y / 1000 + hit_y + hit_h;
				t = u + 1;
				u /= layer->tile_h;
				t /= layer->tile_h;
				if (u == t) {
					entry->y += r;
					delta_y -= r;
					continue;
				}

				if (layer->tilemap->data[t * layer->tilemap->w + entry->x / 1000 / layer->tile_w] & COLLISION_BOTTOM) {
					entry->y_velocity = 0;
					delta_y = 0;
					continue;
				}

				entry->y += r;
				delta_y -= r;
				continue;
			} else {
				if (!r)
					r = 1000;
				u = entry->y / 1000 + hit_y;
				t = u - 1;
				u /= layer->tile_h;
				t /= layer->tile_h;
				if (u == t) {
					entry->y -= r;
					delta_y += r;
					continue;
				}

				if (layer->tilemap->data[t * layer->tilemap->w + entry->x / 1000 / layer->tile_w] & COLLISION_TOP) {
					entry->y_velocity = 0;
					delta_y = 0;
					continue;
				}

				entry->y -= r;
				delta_y += r;
				continue;
			}
		}
	}

	return -1462573849;
}


void movableLoop(int layer) {
	int i;

	for (i = 0; i < s->movable.movables; i++) {
		if (s->movable.movable[i].l != layer)
			continue;
		movableGravity(&s->movable.movable[i]);
		d_sprite_move(s->movable.movable[i].sprite, s->movable.movable[i].x / 1000, s->movable.movable[i].y / 1000);
		d_sprite_draw(s->movable.movable[i].sprite);
	}
}


