#ifndef __PLAYER_H__
#define	__PLAYER_H__

typedef struct {
	int		slide_start;
	int		sliding;
	int		last_walk_dir;
	unsigned int	*coll_test;
} PLAYER;

static PLAYER p;

#endif
