#include "main.h"
#include <queue>

queue<Action> ActionList;

const GLfloat Tv1[]={0.0f,1.0f,0.0f},Tv2[]={-0.866f,-0.5f,0.0f},Tv3[]={0.866f,-0.5f,0.0f};
GLfloat Tc1[]={1.0f, 0.0f, 0.0f, 0.5f},Tc2[]={0.0f, 1.0f, 0.0f, 0.5f},Tc3[]={0.0f, 0.0f, 1.0f, 0.5f};
const GLfloat *Tp1=Tc1,*Tp2=Tc2,*Tp3=Tc3;

const GLuint TriangleAnimationFrameSpan=60;	//How many frames it takes to complete an animation
GLuint CurrentTriangleAnimationFrame=0;
const GLuint TriangleLightEffectFrameSpan=300;
GLuint CurrentTriangleLightEffectFrame=0;
const GLuint TriangleLightTransitionFrameSpan=300;
GLuint CurrentTriangleLightTransitionFrame=0;
GLfloat FramePercentage=0;
bool NoLightEffect,LightInTransition,NoAnimation;

void DrawColorfulTriangle()
{
	glBegin(GL_TRIANGLES);
		glColor4fv(Tp1);
		glVertex3fv(Tv1);
		glColor4fv(Tp2);
		glVertex3fv(Tv2);
		glColor4fv(Tp3);
		glVertex3fv(Tv3);
	glEnd();
}

void TriangleAnimation()
{
	CurrentTriangleAnimationFrame+=ActionList.size();	//The more pending actions, finish the faster.
	FramePercentage+=(GLfloat)ActionList.size()/(GLfloat)TriangleAnimationFrameSpan;
	
	if(CurrentTriangleAnimationFrame>=TriangleAnimationFrameSpan)
	{
		const GLfloat *tmp;
		switch(ActionList.front())
		{
			case a132:	tmp=Tp2;	Tp2=Tp3;	Tp3=tmp;				break;
			case a213:	tmp=Tp1;	Tp1=Tp2;	Tp2=tmp;				break;
			case a321:	tmp=Tp1;	Tp1=Tp3;	Tp3=tmp;				break;
			case a312:	tmp=Tp3;	Tp3=Tp2;	Tp2=Tp1;	Tp1=tmp;	break;
			case a231:	tmp=Tp1;	Tp1=Tp2;	Tp2=Tp3;	Tp3=tmp;	break;
			case a123:													break;
		}

		CurrentTriangleAnimationFrame=0;
		FramePercentage=0;
		ActionList.pop();
	}
	else if(!ActionList.empty())
	{
		if(!NoAnimation)
			switch(ActionList.front())
			{
				case a132:	glRotatef( 180.0f*FramePercentage,  0.0f,    1.0f, 0.0f);	break;
				case a213:	glRotatef( 180.0f*FramePercentage,  0.866f,	-0.5f, 0.0f);	break;
				case a321:	glRotatef( 180.0f*FramePercentage, -0.866f,	-0.5f, 0.0f);	break;
				case a312:	glRotatef( 120.0f*FramePercentage,  0.0f,    0.0f, 1.0f);	break;
				case a231:	glRotatef(-120.0f*FramePercentage,  0.0f,    0.0f, 1.0f);	break;
				case a123:	glTranslatef(0.0f, 0.0f, (1-cos(FramePercentage*2*Pi))/4);	break;
				case motionless:	CurrentTriangleAnimationFrame=TriangleAnimationFrameSpan;	//Force it to skip to the next round
			}
		else
			CurrentTriangleAnimationFrame=TriangleAnimationFrameSpan;
	}

	GLfloat LightFramePercentage=(GLfloat)CurrentTriangleLightEffectFrame/(GLfloat)TriangleLightEffectFrameSpan;
	if(LightInTransition)
	{
		CurrentTriangleLightTransitionFrame++;
		if(CurrentTriangleLightTransitionFrame>=TriangleLightTransitionFrameSpan)
		{
			LightInTransition=false;
			CurrentTriangleLightTransitionFrame=0;
		}
		CurrentTriangleLightEffectFrame++;
		CurrentTriangleLightEffectFrame%=TriangleLightEffectFrameSpan;

		Tc1[0]=(sin( LightFramePercentage           *Pi*2)/4.0f+0.875f);
		Tc2[1]=(sin((LightFramePercentage+1.0f/3.0f)*Pi*2)/4.0f+0.875f);
		Tc3[2]=(sin((LightFramePercentage+2.0f/3.0f)*Pi*2)/4.0f+0.875f);
		GLfloat TransitionPercentage=sin(CurrentTriangleLightTransitionFrame/TriangleLightTransitionFrameSpan*Pi/2.0f);
		if(NoLightEffect)
			TransitionPercentage=1-TransitionPercentage;
		Tc1[0]=Tc1[0]*TransitionPercentage+0.75f*(1-TransitionPercentage);
		Tc2[1]=Tc2[1]*TransitionPercentage+0.75f*(1-TransitionPercentage);
		Tc3[2]=Tc3[2]*TransitionPercentage+0.75f*(1-TransitionPercentage);
	}
	else if(!NoLightEffect)
	{
		CurrentTriangleLightEffectFrame++;
		CurrentTriangleLightEffectFrame%=TriangleLightEffectFrameSpan;
		Tc1[0]=sin( (GLfloat)CurrentTriangleLightEffectFrame/(GLfloat)TriangleLightEffectFrameSpan           *Pi*2)/4.0f+0.875f;
		Tc2[1]=sin(((GLfloat)CurrentTriangleLightEffectFrame/(GLfloat)TriangleLightEffectFrameSpan+1.0f/3.0f)*Pi*2)/4.0f+0.875f;
		Tc3[2]=sin(((GLfloat)CurrentTriangleLightEffectFrame/(GLfloat)TriangleLightEffectFrameSpan+2.0f/3.0f)*Pi*2)/4.0f+0.875f;
	}
	else
		Tc1[0]=Tc2[1]=Tc3[2]=0.75f;

	DrawColorfulTriangle();
}

void TriangleKeyAction(unsigned char key, int x, int y)
{
	switch(key)
	{
		case '1':	ActionList.push(a123);			break;
		case '2':	ActionList.push(a132);			break;
		case '3':	ActionList.push(a321);			break;
		case '4':	ActionList.push(a213);			break;
		case '5':	ActionList.push(a231);			break;
		case '6':	ActionList.push(a312);			break;
		case '0':	ActionList.push(motionless);	break;	//Help stop animation
		case 'r':	Tp1=Tc1; Tp2=Tc2; Tp3=Tc3;		break;	//Reset position
		case 'l':	NoLightEffect = !NoLightEffect;	
					LightInTransition=true;
					break;	//Enable/disable light effect
		case 'n':	NoAnimation   = !NoAnimation;	break;	//Enable/disable animation
		default:	KeyAction(key, x, y);
	}
}