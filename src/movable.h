#ifndef __MOVABLE_H__
#define	__MOVABLE_H__

#define	COLLISION_BOTTOM	0x10000
#define	COLLISION_LEFT		0x20000
#define	COLLISION_TOP		0x40000
#define	COLLISION_RIGHT		0x80000
#define	COLLISION_KILL		0x100000
#define	COLLISION_CHECKPOINT	0x200000


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
	int			hit;
	int			hit_time;
	int			type;
	int			touch_dmg;
	int			prevent_respawn;
	void			(*ai)(void *s, void *entry, MOVABLE_MSG msg);
} MOVABLE_ENTRY;
	

typedef struct {
	MOVABLE_ENTRY		*movable;
	unsigned int		*coll_buf;
	unsigned int		*ai_coll_buf;
	DARNIT_BBOX		*bbox;
	int			movables;
	DARNIT_DYNLIB		*ai;
	DARNIT_STRINGTABLE	*ai_table;
	int			respawn_x;
	int			respawn_y;
} MOVABLE;

int movableInit();
int movableLoad();
void movableSpawn();
void movableKillEmAll();
int movableGravity(MOVABLE_ENTRY *entry);
void movableLoop();
void movableLoopRender(int layer);
int movableTileCollision(MOVABLE_ENTRY *entry, int off_x, int off_y);
void movableFreezeSprites(int freeze);
void movableRespawn();


#endif
