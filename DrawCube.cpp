#include "main.h"
//draw cube
void DrawCube(CubeID CubeNumber,GLfloat Xposition,GLfloat Yposition,GLfloat Zposition)	//在(X,Y,Z)坐标绘制编号为CubeNumber的带贴图方块。
{
	//GLint Xposition = (GLint)((GLfloat)X+0.5f);	//四舍五入取整数,保证在整数坐标上绘制方块。
	//GLint Yposition = (GLint)((GLfloat)Y+0.5f);	//不能通过编译???
	//GLint Zposition = (GLint)((GLfloat)Z+0.5f);
	//GLint Xposition = round(X);	//四舍五入取整数,保证在整数坐标上绘制方块。
	//GLint Yposition = round(Y);
	//GLint Zposition = round(Z);
	GLfloat Xtemp = Xposition + CubeSize;	//为了加快速度,预先算好放在这里。
	GLfloat Ytemp = Yposition + CubeSize;
	GLfloat Ztemp = Zposition - CubeSize;

	if(CubeNumber >AmountOfCubes)	//如果要求绘制的方块还没有被做好,
		return;						//不应该绘制。不然访问会数组下标越界。
	if((*CubeRules[CubeNumber]).IsCube == 1)	//只画正方体方块。
	{
		glColor3f(1.0f, 0.0f, 0.0f);//就算连"Texture Missing"材质都没有,至少也能看到红色。

		//glEnable(GL_CULL_FACE);		//允许剔除表面,理论上可以加快速度,不过问题是实际上好像不能。
		//glCullFace(GL_BACK);
		//注意:这个表面剔除仍有Bug。

		//绘制六个面
		if((*CubeRules[CubeNumber]).SurfacesAllTheSame == 0)	//如果六个面不都一样,那么需要给每个面单独上材质。
		{
			//顶面
			glBindTexture(GL_TEXTURE_2D, CubeTextureNumbers[CubeNumber][0]);
			glBegin(GL_QUADS);
				glTexCoord2f(0.0f, 0.0f); glVertex3f(Xtemp,Ytemp,Zposition);
				glTexCoord2f(0.0f, 1.0f); glVertex3f(Xtemp,Yposition,Zposition);
				glTexCoord2f(1.0f, 1.0f); glVertex3f(Xposition,Yposition,Zposition);
				glTexCoord2f(1.0f, 0.0f); glVertex3f(Xposition,Ytemp,Zposition);
			glEnd();
			//底面
			glBindTexture(GL_TEXTURE_2D, CubeTextureNumbers[CubeNumber][3]);
			glBegin(GL_QUADS);
				glTexCoord2f(1.0f, 0.0f); glVertex3f(Xtemp,Ytemp,Ztemp);
				glTexCoord2f(1.0f, 1.0f); glVertex3f(Xtemp,Yposition,Ztemp);
				glTexCoord2f(0.0f, 1.0f); glVertex3f(Xposition,Yposition,Ztemp);
				glTexCoord2f(0.0f, 0.0f); glVertex3f(Xposition,Ytemp,Ztemp);
			glEnd();
			//各个侧面
			glBindTexture(GL_TEXTURE_2D, CubeTextureNumbers[CubeNumber][1]);
			glBegin(GL_QUADS);
				//一个侧面
				glTexCoord2f(0.0f, 0.0f); glVertex3f(Xposition,Ytemp,Ztemp);
				glTexCoord2f(0.0f, 1.0f); glVertex3f(Xposition,Ytemp,Zposition);
				glTexCoord2f(1.0f, 1.0f); glVertex3f(Xposition,Yposition,Zposition);
				glTexCoord2f(1.0f, 0.0f); glVertex3f(Xposition,Yposition,Ztemp);
				//其对面
				glTexCoord2f(1.0f, 0.0f); glVertex3f(Xtemp,Ytemp,Ztemp);
				glTexCoord2f(1.0f, 1.0f); glVertex3f(Xtemp,Ytemp,Zposition);
				glTexCoord2f(0.0f, 1.0f); glVertex3f(Xtemp,Yposition,Zposition);
				glTexCoord2f(0.0f, 0.0f); glVertex3f(Xtemp,Yposition,Ztemp);
			glEnd();
			glBindTexture(GL_TEXTURE_2D, CubeTextureNumbers[CubeNumber][2]);
			glBegin(GL_QUADS);
				//另一个侧面
				glTexCoord2f(0.0f, 0.0f); glVertex3f(Xposition,Yposition,Ztemp);
				glTexCoord2f(0.0f, 1.0f); glVertex3f(Xposition,Yposition,Zposition);
				glTexCoord2f(1.0f, 1.0f); glVertex3f(Xtemp,Yposition,Zposition);
				glTexCoord2f(1.0f, 0.0f); glVertex3f(Xtemp,Yposition,Ztemp);
				//其对面
				glTexCoord2f(1.0f, 0.0f); glVertex3f(Xposition,Ytemp,Ztemp);
				glTexCoord2f(1.0f, 1.0f); glVertex3f(Xposition,Ytemp,Zposition);
				glTexCoord2f(0.0f, 1.0f); glVertex3f(Xtemp,Ytemp,Zposition);
				glTexCoord2f(0.0f, 0.0f); glVertex3f(Xtemp,Ytemp,Ztemp);
			glEnd();
		}
		else												//不然不需要多次更改材质
		{
			//顶面
			glBindTexture(GL_TEXTURE_2D, CubeTextureNumbers[CubeNumber][0]);
			glBegin(GL_QUADS);
				glTexCoord2f(0.0f, 0.0f); glVertex3f(Xtemp,Ytemp,Zposition);
				glTexCoord2f(0.0f, 1.0f); glVertex3f(Xtemp,Yposition,Zposition);
				glTexCoord2f(1.0f, 1.0f); glVertex3f(Xposition,Yposition,Zposition);
				glTexCoord2f(1.0f, 0.0f); glVertex3f(Xposition,Ytemp,Zposition);
			//底面
				glTexCoord2f(1.0f, 0.0f); glVertex3f(Xtemp,Ytemp,Ztemp);
				glTexCoord2f(1.0f, 1.0f); glVertex3f(Xtemp,Yposition,Ztemp);
				glTexCoord2f(0.0f, 1.0f); glVertex3f(Xposition,Yposition,Ztemp);
				glTexCoord2f(0.0f, 0.0f); glVertex3f(Xposition,Ytemp,Ztemp);
			//各个侧面
			//一个侧面
				glTexCoord2f(0.0f, 0.0f); glVertex3f(Xposition,Ytemp,Ztemp);
				glTexCoord2f(0.0f, 1.0f); glVertex3f(Xposition,Ytemp,Zposition);
				glTexCoord2f(1.0f, 1.0f); glVertex3f(Xposition,Yposition,Zposition);
				glTexCoord2f(1.0f, 0.0f); glVertex3f(Xposition,Yposition,Ztemp);
			//其对面
				glTexCoord2f(1.0f, 0.0f); glVertex3f(Xtemp,Ytemp,Ztemp);
				glTexCoord2f(1.0f, 1.0f); glVertex3f(Xtemp,Ytemp,Zposition);
				glTexCoord2f(0.0f, 1.0f); glVertex3f(Xtemp,Yposition,Zposition);
				glTexCoord2f(0.0f, 0.0f); glVertex3f(Xtemp,Yposition,Ztemp);
			//另一个侧面
				glTexCoord2f(0.0f, 0.0f); glVertex3f(Xposition,Yposition,Ztemp);
				glTexCoord2f(0.0f, 1.0f); glVertex3f(Xposition,Yposition,Zposition);
				glTexCoord2f(1.0f, 1.0f); glVertex3f(Xtemp,Yposition,Zposition);
				glTexCoord2f(1.0f, 0.0f); glVertex3f(Xtemp,Yposition,Ztemp);
			//其对面
				glTexCoord2f(1.0f, 0.0f); glVertex3f(Xposition,Ytemp,Ztemp);
				glTexCoord2f(1.0f, 1.0f); glVertex3f(Xposition,Ytemp,Zposition);
				glTexCoord2f(0.0f, 1.0f); glVertex3f(Xtemp,Ytemp,Zposition);
				glTexCoord2f(0.0f, 0.0f); glVertex3f(Xtemp,Ytemp,Ztemp);
			glEnd();
		}

		//glDisable(GL_CULL_FACE);//停止剔除表面,避免以后发生错误。
	}

	return;
}

