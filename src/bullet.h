#ifndef __BULLET_H__
#define	__BULLET_H__

#define	BULLET_CAP		1024


typedef struct {
	int			x_pos;
	int			y_pos;
	int			w;
	int			h;
	int			x_speed;
	int			y_speed;
	int			life;
} BULLET_TYPE;


typedef struct {
	int			x;
	int			y;
	int			x_vel;
	int			y_vel;
	int			owner;
	int			type;
	int			life;
} BULLET_ENTRY;


typedef struct {
	BULLET_ENTRY		*b;
	int			bs;
	DARNIT_TILESHEET	*ts;
	DARNIT_TILE		*tc;
	DARNIT_BBOX		*bbox;
	unsigned int		*btest;
	BULLET_TYPE		*type;
	int			types;
	int			*dmg;
} BULLET;


void bulletInit();
void bulletDeInit();
void bulletLoop();
void bulletDraw();
void bulletSpawn(int type, int direction, MOVABLE_ENTRY *owner_e, int x, int y);
void bulletOrphan(int owner);
void bulletTest(MOVABLE_ENTRY *movable);


#endif
