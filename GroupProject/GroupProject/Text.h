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
	base = glGenLists(256);                                          //创建256个显示列表  
}

void Text::BuildFont() {
	hDC = CreateCompatibleDC(wglGetCurrentDC());
	HFONT font, oldfont;                                             //字体句柄, 旧的字体句柄  

	font = CreateFont(                                               //创建字体  
		-24,                                                         //字体高度(告诉Windows寻找基于CHARACTER高度的字体.如果是正数, 就寻找基于CELL的高度相匹配的字体)  
		0,                                                           //字体宽度(使用默认值)  
		0,                                                           //字体的旋转角度Angle Of Escapement  
		0,                                                           //字体底线的旋转角度Orientation Angle  
		FW_BOLD,                                                     //字体的重量(0-1000)[FW_DONTCARE是0, FW_NORMAL是400, FW_BOLD是700, FW_BLACK是900]  
		FALSE,                                                       //是否使用斜体  
		FALSE,                                                       //是否使用下划线  
		FALSE,                                                       //是否使用删除线  
		ANSI_CHARSET,                                                //设置字符集  
		OUT_TT_PRECIS,                                               //输出精度  
		CLIP_DEFAULT_PRECIS,                                         //裁剪精度  
		ANTIALIASED_QUALITY,                                         //输出质量  
		DEFAULT_PITCH | FF_DONTCARE,                                 //Pitch And Family  
		"Times New Roman"                                            //字体名称  
		);

	oldfont = (HFONT)SelectObject(hDC, font);                        //选择需要的字体  
	wglUseFontOutlines(                                              //使用Windows的wgl函数来创建字体  
		hDC,                                                         //设置当前窗口设备描述表的句柄  
		0,                                                           //用于创建显示列表字体的第1个字符的ASCII值  
		255,                                                         //字符数  
		base,                                                        //第1个显示列表的名称  
		0.0f,                                                        //字体的光滑度, 越小越光滑, 0.0为最光滑的状态  
		0.2f,                                                        //在Z方向突出的距离(即轮廓字体的厚度)  
		WGL_FONT_POLYGONS,                                           //使用多边形来生成字符, 每个顶点具有独立的法线(WGL_FONT_LINES:使用线形生成字符)  
		gmf                                                          //一个接收字形度量数据的数组的地址, 每个数组元素用它对应的显示列表字符的数据填充  
		);
	SelectObject(hDC, oldfont);                                      //选择原来的字体  
	DeleteObject(font);
}

void Text::glPrintf(const char *fmt, ...){
	if (!fmt) return;                                                 //如果无输入则返回  

	char text[256];                                                  //保存文字串  
	va_list ap;                                                      //指向一个变量列表的指针  
	va_start(ap, fmt);                                               //分析可变参数  
	vsprintf(text, fmt, ap);                                     //把参数值写入字符串  
	va_end(ap);                                                      //结束分析  

	/////////////////////将字符串居中/////////////////////  
	float length = 0.0f;                                             //保存字符串的长度  
	for (UINT i = 0; i<strlen(text); i++){                                //查找整个字符串的长度  
		length += gmf[text[i]].gmfCellIncX;                          //计算轮廓后字符串的宽度(gmfCellIncX表示显示位置从已绘制上的上一个字符向右移动的真正距离)  
	}
	glTranslatef(-length, 0.0f, 0.0f);                          //把字符串置于最左边  
	//////////////////////////////////////////////////////  

	glPushAttrib(GL_LIST_BIT);                                       //把显示列表属性压入属性堆栈  
	glListBase(base);                                                //设置显示列表的基础值为0  
	glCallLists(strlen(text), GL_UNSIGNED_BYTE, text);               //调用显示列表绘制字符串  
	glPopAttrib();                                                   //弹出属性堆栈  
}

void Text::KillFont() {
	glDeleteLists(base, 256);
}