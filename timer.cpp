#include "main.h"

/*����SpeedManage
*�������ٶ�˥�����������ٶȵȡ�
*/
void SpeedManage(void)
{
	switch(PlayerMoveMode)
	{
		case SuperFlying:
		{
			CorrectXIncrement = DEGsin(CorrectSpeedAngleIncrement+angleX_Y)*CorrectTotalSpeed;
			CorrectYIncrement = DEGcos(CorrectSpeedAngleIncrement+angleX_Y)*CorrectTotalSpeed;

			if(SpeedRiseCounter < SpeedRiseTime * MoveTimerFrequency / 1000)
			{
				CurrentXIncrement += CorrectXIncrement/SpeedRiseTime/MoveTimerFrequency*1000;
				CurrentYIncrement += CorrectYIncrement/SpeedRiseTime/MoveTimerFrequency*1000;

				CurrentTotalSpeed = sqrt(CurrentXIncrement*CurrentXIncrement + CurrentYIncrement*CurrentYIncrement);
				if(CurrentYIncrement >= 0)
				{
					if(asin(CurrentYIncrement/CurrentTotalSpeed)/Pi*180 >= 0)
						CurrentSpeedAngle = asin(CurrentXIncrement/CurrentTotalSpeed) / Pi * 180;
					else
						CurrentSpeedAngle = 360-(asin(CurrentXIncrement/CurrentTotalSpeed) / Pi * 180);
				}
				else
				{
					CurrentSpeedAngle = 180-asin(CurrentXIncrement/CurrentTotalSpeed) / Pi * 180;
				}

				SpeedRiseCounter+=1;
			}

			if(FlyAirResistance < 0.001)
			{
				CurrentTotalSpeed = CurrentTotalSpeed*49/50;
			}
				
			if(CurrentTotalSpeed > FlySpeed*1.5)
			{
				CurrentTotalSpeed = FlySpeed*1.5;
			}
			CurrentXIncrement = CurrentTotalSpeed * DEGsin(CurrentSpeedAngle);
			CurrentYIncrement = CurrentTotalSpeed * DEGcos(CurrentSpeedAngle);

			break;
		}

		default:
			break;
	}

	positionX += CurrentXIncrement/MoveTimerFrequency;
	positionY += CurrentYIncrement/MoveTimerFrequency;

	MouseRefresh();

	return;
}

void timer(int value)
{
	switch(value)
	{
		case 0:	//���Ǵ����ٶȵĶ�ʱ����
		{
			SpeedManage();
			glutTimerFunc((GLuint)1000/MoveTimerFrequency, timer, 0);	//�ٴ����ô����ٶ����ö�ʱ����
			break;
		}
		default:
			break;
	}

	return;
}