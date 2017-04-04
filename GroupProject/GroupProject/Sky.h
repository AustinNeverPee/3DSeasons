#ifndef _SKY_H_
#define _SKY_H_

#include <gl/glut.h>
#include <iostream>

class Sky{
public:
	Sky();

	//初始化天空的位置，半径和纹理
	void InitSky(float skyX, float skyY, float skyZ, float skyR, unsigned int texture);

	//显示天空
	void ShowSky();

	//获得天空的属性
	float GetSkyX(void);
	float GetSkyY(void);
	float GetSkyZ(void);
	float GetSkyR(void);
	unsigned int GetSkyTexture(void);

public:
	float X;
	float Y;
	float Z;
	float R;
	unsigned int T;
	GLUquadricObj *qobj;
};

#endif


Sky::Sky()
{
	X = 0;
	Y = 0;
	Z = 0;
	R = 1000;
}

void Sky::InitSky(float skyX, float skyY, float skyZ, float skyR, unsigned int texture)
{
	X = skyX;
	Y = skyY;
	Z = skyZ;
	R = skyR;
	T = texture;
	
	qobj = gluNewQuadric();
	gluQuadricNormals(qobj, GLU_SMOOTH);
	gluQuadricTexture(qobj, GL_TRUE);
}

void Sky::ShowSky()
{
	static float r = 0.0;
	r += 0.01;

	glEnable(GL_CULL_FACE);

	glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_FALSE);
	glPushMatrix();

	glCullFace(GL_BACK);

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, T);

	glTranslatef(X, Y, Z);
	glRotatef(r, 0.0f, 1.0f, 0.0f); //天空慢慢旋转,模拟云流动
	glRotatef(90, 1, 0, 0);
	glColor4f(1, 1, 1, 1);
	gluSphere(qobj, R, 32, 32);
	glPopMatrix();
	glDisable(GL_CULL_FACE);
}

float Sky::GetSkyR()
{
	return R;
}
float Sky::GetSkyX()
{
	return X;
}
float Sky::GetSkyY()
{
	return Y;
}
float Sky::GetSkyZ()
{
	return Z;
}