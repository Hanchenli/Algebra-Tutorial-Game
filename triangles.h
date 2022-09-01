#ifndef _TRIANGLES_H_
#define _TRIANGLES_H_

struct Point {
     GLfloat position[3];
    int      id;
};

enum Action	{motionless=0, a123=1, a132, a321, a213, a231, a312};

extern void DrawColorfulTriangle(GLfloat *v1, GLfloat *v2, GLfloat *v3);
extern void TriangleAnimation();
extern void TriangleKeyAction(unsigned char key, int x, int y);

#endif