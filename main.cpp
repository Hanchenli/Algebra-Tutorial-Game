/*
版本:-1.2.2
开始开发时间:2016.8.25
完成时间:2016.8.2
更新内容:
1.制作了简易的碰撞检测。
Bug修复:无。
新发现Bug:无。
updated version
*/
#include "main.h"

void MoveCursor(int x, int y)
{
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD c = {x, y};
	SetConsoleCursorPosition(hOut, c);
}

double CalFrequency()
{
	static int count;
	static double save;
	static clock_t last, current;
	double timegap;

	++count;
	if(count <= 50)
	    return save;
	count = 0;
	last = current;
	current = clock();
	timegap = (current-last)/(double)CLK_TCK;
	save = 50.0/timegap;
	return save;
}

void display(void)
{
	double FPS = CalFrequency();
	MoveCursor(10,0);								//如果不移动光标,就不能删除其他行的文字,只能删除本行的文字。
	cout<<"\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b";	//删除上次的输出,保证数据输出在窗口的同一位置。
	cout<<"\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b";
	cout<<"FPS = "<<FPS<<endl;
	cout<<"Position:		"<<endl
		<<"  X:"<<positionX<<"		"<<endl
		<<"  Y:"<<positionY<<"		"<<endl
		<<"  Z:"<<positionZ<<"		"<<endl;
	cout<<"VisionLine:		"<<endl
		<<"  Transverse   angle:"<<angleX_Y<<"		"<<endl
		<<"  Longitudinal angle:"<<angleXY_Z<<"		"<<endl;

	glMatrixMode( GL_PROJECTION );
	glLoadIdentity();

	gluPerspective(75.0f+CurrentTotalSpeed/2, (GLdouble)WindowWidth/WindowHeight, 0.01f, 1000.0f);
	//gluPerspective(75.0f , (GLdouble)WindowWidth/WindowHeight, 1.0f, 1000.0f);
	gluLookAt(positionX, positionY, positionZ, orientationX, orientationY, orientationZ, 0, 0, 1); //从视点看远点,z轴方向(0,0,1)是上方向。

	glPushMatrix();
	glClearColor(0.7f, 0.8f, 1.0f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	TriangleAnimation();
	glPopMatrix();
	//DrawMapTemp();
	//TriangleAnimation();
	//DrawCube(2,0,0,0);
	//DrawChunk(&Chunk1Temp[0], 0, 0);

	//Write1MapFile();

	glFlush();
	glutSwapBuffers();
}

void reshape(int w,int h)	//要是窗口长宽比变了,显示比例也要调整。
{
	WindowWidth = w;		//保存新的窗口长、宽。
	WindowHeight = h;

	glViewport(0, 0, WindowWidth, WindowHeight);
	glMatrixMode( GL_PROJECTION );
	glLoadIdentity();
	gluPerspective(75.0f, (GLdouble)WindowWidth/h, 1.0f, 1000.0f);
	glMatrixMode( GL_MODELVIEW );
}

int main(int argc, char *argv[]) 
{ 
	glutInit(&argc, argv); 
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH ); 
	glutInitWindowPosition(100, 100); 
	glutInitWindowSize(WindowWidth, WindowHeight);
	glutCreateWindow("演示程序"); 
	glutReshapeFunc( reshape );
	glutDisplayFunc(display);
	glutIdleFunc(display);  //设置不断调用显示函数。

	// 在这里做一些初始化。
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_TEXTURE_2D);
	ReadAllRules();
	LoadAllCubeTextures();

	//监听鼠标。
	glutMouseFunc(&Mouse);
	glutMotionFunc(&onMouseMove);
	MouseRefresh();			//预先刷新一下显示用的数据。

	//监听键盘。
	glutKeyboardFunc(&TriangleKeyAction);
	glutSpecialFunc(&SpecialKeyAction);

	//设置定时器。
	glutTimerFunc((GLuint)1000/MoveTimerFrequency, timer, 0);//设置定时器。

	Read1MapFile();				//加载地图。
	//MapInit();				//加载地图。
	//ChunkInit(&Chunk1Temp[0]);

	cout<<"已经加载完毕。"<<endl;
	system("pause");		//等待用户准备好。

	//开始!
	glutMainLoop(); 
	return 0; 
} 