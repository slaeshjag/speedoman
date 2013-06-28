#include "speedoman.h"


void pausescreen_init() {
	int x, y;

	s->var.pause.selection = 0;
	s->var.pause.active = 1;
	s->var.pause.menu_background = d_map_load("maps/menu_background.ldmz");
	x = (s->var.screen_w - s->var.pause.menu_background->layer->tilemap->w * s->var.pause.menu_background->layer->tile_w) >> 1;
	y = (s->var.screen_h - s->var.pause.menu_background->layer->tilemap->h * s->var.pause.menu_background->layer->tile_h) >> 1;
	d_map_camera_move(s->var.pause.menu_background, -x, -y);
	
	return;
}


void pausescreen_draw() {
	DARNIT_KEYS keys;

	if (!s->var.pause.active)
		return;
	d_tilemap_draw(s->var.pause.menu_background->layer->tilemap);
	keys = d_keys_get();

	if (keys.BUTTON_CANCEL)
		s->var.pause.active = 0;

	return;
}
