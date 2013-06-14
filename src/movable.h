#ifndef __MOVABLE_H__
#define	__MOVABLE_H__

#define	COLLISION_BOTTOM	0x10000
#define	COLLISION_LEFT		0x20000
#define	COLLISION_TOP		0x40000
#define	COLLISION_RIGHT		0x80000


typedef enum {
	MOVABLE_MSG_INIT,
	MOVABLE_MSG_LOOP,
	MOVABLE_MSG_COLLISION,
	MOVABLE_MSG_DESTROY
} MOVABLE_MSG;


typedef struct {
	int			x;
	int			y;
	int			w;
	int			h;
} MOVABLE_HITBOX;


typedef struct {
	int			bbox;
	DARNIT_SPRITE		*sprite;
	int			x;
	int			y;
	int			l;
	int			w;
	int			h;
	int			x_off;
	int			y_off;
	int			direction;
	int			x_velocity;
	int			y_velocity;
	int			gravity_effect;
	int			hp;
	int			hp_max;
	void			(*ai)(void *s, void *entry, MOVABLE_MSG msg);
} MOVABLE_ENTRY;
	

typedef struct {
	MOVABLE_ENTRY		*movable;
	int			movables;
	DARNIT_DYNLIB		*ai;
	DARNIT_STRINGTABLE	*ai_table;
} MOVABLE;

int movableInit();
int movableLoad();
int movableGravity(MOVABLE_ENTRY *entry);
void movableLoop(int layer);


#endif
