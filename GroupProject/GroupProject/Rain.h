#define	MAX_PARTICLES	50000	// 定义最大的粒子数

#include<gl/glut.h>
#include <gl\gl.h>												/**< 包含OpenGL头文件 */
#include <gl\glu.h>																						
#include<iostream>
#include<vector>

using namespace std;

#pragma comment(lib, "opengl32.lib")							/**< 包含OpenGL链接库文件 */
#pragma comment(lib, "glu32.lib")	
#pragma comment(lib, "glut32.lib")	


typedef struct						// 创建粒子数据结构
{
	bool	active;					// 是否激活 
	float	life;					// 粒子生命
	float	fade;					// 衰减速度

	float	r;					// 红色值
	float	g;					// 绿色值
	float	b;					// 蓝色值
	float   alpha;

	float	x;					// X 位置
	float	y;					// Y 位置
	float	z;					// Z 位置

	float	xi;					// X 方向
	float	yi;					// Y 方向
	float	zi;				    // Z 方向

	float	xg;					// X 方向重力加速度
	float	yg;					// Y 方向重力加速度
	float	zg;					// Z 方向重力加速度

}particles;
typedef struct{
	float x;
	float y;
	float z;
}points;

static GLfloat colors[12][3] =				// 彩虹颜色
{
	{ 1.0f, 1.0f, 0.95f }, { .9f, 0.9f, 0.95f }, { 0.8f, 0.8f, .95f }, { 0.7f, 0.7f, 0.95f },
	{ 1.0f, 1.0f, 1.f }, { 0.9f, 0.9f, 1.f }, { 0.8f, 0.8f, 1.f }, { 0.7f, 0.7f, 1.f },
	{ .0f, .0f, .5f }, { .0f, .0f, .6f }, { .0f, .0f, .7f }, { .0f, .0f, .8f }
};

class Rain {
public:
	particles particle[MAX_PARTICLES];

	float	slowdown = 0.2f;			// 减速粒子
	float length = 0.002;
	//	float	zoom = .0f;			// 沿Z轴缩放

	void init();

	void showRain();
};
