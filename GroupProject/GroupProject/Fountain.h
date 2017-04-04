#define	MAX_FOUNTAIN_PARTICLES	2000		// ��������������
#include<gl/glut.h>
#include <gl\gl.h>												/**< ����OpenGLͷ�ļ� */
#include <gl\glu.h>																						
#include<iostream>
#include<vector>

using namespace std;

#pragma comment(lib, "opengl32.lib")							/**< ����OpenGL���ӿ��ļ� */
#pragma comment(lib, "glu32.lib")	
#pragma comment(lib, "glut32.lib")	


typedef struct						// �����������ݽṹ
{
	bool	active;					// �Ƿ񼤻� 
	float	life;					// ��������
	float	fade;					// ˥���ٶ�

	float	r;					// ��ɫֵ
	float	g;					// ��ɫֵ
	float	b;					// ��ɫֵ

	float	x;					// X λ��
	float	y;					// Y λ��
	float	z;					// Z λ��

	float	xi;					// X ����
	float	yi;					// Y ����
	float	zi;				    // Z ����

	float	xg;					// X �����������ٶ�
	float	yg;					// Y �����������ٶ�
	float	zg;					// Z �����������ٶ�

}Fparticles;
typedef struct{
	float x;
	float y;
	float z;
}Fpoints;

static GLfloat Fcolors[12][3] =				// �ʺ���ɫ
{
	{ 1.0f, 1.0f, 1.0f }, { .9f, 0.9f, 1.0f }, { 0.8f, 0.8f, 1.0f }, { 0.7f, 0.7f, 1.0f },
	{ 0.6f, 0.6f, 1.f }, { 0.6f, 0.8f, 1.f }, { 0.7f, 0.8f, 1.f }, { 0.8f, 0.8f, 1.f },
	{ 0.5f, 0.8f, 1.0f }, { 1.0f, 1.0f, 1.0f }, { 1.0f, 1.0f, 1.0f }, { 1.0f, 1.0f,1.0f }
};

class Fountain {
public:
	Fparticles particle[MAX_FOUNTAIN_PARTICLES];
	Fpoints center;
	float	slowdown = 2.0f;			// ��������
	float	xspeed;				// X������ٶ�
	float	yspeed;				// Y������ٶ�
	float	zoom = .0f;			// ��Z������



	void init();
	void setCenter(float x_, float y_, float z_);
	void display();
};
