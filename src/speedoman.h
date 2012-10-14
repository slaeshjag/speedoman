#ifndef __SPEEDOMAN_H__
#define	__SPEEDOMAN_H__


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <darnit/darnit.h>

#include "state.h"
#include "movable.h"
#include "level.h"


typedef struct {
	int			terminal_velocity;
	int			jump_acceleration;
	int			gravity_strong;
	int			gravity_weak;
} CONFIG;


typedef struct {
	MOVABLE			movable;
	DARNIT_MAP		*active_level;
	DARNIT_STRINGTABLE	*config;
	CONFIG			cfg;
	int			state;
	int			newstate;
} SPEEDOMAN;

SPEEDOMAN *s;		/* Just this one, promise :x */

#endif
