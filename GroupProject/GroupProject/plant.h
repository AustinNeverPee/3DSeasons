#ifndef _PLANT_H
#define _PLANT_H

#include <Windows.h>
#include <Mmsystem.h>
#include <GL/glut.h>
#include <stdlib.h>
#include <fstream>
#include <iostream>
#include <vector>
#include <string>
#include <math.h>
#include <time.h>;

using namespace std;

class Plant {
	public:
		Plant();
		void init();
		void push();
		void pop();
		void rotL();
		void rotR();
		void rotM();
		void rotN();
		void leaf();
		void flower();
		void drawBranch(float w, float l);
		void drawWhite(float w, float l);
		void draw();
		void expand();
		void animation();
		void display();
		void setDepth(float dep);
		void BuildLists();
		void expandDepth(float dep);
		void drawPart(float d);

	private:
		float DEPTH;
		// Angle of branches, and depth of tree
		float depth;
		float dp;
		vector<string> *trees;

		double lastTime, elapsedTime, lastElapsedTime;

		float eyeX, eyeY, eyeZ, lookX, lookY, lookZ,
				upX, upY, upZ, fieldOfView, length, num, incr;

		// L-System
		string str;
		float d1, d2, a, lr, vr, width, l;

		int first, firstD;
		GLuint spring1, spring2, spring3, spring4, spring5, spring6, spring7, spring8;
		GLuint summer1, summer2, summer3, summer4, summer5, summer6, summer7;
		GLuint fall1, fall2, fall3, fall4, fall5, fall6;
		GLuint winter1, winter2, winter3, winter4, winter5;
};
#endif

Plant::Plant() {
	DEPTH = 4;

	depth = 0;
	trees = new vector<string>();

	lastTime = elapsedTime = lastElapsedTime = 0;

	eyeX = eyeY = eyeZ = lookX = lookY = lookZ =
	upX = upY = upZ = fieldOfView = length = 0.001;
	num = 0;
	incr = 0.1;

	str = "WDV/X";
	d1 = 137.50;
	d2 = 137.50;
	a = 25;
	lr = 1.109;
	vr = 1.732; 
	width = l = 0;

	first = firstD = 0;
}

void Plant::init() {
	srand( (unsigned)time( NULL ) );

	/*trees = new vector<string>();
	DEPTH = 7;
	for(int i = 0; i <= DEPTH; i++){
		expand();
	}*/

	BuildLists();
}

void Plant::push(){
	glPushMatrix();
	if (width > 0)
		width /= vr;
}

void Plant::pop(){
	glPopMatrix();
	width *= vr;
}

void Plant::rotL(){
	glRotatef(0, 1, 0, 0);
	glRotatef(d1, 0, 1, 0);
	glRotatef(0, 0, 0, 1);
}

void Plant::rotR(){
	glRotatef(0, 1, 0, 0);
	glRotatef(d2, 0, 1, 0);
	glRotatef(0, 0, 0, 1);
}

void Plant::rotM() {
	glRotatef(a, 1, 0, 0);
	glRotatef(0, 0, 1, 0);
	glRotatef(0, 0, 0, 1);
}

void Plant::rotN() {
	glRotatef(30, 1, 0, 0);
	glRotatef(0, 0, 1, 0);
	glRotatef(0, 0, 0, 1);
}

void Plant::flower(){
	glPushAttrib(GL_LIGHTING_BIT);//saves current lighting stuff
				//glColor3f(0.50, 1.0, 0.0);
		GLfloat ambient[4] = {0.96, 0.71, 0.678, 1.0};    // ambient reflection
		GLfloat specular[4] = {0.96, 0.71, 0.678, 1.0};   // specular reflection
		GLfloat diffuse[4] = {0.96, 0.71, 0.678, 1.0};   // diffuse reflection
	
				// set the ambient reflection for the object
		glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ambient);
				// set the diffuse reflection for the object
		glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diffuse);
				// set the specular reflection for the object      
		glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specular);
				// set the size of the specular highlights
		glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 20.0);

			//glutSolidCube(depth+1);
		glBegin(GL_TRIANGLES);
			glVertex3f(0, 0, 0);
			glVertex3f(0.6, 0, 0.9);
			glVertex3f(0, 1.2, 0);
			glVertex3f(0, 0, 0);
			glVertex3f(-0.6, 0, -0.9);
			glVertex3f(0, 1.2, 0);
		glEnd();
	glPopAttrib();
}

