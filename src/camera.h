#ifndef __CAMERA_H__
#define	__CAMERA_H__


typedef struct {
	int			x;
	int			y;
	int			follow;
} CAMERA;


void cameraInit();
void cameraLoop();
void cameraMovableFollow(MOVABLE_ENTRY *m);


#endif
