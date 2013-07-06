#include "speedoman.h"


int speedomanPlayerAddHP(int hp) {
	int i;

	for (i = 0; i < s->movable.movables; i++) {
		if (!strcmp(d_map_prop(s->active_level->object[i].ref, "ai"), "PLAYER")) {
			s->movable.movable[i].hp += hp;
			if (s->movable.movable[i].hp > s->movable.movable[i].hp_max)
				s->movable.movable[i].hp = s->movable.movable[i].hp_max;
			break;
		}
	}

	return s->movable.movable[i].hp_max - s->movable.movable[i].hp;
}


SPEEDOMAN *speedomanInit() {

	if ((s = malloc(sizeof(SPEEDOMAN))) == NULL)
		return NULL;
	
//	s->newstate = STATE_TESTGAME;
	s->newstate = STATE_STAGE_SELECT;
	s->state = STATE_DUMMY;

	if ((s->config = d_stringtable_open("misc/config.ldsz")) == NULL)
		return NULL;
	d_stringtable_section_load(s->config, "INDEX");
	s->var.lang = d_stringtable_open("misc/lang.ldsz");
	d_stringtable_section_load(s->var.lang, "EN");

	s->cfg.terminal_velocity = atoi(d_stringtable_entry(s->config, "TERMINAL_VELOCITY"));
	s->cfg.jump_acceleration = atoi(d_stringtable_entry(s->config, "JUMP_ACCELERATION"));
	s->cfg.gravity_strong = atoi(d_stringtable_entry(s->config, "GRAVITY_STRONG"));
	s->cfg.gravity_weak = atoi(d_stringtable_entry(s->config, "GRAVITY_WEAK"));
	s->cfg.speedoman_walk_speed = atoi(d_stringtable_entry(s->config, "SPEEDOMAN_WALK_SPEED"));
	s->cfg.speedoman_hp = atoi(d_stringtable_entry(s->config, "SPEEDOMAN_HP"));

	s->var.screen_w = 800;
	s->var.screen_h = 480;
	s->var.selected_weapon = -1;
	
	s->active_level = NULL;
	s->var.camera_follow = cameraMovableFollow;
	s->var.bullet_spawn = bulletSpawn;
	s->var.meter_watch = meterWatch;
	s->var.movable_tile_coll = movableTileCollision;
	s->var.movable_freeze_sprites = movableFreezeSprites;
	s->var.speedoman_player_add_hp = speedomanPlayerAddHP;
	s->var.font = d_font_load("assets/dejavusans.ttf", 24, 512, 512);

	meterSetup();
	bulletInit();
	movableInit();
	cameraInit();
	save_init();
	pausescreen_init();
	stageSelectInit();

	return s;
}


int main(int argc, char **argv) {
	if (d_init("Speedoman", "speedoman", NULL) == NULL)
		return -1;
	
	d_fs_mount_self();
	d_fs_mount("data/misc.ldi");
	d_fs_mount("data/maps.ldi");
	d_fs_mount("data/assets.ldi");

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
