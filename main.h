#ifndef _MAIN_H_
#define _MAIN_H_

#include <windows.h>
#include <iostream>
#include <fstream>
using namespace std;
#define GLUT_DISABLE_ATEXIT_HACK	//�����������___glutInitWithExit@12����???
#include <GL/glew.h>	//����glGenQueries�ȵ��ڵ���ѯ��صĺ����ͺ�ֻ����������ҵ���
#include <GL/glut.h>
//#include "glut.h"
#pragma comment (lib, "glew32.lib")	//glew��Ҫ����
#include <time.h>
#include <math.h>
#include "MyMath.h"
#include <stdlib.h>
#include "GeneralRules.h"
#include "PlayerData.h"
#include "mouse.h"
#include "keyboard.h"
#include "ReadRules.h"
#include "LoadBitmap.h"
#include "DrawCube.h"
#include "DrawMap.h"
#include "timer.h"
#include "OperateMapFile.h"
#include "triangles.h"

#endif