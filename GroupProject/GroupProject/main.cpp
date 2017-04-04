#include <math.h>
#include <string>
#include <GL/glut.h>
#include <GL/GLAUX.H>

#include <stdlib.h>
#include <iostream>
#include "Sky.h"
#include "Terrain.h"
#include "Rain.h"
#include "Snow.h"
#include "Fountain.h"
#include "Plant.h"
#include "Text.h"
#include "CLoad3DS.h"
#include "walkcamera.h"
#include "MultiTexture.h"
using namespace std;

// ����GUTEMB_L
CLoad3DS *gothicLoaderHouse1 = new(CLoad3DS);
t3DModel gothicModelHouse1;
float gothicTransHouse1[10] = {
	-20, -10, -100,     //��ʾ����������λ��
	0.5, 0.5, 0.5,      //��ʾxyz�Ŵ���
	0, 0, 0, 0  //��ʾ��ת
};
// ����STUT_C_L
CLoad3DS *gothicLoaderHouse2 = new(CLoad3DS);
t3DModel gothicModelHouse2;
float gothicTransHouse2[10] = {
	20, -10, -60,     //��ʾ����������λ��
	0.008, 0.008, 0.008,      //��ʾxyz�Ŵ���
	0, 0, 0, 0  //��ʾ��ת
};
// ����Twostory
CLoad3DS *gothicLoaderHouse5 = new(CLoad3DS);
t3DModel gothicModelHouse5;
float gothicTransHouse5[10] = {
	-15, -15, -120,     //��ʾ����������λ��
	0.008, 0.008, 0.008,      //��ʾxyz�Ŵ���
	0, 0, 0, 0  //��ʾ��ת
};
// ����
CLoad3DS *gothicLoaderBalloon = new(CLoad3DS);
t3DModel gothicModelBalloon;
float gothicTransBalloon[10] = {
	-50, 0, -100,     //��ʾ����������λ��
	2.0, 2.0, 2.0,      //��ʾxyz�Ŵ���
	0, 0, 0, 0  //��ʾ��ת
};
// ����
CLoad3DS *gothicLoaderDinosaur = new(CLoad3DS);
t3DModel gothicModelDinosaur;
float gothicTransDinosaur[10] = {
	200, 0, -100,     //��ʾ����������λ��
	5.0, 5.0, 5.0,      //��ʾxyz�Ŵ���
	0, 0, 0, 0  //��ʾ��ת
};

static float ratio;

bool isSpring = false;
bool isSummer = false;
bool isAutumn = false;
bool isWinter = true;
Sky sky;
Terrain terrain;
Rain rain;
Snow snow;
Fountain fountain;
Plant plant;

WalkCamera camera(0, 0, 1);

char terrainSource[30] = "Data/terrain/snow.bmp";
char text[15] = "Winter";
GLfloat textColor[] = { 1.0, 1.0, 1.0 };

AUX_RGBImageRec* TextureImage;

//GLuint tid[4] = { 0, 1, 2 };
GLuint tid[3];
//���ù�Դ����
GLfloat LightAmbient[] = { 0.5f, 0.5f, 0.5f, 1.0f }; 				// ���������
GLfloat LightDiffuse[] = { 1.0f, 1.0f, 1.0f, 1.0f };				 // ��������
//ָ����Դ��λ��
GLfloat LightPosition[] = { 0.0f, 100.0f, 0.0f, 1.0f };

// ��ʾ���֣�Ӣ�ļ����֣�
#define MAX_CHAR        128
void initLight1() {
	// set the lighting
	glShadeModel(GL_SMOOTH);
	GLfloat lightP[4] = { 0.0, 800.0, 0.0, 1.0 };
	glLightfv(GL_LIGHT1, GL_POSITION, lightP);

	// set the ambient light colour    
	GLfloat lightA[4] = { 0.5, 0.5, 0.5, 1 };
	glLightfv(GL_LIGHT1, GL_AMBIENT, lightA);

	// set the specular light colour         
	GLfloat lightS[4] = { 0.9, 0.9, 0.9, 1.0 };
	glLightfv(GL_LIGHT1, GL_SPECULAR, lightS);

	// set the diffuse light colour
	GLfloat lightD[4] = { 0.9, 0.9, 0.9, 1.0 };
	glLightfv(GL_LIGHT1, GL_DIFFUSE, lightD);
}

