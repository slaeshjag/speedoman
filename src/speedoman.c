#include "speedoman.h"


SPEEDOMAN *speedomanInit() {

	if ((s = malloc(sizeof(SPEEDOMAN))) == NULL)
		return NULL;
	
	s->newstate = STATE_TESTGAME;
	s->state = STATE_DUMMY;

	s->movable.movable = NULL;
	s->movable.movables = 0;

	if ((s->config = darnitStringtableOpen("misc/config.ldsz")) == NULL)
		return NULL;
	darnitStringtableSectionLoad(s->config, "INDEX");
	s->cfg.terminal_velocity = atoi(darnitStringtableEntryGet(s->config, "TERMINAL_VELOCITY"));
	s->cfg.jump_acceleration = atoi(darnitStringtableEntryGet(s->config, "JUMP_ACCELERATION"));
	s->cfg.gravity_strong = atoi(darnitStringtableEntryGet(s->config, "GRAVITY_STRONG"));
	s->cfg.gravity_weak = atoi(darnitStringtableEntryGet(s->config, "GRAVITY_WEAK"));
	

	return s;
}


int main(int argc, char **argv) {
	void *handle;
	DARNIT_KEYS keys;

	if ((handle = darnitInit("Speedoman", "speedoman")) == NULL)
		return -1;
	
	darnitFSMount("misc.ldi");

	/* Nollställer allt och sätter upp alla strukturer för informationsskärm som visas i början */
	if ((s = speedomanInit(s)) == NULL)
		darnitQuit();

	for (;;) {
		stateHandle(s);
		keys = darnitButtonGet();
		if (keys.x)
			return 0;
		darnitLoop();
	}

	return 0;
}
