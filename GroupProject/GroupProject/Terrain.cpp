#include "Terrain.h"

Terrain::Terrain(){
	m_heights = NULL;
}

bool Terrain::init(char* rawname, LPCSTR texturename, float vertexInterval, float heightScale, GLuint &tex){
	glEnable(GL_TEXTURE_2D);
	texid = tex;
	if (!LoadBMP(texturename, texid)){
		return false;
	}


	m_fVertexInterval = vertexInterval;
	m_fHeightScale = heightScale;


	// step1 : 读取高度
	FILE* fp = fopen(rawname, "rb");
	if (!fp)
		return false;

	fseek(fp, 0, SEEK_END);
	int fileSize = ftell(fp);
	fseek(fp, 0, SEEK_SET);

	int iVertexNum = fileSize;
	m_iRowNum = (int)sqrt((double)fileSize);
	unsigned char* ucHeights = new unsigned char[iVertexNum];
	m_heights = new float[iVertexNum];

	fread(ucHeights, iVertexNum, 1, fp);
	fclose(fp);

	int i;
	for (i = 0; i < iVertexNum; i++)
		m_heights[i] = ucHeights[i] * m_fHeightScale;

	delete[] ucHeights;

	glDisable(GL_TEXTURE_2D);
}



float Terrain::GetHeight(float x, float z)
{
	float terrainSize = (m_iRowNum - 1) * m_fVertexInterval;

	x = terrainSize * 0.5f + x;
	z = terrainSize * 0.5f - z;

	x /= m_fVertexInterval;
	z /= m_fVertexInterval;

	int i = (int)z;
	int j = (int)x;

	//计算出A,B,C,D四个点的高度
	float A = m_heights[i * m_iRowNum + j];
	float B = m_heights[i * m_iRowNum + j + 1];
	float C = m_heights[(i + 1) * m_iRowNum + j];
	float D = m_heights[(i + 1) * m_iRowNum + j + 1];

	float dx = x - j;
	float dz = z - i;
	float height;

	if (dx + dz < 1.0f) // 如果落在三角形ABC中
	{
		height = A + (B - A) * dx + (C - A) * dz;
	}
	else //如果落在三角形BCD中
	{
		height = D + (B - D) * (1.0f - dz) + (C - D) * (1.0f - dx);
	}
	return height;
}

void Terrain::Render(){
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texid);
	glBegin(GL_TRIANGLES);
	//glBegin(GL_LINES);
	float fStartZ = -(m_iRowNum - 1) * m_fVertexInterval * 0.5f;
	float fStartX = fStartZ;
	for (int j = 0; j < m_iRowNum - 1; j++){
		for (int i = 0; i < m_iRowNum - 1; i++){

			glTexCoord2f((float)j / (float)(m_iRowNum - 1), (float)i / (float)(m_iRowNum - 1));
			glVertex3f(fStartX + j * m_fVertexInterval, m_heights[j * m_iRowNum + i] - 29, fStartZ + (float)i * (float)m_fVertexInterval);

			glTexCoord2f((float)(j + 1) / (float)(m_iRowNum - 1), (float)(i + 1) / (float)(m_iRowNum - 1));
			glVertex3f(fStartX + (j + 1) * m_fVertexInterval, m_heights[(j + 1) * m_iRowNum + (i + 1)] - 29, fStartZ + (float)(i + 1) * (float)m_fVertexInterval);

			glTexCoord2f((float)(j) / (float)(m_iRowNum - 1), (float)(i + 1) / (float)(m_iRowNum - 1));
			glVertex3f(fStartX + (j)* m_fVertexInterval, m_heights[(j)* m_iRowNum + (i + 1)] - 29, fStartZ + (float)(i + 1) * (float)m_fVertexInterval);

			glTexCoord2f((float)j / (float)(m_iRowNum - 1), (float)i / (float)(m_iRowNum - 1));
			glVertex3f(fStartX + j * m_fVertexInterval, m_heights[j * m_iRowNum + i] - 29, fStartZ + (float)i * (float)m_fVertexInterval);

			glTexCoord2f((float)(j + 1) / (float)(m_iRowNum - 1), (float)(i) / (float)(m_iRowNum - 1));
			glVertex3f(fStartX + (j + 1) * m_fVertexInterval, m_heights[(j + 1) * m_iRowNum + (i)] - 29, fStartZ + (float)(i)* (float)m_fVertexInterval);

			glTexCoord2f((float)(j + 1) / (float)(m_iRowNum - 1), (float)(i + 1) / (float)(m_iRowNum - 1));
			glVertex3f(fStartX + (j + 1) * m_fVertexInterval, m_heights[(j + 1) * m_iRowNum + (i + 1)] - 29, fStartZ + (float)(i + 1) * (float)m_fVertexInterval);


			/*glVertex3f(0.0f, 0.0f, -7.0f);
			glVertex3f(0.0f, 1.0f, -7.0f);
			glVertex3f(1.0f, 1.0f, -7.0f);
			glVertex3f(1.0f, 0.0f, -7.0f);*/
		}
	}
	glEnd();

	glDisable(GL_TEXTURE_2D);
}