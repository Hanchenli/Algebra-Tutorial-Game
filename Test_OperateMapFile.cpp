#include "main.h"

void ChunkInit(CubeID *ChunkTemp)	
{
	for(int i=0;i<ChunkSize;i++)
	{
		for(int j=0;j<ChunkSize;j++)
		{
			ChunkTemp[i*ChunkSize*maxZ+j*maxZ] = 1;
		}
	}

	return;
}

void MapInit(void)		//test only
{
	for(int i=0;i<SightTemp;i++)
	{
		for(int j=0;j<SightTemp;j++)
		{
			MapTemp[i][j][0] = 1;
		}
	}

	return;
}

void Read1MapFile(void)	//��ȡһ����ͼ�ļ�,�ļ�����Ĭ�ϵ�"map.map"
{
	unsigned int FileReadingOperationPosition;		//�洢�ļ���ȡָ���λ�á�����tellgЧ�ʲ��ߡ�

	//char buffer[maxZ];
	fstream MapFile;
	MapFile.open("map.map", ios::in|ios::out|ios::binary);

	//����ͼ�ļ��汾��
	FileReadingOperationPosition = VersionNumberPosition;
	MapFile.seekg(FileReadingOperationPosition);
	if(MapFile.get() > SupportedMapFileVersions)	//�����ͼ�ļ��汾̫��,
	{
		cout<<"Map file is not supported!"<<endl;	//����
		system("pause");
		return;
	}

	//�����ļ�ͷ��ʼ��ȡ"�������ļ�����"��
	FileReadingOperationPosition = FileHeadLength;
	MapFile.seekg(FileReadingOperationPosition);

	for(int i = 0;i < SightTemp;i++)
	{
		for(int j = 0;j < SightTemp;j++)
		{
			for(int k = 0;k < maxZ;k++)
			{
				MapTemp[i][j][k] = MapFile.get();
				FileReadingOperationPosition ++;

				//MapFile.get((char *)&MapTemp[i][j][0], maxZ, (unsigned char)255);	//��ȡ256���������Ϣ;255�������Ǳ�����,�����ȡ������,��˵���ö�ȡ��һ���ˡ�
				//FileReadingOperationPosition += maxZ;
				////ע��:����ʵ�������������,��һ�����ﲻ�ԡ�����ʱ����ʱ�����ɡ�
			}
		}
	}


	MapFile.close();
	return;
}

void Write1MapFile(void)
{
	unsigned int FileWritingOperationPosition,		//�洢�ļ�дָ���λ�á�����tellpЧ�ʲ��ߡ�
				 FileReadingOperationPosition;		//���ж�ָ�롣

	fstream MapFile;
	MapFile.open("map.map", ios::in|ios::out|ios::binary);

	//����ͼ�ļ��汾��
	FileReadingOperationPosition = VersionNumberPosition;
	MapFile.seekg(FileReadingOperationPosition);
	if(MapFile.get() > SupportedMapFileVersions)	//�����ͼ�ļ��汾̫��,
	{
		cout<<"Map file is not supported!"<<endl;	//����
		system("pause");
		return;
	}

	//�����ļ�ͷ��ʼ��ȡ"�������ļ�����"��
	FileWritingOperationPosition = FileHeadLength;
	MapFile.seekp(FileWritingOperationPosition);

	for(int i = 0;i < SightTemp;i++)
	{
		for(int j = 0;j < SightTemp;j++)
		{
			for(int k = 0;k < maxZ;k++)
			{
				MapFile.put(MapTemp[i][j][k]);
				FileWritingOperationPosition ++;
			}
		}
	}


	MapFile.close();
	return;
}