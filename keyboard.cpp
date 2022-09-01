#include "main.h"

void KeyAction(unsigned char key, int x, int y)
{
	switch(PlayerMoveMode)
	{
		case SuperFlying:
		{
			switch(key)
			{
				case 'W':	//不管是大写小写都执行同样的动作。
				case 'w':	//前进。
				{
					CorrectSpeedAngleIncrement = 0;
					CorrectTotalSpeed = FlySpeed;
					CorrectXIncrement = DEGsin(CorrectSpeedAngleIncrement+angleX_Y)*CorrectTotalSpeed;
					CorrectYIncrement = DEGcos(CorrectSpeedAngleIncrement+angleX_Y)*CorrectTotalSpeed;
					SpeedRiseCounter = 0;
					break;
				}
				case 'A':
				case 'a':	//不改变面朝的方向而向左飞行。
				{
					CorrectSpeedAngleIncrement = 270.0f;
					CorrectTotalSpeed = FlySpeed;
					CorrectXIncrement = DEGsin(CorrectSpeedAngleIncrement+angleX_Y)*CorrectTotalSpeed;
					CorrectYIncrement = DEGcos(CorrectSpeedAngleIncrement+angleX_Y)*CorrectTotalSpeed;
					SpeedRiseCounter = 0;
					break;
				}
				case 'S':
				case 's':	//后退。
				{
					CorrectSpeedAngleIncrement = 180.0f;
					CorrectTotalSpeed = FlySpeed;
					CorrectXIncrement = DEGsin(CorrectSpeedAngleIncrement+angleX_Y)*CorrectTotalSpeed;
					CorrectYIncrement = DEGcos(CorrectSpeedAngleIncrement+angleX_Y)*CorrectTotalSpeed;
					SpeedRiseCounter = 0;
					break;
				}
				case 'D':
				case 'd':	//不改变面朝的方向而向右飞行。
				{
					CorrectSpeedAngleIncrement = 90.0f;
					CorrectTotalSpeed = FlySpeed;
					CorrectXIncrement = DEGsin(CorrectSpeedAngleIncrement+angleX_Y)*CorrectTotalSpeed;
					CorrectYIncrement = DEGcos(CorrectSpeedAngleIncrement+angleX_Y)*CorrectTotalSpeed;
					SpeedRiseCounter = 0;
					break;
				}
				case ' ':	//向上飞。
				{
					positionZ += FlyHeight;
					break;
				}
				case 'Z':
				case 'z':	//飞行着向下降。
				{
					positionZ -= FlyHeight;
					break;
				}
				default:
					break;
			}

			break;
		}
		default:
			break;
	}

	MouseRefresh();

	return;
}

void SpecialKeyAction(int key, int x, int y)
{
	// make a choice
	switch(key)
	{
		case GLUT_KEY_RIGHT:
		{
			angleX_Y += TurnRangeX_Y * ArrowKeyTurnRange;
			if(angleX_Y > 360.0f)
				angleX_Y = 0.0f;
			break;
		}
		case GLUT_KEY_LEFT:
		{
			angleX_Y -= TurnRangeX_Y * ArrowKeyTurnRange;
			if(angleX_Y < 0.0f)
				angleX_Y = 360.0f;
			break;
		}
		case GLUT_KEY_UP:
		{
			angleXY_Z += TurnRangeXY_Z * ArrowKeyTurnRange;
			if(angleXY_Z > HighestOrientationZ)
				angleXY_Z = HighestOrientationZ;
			break;
		}
		case GLUT_KEY_DOWN:
		{
			angleXY_Z -= TurnRangeXY_Z * ArrowKeyTurnRange;
			if(angleXY_Z < LowestOrientationZ)
				angleXY_Z = LowestOrientationZ;
			break;
		}
		default:
			break;
	}

	MouseRefresh();

	return;
}