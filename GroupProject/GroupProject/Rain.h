#define	MAX_PARTICLES	50000	// ��������������

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
	float   alpha;

	float	x;					// X λ��
	float	y;					// Y λ��
	float	z;					// Z λ��

	float	xi;					// X ����
	float	yi;					// Y ����
	float	zi;				    // Z ����

	float	xg;					// X �����������ٶ�
	float	yg;					// Y �����������ٶ�
	float	zg;					// Z �����������ٶ�

}particles;
typedef struct{
	float x;
	float y;
	float z;
}points;

static GLfloat colors[12][3] =				// �ʺ���ɫ
{
	{ 1.0f, 1.0f, 0.95f }, { .9f, 0.9f, 0.95f }, { 0.8f, 0.8f, .95f }, { 0.7f, 0.7f, 0.95f },
	{ 1.0f, 1.0f, 1.f }, { 0.9f, 0.9f, 1.f }, { 0.8f, 0.8f, 1.f }, { 0.7f, 0.7f, 1.f },
	{ .0f, .0f, .5f }, { .0f, .0f, .6f }, { .0f, .0f, .7f }, { .0f, .0f, .8f }
};

class Rain {
public:
	particles particle[MAX_PARTICLES];

	float	slowdown = 0.2f;			// ��������
	float length = 0.002;
	//	float	zoom = .0f;			// ��Z������

	void init();

	void showRain();
};
