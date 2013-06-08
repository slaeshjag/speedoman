#include "speedoman.h"


int movableInit() {
	s->movable.movable = NULL;
	s->movable.movables = 0;

	s->movable.ai = d_dynlib_open(d_stringtable_entry(s->config, "AI_LIB"));
	s->movable.ai_table = d_stringtable_open(d_stringtable_entry(s->config, "AI_TABLE"));
	
	if (!s->movable.ai || !s->movable.ai_table)
		return -1;

	return 0;
}


void movableHitboxLoad(MOVABLE_ENTRY *entry, const char *name) {
	int i, coords[32*4];

	i = d_util_string_to_int_array(d_stringtable_entry(s->config, name), ",", coords, 32*4);

	for (; i < 32*4; i++)
		coords[i] = -1;
	
	for (i = 0; i < 32; i++) {
		entry->hitbox[i].x = coords[i*4];
		entry->hitbox[i].y = coords[i*4 + 1];
		entry->hitbox[i].w = coords[i*4 + 2];
		entry->hitbox[i].h = coords[i*4 + 3];
	}

	return;
}


void movableUpdateHitbox(MOVABLE_ENTRY *entry) {
	entry->w = entry->hitbox[entry->direction].w;
	entry->h = entry->hitbox[entry->direction].h;
	entry->x_off = entry->hitbox[entry->direction].x;
	entry->y_off = entry->hitbox[entry->direction].y;

	return;
}


int movableLoad() {
	int i;
	MOVABLE_ENTRY *entry;

	for (i = 0; i < s->movable.movables; i++)
		d_sprite_free(s->movable.movable[i].sprite);
	if (!(entry = realloc(s->movable.movable, sizeof(MOVABLE_ENTRY) * s->active_level->objects))) {
		free(s->movable.movable);
		movableInit();
		return -1;
	}

	s->movable.movable = entry;
	s->movable.movables = s->active_level->objects;

	for (i = 0; i < s->movable.movables; i++) {
		movableHitboxLoad(&s->movable.movable[i], d_map_prop(s->active_level->object[i].ref, "NAME"));
		s->movable.movable[i].sprite = d_sprite_load(d_map_prop(s->active_level->object[i].ref, "sprite"), 0, DARNIT_PFORMAT_RGB5A1);
		s->movable.movable[i].ai = d_dynlib_get(s->movable.ai, d_stringtable_entry(s->movable.ai_table, d_map_prop(s->active_level->object[i].ref, "ai")));
		s->movable.movable[i].x = s->active_level->object[i].x;
		s->movable.movable[i].y = s->active_level->object[i].y;
		s->movable.movable[i].l = s->active_level->object[i].l;
		s->movable.movable[i].direction = 0;
		movableUpdateHitbox(&s->movable.movable[i]);
	}

	return 0;
}


int movableGravity(MOVABLE_ENTRY *entry) {
	int gravity, delta, xi, dx, yi, dy, i, j, final_y;
	DARNIT_MAP_LAYER *layer = &s->active_level->layer[entry->l];

	if (entry->gravity_effect == 0)
		return -1;
	gravity = (entry->gravity_effect == 2) ? s->cfg.gravity_strong : s->cfg.gravity_weak;

	if (entry->velocity + gravity * d_last_frame_time() > s->cfg.terminal_velocity)
		entry->velocity = s->cfg.terminal_velocity;
	delta = (entry->velocity * d_last_frame_time() >> 16);
	if (delta == 0)
		return -1;
	
	final_y = entry->y + delta;
	
	if (delta < 0) {		/* Mkay, we're still moving up */
		xi = entry->x / layer->tile_w;
		yi = entry->y / layer->tile_h;
		dx = (entry->x + entry->w) / layer->tile_w - xi;
		dy = (entry->h + delta) / layer->tile_h - yi;
		
		for (i = -1; i >= dy && (yi + i >= 0); i--) {
			for (j = 0; j <= dx; j++)
				if (layer->tilemap->data[xi+j + (yi+i) * layer->tilemap->w] & COLLISION_TOP)
					break;
			if (j <= dx) {
				entry->y = (yi + i + 1) * layer->tile_h;
				return 0;
			}
			entry->y = (yi + i) * layer->tile_h;
		}
		
		entry->y = final_y;
		return 0;
	} else {
		xi = entry->x / layer->tile_w;
		yi = (entry->y + entry->h) / layer->tile_h;
		dx = (entry->x + entry->w) / layer->tile_w - xi;
		dy = (entry->y + entry->h + delta) / layer->tile_h - yi;

		for (i = 1; i <= dy; i++) {
			for (j = 0; j <= dx; j++)
				if (layer->tilemap->data[xi+j + (yi+i) * layer->tilemap->h] & COLLISION_BOTTOM)
					break;
			if (j <= dx) {
				entry->y = (yi + i) * layer->tile_h - entry->h - 1;
				return 0;
			}
			entry->y = (yi + i) * layer->tile_h - entry->h - 1;
		}

		entry->y = final_y;
		return 0;
	}

	return -1462573849;
}
