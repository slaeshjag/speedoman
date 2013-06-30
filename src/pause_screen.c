#include "speedoman.h"


void pausescreen_move_cursor();

void pausescreen_init() {
	int x, y;

	s->var.pause.selection = 0;
	s->var.pause.active = 0;
	s->var.pause.menu_background = d_map_load("maps/menu_background.ldmz");
	x = (s->var.screen_w - s->var.pause.menu_background->layer->tilemap->w * s->var.pause.menu_background->layer->tile_w) >> 1;
	y = (s->var.screen_h - s->var.pause.menu_background->layer->tilemap->h * s->var.pause.menu_background->layer->tile_h) >> 1;
	d_map_camera_move(s->var.pause.menu_background, -x, -y);
	s->var.pause.menu_options = d_text_surface_color_new(s->var.font, 512, s->var.pause.menu_background->layer->tile_w * s->var.pause.menu_background->layer->tilemap->w, x + 64, y + 32);
	s->var.pause.selected = d_render_tile_new(1, s->var.pause.menu_background->layer->ts);
	d_render_tile_set(s->var.pause.selected, 0, 4);
	pausescreen_move_cursor();
	
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


void pausescreen_move_cursor() {
	int x, y;

	x = (s->var.screen_w - s->var.pause.menu_background->layer->tilemap->w * s->var.pause.menu_background->layer->tile_w) >> 1;
	y = (s->var.screen_h - s->var.pause.menu_background->layer->tilemap->h * s->var.pause.menu_background->layer->tile_h) >> 1;

	x += 32;
	y += (32 + (d_font_glyph_hs(s->var.font) - 16) / 2);

	y += (s->var.pause.selection * d_font_glyph_hs(s->var.font));
	d_render_tile_move(s->var.pause.selected, 0, x, y);

	return;
}


void pausescreen_handle_menu() {
	DARNIT_KEYS keys;
	int dir;

	keys = d_keys_get();

	dir = 0;
	if (keys.up) {
		dir = -1;
		keys = d_keys_zero();
		keys.up = 1;
	} else if (keys.down) {
		dir = 1;
		keys = d_keys_zero();
		keys.down = 1;
	} else if (keys.BUTTON_ACCEPT || keys.start) {
		d_keys_set(keys);
		
		if (s->var.pause.selection == 0) {
			s->var.movable_freeze_sprites(0);
			s->var.pause.active = 0;
		} else if (s->var.pause.selection == 12)
			s->newstate = STATE_STAGE_SELECT;
	} else if (keys.BUTTON_CANCEL) {
		s->var.pause.active = 0;
		s->var.movable_freeze_sprites(0);
		d_keys_set(keys);
	}

	if (dir) {
		d_keys_set(keys);
		for (;;) {
			s->var.pause.selection += dir;
			if (s->var.pause.selection < 0) {
				s->var.pause.selection = 12;
				break;
			} else if (s->var.pause.selection > 12) {
				s->var.pause.selection = 0;
				break;
			} else if (s->var.pause.selection > 9)
				break;
			else if (s->var.pause.selection < 2)
				break;
			else if ((1 << (s->var.pause.selection - 2)) & s->var.progress.stages)
				break;
		}
		pausescreen_move_cursor();
	}

	return;
}


void pausescreen_draw() {
	if (!s->var.pause.active)
		return;
	pausescreen_generate_menu_text();
	pausescreen_handle_menu();
	d_tilemap_draw(s->var.pause.menu_background->layer->tilemap);
	d_render_blend_enable();
	d_text_surface_draw(s->var.pause.menu_options);
	d_render_tile_draw(s->var.pause.selected, 1);
	d_render_blend_disable();

	return;
}
