#ifndef TERRAIN_H
#define TERRAIN_H

#include <cstdio>
#include <math.h>
#include "Functions.h"
#include <GL/glut.h>
#include <GL/GLAUX.H>

class Terrain
{
public:
	Terrain();
	bool init(char* rawname, LPCSTR texturename, float vertexInterval, float heightScale, GLuint &texid);
	void Render();
	float GetHeight(float x, float z);

private:
	float* m_heights;
	int m_iRowNum;
	float m_fVertexInterval;
	float m_fHeightScale;
	GLuint texid;
};


#endif