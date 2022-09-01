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

void Read1MapFile(void)	//读取一个地图文件,文件名是默认的"map.map"
{
	unsigned int FileReadingOperationPosition;		//存储文件读取指针的位置。老用tellg效率不高。

	//char buffer[maxZ];
	fstream MapFile;
	MapFile.open("map.map", ios::in|ios::out|ios::binary);

	//检查地图文件版本。
	FileReadingOperationPosition = VersionNumberPosition;
	MapFile.seekg(FileReadingOperationPosition);
	if(MapFile.get() > SupportedMapFileVersions)	//如果地图文件版本太高,
	{
		cout<<"Map file is not supported!"<<endl;	//报错。
		system("pause");
		return;
	}

	//跳出文件头开始读取"真正的文件内容"。
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

				//MapFile.get((char *)&MapTemp[i][j][0], maxZ, (unsigned char)255);	//读取256个方块的信息;255这个编号是保留的,如果读取到了它,就说明该读取下一格了。
				//FileReadingOperationPosition += maxZ;
				////注意:这样实际上是有问题的,想一下哪里不对。限于时间暂时这样吧。
			}
		}
	}


	MapFile.close();
	return;
}

void Write1MapFile(void)
{
	unsigned int FileWritingOperationPosition,		//存储文件写指针的位置。老用tellp效率不高。
				 FileReadingOperationPosition;		//还有读指针。

	fstream MapFile;
	MapFile.open("map.map", ios::in|ios::out|ios::binary);

	//检查地图文件版本。
	FileReadingOperationPosition = VersionNumberPosition;
	MapFile.seekg(FileReadingOperationPosition);
	if(MapFile.get() > SupportedMapFileVersions)	//如果地图文件版本太高,
	{
		cout<<"Map file is not supported!"<<endl;	//报错。
		system("pause");
		return;
	}

	//跳出文件头开始读取"真正的文件内容"。
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