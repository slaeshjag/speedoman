#include <darnit/darnit.h>

#include "../speedoman.h"

void player(SPEEDOMAN *s, MOVABLE_ENTRY *self) {
	if (d_keys_get().x && !self->y_velocity) {
		self->y_velocity = atoi(d_stringtable_entry(s->config, "JUMP_ACCELERATION"));
	}

	if (d_keys_get().left)
		self->x_velocity = -20;
	else if (d_keys_get().right)
		self->x_velocity = 20;
	else
		self->x_velocity = 0;
//	fprintf(stderr, "Blah\n");
	return;
}


int bleh() {
	return 0;
}
