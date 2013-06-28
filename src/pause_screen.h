#ifndef __PAUSE_SCREEN_H__
#define	__PAUSE_SCREEN_H__

typedef struct {
	int			selection;
	int			active;
	DARNIT_MAP		*menu_background;
} PAUSE_SCREEN;

void pausescreen_init();
void pausescreen_draw();

#endif
