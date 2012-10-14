#include "speedoman.h"


int levelLoad(const char *level) {

	if (s->active_level)
		s->active_level = darnitMapUnload(s->active_level);
	
	if (!(s->active_level = darnitMapLoad(level)))
		return -1;

	return 0;
}
