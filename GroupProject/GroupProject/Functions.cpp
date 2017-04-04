#include "Functions.h"

bool LoadBMP(LPCSTR Filename, GLuint &texid){
	//下面这些是无用的代码，一直想要直接用windows自带的东西弄但是总是出错……
	/*
	HBITMAP hBMP;             // Handle Of The Bitmap
	BITMAP BMP;             // Bitmap Structure
	memset(&hBMP, 0, sizeof(HBITMAP));
	memset(&BMP, 0, sizeof(BITMAP));
	glGenTextures(1, &texid);          // Create The Texture
	hBMP=(HBITMAP)LoadImage(GetModuleHandle(NULL), Filename, IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION | LR_LOADFROMFILE );

	if (!hBMP)              // Does The Bitmap Exist?
	return FALSE;            // If Not Return False

	GetObject(hBMP, sizeof(BMP), &BMP);        // Get The Object
	// hBMP:        Handle To Graphics Object
	// sizeof(BMP): Size Of Buffer For Object Information
	// &BMP:        Buffer For Object Information

	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);       // Pixel Storage Mode (Word Alignment / 4 Bytes)

	// Typical Texture Generation Using Data From The Bitmap
	glBindTexture(GL_TEXTURE_2D, texid);        // Bind To The Texture ID
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); // Linear Min Filter
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); // Linear Mag Filter
	glTexImage2D(GL_TEXTURE_2D, 0, 3, BMP.bmWidth, BMP.bmHeight, 0, GL_BGR_EXT, GL_UNSIGNED_SHORT, BMP.bmBits);

	DeleteObject(hBMP);            // Delete The Object
	return TRUE;             // Loading Was Successful
	*/

	AUX_RGBImageRec * imageRec = auxDIBImageLoad(Filename);
	//glPixelStorei(GL_UNPACK_ALIGNMENT, 4);       
	glGenTextures(1, &texid);
	glBindTexture(GL_TEXTURE_2D, texid);
	/*glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR_MIPMAP_NEAREST); //MipMapped过滤*/
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	gluBuild2DMipmaps(GL_TEXTURE_2D, 3, imageRec->sizeX, imageRec->sizeY, GL_RGB, GL_UNSIGNED_BYTE, imageRec->data);



	return true;
}