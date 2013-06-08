#include "speedoman.h"


SPEEDOMAN *speedomanInit() {

	if ((s = malloc(sizeof(SPEEDOMAN))) == NULL)
		return NULL;
	
	s->newstate = STATE_TESTGAME;
	s->state = STATE_DUMMY;

	if ((s->config = d_stringtable_open("misc/config.ldsz")) == NULL)
		return NULL;
	d_stringtable_section_load(s->config, "INDEX");
	d_stringtable_section_load(s->config, "HITBOX");

	s->cfg.terminal_velocity = atoi(d_stringtable_entry(s->config, "TERMINAL_VELOCITY"));
	s->cfg.jump_acceleration = atoi(d_stringtable_entry(s->config, "JUMP_ACCELERATION"));
	s->cfg.gravity_strong = atoi(d_stringtable_entry(s->config, "GRAVITY_STRONG"));
	s->cfg.gravity_weak = atoi(d_stringtable_entry(s->config, "GRAVITY_WEAK"));
	
	s->active_level = NULL;
	movableInit();

	return s;
}


int main(int argc, char **argv) {
	DARNIT_KEYS keys;

	if (d_init("Speedoman", "speedoman", NULL) == NULL)
		return -1;
	
	d_fs_mount("misc.ldi");
	d_fs_mount("maps.ldi");
	d_fs_mount("assets.ldi");

	/* Nollställer allt och sätter upp alla strukturer för informationsskärm som visas i början */
	if ((s = speedomanInit(s)) == NULL)
		d_quit();
	/* Just testing */
	levelLoad("maps/test.ldmz");

	for (;;) {
		d_render_begin();
		stateHandle(s);
		keys = d_keys_get();
		if (keys.x)
			return 0;
		d_render_end();
		d_loop();
	}

	return 0;
}
