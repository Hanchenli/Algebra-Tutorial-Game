#ifndef _GENERALRULES_H_
#define _GENERALRULES_H_

typedef unsigned char CubeID;
const CubeID AmountOfCubes = 2;	//有效方块种类总数。注意,方块ID是从1开始的,0是空气,不计入有效方块种类总数。

//DrawCube.cpp&DrawCube.h相关,规定方块尺寸等。
#ifndef CubeSize		//如果另有约定,就遵循另外的约定。
	#define CubeSize 1.0f;	//每个正方体的棱长。定义为宏加快速度(免去变量访问)。
#endif
#ifndef SizeTemp
	#define SizeTemp 0.5f;	//本来是应该写CubeSize/2的,但是那样要在程序里做除法,所以预先算好放在这里。
#endif

//keyboard.cpp&keyboard.h相关,控制移动。
const GLfloat FlySpeed = 4;				//飞行的最高速度。
const GLfloat FlyHeight = 1;			//每次向上飞飞行的高度、每次向下降降落的高度。
const GLfloat WalkSpeed = 1;			//行走的最高速度。
const GLfloat ArrowKeyTurnRange = 10;	//使用方向键转向时的转动幅度,与TurnRangeX_Y、TurnRangeXY_Z配合使用。

//mouse.cpp&mouse.h相关,控制转向等。
const GLfloat TurnRangeX_Y = 0.3f,TurnRangeXY_Z = 0.3f;		//TurnRangeX_Y是X、Y平面上每次转动的幅度,TurnRangeXY_Z是X、Y平面与Z之间转动的幅度。
const GLfloat HighestOrientationZ = 89.9f,					//人物最高能仰视到的角度。
			LowestOrientationZ  = -89.9f;					//人物最低能俯视到的角度。

//DrawMap.cpp&.h相关,控制地图绘制等。
#define sight 10					//最多能看到多少格以外的方块。
const int maxZ = 256;					//地图最高能有多高。
#define ChunkSize 16					//一个chunk的长、宽。

//timer.cpp&.h相关,控制速度等。
const GLfloat FlyAirResistance = -3;		//空气阻力,使飞行时和行走时速度衰减。注意,给它一个正值会带来加速度,给它一个负值才会带来减速度。
enum MoveMode {SuperFlying, flying, walking};
const GLfloat MoveTimerFrequency = 100;		//管理速度的定时器溢出频率,单位:Hz。
const GLint SpeedRiseTime = 200;				//速度上升的持续时间,单位:毫秒。

//ReadMapFile.cpp&.h相关,规定地图文件格式。
#define SupportedMapFileVersions 1	//支持的地图文件版本数量,目前为1。如果文件版本大于它,则不能被正确地识别,就需要报错。

#define FileHeadLength 64		//有一段文件头记录一些信息,长度为64字节。注意:使用seekg、seekp等可能要减1。
#define VersionNumberPosition 0	//地图文件版本号在文件中的位置。
#define VersionNumberLength 1	//地图文件版本号长度的字节数。

#endif