void Plant::leaf(){
	glPushAttrib(GL_LIGHTING_BIT);//saves current lighting stuff
				glColor3f(0.00, 1.0, 0.0);
		GLfloat ambient[4] = {0.00, 1.0, 0.0, 1.0};    // ambient reflection
		GLfloat specular[4] = {0.00, 1.0, 0.0, 1.0};   // specular reflection
		GLfloat diffuse[4] = {0.00, 1.0, 0.0, 1.0};   // diffuse reflection
	
				// set the ambient reflection for the object
		glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ambient);
				// set the diffuse reflection for the object
		glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diffuse);
				// set the specular reflection for the object      
		glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specular);
				// set the size of the specular highlights
		glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 20.0);

		//int size = rand() % 3 + 1;
		int size = 3;

			//glutSolidCube(depth+1);
		glBegin(GL_TRIANGLES);
			glVertex3f(0, 0, 0);
			glVertex3f(0.33 * size, 0, 0.66 * size);
			glVertex3f(0, size, 0);
			glVertex3f(0, 0, 0);
			glVertex3f(-0.33 * size, 0, -0.66 * size);
			glVertex3f(0, size, 0);
		glEnd();
	glPopAttrib();
}

void Plant::drawBranch(float w, float l) {
	glPushAttrib(GL_LIGHTING_BIT);//saves current lighting stuff
		GLfloat ambient[4] = {0.56, 0.3, 0.137};    // ambient reflection
		GLfloat specular[4] = {0.56, 0.3, 0.137};   // specular reflection
		GLfloat diffuse[4] = {0.56, 0.3, 0.137};   // diffuse reflection
	
		glColor3f(0.56, 0.3, 0.137);
		// set the ambient reflection for the object
		glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ambient);
		// set the diffuse reflection for the object
		glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diffuse);

		glPushMatrix();
			glRotatef(-90, 1, 0, 0);
			GLUquadricObj *quadratic; quadratic=gluNewQuadric(); 
			gluCylinder(quadratic, w, w/vr, l, 5, 5);
		glPopMatrix();

		glTranslatef(0, l, 0);
	glPopAttrib();
}

void Plant::drawWhite(float w, float l) {
	glPushAttrib(GL_LIGHTING_BIT);//saves current lighting stuff
		GLfloat ambient[4] = {1.0, 1.0, 1.0};    // ambient reflection
		GLfloat specular[4] = {1.0, 1.0, 1.0};   // specular reflection
		GLfloat diffuse[4] = {1.0, 1.0, 1.0};   // diffuse reflection

		glColor3f(1.0, 1.0, 1.0);
		// set the ambient reflection for the object
		glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ambient);
		// set the diffuse reflection for the object
		glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diffuse);

		glPushMatrix();
			glRotatef(-90, 1, 0, 0);
			GLUquadricObj *quadratic; quadratic=gluNewQuadric(); 
			gluCylinder(quadratic, w*vr, w, l, 32, 20);
			gluSphere(quadratic, w*vr, 32, 20);
		glPopMatrix();
		glTranslatef(0, l, 0);
	glPopAttrib();
}

