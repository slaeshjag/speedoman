#include "speedoman.h"


int levelLoad(const char *level) {

	if (s->active_level)
		s->active_level = d_map_unload(s->active_level);
	
	if (!(s->active_level = d_map_load(level)))
		return -1;

	return 0;
}