void DrawCubeWithoutTexture(GLfloat X,GLfloat Y,GLfloat Z)	//在(X,Y,Z)坐标绘制b不带贴图的方块,供遮挡查询使用。因为不需要材质,所以不需要方块编号。
{
	//GLint Xposition = (GLint)((GLfloat)X+0.5f);	//四舍五入取整数,保证在整数坐标上绘制方块。
	//GLint Yposition = (GLint)((GLfloat)Y+0.5f);
	//GLint Zposition = (GLint)((GLfloat)Z+0.5f);
	//GLint Xposition = round(X);	//四舍五入取整数,保证在整数坐标上绘制方块。
	//GLint Yposition = round(Y);
	//GLint Zposition = round(Z);
	GLfloat Xposition = (X);
	GLfloat Yposition = (Y);
	GLfloat Zposition = (Z);
	GLfloat Xtemp1 = Xposition + SizeTemp;	//为了加快速度,预先算好放在这里。
	GLfloat Xtemp2 = Xposition - SizeTemp;
	GLfloat Ytemp1 = Xposition + SizeTemp;
	GLfloat Ytemp2 = Xposition - SizeTemp;
	GLfloat Ztemp1 = Xposition + SizeTemp;
	GLfloat Ztemp2 = Xposition - SizeTemp;

	glColor3f(0.0f, 0.0f, 1.0f);	//显示蓝色。
	glBegin(GL_QUADS);
		glTexCoord2f(0.0f, 0.0f); glVertex3f(Xtemp2,Ytemp2,Ztemp1);
		glTexCoord2f(0.0f, 1.0f); glVertex3f(Xtemp2,Ytemp1,Ztemp1);
		glTexCoord2f(1.0f, 1.0f); glVertex3f(Xtemp1,Ytemp1,Ztemp1);
		glTexCoord2f(1.0f, 0.0f); glVertex3f(Xtemp1,Ytemp2,Ztemp1);
		//底面
		glTexCoord2f(1.0f, 0.0f); glVertex3f(Xtemp2,Ytemp2,Ztemp2);
		glTexCoord2f(1.0f, 1.0f); glVertex3f(Xtemp2,Ytemp1,Ztemp2);
		glTexCoord2f(0.0f, 1.0f); glVertex3f(Xtemp1,Ytemp1,Ztemp2);
		glTexCoord2f(0.0f, 0.0f); glVertex3f(Xtemp1,Ytemp2,Ztemp2);
		//各个侧面
		//一个侧面
		glTexCoord2f(0.0f, 0.0f); glVertex3f(Xtemp1,Ytemp2,Ztemp2);
		glTexCoord2f(0.0f, 1.0f); glVertex3f(Xtemp1,Ytemp2,Ztemp1);
		glTexCoord2f(1.0f, 1.0f); glVertex3f(Xtemp1,Ytemp1,Ztemp1);
		glTexCoord2f(1.0f, 0.0f); glVertex3f(Xtemp1,Ytemp1,Ztemp2);
		//其对面
		glTexCoord2f(1.0f, 0.0f); glVertex3f(Xtemp2,Ytemp2,Ztemp2);
		glTexCoord2f(1.0f, 1.0f); glVertex3f(Xtemp2,Ytemp2,Ztemp1);
		glTexCoord2f(0.0f, 1.0f); glVertex3f(Xtemp2,Ytemp1,Ztemp1);
		glTexCoord2f(0.0f, 0.0f); glVertex3f(Xtemp2,Ytemp1,Ztemp2);
		//另一个侧面
		glTexCoord2f(0.0f, 0.0f); glVertex3f(Xtemp1,Ytemp1,Ztemp2);
		glTexCoord2f(0.0f, 1.0f); glVertex3f(Xtemp1,Ytemp1,Ztemp1);
		glTexCoord2f(1.0f, 1.0f); glVertex3f(Xtemp2,Ytemp1,Ztemp1);
		glTexCoord2f(1.0f, 0.0f); glVertex3f(Xtemp2,Ytemp1,Ztemp2);
		//其对面
		glTexCoord2f(1.0f, 0.0f); glVertex3f(Xtemp1,Ytemp2,Ztemp2);
		glTexCoord2f(1.0f, 1.0f); glVertex3f(Xtemp1,Ytemp2,Ztemp1);
		glTexCoord2f(0.0f, 1.0f); glVertex3f(Xtemp2,Ytemp2,Ztemp1);
		glTexCoord2f(0.0f, 0.0f); glVertex3f(Xtemp2,Ytemp2,Ztemp2);
	glEnd();

	return;
}