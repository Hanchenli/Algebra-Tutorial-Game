#ifndef _GENERALRULES_H_
#define _GENERALRULES_H_

typedef unsigned char CubeID;
const CubeID AmountOfCubes = 2;	//��Ч��������������ע��,����ID�Ǵ�1��ʼ��,0�ǿ���,��������Ч��������������

//DrawCube.cpp&DrawCube.h���,�涨����ߴ�ȡ�
#ifndef CubeSize		//�������Լ��,����ѭ�����Լ����
	#define CubeSize 1.0f;	//ÿ����������ⳤ������Ϊ��ӿ��ٶ�(��ȥ��������)��
#endif
#ifndef SizeTemp
	#define SizeTemp 0.5f;	//������Ӧ��дCubeSize/2��,��������Ҫ�ڳ�����������,����Ԥ����÷������
#endif

//keyboard.cpp&keyboard.h���,�����ƶ���
const GLfloat FlySpeed = 4;				//���е�����ٶȡ�
const GLfloat FlyHeight = 1;			//ÿ�����Ϸɷ��еĸ߶ȡ�ÿ�����½�����ĸ߶ȡ�
const GLfloat WalkSpeed = 1;			//���ߵ�����ٶȡ�
const GLfloat ArrowKeyTurnRange = 10;	//ʹ�÷����ת��ʱ��ת������,��TurnRangeX_Y��TurnRangeXY_Z���ʹ�á�

//mouse.cpp&mouse.h���,����ת��ȡ�
const GLfloat TurnRangeX_Y = 0.3f,TurnRangeXY_Z = 0.3f;		//TurnRangeX_Y��X��Yƽ����ÿ��ת���ķ���,TurnRangeXY_Z��X��Yƽ����Z֮��ת���ķ��ȡ�
const GLfloat HighestOrientationZ = 89.9f,					//������������ӵ��ĽǶȡ�
			LowestOrientationZ  = -89.9f;					//��������ܸ��ӵ��ĽǶȡ�

//DrawMap.cpp&.h���,���Ƶ�ͼ���Ƶȡ�
#define sight 10					//����ܿ������ٸ�����ķ��顣
const int maxZ = 256;					//��ͼ������ж�ߡ�
#define ChunkSize 16					//һ��chunk�ĳ�����

//timer.cpp&.h���,�����ٶȵȡ�
const GLfloat FlyAirResistance = -3;		//��������,ʹ����ʱ������ʱ�ٶ�˥����ע��,����һ����ֵ��������ٶ�,����һ����ֵ�Ż�������ٶȡ�
enum MoveMode {SuperFlying, flying, walking};
const GLfloat MoveTimerFrequency = 100;		//�����ٶȵĶ�ʱ�����Ƶ��,��λ:Hz��
const GLint SpeedRiseTime = 200;				//�ٶ������ĳ���ʱ��,��λ:���롣

//ReadMapFile.cpp&.h���,�涨��ͼ�ļ���ʽ��
#define SupportedMapFileVersions 1	//֧�ֵĵ�ͼ�ļ��汾����,ĿǰΪ1������ļ��汾������,���ܱ���ȷ��ʶ��,����Ҫ����

#define FileHeadLength 64		//��һ���ļ�ͷ��¼һЩ��Ϣ,����Ϊ64�ֽڡ�ע��:ʹ��seekg��seekp�ȿ���Ҫ��1��
#define VersionNumberPosition 0	//��ͼ�ļ��汾�����ļ��е�λ�á�
#define VersionNumberLength 1	//��ͼ�ļ��汾�ų��ȵ��ֽ�����

#endif