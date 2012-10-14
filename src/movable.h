#ifndef __MOVABLE_H__
#define	__MOVABLE_H__

#define	COLLISION_BOTTOM	0x10000
#define	COLLISION_LEFT		0x20000
#define	COLLISION_TOP		0x40000
#define	COLLISION_RIGHT		0x80000


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
	int			velocity;
	int			gravity_effect;
	MOVABLE_HITBOX		hitbox[32];
	void			(*ai)(void *s, void *entry);
} MOVABLE_ENTRY;
	

typedef struct {
	MOVABLE_ENTRY		*movable;
	int			movables;
	DARNIT_STRINGTABLE	*hitbox_data;
	DARNIT_DYNLIB		*ai;
	DARNIT_STRINGTABLE	*ai_table;
} MOVABLE;

int movableInit();
void movableUpdateHitbox(MOVABLE_ENTRY *entry);
int movableLoad();
int movableGravity(MOVABLE_ENTRY *entry);


#endif
