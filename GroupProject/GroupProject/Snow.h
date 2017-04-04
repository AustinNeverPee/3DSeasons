#define	MAX_SNOW_PARTICLES	10000	// ��������������

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

}Sparticles;



class Snow {
public:
	Sparticles particle[MAX_SNOW_PARTICLES];

	float	slowdown = 0.15f;			// ��������
	float length = 0.0025;
	//	float	zoom = .0f;			// ��Z������

	void init();

	void showSnow();
};