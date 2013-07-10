#ifndef __SPEEDOMAN_H__
#define	__SPEEDOMAN_H__


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#include <darnit/darnit.h>
#undef	BUTTON_ACCEPT
#undef 	BUTTON_CANCEL
#define	BUTTON_ACCEPT			x
#define	BUTTON_CANCEL			l
#define	SPEEDOMAN_START_AMOUNT_LIVES	5

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
	unsigned int		e_tank;
	unsigned int		w_tank;
	int			lives;
	unsigned int		death_count;
	unsigned int		game_over_count;
} PROGRESS;


typedef struct {
	int			request_respawn;
	int			respawn_time;
	DARNIT_TEXT_SURFACE	*ready;
	DARNIT_TEXT_SURFACE	*game_over;
	DARNIT_PARTICLE		*player_death[4];
} RESPAWN;


typedef struct {
	int			screen_w;
	int			screen_h;
	METER_STRUCT		meter;
	STAGE_SELECT		stage;
	PROGRESS		progress;
	PAUSE_SCREEN		pause;
	DARNIT_FONT		*font;
	DARNIT_TILESHEET	*items;
	DARNIT_STRINGTABLE	*lang;
	RESPAWN			respawn;
	void			(*camera_follow)(MOVABLE_ENTRY *e);
	void			(*bullet_spawn)(int type, int direction, MOVABLE_ENTRY *owner_e, int x, int y);
	void			(*meter_watch)(METER *m, int type, int *watch, int max);
	int			(*movable_tile_coll)(MOVABLE_ENTRY *entry, int off_x, int off_y);
	void 			(*movable_freeze_sprites)(int freeze);
	int			(*speedoman_player_add_hp)(int hp);
	int			selected_weapon;
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


int speedomanPlayerAddHP(int hp);

SPEEDOMAN *s;		/* Just this one, promise :x */

#endif
