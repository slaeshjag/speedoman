#include "speedoman.h"


SPEEDOMAN *speedomanInit() {

	if ((s = malloc(sizeof(SPEEDOMAN))) == NULL)
		return NULL;
	
	s->newstate = STATE_TESTGAME;
	s->state = STATE_DUMMY;

	if ((s->config = darnitStringtableOpen("misc/config.ldsz")) == NULL)
		return NULL;
	darnitStringtableSectionLoad(s->config, "INDEX");
	darnitStringtableSectionLoad(s->config, "HITBOX");

	s->cfg.terminal_velocity = atoi(darnitStringtableEntryGet(s->config, "TERMINAL_VELOCITY"));
	s->cfg.jump_acceleration = atoi(darnitStringtableEntryGet(s->config, "JUMP_ACCELERATION"));
	s->cfg.gravity_strong = atoi(darnitStringtableEntryGet(s->config, "GRAVITY_STRONG"));
	s->cfg.gravity_weak = atoi(darnitStringtableEntryGet(s->config, "GRAVITY_WEAK"));
	
	s->active_level = NULL;
	movableInit();

	return s;
}


int main(int argc, char **argv) {
	DARNIT_KEYS keys;

	if (darnitInit("Speedoman", "speedoman") == NULL)
		return -1;
	
	darnitFSMount("misc.ldi");
	darnitFSMount("maps.ldi");
	darnitFSMount("assets.ldi");

	/* Nollställer allt och sätter upp alla strukturer för informationsskärm som visas i början */
	if ((s = speedomanInit(s)) == NULL)
		darnitQuit();
	/* Just testing */
	levelLoad("maps/test.ldmz");

	for (;;) {
		darnitRenderBegin();
		stateHandle(s);
		keys = darnitButtonGet();
		if (keys.x)
			return 0;
		darnitRenderEnd();
		darnitLoop();
	}

	return 0;
}
