#ifndef __SPEEDOMAN_H__
#define	__SPEEDOMAN_H__


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <darnit.h>


#include "state.h"

typedef struct {
	DARNIT_TILEMAP		map;
	DARNIT_TILEMAP		backdrop;
} TILEMAP;


typedef struct {
	void			*mapsheet;
	void			*backdropsheet;
} TILESHEET;


typedef struct {
	int			bbox;
	void			*sprite;
	int			x;
	int			y;
} MOVABLE_ENTRY;
	

typedef struct {
	MOVABLE_ENTRY		*movable;
	int			movables;
} MOVABLE;


typedef struct {
	TILEMAP			tilemap;
	TILESHEET		tilesheet;
	MOVABLE			movable;
	int			state;
	int			newstate;
} SPEEDOMAN;


#endif
