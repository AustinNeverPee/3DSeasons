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


AUX_RGBImageRec * CTexture::LoadBMP(CHAR *Filename)				// 载入位图图象
{
	FILE *File=NULL;									// 文件句柄
	if (!Filename)										// 确保文件名已提供
	{
		return NULL;									// 如果没提供，返回 NULL
	}
	File=fopen(Filename,"r");							// 尝试打开文件
	if (File)											// 文件存在么?
	{
		fclose(File);									// 关闭句柄
		return auxDIBImageLoadA(Filename);				// 载入位图并返回指针
	}
	return NULL;										// 如果载入失败，返回 NULL
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
