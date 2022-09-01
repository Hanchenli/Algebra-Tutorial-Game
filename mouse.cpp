#include "main.h"
//control
GLint oldmy = -1,oldmx = -1;
GLfloat r = 1.0f;										//r���ӵ��뵱ǰ����λ�õľ��롣(���ȡʲôֵ������)

void Mouse(int button, int state, int x, int y)			//�����������
{
	if(state == GLUT_DOWN)								//��һ����갴��ʱ,��¼����ڴ����еĳ�ʼ���ꡣ
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

void onMouseMove(int x,int y)							//��������϶���
{
	angleX_Y -= TurnRangeX_Y * (oldmx - x);				//����ת��
	if(angleX_Y > 360.0f)								//������ת�Ƕ�̫���̫С����Ȼ����360.0���ܲ������ϳ�������,������ֵ�ۼӵ�̫���̫С��������ȷ��ա�
		angleX_Y = 0.0f;
	else if(angleX_Y < 0.0f)
		angleX_Y = 360.0f;

	angleXY_Z += TurnRangeXY_Z * (oldmy - y);			//����ת��
	if(angleXY_Z > HighestOrientationZ)
		angleXY_Z = HighestOrientationZ;				//�������￴�����Ķ�����
	else if(angleXY_Z < LowestOrientationZ)
		angleXY_Z = LowestOrientationZ;

	MouseRefresh();

	oldmx=x,oldmy=y;									//�Ѵ�ʱ�����������Ϊ��ֵ,Ϊ��һ�μ���������׼����
}