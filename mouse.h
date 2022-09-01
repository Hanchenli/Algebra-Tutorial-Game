#ifndef _MOUSE_H_
#define _MOUSE_H_

extern GLint oldmy,oldmx;
extern GLfloat r;

extern void Mouse(int button, int state, int x, int y);
extern void MouseRefresh(void);
extern void onMouseMove(int x,int y);

#endif //_MOUSE_H_