void Plant::BuildLists() {
	// Spring
	spring1 = glGenLists(22);
	expandDepth(7);
	glNewList(spring1, GL_COMPILE);
	drawPart(0);
	glEndList();

	spring2 = spring1 + 1;
	glNewList(spring2, GL_COMPILE);
	drawPart(1);
	glEndList();

	spring3 = spring2 + 1;
	glNewList(spring3, GL_COMPILE);
	drawPart(2);
	glEndList();

	spring4 = spring3 + 1;
	glNewList(spring4, GL_COMPILE);
	drawPart(3);
	glEndList();

	spring5 = spring4 + 1;
	glNewList(spring5, GL_COMPILE);
	drawPart(4);
	glEndList();

	spring6 = spring5 + 1;
	glNewList(spring6, GL_COMPILE);
	drawPart(5);
	glEndList();

	spring7 = spring6 + 1;
	glNewList(spring7, GL_COMPILE);
	drawPart(6);
	glEndList();

	spring8 = spring7 + 1;
	glNewList(spring8, GL_COMPILE);
	drawPart(7);
	glEndList();

	// Summer
	expandDepth(6);
	summer1 = spring8 + 1;
	glNewList(summer1, GL_COMPILE);
	drawPart(0);
	glEndList();

	summer2 = summer1 + 1;
	glNewList(summer2, GL_COMPILE);
	drawPart(1);
	glEndList();

	summer3 = summer2 + 1;
	glNewList(summer3, GL_COMPILE);
	drawPart(2);
	glEndList();

	summer4 = summer3 + 1;
	glNewList(summer4, GL_COMPILE);
	drawPart(3);
	glEndList();

	summer5 = summer4 + 1;
	glNewList(summer5, GL_COMPILE);
	drawPart(4);
	glEndList();

	summer6 = summer5 + 1;
	glNewList(summer6, GL_COMPILE);
	drawPart(5);
	glEndList();

	summer7 = summer6 + 1;
	glNewList(summer7, GL_COMPILE);
	drawPart(6);
	glEndList();

	// autumn
	expandDepth(5);
	fall1 = summer7 + 1;
	glNewList(fall1, GL_COMPILE);
	drawPart(0);
	glEndList();

	fall2 = fall1 + 1;
	glNewList(fall2, GL_COMPILE);
	drawPart(1);
	glEndList();

	fall3 = fall2 + 1;
	glNewList(fall3, GL_COMPILE);
	drawPart(2);
	glEndList();

	fall4 = fall3 + 1;
	glNewList(fall4, GL_COMPILE);
	drawPart(3);
	glEndList();

	fall5 = fall4 + 1;
	glNewList(fall5, GL_COMPILE);
	drawPart(4);
	glEndList();

	fall6 = fall5 + 1;
	glNewList(fall6, GL_COMPILE);
	drawPart(5);
	glEndList();

	// Winter
	expandDepth(4);
	winter1 = fall6 + 1;
	glNewList(winter1, GL_COMPILE);
	drawPart(0);
	glEndList();

	winter2 = winter1 + 1;
	glNewList(winter2, GL_COMPILE);
	drawPart(1);
	glEndList();

	winter3 = winter2 + 1;
	glNewList(winter3, GL_COMPILE);
	drawPart(2);
	glEndList();

	winter4 = winter3 + 1;
	glNewList(winter4, GL_COMPILE);
	drawPart(3);
	glEndList();

	winter5 = winter4 + 1;
	glNewList(winter5, GL_COMPILE);
	drawPart(4);
	glEndList();
}

void Plant::drawPart(float d) {
	string ch = "";
	string LSystem = trees->at(d);
	for (int i = 0; i < LSystem.length(); i++){
		ch = LSystem.at(i);

		if (ch.compare("W") == 0){
			width = 3;
		} else if (ch.compare("D") == 0) {
			l = 60 * lr;
		} else if (ch.compare("[") == 0){
			push();
		} else if (ch.compare("]") == 0){
			pop();
		} else if (ch.compare("V") == 0){
			flower();
		} else if (ch.compare(">") == 0){
			rotR();
		} else if (ch.compare("<") == 0){
			rotL();
		} else if (ch.compare("&") == 0){
			rotM();
		} else if (ch.compare("!") == 0) {
			if (first <= 0) {
				first += 1;
			} else {
				drawBranch(width, l);
			}
		} else if (ch.compare("F") == 0) {
			l = 12 * lr;
		} else if (ch.compare("Y") == 0) {
			if (first <= 0) {
				first += 1;
			} else {
				drawWhite(width, l);
			}
		} else if (ch.compare("|") == 0) {
			rotN();
		} else if (ch.compare("L") == 0) {
			leaf();
		}
	}
}

