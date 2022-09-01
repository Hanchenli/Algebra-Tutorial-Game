/*
�汾:-1.2.2
��ʼ����ʱ��:2016.8.25
���ʱ��:2016.8.2
��������:
1.�����˼��׵���ײ��⡣
Bug�޸�:�ޡ�
�·���Bug:�ޡ�
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
	MoveCursor(10,0);								//������ƶ����,�Ͳ���ɾ�������е�����,ֻ��ɾ�����е����֡�
	cout<<"\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b";	//ɾ���ϴε����,��֤��������ڴ��ڵ�ͬһλ�á�
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
	gluLookAt(positionX, positionY, positionZ, orientationX, orientationY, orientationZ, 0, 0, 1); //���ӵ㿴Զ��,z�᷽��(0,0,1)���Ϸ���

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

void reshape(int w,int h)	//Ҫ�Ǵ��ڳ���ȱ���,��ʾ����ҲҪ������
{
	WindowWidth = w;		//�����µĴ��ڳ�����
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
	glutCreateWindow("��ʾ����"); 
	glutReshapeFunc( reshape );
	glutDisplayFunc(display);
	glutIdleFunc(display);  //���ò��ϵ�����ʾ������

	// ��������һЩ��ʼ����
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_TEXTURE_2D);
	ReadAllRules();
	LoadAllCubeTextures();

	//������ꡣ
	glutMouseFunc(&Mouse);
	glutMotionFunc(&onMouseMove);
	MouseRefresh();			//Ԥ��ˢ��һ����ʾ�õ����ݡ�

	//�������̡�
	glutKeyboardFunc(&TriangleKeyAction);
	glutSpecialFunc(&SpecialKeyAction);

	//���ö�ʱ����
	glutTimerFunc((GLuint)1000/MoveTimerFrequency, timer, 0);//���ö�ʱ����

	Read1MapFile();				//���ص�ͼ��
	//MapInit();				//���ص�ͼ��
	//ChunkInit(&Chunk1Temp[0]);

	cout<<"�Ѿ�������ϡ�"<<endl;
	system("pause");		//�ȴ��û�׼���á�

	//��ʼ!
	glutMainLoop(); 
	return 0; 
} 