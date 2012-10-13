#ifndef __MOVABLE_H__
#define	__MOVABLE_H__

#define	COLLISION_BOTTOM	0x10000
#define	COLLISION_LEFT		0x20000
#define	COLLISION_TOP		0x40000
#define	COLLISION_RIGHT		0x80000


typedef struct {
	int			bbox;
	DARNIT_SPRITE		*sprite;
	int			x;
	int			y;
	int			l;
	int			w;
	int			h;
	int			velocity;
	int			gravity_effect;
} MOVABLE_ENTRY;
	

typedef struct {
	MOVABLE_ENTRY		*movable;
	int			movables;
} MOVABLE;


#endif
