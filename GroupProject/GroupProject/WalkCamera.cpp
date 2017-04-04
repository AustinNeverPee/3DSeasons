// WalkCamera.cpp: implementation of the WalkCamera class.
//
//////////////////////////////////////////////////////////////////////

#include "WalkCamera.h"
#include "gl\glut.h"
#include "math.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

WalkCamera::WalkCamera(float eyex, float eyey, float eyez)
{
	m_fEye[0] = eyex;
	m_fEye[1] = eyey;
	m_fEye[2] = eyez;
}

WalkCamera::~WalkCamera()
{

}

void WalkCamera::Left()
{
	m_fTheta += dTheta;
}

void WalkCamera::Right()
{
	m_fTheta -= dTheta;
}

void WalkCamera::Up()
{
	m_fAlpha += dAlpha;
}

void WalkCamera::Down()
{
	m_fAlpha -= dAlpha;
}

void WalkCamera::Forward()
{
	m_fEye[0] -= dStep*sin(m_fTheta);
	m_fEye[2] -= dStep*cos(m_fTheta);

}

void WalkCamera::Backward()
{
	m_fEye[0] += dStep*sin(m_fTheta);
	m_fEye[2] += dStep*cos(m_fTheta);

}

void WalkCamera::Look()
{
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	float dest[3];
	dest[0] = m_fEye[0] - D*cos(m_fAlpha) * sin(m_fTheta);
	dest[1] = m_fEye[1] + D*sin(m_fAlpha);
	dest[2] = m_fEye[2] - D*cos(m_fAlpha) * cos(m_fTheta);
	gluLookAt(m_fEye[0],m_fEye[1],m_fEye[2], dest[0], dest[1], dest[2], 0,1,0);
}
