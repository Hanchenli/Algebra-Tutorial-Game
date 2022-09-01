#include "main.h"
//draw cube
void DrawCube(CubeID CubeNumber,GLfloat Xposition,GLfloat Yposition,GLfloat Zposition)	//��(X,Y,Z)������Ʊ��ΪCubeNumber�Ĵ���ͼ���顣
{
	//GLint Xposition = (GLint)((GLfloat)X+0.5f);	//��������ȡ����,��֤�����������ϻ��Ʒ��顣
	//GLint Yposition = (GLint)((GLfloat)Y+0.5f);	//����ͨ������???
	//GLint Zposition = (GLint)((GLfloat)Z+0.5f);
	//GLint Xposition = round(X);	//��������ȡ����,��֤�����������ϻ��Ʒ��顣
	//GLint Yposition = round(Y);
	//GLint Zposition = round(Z);
	GLfloat Xtemp = Xposition + CubeSize;	//Ϊ�˼ӿ��ٶ�,Ԥ����÷������
	GLfloat Ytemp = Yposition + CubeSize;
	GLfloat Ztemp = Zposition - CubeSize;

	if(CubeNumber >AmountOfCubes)	//���Ҫ����Ƶķ��黹û�б�����,
		return;						//��Ӧ�û��ơ���Ȼ���ʻ������±�Խ�硣
	if((*CubeRules[CubeNumber]).IsCube == 1)	//ֻ�������巽�顣
	{
		glColor3f(1.0f, 0.0f, 0.0f);//������"Texture Missing"���ʶ�û��,����Ҳ�ܿ�����ɫ��

		//glEnable(GL_CULL_FACE);		//�����޳�����,�����Ͽ��Լӿ��ٶ�,����������ʵ���Ϻ����ܡ�
		//glCullFace(GL_BACK);
		//ע��:��������޳�����Bug��

		//����������
		if((*CubeRules[CubeNumber]).SurfacesAllTheSame == 0)	//��������治��һ��,��ô��Ҫ��ÿ���浥���ϲ��ʡ�
		{
			//����
			glBindTexture(GL_TEXTURE_2D, CubeTextureNumbers[CubeNumber][0]);
			glBegin(GL_QUADS);
				glTexCoord2f(0.0f, 0.0f); glVertex3f(Xtemp,Ytemp,Zposition);
				glTexCoord2f(0.0f, 1.0f); glVertex3f(Xtemp,Yposition,Zposition);
				glTexCoord2f(1.0f, 1.0f); glVertex3f(Xposition,Yposition,Zposition);
				glTexCoord2f(1.0f, 0.0f); glVertex3f(Xposition,Ytemp,Zposition);
			glEnd();
			//����
			glBindTexture(GL_TEXTURE_2D, CubeTextureNumbers[CubeNumber][3]);
			glBegin(GL_QUADS);
				glTexCoord2f(1.0f, 0.0f); glVertex3f(Xtemp,Ytemp,Ztemp);
				glTexCoord2f(1.0f, 1.0f); glVertex3f(Xtemp,Yposition,Ztemp);
				glTexCoord2f(0.0f, 1.0f); glVertex3f(Xposition,Yposition,Ztemp);
				glTexCoord2f(0.0f, 0.0f); glVertex3f(Xposition,Ytemp,Ztemp);
			glEnd();
			//��������
			glBindTexture(GL_TEXTURE_2D, CubeTextureNumbers[CubeNumber][1]);
			glBegin(GL_QUADS);
				//һ������
				glTexCoord2f(0.0f, 0.0f); glVertex3f(Xposition,Ytemp,Ztemp);
				glTexCoord2f(0.0f, 1.0f); glVertex3f(Xposition,Ytemp,Zposition);
				glTexCoord2f(1.0f, 1.0f); glVertex3f(Xposition,Yposition,Zposition);
				glTexCoord2f(1.0f, 0.0f); glVertex3f(Xposition,Yposition,Ztemp);
				//�����
				glTexCoord2f(1.0f, 0.0f); glVertex3f(Xtemp,Ytemp,Ztemp);
				glTexCoord2f(1.0f, 1.0f); glVertex3f(Xtemp,Ytemp,Zposition);
				glTexCoord2f(0.0f, 1.0f); glVertex3f(Xtemp,Yposition,Zposition);
				glTexCoord2f(0.0f, 0.0f); glVertex3f(Xtemp,Yposition,Ztemp);
			glEnd();
			glBindTexture(GL_TEXTURE_2D, CubeTextureNumbers[CubeNumber][2]);
			glBegin(GL_QUADS);
				//��һ������
				glTexCoord2f(0.0f, 0.0f); glVertex3f(Xposition,Yposition,Ztemp);
				glTexCoord2f(0.0f, 1.0f); glVertex3f(Xposition,Yposition,Zposition);
				glTexCoord2f(1.0f, 1.0f); glVertex3f(Xtemp,Yposition,Zposition);
				glTexCoord2f(1.0f, 0.0f); glVertex3f(Xtemp,Yposition,Ztemp);
				//�����
				glTexCoord2f(1.0f, 0.0f); glVertex3f(Xposition,Ytemp,Ztemp);
				glTexCoord2f(1.0f, 1.0f); glVertex3f(Xposition,Ytemp,Zposition);
				glTexCoord2f(0.0f, 1.0f); glVertex3f(Xtemp,Ytemp,Zposition);
				glTexCoord2f(0.0f, 0.0f); glVertex3f(Xtemp,Ytemp,Ztemp);
			glEnd();
		}
		else												//��Ȼ����Ҫ��θ��Ĳ���
		{
			//����
			glBindTexture(GL_TEXTURE_2D, CubeTextureNumbers[CubeNumber][0]);
			glBegin(GL_QUADS);
				glTexCoord2f(0.0f, 0.0f); glVertex3f(Xtemp,Ytemp,Zposition);
				glTexCoord2f(0.0f, 1.0f); glVertex3f(Xtemp,Yposition,Zposition);
				glTexCoord2f(1.0f, 1.0f); glVertex3f(Xposition,Yposition,Zposition);
				glTexCoord2f(1.0f, 0.0f); glVertex3f(Xposition,Ytemp,Zposition);
			//����
				glTexCoord2f(1.0f, 0.0f); glVertex3f(Xtemp,Ytemp,Ztemp);
				glTexCoord2f(1.0f, 1.0f); glVertex3f(Xtemp,Yposition,Ztemp);
				glTexCoord2f(0.0f, 1.0f); glVertex3f(Xposition,Yposition,Ztemp);
				glTexCoord2f(0.0f, 0.0f); glVertex3f(Xposition,Ytemp,Ztemp);
			//��������
			//һ������
				glTexCoord2f(0.0f, 0.0f); glVertex3f(Xposition,Ytemp,Ztemp);
				glTexCoord2f(0.0f, 1.0f); glVertex3f(Xposition,Ytemp,Zposition);
				glTexCoord2f(1.0f, 1.0f); glVertex3f(Xposition,Yposition,Zposition);
				glTexCoord2f(1.0f, 0.0f); glVertex3f(Xposition,Yposition,Ztemp);
			//�����
				glTexCoord2f(1.0f, 0.0f); glVertex3f(Xtemp,Ytemp,Ztemp);
				glTexCoord2f(1.0f, 1.0f); glVertex3f(Xtemp,Ytemp,Zposition);
				glTexCoord2f(0.0f, 1.0f); glVertex3f(Xtemp,Yposition,Zposition);
				glTexCoord2f(0.0f, 0.0f); glVertex3f(Xtemp,Yposition,Ztemp);
			//��һ������
				glTexCoord2f(0.0f, 0.0f); glVertex3f(Xposition,Yposition,Ztemp);
				glTexCoord2f(0.0f, 1.0f); glVertex3f(Xposition,Yposition,Zposition);
				glTexCoord2f(1.0f, 1.0f); glVertex3f(Xtemp,Yposition,Zposition);
				glTexCoord2f(1.0f, 0.0f); glVertex3f(Xtemp,Yposition,Ztemp);
			//�����
				glTexCoord2f(1.0f, 0.0f); glVertex3f(Xposition,Ytemp,Ztemp);
				glTexCoord2f(1.0f, 1.0f); glVertex3f(Xposition,Ytemp,Zposition);
				glTexCoord2f(0.0f, 1.0f); glVertex3f(Xtemp,Ytemp,Zposition);
				glTexCoord2f(0.0f, 0.0f); glVertex3f(Xtemp,Ytemp,Ztemp);
			glEnd();
		}

		//glDisable(GL_CULL_FACE);//ֹͣ�޳�����,�����Ժ�������
	}

	return;
}

