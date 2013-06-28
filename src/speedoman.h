#ifndef __SPEEDOMAN_H__
#define	__SPEEDOMAN_H__


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#include <darnit/darnit.h>

#include "state.h"
#include "movable.h"
#include "level.h"
#include "camera.h"
#include "bullet.h"
#include "meter.h"
#include "stage_select.h"
#include "save.h"
#include "pause_screen.h"


typedef struct {
	int			terminal_velocity;
	int			jump_acceleration;
	int			gravity_strong;
	int			gravity_weak;
	int			speedoman_walk_speed;
	int			speedoman_hp;
} CONFIG;


typedef struct {
	METER			*player_health;
	METER			*player_weapon;
	METER			*boss_health;
	DARNIT_TILESHEET	*ts;
} METER_STRUCT;
	

typedef struct {
	unsigned int		stages		: 8;
	unsigned int		boss_stage	: 8;
	unsigned int		weapon_status[8];
} PROGRESS;


typedef struct {
	int			screen_w;
	int			screen_h;
	METER_STRUCT		meter;
	STAGE_SELECT		stage;
	PROGRESS		progress;
	PAUSE_SCREEN		pause;
	void			(*camera_follow)(MOVABLE_ENTRY *e);
	void			(*bullet_spawn)(int type, int direction, MOVABLE_ENTRY *owner_e, int x, int y);
	void			(*meter_watch)(METER *m, int type, int *watch, int max);
	int			(*movable_tile_coll)(MOVABLE_ENTRY *entry, int off_x, int off_y);
} VAR;


typedef struct {
	MOVABLE			movable;
	DARNIT_MAP		*active_level;
	DARNIT_STRINGTABLE	*config;
	CONFIG			cfg;
	CAMERA			camera;
	VAR			var;
	BULLET			bullet;
	const char		*load_level;
	int			state;
	int			newstate;
	int			player;
} SPEEDOMAN;

SPEEDOMAN *s;		/* Just this one, promise :x */

#endif
