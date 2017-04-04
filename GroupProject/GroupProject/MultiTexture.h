#include<windows.h>
#include <GL/glut.h>
#include<GL/glext.h>
#include <stdlib.h>
#include <stdio.h>

#include<iostream>
#include<fstream>

//#include "Text.h"

using namespace std;
#define	checkImageWidth 128
#define	checkImageHeight 128

static GLubyte firstImage[128 * 128][4];
static GLubyte secondImage[128 * 128][4];

char fontTexture1[50];
char fontTexture2[50];

#ifdef GL_VERSION_1_1
static GLuint firstTex;   // marble texture
static GLuint secondTex;  // warter texture
#endif



PFNGLMULTITEXCOORD1FARBPROC        glMultiTexCoord1fARB = NULL;
PFNGLMULTITEXCOORD2FARBPROC        glMultiTexCoord2fARB = NULL;
PFNGLACTIVETEXTUREARBPROC        glActiveTextureARB = NULL;
PFNGLCLIENTACTIVETEXTUREARBPROC    glClientActiveTextureARB = NULL;



void displayText(void)
{

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	Text text1;
	text1.BuildFont();
	glTranslatef(0.5f, 0.0f, -0.3f);


	glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_OBJECT_LINEAR);

	glTexGeni(GL_T, GL_TEXTURE_GEN_MODE, GL_OBJECT_LINEAR);

	glEnable(GL_TEXTURE_GEN_S);				// 使用自动生成纹理

	glEnable(GL_TEXTURE_GEN_T);
	

	/***************************/
	glActiveTextureARB(GL_TEXTURE0_ARB);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, secondTex);
	

	glActiveTextureARB(GL_TEXTURE1_ARB);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, firstTex);



	text1.glPrintf("Spring");


	glDisable(GL_TEXTURE_2D);
	glDisable(GL_BLEND);
	//glutSwapBuffers();
	glFlush();
}

bool ReadBMP(void) {
	//windows.h，他可以帮我们搞定BMP的类型。

	BITMAPFILEHEADER fileheader;
	BITMAPINFOHEADER infoheader;
	RGBTRIPLE rgb;
	FILE* fp;
	int width, height;

	char* filename = fontTexture1;
	if ((fp = fopen(filename, "rb")) == NULL) { cout << "fail!"; return false; } // 打开文件 
	cout << "test";
	fread(&fileheader, sizeof(fileheader), 1, fp); //从fp文件中读取1次fileheader大小的信 

	fread(&infoheader, sizeof(infoheader), 1, fp); // 同理
	//fseek(fp, sizeof(infoheader), SEEK_SET); // Jump the fileheader 

	width = infoheader.biWidth;
	height = infoheader.biHeight;

	// 为纹理信息分配存储空间
	cout << width << " " << height << endl;
	// 现在我们读取每一个信息 
	for (int j = 0; j < infoheader.biWidth*infoheader.biHeight; j++)
	{

		fread(&rgb, sizeof(rgb), 1, fp);

		firstImage[j][0] = rgb.rgbtRed; // Red component
		firstImage[j][1] = rgb.rgbtGreen; // Green component
		firstImage[j][2] = rgb.rgbtBlue; // Blue component
		firstImage[j][3] = 255; // Alpha value，按照需求设定

	}

	filename = fontTexture2;
	if ((fp = fopen(filename, "rb")) == NULL) { cout << "fail!"; return false; } // 打开文件 

	fread(&fileheader, sizeof(fileheader), 1, fp); //从fp文件中读取1次fileheader大小的信 
	fread(&infoheader, sizeof(infoheader), 1, fp); // 同理

	width = infoheader.biWidth;
	height = infoheader.biHeight;


	// 现在我们读取每一个信息 
	for (int j = 0; j < infoheader.biWidth*infoheader.biHeight; j++)
	{
		fread(&rgb, sizeof(rgb), 1, fp);
		secondImage[j][0] = rgb.rgbtRed; // Red component
		secondImage[j][1] = rgb.rgbtGreen; // Green component
		secondImage[j][2] = rgb.rgbtBlue; // Blue component
		secondImage[j][3] = 255; // Alpha value，按照需求设定
	}
}

void initMultiTexture() {
	glMultiTexCoord1fARB = (PFNGLMULTITEXCOORD1FARBPROC)wglGetProcAddress("glMultiTexCoord1fARB");
	glMultiTexCoord2fARB = (PFNGLMULTITEXCOORD2FARBPROC)wglGetProcAddress("glMultiTexCoord2fARB");
	glActiveTextureARB = (PFNGLACTIVETEXTUREARBPROC)wglGetProcAddress("glActiveTextureARB");
	glClientActiveTextureARB = (PFNGLCLIENTACTIVETEXTUREARBPROC)wglGetProcAddress("glClientActiveTextureARB");
}

void initFontTexture(void)
{
	//glClearColor(0.0, 0.0, 0.0, 0.0);
	glShadeModel(GL_FLAT);
	glEnable(GL_DEPTH_TEST);


	initMultiTexture();
	ReadBMP();

	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

#ifdef GL_VERSION_1_1
	glGenTextures(1, &firstTex);//命名纹理图像(第一步)
	glBindTexture(GL_TEXTURE_2D, firstTex);//创建纹理对象(第一步)
#endif


	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);//指定这个纹理对象的包装形式，并指定纹理的颜色应该如何进行过滤(第一步)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
#ifdef GL_VERSION_1_1
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB8, checkImageWidth, checkImageHeight,//指定一个纹理 (第一步)
		0, GL_RGBA, GL_UNSIGNED_BYTE, firstImage);
#else
	glTexImage2D(GL_TEXTURE_2D, 0, 4, checkImageWidth, checkImageHeight,
		0, GL_RGBA, GL_UNSIGNED_BYTE, checkImage2);
#endif
	// generate water texture
#ifdef GL_VERSION_1_1
	glGenTextures(1, &secondTex);//命名纹理图像(第一步)
	glBindTexture(GL_TEXTURE_2D, secondTex);//创建纹理对象(第一步)
#endif

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);//指定这个纹理对象的包装形式，并指定纹理的颜色应该如何进行过滤(第一步)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
#ifdef GL_VERSION_1_1
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB8, checkImageWidth, checkImageHeight,//指定一个纹理 (第一步)
		0, GL_RGBA, GL_UNSIGNED_BYTE, secondImage);
#else
	glTexImage2D(GL_TEXTURE_2D, 0, 4, checkImageWidth, checkImageHeight,
		0, GL_RGBA, GL_UNSIGNED_BYTE, warterImage);
#endif
	glDisable(GL_TEXTURE);
}






