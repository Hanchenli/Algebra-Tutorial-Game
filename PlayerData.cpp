#include "main.h"

GLuint WindowWidth = 400;
GLuint WindowHeight = 400;

GLfloat positionX = 0.0f,positionY = 0.0f,positionZ = 3.0f;	//��¼��ҵ�ǰ��λ�á�����ֵ����¼x�ᡢy�ᡢz��λ�á�

GLfloat orientationX = 0.0f,orientationY = 0.0f,orientationZ = 2.0f;//��3��������¼���ӵ��λ�á�
GLfloat angleX_Y = 0.0f,angleXY_Z = -89.9f;				//angleX_Y�����������X��Yƽ���ϵĽǶ�,angleXY_Z��������ߵ�Z��X��Yƽ�����ɵĽǶȡ�
														//angleXY_Z<0,���ǵ���ͷ�����档=0,����ƽ�ӡ�>0,��������ͷ��

GLdouble CurrentTotalSpeed = 0,CorrectTotalSpeed = 0;
GLdouble CurrentSpeedAngle = angleX_Y,CorrectSpeedAngleIncrement = 0;//�˶�����
GLdouble CorrectXIncrement = 0,CorrectYIncrement = 0;
GLdouble CurrentXIncrement = 0,CurrentYIncrement = 0;
GLuint SpeedRiseCounter = SpeedRiseTime * MoveTimerFrequency / 1000;
enum MoveMode PlayerMoveMode = SuperFlying;				//��ҵ��ƶ�ģʽ��SuperFlying=�ɴ�ǽ����,flying=��ͨ����,walking=�������ߡ