#include "main.h"
//control
GLint oldmy = -1,oldmx = -1;
GLfloat r = 1.0f;										//r是视点离当前人物位置的距离。(随便取什么值都可以)

void Mouse(int button, int state, int x, int y)			//处理鼠标点击。
{
	if(state == GLUT_DOWN)								//第一次鼠标按下时,记录鼠标在窗口中的初始坐标。
		oldmx = x,oldmy = y;
}

void MouseRefresh(void)
{
	GLfloat temp;

	if(angleXY_Z >= 0.0f)
	{
		orientationZ = positionZ + r * DEGsin(angleXY_Z);
		temp = r * DEGcos(angleXY_Z);
		orientationX = positionX + temp * DEGsin(angleX_Y);
		orientationY = positionY + temp * DEGcos(angleX_Y);
	}
	else
	{
		orientationZ = positionZ - r * DEGsin(-angleXY_Z);
		temp = -r * DEGcos(-angleXY_Z);
		orientationX = positionX - temp * DEGsin(angleX_Y);
		orientationY = positionY - temp * DEGcos(angleX_Y);
	}
}

void onMouseMove(int x,int y)							//处理鼠标拖动。
{
	angleX_Y -= TurnRangeX_Y * (oldmx - x);				//左右转。
	if(angleX_Y > 360.0f)								//避免旋转角度太大或太小。虽然超出360.0可能不会马上出现问题,但是数值累加得太大或太小会有溢出等风险。
		angleX_Y = 0.0f;
	else if(angleX_Y < 0.0f)
		angleX_Y = 360.0f;

	angleXY_Z += TurnRangeXY_Z * (oldmy - y);			//上下转。
	if(angleXY_Z > HighestOrientationZ)
		angleXY_Z = HighestOrientationZ;				//避免人物看到身后的东西。
	else if(angleXY_Z < LowestOrientationZ)
		angleXY_Z = LowestOrientationZ;

	MouseRefresh();

	oldmx=x,oldmy=y;									//把此时的鼠标坐标作为旧值,为下一次计算增量做准备。
}