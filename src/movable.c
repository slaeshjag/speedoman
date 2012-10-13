#include "speedoman.h"


int movableGravity(MOVABLE_ENTRY *entry) {
	int gravity, delta, xi, dx, yi, dy, i, j, final_y;
	DARNIT_MAP_LAYER *layer = &s->active_level->layer[entry->l];

	if (entry->gravity_effect == 0)
		return;
	gravity = (entry->gravity_effect == 2) ? s->cfg.gravity_strong : s->cfg.gravity_weak;

	if (entry->velocity + gravity * darnitTimeLastFrameTook() > s->cfg.terminal_velocity)
		entry->velocity = s->cfg.terminal_velocity;
	delta = (entry->velocity * darnitTimeLastFrameTook() >> 16);
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
