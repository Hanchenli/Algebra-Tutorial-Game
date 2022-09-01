#ifndef _MAIN_H_
#define _MAIN_H_

#include <windows.h>
#include <iostream>
#include <fstream>
using namespace std;
#define GLUT_DISABLE_ATEXIT_HACK	//必须用它解决___glutInitWithExit@12问题???
#include <GL/glew.h>	//好像glGenQueries等等遮挡查询相关的函数和宏只在这里才能找到。
#include <GL/glut.h>
//#include "glut.h"
#pragma comment (lib, "glew32.lib")	//glew需要它。
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