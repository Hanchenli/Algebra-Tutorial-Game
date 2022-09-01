//#include <GL/glew.h>
#include "main.h"

//CubeID MapTemp[VisionTemp][VisionTemp][VisionTemp]
//int VisionTemp = 2 * VisionRange +1;
#define VisionTemp (2*VisionRange+1)
//GLuint QueryIDs[(VisionTemp^3) * 6];	//那个6是正方体的6个面。
GLuint QueryIDs[VisionTemp^3];

void DrawMap(void)
{
	//int Xcounter = positionX - VisionRange,Ycounter = positionY - VisionRange,Zcounter = positionZ - VisionRange;
	int Xcounter = 0,Ycounter = 0,Zcounter = 0;
	if(Zcounter < 0)	//如果Zcounter小于0,会把方块绘制到虚空里。
		Zcounter = 0;	//直接置0。

	//glewInit();	//不知道需不需要这句。
	//先对每个方块进行遮挡查询。

	//不需要纹理、光照,不需要往缓冲区中写值。
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