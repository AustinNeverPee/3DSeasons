// Texture.cpp: implementation of the CTexture class.
//
//////////////////////////////////////////////////////////////////////

#include "stdio.h"
#include "Texture.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CTexture::CTexture()
{

}

CTexture::~CTexture()
{

}


AUX_RGBImageRec * CTexture::LoadBMP(CHAR *Filename)				// ����λͼͼ��
{
	FILE *File=NULL;									// �ļ����
	if (!Filename)										// ȷ���ļ������ṩ
	{
		return NULL;									// ���û�ṩ������ NULL
	}
	File=fopen(Filename,"r");							// ���Դ��ļ�
	if (File)											// �ļ�����ô?
	{
		fclose(File);									// �رվ��
		return auxDIBImageLoadA(Filename);				// ����λͼ������ָ��
	}
	return NULL;										// �������ʧ�ܣ����� NULL
}

void CTexture::LoadTexture(char* filename)
{
	img = auxDIBImageLoad(filename);
	glGenTextures(1, &m_ID);
	glBindTexture(GL_TEXTURE_2D, m_ID);
	
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, img->sizeX, img->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, img->data);
}


void CTexture::Apply()
{
	glBindTexture(GL_TEXTURE_2D, m_ID);
}
