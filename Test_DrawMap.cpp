#include "main.h"

CubeID MapTemp[SightTemp][SightTemp][maxZ] = {0};
CubeID Chunk1Temp[ChunkSize * ChunkSize * maxZ]= {0};
GLuint QueryIDs[SightTemp^3];

void DrawMapTemp(void)
{
	int Xcounter = 0,Ycounter = 0,Zcounter = 0;
	//if(Zcounter < 0)	//���ZcounterС��0,��ѷ�����Ƶ�����
	//	Zcounter = 0;		//ֱ����0��

	//for(;Zcounter < SightTemp&& Zcounter<= maxZ;Zcounter++)
	for(;Zcounter < SightTemp;Zcounter++)
	{
		for(;Ycounter < SightTemp;Ycounter++)
		{
			for(;Xcounter < SightTemp;Xcounter++)
			{
				if(!MapTemp[Xcounter][Ycounter][Zcounter])
					continue;	//�ǿ����ͱ������,ʡȥ�������á�
				DrawCube(MapTemp[Xcounter][Ycounter][Zcounter],Xcounter,Ycounter,Zcounter);
			}
			Xcounter = 0;
		}
		Ycounter = 0;
	}

	 return;
}

void DrawChunk(CubeID *ChunkTemp,GLint ChunkPositionX,GLint ChunkPositionY)
{
	int Xcounter = ChunkPositionX * 16, Ycounter = ChunkPositionY * 16, Zcounter = 0, IndexTemp = (Xcounter*ChunkSize*maxZ)+(Ycounter*maxZ)+Zcounter;

	for(;Xcounter < ChunkPositionX * 16 + ChunkSize;Xcounter++)
	{
		for(;Ycounter < ChunkPositionY * 16 + ChunkSize;Ycounter++)
		{
			for(;Zcounter < maxZ;Zcounter++)
			{
				if(!ChunkTemp[IndexTemp])
				{
					IndexTemp ++;
					continue;	//�ǿ����ͱ������,ʡȥ�������á�
				}
				DrawCube(ChunkTemp[IndexTemp], Xcounter, Ycounter, Zcounter);
				//DrawCube(1,Xcounter, Ycounter ,Zcounter);
				//DrawCube(1,0,0,0);

				IndexTemp ++;
			}
			Zcounter = 0;
			//IndexTemp += maxZ;
		}
		Ycounter = ChunkPositionY * 16;	
	}

	 return;
}
