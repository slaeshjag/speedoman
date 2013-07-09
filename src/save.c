#include "speedoman.h"

int save_init() {
	DARNIT_FILE *f;

	memset(&s->var.progress, 0, sizeof(PROGRESS));
	s->var.progress.lives = SPEEDOMAN_START_AMOUNT_LIVES;

	if (!(f = d_file_open("savegame.dat", "rb")))
		return 0;
	d_file_read_ints(&s->var.progress, sizeof(s->var.progress) / 4, f);
	d_file_close(f);

	return 0;
}


int save_save() {
	DARNIT_FILE *f;

	if (!(f = d_file_open("savegame.dat", "wb")))
		return 0;
	d_file_write_ints(&s->var.progress, sizeof(s->var.progress) / 4, f);
	d_file_close(f);
	return 0;
}
