#ifndef __SPEEDOMAN_H__
#define	__SPEEDOMAN_H__


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <darnit/darnit.h>

#include "state.h"
#include "movable.h"
#include "level.h"
#include "camera.h"


typedef struct {
	int			terminal_velocity;
	int			jump_acceleration;
	int			gravity_strong;
	int			gravity_weak;
	int			speedoman_walk_speed;
} CONFIG;


typedef struct {
	int			screen_w;
	int			screen_h;
	void			(*camera_follow)(MOVABLE_ENTRY *e);
	void			(*camera_loop)();
} VAR;


typedef struct {
	MOVABLE			movable;
	DARNIT_MAP		*active_level;
	DARNIT_STRINGTABLE	*config;
	CONFIG			cfg;
	CAMERA			camera;
	VAR			var;
	int			state;
	int			newstate;
	int			player;
} SPEEDOMAN;

SPEEDOMAN *s;		/* Just this one, promise :x */

#endif
