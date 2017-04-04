#include <Windows.h>
#include <cstdio>
#include <cstdarg>
#include <cmath>
#include <GL\glut.h>

class Text {
public:
	Text();
	void BuildFont();
	void glPrintf(const char *fmt, ...);
	void KillFont();

private:
	GLuint base;
	GLYPHMETRICSFLOAT gmf[256];
	HDC hDC;
};

Text::Text() {
	base = glGenLists(256);                                          //����256����ʾ�б�  
}

void Text::BuildFont() {
	hDC = CreateCompatibleDC(wglGetCurrentDC());
	HFONT font, oldfont;                                             //������, �ɵ�������  

	font = CreateFont(                                               //��������  
		-24,                                                         //����߶�(����WindowsѰ�һ���CHARACTER�߶ȵ�����.���������, ��Ѱ�һ���CELL�ĸ߶���ƥ�������)  
		0,                                                           //������(ʹ��Ĭ��ֵ)  
		0,                                                           //�������ת�Ƕ�Angle Of Escapement  
		0,                                                           //������ߵ���ת�Ƕ�Orientation Angle  
		FW_BOLD,                                                     //���������(0-1000)[FW_DONTCARE��0, FW_NORMAL��400, FW_BOLD��700, FW_BLACK��900]  
		FALSE,                                                       //�Ƿ�ʹ��б��  
		FALSE,                                                       //�Ƿ�ʹ���»���  
		FALSE,                                                       //�Ƿ�ʹ��ɾ����  
		ANSI_CHARSET,                                                //�����ַ���  
		OUT_TT_PRECIS,                                               //�������  
		CLIP_DEFAULT_PRECIS,                                         //�ü�����  
		ANTIALIASED_QUALITY,                                         //�������  
		DEFAULT_PITCH | FF_DONTCARE,                                 //Pitch And Family  
		"Times New Roman"                                            //��������  
		);

	oldfont = (HFONT)SelectObject(hDC, font);                        //ѡ����Ҫ������  
	wglUseFontOutlines(                                              //ʹ��Windows��wgl��������������  
		hDC,                                                         //���õ�ǰ�����豸������ľ��  
		0,                                                           //���ڴ�����ʾ�б�����ĵ�1���ַ���ASCIIֵ  
		255,                                                         //�ַ���  
		base,                                                        //��1����ʾ�б������  
		0.0f,                                                        //����Ĺ⻬��, ԽСԽ�⻬, 0.0Ϊ��⻬��״̬  
		0.2f,                                                        //��Z����ͻ���ľ���(����������ĺ��)  
		WGL_FONT_POLYGONS,                                           //ʹ�ö�����������ַ�, ÿ��������ж����ķ���(WGL_FONT_LINES:ʹ�����������ַ�)  
		gmf                                                          //һ���������ζ������ݵ�����ĵ�ַ, ÿ������Ԫ��������Ӧ����ʾ�б��ַ����������  
		);
	SelectObject(hDC, oldfont);                                      //ѡ��ԭ��������  
	DeleteObject(font);
}

void Text::glPrintf(const char *fmt, ...){
	if (!fmt) return;                                                 //����������򷵻�  

	char text[256];                                                  //�������ִ�  
	va_list ap;                                                      //ָ��һ�������б��ָ��  
	va_start(ap, fmt);                                               //�����ɱ����  
	vsprintf(text, fmt, ap);                                     //�Ѳ���ֵд���ַ���  
	va_end(ap);                                                      //��������  

	/////////////////////���ַ�������/////////////////////  
	float length = 0.0f;                                             //�����ַ����ĳ���  
	for (UINT i = 0; i<strlen(text); i++){                                //���������ַ����ĳ���  
		length += gmf[text[i]].gmfCellIncX;                          //�����������ַ����Ŀ��(gmfCellIncX��ʾ��ʾλ�ô��ѻ����ϵ���һ���ַ������ƶ�����������)  
	}
	glTranslatef(-length, 0.0f, 0.0f);                          //���ַ������������  
	//////////////////////////////////////////////////////  

	glPushAttrib(GL_LIST_BIT);                                       //����ʾ�б�����ѹ�����Զ�ջ  
	glListBase(base);                                                //������ʾ�б�Ļ���ֵΪ0  
	glCallLists(strlen(text), GL_UNSIGNED_BYTE, text);               //������ʾ�б�����ַ���  
	glPopAttrib();                                                   //�������Զ�ջ  
}

void Text::KillFont() {
	glDeleteLists(base, 256);
}