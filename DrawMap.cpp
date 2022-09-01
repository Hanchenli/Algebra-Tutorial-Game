//#include <GL/glew.h>
#include "main.h"

//CubeID MapTemp[VisionTemp][VisionTemp][VisionTemp]
//int VisionTemp = 2 * VisionRange +1;
#define VisionTemp (2*VisionRange+1)
//GLuint QueryIDs[(VisionTemp^3) * 6];	//�Ǹ�6���������6���档
GLuint QueryIDs[VisionTemp^3];

void DrawMap(void)
{
	//int Xcounter = positionX - VisionRange,Ycounter = positionY - VisionRange,Zcounter = positionZ - VisionRange;
	int Xcounter = 0,Ycounter = 0,Zcounter = 0;
	if(Zcounter < 0)	//���ZcounterС��0,��ѷ�����Ƶ�����
		Zcounter = 0;	//ֱ����0��

	//glewInit();	//��֪���費��Ҫ��䡣
	//�ȶ�ÿ����������ڵ���ѯ��

	//����Ҫ��������,����Ҫ����������дֵ��
	/*
	glShadeModel(GL_FLAT);
	glDisable(GL_LIGHTING);
	glDisable(GL_COLOR_MATERIAL);
	glDisable(GL_NORMALIZE);
	glDepthMask(GL_FALSE);
	glColorMask(0, 0, 0, 0);
	*/

	//glGenQueries((VisionTemp^3) * 6, QueryIDs);
	//glGenQueries(1, QueryIDs);

	/*
	//currect code
	for(;Zcounter <= positionZ + VisionRange && positionZ <= maxZ;Zcounter++)
	{
		for(;Ycounter <= positionY + VisionRange;Ycounter++)
		{
			for(;Xcounter <= positionX + VisionRange;Xcounter++)
			{
				//QueryIDs[Xcounter+VisionRange][Ycounter+VisionRange][Zcounter+VisionRange] = 1;
				//DrawCube(QueryIDs[Xcounter+VisionRange][Ycounter+31][Zcounter+VisionRange],Xcounter,Ycounter,Zcounter);
				DrawCube(1,Xcounter,Ycounter,Zcounter);
			}
			Xcounter = 0;
		}
		Ycounter = 0;
	}*/
	for(;Zcounter <= VisionRange && Zcounter<= maxZ;;Zcounter++)
	{
		for(;Ycounter <= VisionRange;Ycounter++)
		{
			for(;Xcounter <= VisionRange;Xcounter++)
			{
				//glBeginQuery(GL_SAMPLES_PASSED, QueryIDs[Zcounter*(VisionRange^2)+Ycounter*VisionRange+Xcounter]);
				DrawCubeWithoutTexture(Xcounter,Ycounter,Zcounter);
				//glEndQuery(GL_SAMPLES_PASSED); 
			}
			Xcounter = 0;
		}
		Ycounter = 0;
	}

	//glDeleteQueries(1, QueryIDs);

	 return;
}