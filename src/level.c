#include "speedoman.h"


int levelLoad() {

	if (s->active_level)
		s->active_level = d_map_unload(s->active_level);

	s->camera.x = s->camera.y = 0;
	if (!(s->active_level = d_map_load(s->load_level)))
		return -1;
	
	s->movable.respawn_x = s->movable.respawn_y = -1;
	
	return 0;
}
