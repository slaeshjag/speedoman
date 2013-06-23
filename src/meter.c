#include "speedoman.h"


void meterSetup() {
	s->var.meter.ts = d_render_tilesheet_load("assets/meters.png", METER_WIDTH, METER_HEIGHT, DARNIT_PFORMAT_RGB5A1);
	s->var.meter.player_health = meterInit(s->var.meter.ts, 0, 0);
	s->var.meter.player_weapon = meterInit(s->var.meter.ts, METER_WIDTH, 0);
	s->var.meter.boss_health = meterInit(s->var.meter.ts, s->var.screen_w - METER_WIDTH, 0);

	return;
}


METER *meterInit(DARNIT_TILESHEET *ts, int x, int y) {
	METER *m;

	m = malloc(sizeof(*m));
	m->watch = NULL;
	m->watch_max = 0;
	m->watch_last = 0;
	m->type = 0;
	m->x = x;
	m->y = y;
	d_render_tilesheet_geometrics(ts, NULL, NULL, &m->w, &m->h);
	
	m->tc = d_render_tile_new(2, ts);
	d_render_tile_move(m->tc, 0, x, y);

	return m;
}


void meterUpdate(METER *m) {
	int pos;

	if (!m->watch)
		return;
	pos = *m->watch * m->h / m->watch_max;
	m->watch_last = *m->watch;
	d_render_tile_move(m->tc, 1, m->x, m->y + (m->h - pos));
	d_render_tile_size_set(m->tc, 1, m->w, pos);
	d_render_tile_tilesheet_coord_set(m->tc, 1, m->w * m->type, 0, m->w, pos);
	
	d_render_tile_size_set(m->tc, 0, m->w, m->h - pos);
	d_render_tile_tilesheet_coord_set(m->tc, 0, 0, 0, m->w, m->h - pos);

	return;
}


void meterWatch(METER *m, int type, int *watch, int max) {
	m->watch = watch;
	m->type = type;
	m->watch_max = max;

	meterUpdate(m);

	return;
}


void meterDraw(METER *m) {
	if (!m->watch)
		return;
	if (*m->watch != m->watch_last)
		meterUpdate(m);
	d_render_tile_draw(m->tc, 2);
	return;
}


METER *meterFree(METER *m) {
	d_render_tile_free(m->tc);
	free(m);
	return NULL;
}


void meterDrawAll() {
	meterDraw(s->var.meter.player_health);
	meterDraw(s->var.meter.player_weapon);
	meterDraw(s->var.meter.boss_health);

	return;
}