void DrawCubeWithoutTexture(GLfloat X,GLfloat Y,GLfloat Z)	//��(X,Y,Z)�������b������ͼ�ķ���,���ڵ���ѯʹ�á���Ϊ����Ҫ����,���Բ���Ҫ�����š�
{
	//GLint Xposition = (GLint)((GLfloat)X+0.5f);	//��������ȡ����,��֤�����������ϻ��Ʒ��顣
	//GLint Yposition = (GLint)((GLfloat)Y+0.5f);
	//GLint Zposition = (GLint)((GLfloat)Z+0.5f);
	//GLint Xposition = round(X);	//��������ȡ����,��֤�����������ϻ��Ʒ��顣
	//GLint Yposition = round(Y);
	//GLint Zposition = round(Z);
	GLfloat Xposition = (X);
	GLfloat Yposition = (Y);
	GLfloat Zposition = (Z);
	GLfloat Xtemp1 = Xposition + SizeTemp;	//Ϊ�˼ӿ��ٶ�,Ԥ����÷������
	GLfloat Xtemp2 = Xposition - SizeTemp;
	GLfloat Ytemp1 = Xposition + SizeTemp;
	GLfloat Ytemp2 = Xposition - SizeTemp;
	GLfloat Ztemp1 = Xposition + SizeTemp;
	GLfloat Ztemp2 = Xposition - SizeTemp;

	glColor3f(0.0f, 0.0f, 1.0f);	//��ʾ��ɫ��
	glBegin(GL_QUADS);
		glTexCoord2f(0.0f, 0.0f); glVertex3f(Xtemp2,Ytemp2,Ztemp1);
		glTexCoord2f(0.0f, 1.0f); glVertex3f(Xtemp2,Ytemp1,Ztemp1);
		glTexCoord2f(1.0f, 1.0f); glVertex3f(Xtemp1,Ytemp1,Ztemp1);
		glTexCoord2f(1.0f, 0.0f); glVertex3f(Xtemp1,Ytemp2,Ztemp1);
		//����
		glTexCoord2f(1.0f, 0.0f); glVertex3f(Xtemp2,Ytemp2,Ztemp2);
		glTexCoord2f(1.0f, 1.0f); glVertex3f(Xtemp2,Ytemp1,Ztemp2);
		glTexCoord2f(0.0f, 1.0f); glVertex3f(Xtemp1,Ytemp1,Ztemp2);
		glTexCoord2f(0.0f, 0.0f); glVertex3f(Xtemp1,Ytemp2,Ztemp2);
		//��������
		//һ������
		glTexCoord2f(0.0f, 0.0f); glVertex3f(Xtemp1,Ytemp2,Ztemp2);
		glTexCoord2f(0.0f, 1.0f); glVertex3f(Xtemp1,Ytemp2,Ztemp1);
		glTexCoord2f(1.0f, 1.0f); glVertex3f(Xtemp1,Ytemp1,Ztemp1);
		glTexCoord2f(1.0f, 0.0f); glVertex3f(Xtemp1,Ytemp1,Ztemp2);
		//�����
		glTexCoord2f(1.0f, 0.0f); glVertex3f(Xtemp2,Ytemp2,Ztemp2);
		glTexCoord2f(1.0f, 1.0f); glVertex3f(Xtemp2,Ytemp2,Ztemp1);
		glTexCoord2f(0.0f, 1.0f); glVertex3f(Xtemp2,Ytemp1,Ztemp1);
		glTexCoord2f(0.0f, 0.0f); glVertex3f(Xtemp2,Ytemp1,Ztemp2);
		//��һ������
		glTexCoord2f(0.0f, 0.0f); glVertex3f(Xtemp1,Ytemp1,Ztemp2);
		glTexCoord2f(0.0f, 1.0f); glVertex3f(Xtemp1,Ytemp1,Ztemp1);
		glTexCoord2f(1.0f, 1.0f); glVertex3f(Xtemp2,Ytemp1,Ztemp1);
		glTexCoord2f(1.0f, 0.0f); glVertex3f(Xtemp2,Ytemp1,Ztemp2);
		//�����
		glTexCoord2f(1.0f, 0.0f); glVertex3f(Xtemp1,Ytemp2,Ztemp2);
		glTexCoord2f(1.0f, 1.0f); glVertex3f(Xtemp1,Ytemp2,Ztemp1);
		glTexCoord2f(0.0f, 1.0f); glVertex3f(Xtemp2,Ytemp2,Ztemp1);
		glTexCoord2f(0.0f, 0.0f); glVertex3f(Xtemp2,Ytemp2,Ztemp2);
	glEnd();

	return;
}