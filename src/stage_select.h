#ifndef __STAGE_SELECT_H__
#define	__STAGE_SELECT_H__

typedef struct {
	DARNIT_TILESHEET	*stage_gfx;
	DARNIT_TILE		*stage;
	int			selected_stage;
} STAGE_SELECT;


void stageSelectMoveCursor();
void stageSelectInit();
void stageSelectDraw();




#endif
