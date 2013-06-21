#ifndef __PLAYER_H__
#define	__PLAYER_H__

typedef struct {
	int		slide_start;
	int		sliding;
	int		shoot_start;
	int		last_walk_dir;
	int		last_dir;
	unsigned int	*coll_test;
} PLAYER;

static PLAYER p;

#endif
