#ifndef __METER_H__
#define	__METER_H__

#define	METER_WIDTH		16
#define	METER_HEIGHT		128

typedef struct {
	int			*watch;
	int			watch_max;
	int			watch_last;
	int			type;
	int			x;
	int			y;
	int			w;
	int			h;
	DARNIT_TILE		*tc;
} METER;


void meterSetup();
METER *meterInit(DARNIT_TILESHEET *ts, int x, int y);
void meterUpdate(METER *m);
void meterWatch(METER *m, int type, int *watch, int max);
void meterDraw(METER *m);
METER *meterFree(METER *m);
void meterDrawAll();


#endif
