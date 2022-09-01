#ifndef _PLAYERDATA_H_
#define _PLAYERDATA_H_

extern GLuint WindowWidth ;
extern GLuint WindowHeight;

extern GLfloat positionX,positionY,positionZ;

extern GLfloat orientationX,orientationY,orientationZ;
extern GLfloat angleX_Y,angleXY_Z;

extern GLdouble CurrentTotalSpeed,CorrectTotalSpeed;
extern GLdouble CurrentSpeedAngle,CorrectSpeedAngleIncrement;//运动方向。
extern GLdouble CorrectXIncrement,CorrectYIncrement;
extern GLdouble CurrentXIncrement,CurrentYIncrement;
extern GLuint SpeedRiseCounter;
extern enum MoveMode PlayerMoveMode;

#endif //_PLAYERDATA_H_