#include "speedoman.h"


void stageSelectMoveCursor() {
	int x_u, y_u;

	x_u = s->var.screen_w / 2 - 224;
	y_u = s->var.screen_h / 2 - 224;

	d_render_tile_move(s->var.stage.stage, 9, x_u + (s->var.stage.selected_stage % 3) * 160, y_u + (s->var.stage.selected_stage / 3) * 160);

	return;
}


void stageSelectInit() {
	int x_u, y_u, i, j;

	x_u = (s->var.screen_w / 2) - 224;
	y_u = (s->var.screen_h / 2) - 224;

	s->var.stage.stage_gfx = d_render_tilesheet_load("assets/stage_select.png", 128, 128, DARNIT_PFORMAT_RGB5A1);
	s->var.stage.stage = d_render_tile_new(10, s->var.stage.stage_gfx);
	s->var.stage.selected_stage = 0;
	d_render_tile_init(s->var.stage.stage, 9, 9, x_u, y_u);

	for (i = 0; i < 3; i++)
		for (j = 0; j < 3; j++)
			d_render_tile_init(s->var.stage.stage, i * 3 + j, i * 3 + j, x_u + 160 * j, y_u + i * 160);
	stageSelectMoveCursor();
	return;
}


void stageSelectDraw() {
	DARNIT_KEYS keys;

	keys = d_keys_get();
	if (keys.left) {
		if ((--s->var.stage.selected_stage) < 0)
			s->var.stage.selected_stage = 8;
		d_keys_set(keys);
	} else if (keys.right) {
		if ((++s->var.stage.selected_stage) > 8)
			s->var.stage.selected_stage = 0;
		d_keys_set(keys);
	} else if (keys.up) {
		if ((s->var.stage.selected_stage -= 3) < 0)
			s->var.stage.selected_stage += 9;
		d_keys_set(keys);
	} else if (keys.down) {
		if ((s->var.stage.selected_stage += 3) > 8)
			s->var.stage.selected_stage -= 9;
		d_keys_set(keys);
	}
			
	stageSelectMoveCursor();

	d_render_offset(0, 0);
	d_render_blend_enable();
	d_render_tile_draw(s->var.stage.stage, 10);
	d_render_blend_disable();

	
	return;
}