// ��ʼ�����
void initSky()
{
	//������OpenGL��������λͼ��Ϣ
	TextureImage = auxDIBImageLoad("skybox2.bmp");
	//Ȼ��������
	glGenTextures(1, &tid[0]);
	glBindTexture(GL_TEXTURE_2D, tid[0]);
	gluBuild2DMipmaps(GL_TEXTURE_2D, 3, TextureImage->sizeX, TextureImage->sizeY,
		GL_RGB, GL_UNSIGNED_BYTE, TextureImage->data);
	sky.InitSky(0, 0, 0, 200, tid[0]);
}

// ��ʼ������
void initTerrain()
{
	glShadeModel(GL_FLAT);
	glClearColor(0.0, 0.0, 0.0, 0.0);

	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
	glHint(GL_POINT_SMOOTH_HINT, GL_NICEST);

	terrain.init("terrain-heightmap.raw", (LPCSTR)terrainSource, 1.0f, 0.06f, tid[2]);
}

void test() {
	glBegin(GL_QUADS);
	glNormal3f(0.0, 0.0, 1.0);
	glMultiTexCoord2fARB(GL_TEXTURE0_ARB, 0.0, 0.0);
	glMultiTexCoord2fARB(GL_TEXTURE1_ARB, 0.0, 0.0);
	glVertex3f(0.0f, 0.0f, 0.0f);

	glNormal3f(0.0, 0.0, 1.0);
	glMultiTexCoord2fARB(GL_TEXTURE0_ARB, 0.0, 1.0);
	glMultiTexCoord2fARB(GL_TEXTURE1_ARB, 0.0, 1.0);

	glVertex3f(0.0f, 1.0f, 0.0f);

	glNormal3f(0.0, 0.0, 1.0);
	glMultiTexCoord2fARB(GL_TEXTURE0_ARB, 1.0, 1.0);
	glMultiTexCoord2fARB(GL_TEXTURE1_ARB, 1.0, 1.0);
	glVertex3f(1.0f, 1.0f, 0.0f);

	glNormal3f(0.0, 0.0, 1.0);
	glMultiTexCoord2fARB(GL_TEXTURE0_ARB, 1.0, 0.0);
	glMultiTexCoord2fARB(GL_TEXTURE1_ARB, 1.0, 0.0);
	glVertex3f(1.0f, 0.0f, 0.0f);
	glEnd();

}
void ShowText() {
	//glEnable(GL_BLEND);
	//glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	Text text1;
	text1.BuildFont();
	glRotatef(5, 0.0, 1.0, 0.0);
	glTranslatef(1.0f, -2.3f, -4.0f);
	
	
	glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_OBJECT_LINEAR);

	glTexGeni(GL_T, GL_TEXTURE_GEN_MODE, GL_OBJECT_LINEAR);

	glEnable(GL_TEXTURE_GEN_S);				// ʹ���Զ���������

	glEnable(GL_TEXTURE_GEN_T);
	
//	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);//���û�ͼģʽ(�ڶ���)

	/***************************/ 
	glActiveTextureARB(GL_TEXTURE0_ARB);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, firstTex);

	
	glActiveTextureARB(GL_TEXTURE1_ARB);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, secondTex);

	

	glPushMatrix();
text1.glPrintf(text);
	// glTranslatef(-1.0, .0, .0);
	// test();
	 glPopMatrix();
