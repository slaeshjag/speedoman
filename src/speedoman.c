#include "speedoman.h"


SPEEDOMAN *speedomanInit() {

	if ((s = malloc(sizeof(SPEEDOMAN))) == NULL)
		return NULL;
	
	s->newstate = STATE_TESTGAME;
	s->state = STATE_DUMMY;

	if ((s->config = d_stringtable_open("misc/config.ldsz")) == NULL)
		return NULL;
	d_stringtable_section_load(s->config, "INDEX");

	s->cfg.terminal_velocity = atoi(d_stringtable_entry(s->config, "TERMINAL_VELOCITY"));
	s->cfg.jump_acceleration = atoi(d_stringtable_entry(s->config, "JUMP_ACCELERATION"));
	s->cfg.gravity_strong = atoi(d_stringtable_entry(s->config, "GRAVITY_STRONG"));
	s->cfg.gravity_weak = atoi(d_stringtable_entry(s->config, "GRAVITY_WEAK"));
	s->cfg.speedoman_walk_speed = atoi(d_stringtable_entry(s->config, "SPEEDOMAN_WALK_SPEED"));

	s->var.screen_w = 800;
	s->var.screen_h = 480;
	
	s->active_level = NULL;
	s->var.camera_follow = cameraMovableFollow;
	s->var.bullet_spawn = bulletSpawn;
	bulletInit();
	movableInit();
	cameraInit();

	return s;
}


int main(int argc, char **argv) {
	if (d_init("Speedoman", "speedoman", NULL) == NULL)
		return -1;
	
	d_fs_mount("misc.ldi");
	d_fs_mount("maps.ldi");
	d_fs_mount("assets.ldi");

	/* Nollställer allt och sätter upp alla strukturer för informationsskärm som visas i början */
	if ((s = speedomanInit(s)) == NULL)
		d_quit();
	/* Just testing */

	for (;;) {
		d_render_begin();
		stateHandle(s);
		d_render_end();
		d_loop();
	}

	return 0;
}
