#ifndef __PAUSE_SCREEN_H__
#define	__PAUSE_SCREEN_H__

typedef struct {
	int			selection;
	int			active;
	DARNIT_MAP		*menu_background;
	DARNIT_TEXT_SURFACE	*menu_options;
	DARNIT_TILE		*selected;
} PAUSE_SCREEN;

void pausescreen_init();
void pausescreen_generate_menu_text();
void pausescreen_draw();

#endif