void Plant::draw(){
	if (DEPTH == 7 && depth == 0) {
		glCallList(spring1);
	} else if (DEPTH == 7 && depth == 1) {
		glCallList(spring2);
	} else if (DEPTH == 7 && depth == 2) {
		glCallList(spring3);
	} else if (DEPTH == 7 && depth == 3) {
		glCallList(spring4);
	} else if (DEPTH == 7 && depth == 4) {
		glCallList(spring5);
	} else if (DEPTH == 7 && depth == 5) {
		glCallList(spring6);
	} else if (DEPTH == 7 && depth == 6) {
		glCallList(spring7);
	} else if (DEPTH == 7 && depth == 7) {
		glCallList(spring8);
	} else if (DEPTH == 6 && depth == 0) {
		glCallList(summer1);
	} else if (DEPTH == 6 && depth == 1) {
		glCallList(summer2);
	} else if (DEPTH == 6 && depth == 2) {
		glCallList(summer3);
	} else if (DEPTH == 6 && depth == 3) {
		glCallList(summer4);
	} else if (DEPTH == 6 && depth == 4) {
		glCallList(summer5);
	} else if (DEPTH == 6 && depth == 5) {
		glCallList(summer6);
	} else if (DEPTH == 6 && depth == 6) {
		glCallList(summer7);
	} else if (DEPTH == 5 && depth == 0) {
		glCallList(fall1);
	} else if (DEPTH == 5 && depth == 1) {
		glCallList(fall2);
	} else if (DEPTH == 5 && depth == 2) {
		glCallList(fall3);
	} else if (DEPTH == 5 && depth == 3) {
		glCallList(fall4);
	} else if (DEPTH == 5 && depth == 4) {
		glCallList(fall5);
	} else if (DEPTH == 5 && depth == 5) {
		glCallList(fall6);
	} else if (DEPTH == 4 && depth == 0) {
		glCallList(winter1);
	} else if (DEPTH == 4 && depth == 1) {
		glCallList(winter2);
	} else if (DEPTH == 4 && depth == 2) {
		glCallList(winter3);
	} else if (DEPTH == 4 && depth == 3) {
		glCallList(winter4);
	} else if (DEPTH == 4 && depth == 4) {
		glCallList(winter5);
	}
}

void Plant::expand(){
	string ch = "";
	for (int i = 0; i < str.length(); i++){
		ch = str.at(i);

		if (ch.compare("X") == 0){
			//str.replace(i, 1, "DD");
			//i = i + 1;
			if (dp == 4 && firstD > 3) {
				str.replace(i, 1, "YFZY[|FXZ]>[|FXZ]<[|FXZ]");
				i += 2;
			} else if (dp == 4 && firstD <= 3) {
				str.replace(i, 1, "!F[|FXZ]>[|FXZ]<[|FXZ]");
				firstD += 1;
			} else if (dp == 7) {
				str.replace(i, 1, "!F[&FXV]>[&FXV]<[&FXV]");
			} else if (dp == 6) {
				str.replace(i, 1, "!F[&FXL]>[&FXL]<[&FXL]");
			} else if (dp == 5) {
				str.replace(i, 1, "!F[&FX]>[&FX]<[&FX]");
				i -= 3;
			}
			i = i + 25;
		}

	} 
	trees->push_back(str);
	//cout << str << endl;
}

void Plant::animation()
{
	/*if (lastTime == 0)
		lastTime = timeGetTime();
	
	elapsedTime = timeGetTime()-lastTime;

	if(elapsedTime-lastElapsedTime > 2000 && depth < DEPTH){
		depth++;
		lastElapsedTime = elapsedTime;
	}
	elapsedTime = elapsedTime/20000;*/
	if (depth < DEPTH)
		depth++;

	glutPostRedisplay();
}

void Plant::setDepth(float dep) {
	DEPTH = dep;
	depth = 0;
}

void Plant::expandDepth(float dep) {
	//setDepth(dep);
	dp = dep;
	trees->clear();
	str = "WDV/X";
	if (dep == 4)
		firstD = 0;
	for(int i = 0; i <= dep; i++){
		expand();
	}
}

void Plant::display() {
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	// gluPerspective(GLdouble fovy,GLdouble aspect,GLdouble zNear,GLdouble zFar)
	// fovy 视角的大小,如果设置为0,相当你闭上眼睛了,所以什么也看不到,如果为180,那么可以认为你的视界很广阔
	// aspect 实际窗口的纵横比,即x/y
	// zNear 近处的裁面
	// zFar 远处的裁面
	gluPerspective(60, 1.0, 1, 2000);
	glMatrixMode(GL_MODELVIEW);

	glScalef(0.4, 0.4, 0.4);
	glTranslatef(18, -60, -300);
	draw();
	glFlush();

	animation();
}