glFlush();	

	glActiveTextureARB(GL_TEXTURE1_ARB);
	glDisable(GL_TEXTURE_2D);
	glActiveTextureARB(GL_TEXTURE0_ARB);
	glEnable(GL_TEXTURE_2D);

	

	glDisable(GL_TEXTURE_GEN_S);				// ʹ���Զ���������

	glDisable(GL_TEXTURE_GEN_T);

	

}
void changeSeason() {
	isSpring = false;
	isSummer = false;
	isAutumn = false;
	isWinter = false;
}
void ToSpring(){
	changeSeason();
	isSpring = true;

	/*   change Terrain */
	strcpy(terrainSource, "Data/terrain/GrassLand.bmp");
	initTerrain();

	/*   change Plant  */
	plant.setDepth(7);
	/*   change Text   */
	strcpy(text, "Spring");
	strcpy(fontTexture1, "fontTexture\\spring1.bmp");
	strcpy(fontTexture2, "fontTexture\\spring2.bmp");
	initFontTexture();

	textColor[0] = (float)255 / 255;
	textColor[1] = (float)174 / 255;
	cout << textColor[1];
	textColor[2] = (float)201 / 255; 

}
void ToSummer(){
	changeSeason();
	isSummer = true;

	/*   change Terrain */
	strcpy(terrainSource, "Data/terrain/summer.bmp");
	initTerrain();

	plant.setDepth(6);
	/*   change Text*/
	strcpy(text, "Summer");
	strcpy(fontTexture1, "fontTexture\\summer1.bmp");
	strcpy(fontTexture2, "fontTexture\\summer2.bmp");
	initFontTexture();

	textColor[0] = (float)119 / 255;
	textColor[1] = (float)241 / 255;
	textColor[2] = (float) 29/ 255;
}
void ToAutumn(){
	changeSeason();
	isAutumn = true;

	/*   change Terrain */
	strcpy(terrainSource, "Data/terrain/fall.bmp");
;

	initTerrain();

	plant.setDepth(5);
	/*   change Text*/
	strcpy(text, "Autumn");
	strcpy(fontTexture1, "fontTexture\\autumn1.bmp");
	strcpy(fontTexture2, "fontTexture\\autumn2.bmp");
	initFontTexture();


	textColor[0] = (float) 176/ 255;
	textColor[1] = (float) 159/ 255;
	textColor[2] = (float) 40/ 255;
}
void ToWinter(){
	changeSeason();
	isWinter = true;
	plant.setDepth(4);
	

	/*   change Terrain */
	strcpy(terrainSource, "Data/terrain/snow.bmp");
	initTerrain();

    strcpy(text, "Winter");
	strcpy(fontTexture1, "fontTexture\\winter1.bmp");
	strcpy(fontTexture2, "fontTexture\\winter2.bmp");
	initFontTexture();
	/*   change Text*/
/*	textColor[0] = (float)255/ 255;
	textColor[1] = (float)255 / 255;
	textColor[2] = (float)255 / 255; */
}

// ��ʼ������
void initScene() 
{
	
	glEnable(GL_DEPTH_TEST);
	//******************
	glGenTextures(3, tid);

	rain.init();
	snow.init();
	fountain.init();
	plant.init();
	fountain.setCenter(0, -20, -0.2);

	initSky();
	initTerrain();

	strcpy(fontTexture1, "fontTexture\\winter1.bmp");
	strcpy(fontTexture2, "fontTexture\\winter2.bmp");
	initFontTexture();

	gothicLoaderHouse1->Import3DS(&gothicModelHouse1, "Data/3ds/GUTEMB_L.3DS");
	gothicLoaderHouse2->Import3DS(&gothicModelHouse2, "Data/3ds/STUT_C_L.3DS");
	gothicLoaderHouse5->Import3DS(&gothicModelHouse5, "Data/3ds/TWOSTORY.3DS");
	gothicLoaderBalloon->Import3DS(&gothicModelBalloon, "Data/3ds/balloon.3DS");
	gothicLoaderDinosaur->Import3DS(&gothicModelDinosaur, "Data/3ds/dinosaur.3DS");
}

void drawSnowMan()
{
	glScalef(2.5, 2.5, 2.5);
	glTranslatef(2, -6, -30);
	glColor3f(1.0f, 1.0f, 1.0f);

	//������
	glTranslatef(0.0f, 0.75f, 0.0f);
	glutSolidSphere(0.75f, 20, 20);


	// ��ͷ
	glTranslatef(0.0f, 1.0f, 0.0f);
	glutSolidSphere(0.25f, 20, 20);

	// ���۾�
	glPushMatrix();
	glColor3f(0.0f, 0.0f, 0.0f);
	glTranslatef(0.05f, 0.10f, 0.18f);
	glutSolidSphere(0.05f, 10, 10);
	glTranslatef(-0.1f, 0.0f, 0.0f);
	glutSolidSphere(0.05f, 10, 10);
	glPopMatrix();

	// ������
	glColor3f(1.0f, 0.5f, 0.5f);
	glRotatef(0.0f, 1.0f, 0.0f, 0.0f);
	glutSolidCone(0.08f, 0.5f, 10, 2);
}

