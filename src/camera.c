#include "speedoman.h"


void cameraInit() {
	s->camera.follow = -1;
	s->camera.x = 0;
	s->camera.y = 0;

	return;
}


void cameraMovableFollow(MOVABLE_ENTRY *m) {
	int p;

	if (!m) {
		s->camera.follow = -1;
		return;
	}

	p = (int) (m - s->movable.movable);
	p /= s->movable.movables;
	if (p < 0 || p >= s->movable.movables)
		return;
	s->camera.follow = p;
	return;
}


void cameraLoop() {
	if (s->camera.follow == -1)
		return;
	s->camera.x = s->movable.movable[s->camera.follow].x / 1000;
	s->camera.y = s->movable.movable[s->camera.follow].y / 1000;

	s->camera.x -= (s->var.screen_w >> 1);
	s->camera.y -= (s->var.screen_h >> 1);
	if (s->camera.x < 0)
		s->camera.x = 0;
	if (s->camera.y < 0)
		s->camera.y = 0;

	return;
}
