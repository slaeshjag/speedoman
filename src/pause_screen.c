#include "speedoman.h"


void pausescreen_init() {
	int x, y;

	s->var.pause.selection = 0;
	s->var.pause.active = 1;
	s->var.pause.menu_background = d_map_load("maps/menu_background.ldmz");
	x = (s->var.screen_w - s->var.pause.menu_background->layer->tilemap->w * s->var.pause.menu_background->layer->tile_w) >> 1;
	y = (s->var.screen_h - s->var.pause.menu_background->layer->tilemap->h * s->var.pause.menu_background->layer->tile_h) >> 1;
	d_map_camera_move(s->var.pause.menu_background, -x, -y);
	s->var.pause.menu_options = d_text_surface_color_new(s->var.font, 512, s->var.pause.menu_background->layer->tile_w * s->var.pause.menu_background->layer->tilemap->w, x + 64, y + 32);
	
	return;
}


void pausescreen_generate_menu_text() {
	char keyname[32];
	int i;

	
	d_text_surface_reset(s->var.pause.menu_options);
	d_text_surface_color_next(s->var.pause.menu_options, 255, 255, 255);
	d_text_surface_string_append(s->var.pause.menu_options, d_stringtable_entry(s->var.lang, "Resume game"));
	d_text_surface_string_append(s->var.pause.menu_options, "\n");
	d_text_surface_string_append(s->var.pause.menu_options, d_stringtable_entry(s->var.lang, "NOWEAPON"));
	d_text_surface_string_append(s->var.pause.menu_options, "\n");

	for (i = 0; i < 8; i++) {
		if (s->var.progress.stages & (1 << i))
			d_text_surface_color_next(s->var.pause.menu_options, 255, 255, 255);
		else
			d_text_surface_color_next(s->var.pause.menu_options, 127, 127, 127);
		sprintf(keyname, "WEAPON%i", i);
		d_text_surface_string_append(s->var.pause.menu_options, d_stringtable_entry(s->var.lang, keyname));
		d_text_surface_string_append(s->var.pause.menu_options, "\n");
	}

	d_text_surface_color_next(s->var.pause.menu_options, 255, 255, 255);
	d_text_surface_string_append(s->var.pause.menu_options, d_stringtable_entry(s->var.lang, "ETANK"));
	d_text_surface_string_append(s->var.pause.menu_options, "\n");
	d_text_surface_string_append(s->var.pause.menu_options, d_stringtable_entry(s->var.lang, "WTANK"));
	d_text_surface_string_append(s->var.pause.menu_options, "\n");
	d_text_surface_string_append(s->var.pause.menu_options, d_stringtable_entry(s->var.lang, "Exit stage"));
	d_text_surface_string_append(s->var.pause.menu_options, "\n");

	return;
}
	



void pausescreen_draw() {
	DARNIT_KEYS keys;

	if (!s->var.pause.active)
		return;
	pausescreen_generate_menu_text();
	d_tilemap_draw(s->var.pause.menu_background->layer->tilemap);
	d_render_blend_enable();
	d_text_surface_draw(s->var.pause.menu_options);
	d_render_blend_disable();
	keys = d_keys_get();

	if (keys.BUTTON_CANCEL)
		s->var.pause.active = 0;

	return;
}
