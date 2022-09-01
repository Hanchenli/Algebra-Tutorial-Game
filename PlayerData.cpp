#include "main.h"

GLuint WindowWidth = 400;
GLuint WindowHeight = 400;

GLfloat positionX = 0.0f,positionY = 0.0f,positionZ = 3.0f;	//记录玩家当前的位置。三个值各记录x轴、y轴、z轴位置。

GLfloat orientationX = 0.0f,orientationY = 0.0f,orientationZ = 2.0f;//这3个变量记录了视点的位置。
GLfloat angleX_Y = 0.0f,angleXY_Z = -89.9f;				//angleX_Y是玩家视线在X、Y平面上的角度,angleXY_Z是玩家视线的Z与X、Y平面所成的角度。
														//angleXY_Z<0,则是低着头看地面。=0,则是平视。>0,就是仰着头。

GLdouble CurrentTotalSpeed = 0,CorrectTotalSpeed = 0;
GLdouble CurrentSpeedAngle = angleX_Y,CorrectSpeedAngleIncrement = 0;//运动方向。
GLdouble CorrectXIncrement = 0,CorrectYIncrement = 0;
GLdouble CurrentXIncrement = 0,CurrentYIncrement = 0;
GLuint SpeedRiseCounter = SpeedRiseTime * MoveTimerFrequency / 1000;
enum MoveMode PlayerMoveMode = SuperFlying;				//玩家的移动模式。SuperFlying=可穿墙飞行,flying=普通飞行,walking=正常行走。