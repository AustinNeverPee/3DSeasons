#include "Snow.h"
//initialization
void Snow::init() {

	for (int loop = 0; loop<MAX_SNOW_PARTICLES; loop++)

	{
		particle[loop].active = true;
		particle[loop].life = float(rand() % 150);
		particle[loop].fade = float(rand() % 100) / 1000.0f + 0.003f;

		// initialize the particle position
		particle[loop].x = (float)(rand() % 1000 - 500) / 500;
		particle[loop].y = (float)(rand() % 1000 - 500) / 500;
		particle[loop].z = (float)(rand() % 1000 - 500) / 500;
		

		// initialize the particle color
		particle[loop].r = 1.0;
		particle[loop].g = 1.0;
		particle[loop].b = 1.0;

		// set the initial speed on y direction
		particle[loop].yi = -4 * (float)(rand() % 100) / 10;

		// set the accleration 
		particle[loop].xg = 0.0f;
		particle[loop].yg = -0.3f;
		particle[loop].zg = 0.0f;

	}
}

#define PI2 6.28318530718
#define PI 3.14159265358979
void Snow::showSnow() {
	//	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	//	glLoadIdentity();
	//	glTranslated(0, 0, -0.5);
	glScalef(200, 200, 200);


	for (int loop = 0; loop < MAX_SNOW_PARTICLES; loop++)
	{
		if (particle[loop].active)					// Èç¹ûÁ£×ÓÎª¼¤»îµÄ
		{
			float x = particle[loop].x;				// ·µ»ØXÖáµÄÎ»ÖÃ
			float y = particle[loop].y;				// ·µ»ØYÖáµÄÎ»ÖÃ
			float z = particle[loop].z;			// ·µ»ØZÖáµÄÎ»ÖÃ

			float alpha = float(rand() % 60) / 100 + 0.4;
			glColor4f(particle[loop].r, particle[loop].g, particle[loop].b, alpha);

			// Draw Snow
			glEnable(GL_BLEND);
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
			glBegin(GL_POINTS);

			  float para;
			  float an;
			  float radis = 0.9*length;
			  float odd = 100;
			  for (int i = 0; i < odd; i++){
				an = 6.2831*float(i) / odd;
				para = 1.0 + 0.7*cos(7.0*an);
				glVertex3f(x + radis* cos(an) * para, y + radis*sin(an) * para, z);
			  }
			glEnd();
			glDisable(GL_BLEND);
			//cout << loop << " ";
			// change the rain height
			particle[loop].y += particle[loop].yi / (slowdown * 1000);	// ¸üÐÂY×ø±êµÄÎ»ÖÃ
			//	particle[loop].y -= 0.001;
			if (y < -1)
				particle[loop].life = -1.0f;

			particle[loop].yi += particle[loop].yg;			// ¸üÐÂYÖá·½ÏòËÙ¶È´óÐ¡

			particle[loop].life -= particle[loop].fade;

			if (particle[loop].life < 0.0f)
			{

				particle[loop].life = 150.0f - float(rand() % 30);				// ²úÉúÒ»¸öÐÂµÄÁ£×Ó
				particle[loop].fade = float(rand() % 100) / 1000.0f + 0.003f;	// Ëæ»úÉú³ÉË¥¼õËÙÂÊ


				// initialize the particle position
				particle[loop].x = (float)(rand() % 1000 - 500) / 500;
				particle[loop].y = 1;
				particle[loop].z = (float)(rand() % 1000 - 500) / 500;


				particle[loop].xi = 0;
				particle[loop].yi = -4 * (float)(rand() % 100) / 10;
				particle[loop].zi = 0;

			}
		}
	}
	//强制执行
	glFlush();
}