void renderScene(void) 
{   
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//��ӹ���
	glLightfv(GL_LIGHT0, GL_AMBIENT, LightAmbient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, LightDiffuse);
	glLightfv(GL_LIGHT0, GL_POSITION, LightPosition);
	glEnable(GL_LIGHT0);
	
	camera.Look();

	
	
	glPushMatrix();
	// �����
	sky.ShowSky();
	// ������
	terrain.Render();
	glPopMatrix();
	

	glPushMatrix();
	  ShowText();
	glPopMatrix();

	/*   Add Tree  */
	glPushMatrix();
	glDisable(GL_LIGHT0);
	glEnable(GL_LIGHT1);
	plant.display();
	glDisable(GL_LIGHT1);
	glEnable(GL_LIGHT0);
	glPopMatrix();

	// ����
	glPushMatrix();
	changeObject(gothicTransDinosaur);
	drawModel(gothicModelDinosaur, true, false);
	glPopMatrix();

	/*   Sprint Characters    */
	if (isSpring) {
		for (int i = 0; i < 1; i++) {
			glPushMatrix();
			fountain.display();
			glPopMatrix();
		}
		// ����5
		glPushMatrix();
		changeObject(gothicTransHouse5);
		drawModel(gothicModelHouse5, true, false);
		glPopMatrix();
	}
	/*    Summer Characters    */
	if (isSummer) {
		// add rain
		glPushMatrix();
		rain.showRain();
		glPopMatrix();
		// ����5
		glPushMatrix();
		changeObject(gothicTransHouse5);
		drawModel(gothicModelHouse5, true, false);
		glPopMatrix();
	}
	/*    Autumn  Characters   */
	if (isAutumn) {
		// ����
		glPushMatrix();
		changeObject(gothicTransBalloon);
		drawModel(gothicModelBalloon, true, false);
		glPopMatrix();

		// ��3dsģ��
		// ����1
		glPushMatrix();
		changeObject(gothicTransHouse1);
		drawModel(gothicModelHouse1, true, false);
		glPopMatrix();

		
	}
	/*    Winter  Characters   */
	if (isWinter) {
		// add Snow
		glPushMatrix();
		snow.showSnow();
		glPopMatrix();

		glPushMatrix();
		drawSnowMan();
		glPopMatrix();

		// ��3dsģ��
		// ����1
		glPushMatrix();
		changeObject(gothicTransHouse1);
		drawModel(gothicModelHouse1, true, false);
		glPopMatrix();


		// ����2
		glPushMatrix();
		changeObject(gothicTransHouse2);
		drawModel(gothicModelHouse2, true, false);
		glPopMatrix();
	}


	
	glutSwapBuffers();
}

void inputKey(unsigned char key, int x, int y)
{
	std::cout << key << std::endl;
	switch (key)
	{
	case 120:			// x - summer
		ToSummer();
		break;
	case 118:			// v - winter
		ToWinter();
		break;
	case 122:			// z - spring
		ToSpring();
		break;
	case 99:			// c - autumn
		ToAutumn();
		break;
	}
}

void specail(int key, int x, int y)
{
	switch (key)
	{
	case GLUT_KEY_LEFT:
		camera.Left();
		break;
	case GLUT_KEY_RIGHT:
		camera.Right();
		break;
	case GLUT_KEY_UP:
		camera.Forward();
		break;
	case GLUT_KEY_DOWN:
		camera.Backward();
		break;

	case GLUT_KEY_PAGE_DOWN:
		camera.Down();
		break;
	case GLUT_KEY_PAGE_UP:
		camera.Up();
		break;
	}
	glutPostRedisplay();
}

void reShape(int w, int h)
{
	// ��ֹ��0��.
	if (h == 0)
		h = 1;

	ratio = 1.0f * w / h;
	// Reset the coordinate system before modifying
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	//�����ӿ�Ϊ�������ڴ�С
	glViewport(0, 0, w, h);

	//���ÿ��ӿռ�
	gluPerspective(45, ratio, -1000, 1000);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}


int main(int argc, char **argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(1000, 600);
	glutCreateWindow("�����ﶬ");

	glEnable(GL_TEXTURE_2D);
	glFrontFace(GL_CW);
	glEnable(GL_LIGHTING);
	glEnable(GL_COLOR_MATERIAL);
	glEnable(GL_DEPTH_TEST);
	
	// ��ʼ������
	initScene();

	// ��ʼ���ƹ�
	initLight1();

	glutKeyboardFunc(inputKey);
	glutSpecialFunc(specail);

	glutDisplayFunc(renderScene);
	glutIdleFunc(renderScene);
	
	glutReshapeFunc(reShape);

	glutMainLoop();

	return(0);
}
