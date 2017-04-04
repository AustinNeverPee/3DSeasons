// Texture.h: interface for the CTexture class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_TEXTURE_H__78301D61_46EA_4AC8_B35D_E949A63804AB__INCLUDED_)
#define AFX_TEXTURE_H__78301D61_46EA_4AC8_B35D_E949A63804AB__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "gl\glaux.h"

class CTexture  
{
public:
	CTexture();
	virtual ~CTexture();

	AUX_RGBImageRec *LoadBMP(CHAR *Filename);				// ‘ÿ»ÎŒªÕºÕºœÛ
	void LoadTexture(char* filename);

	void Apply();


protected:
	AUX_RGBImageRec* img;
	GLuint m_ID;
};

#endif // !defined(AFX_TEXTURE_H__78301D61_46EA_4AC8_B35D_E949A63804AB__INCLUDED_)
