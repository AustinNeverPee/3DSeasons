
#include "Fountain.h"
//initialization
void Fountain::init() {

	for (int loop = 0; loop<MAX_FOUNTAIN_PARTICLES; loop++)

	{
		particle[loop].active = true;
		particle[loop].life = float(rand() % 100 / 10);
		particle[loop].fade = float(rand() % 100) / 1000.0f + 0.003f;

		// initialize the particle position
		particle[loop].x = center.x;
		particle[loop].y = center.y;
		particle[loop].z = center.z;

		// initialize the particle color
		particle[loop].r = Fcolors[loop % 12][0];
		particle[loop].g = Fcolors[loop % 12][1];
		particle[loop].b = Fcolors[loop % 12][2];

		particle[loop].xi = float((rand() % 50) - 26.0f)*10.0f;		// Ëæ»úÉú³ÉXÖá·½ÏòËÙ¶È
		//		particle[loop].yi = float((rand() % 50) - 25.0f)*10.0f;		// Ëæ»úÉú³ÉYÖá·½ÏòËÙ¶È
		particle[loop].zi = float((rand() % 50) - 25.0f)*10.0f;		// Ëæ»úÉú³ÉZÖáÏòËÙ¶È
		particle[loop].yi = 50 - float(rand() % 200 / 4);

		// set the accleration 
		particle[loop].xg = 0.0f;
		particle[loop].yg = -0.8f;
		particle[loop].zg = 0.0f;

	}
}

void Fountain::setCenter(float x_, float y_, float z_) {
	center.x = x_;
	center.y = y_;
	center.z = z_;
}

void Fountain::display() {

//	glLoadIdentity();

	glScalef(0.07, 0.07, 0.07);

	glTranslated(20, 0, -50);
	
	int times = 50;
	while (times--) {
		for (int loop = 0; loop < MAX_FOUNTAIN_PARTICLES; loop++)
		{
			if (particle[loop].active)					// Èç¹ûÁ£×ÓÎª¼¤»îµÄ
			{
				float x = particle[loop].x;				// ·µ»ØXÖáµÄÎ»ÖÃ
				float y = particle[loop].y;				// ·µ»ØYÖáµÄÎ»ÖÃ
				float z = particle[loop].z + zoom;			// ·µ»ØZÖáµÄÎ»ÖÃ


				glEnable(GL_BLEND);
				glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
				float alpha = float(rand() % 40) / 100 + 0.1;
			//	alpha = 0.1;
				glColor4f(particle[loop].r, particle[loop].g, particle[loop].b, alpha);

				glBegin(GL_TRIANGLE_STRIP);				// »æÖÆÈý½ÇÐÎ´ø	
				//glTexCoord2d(1, 1); 
				glVertex3f(x + 0.05f, y + 0.01f, z);
				//glTexCoord2d(0, 1); 
				glVertex3f(x - 0.05f, y + 0.01f, z);
				//glTexCoord2d(1, 0);
				glVertex3f(x + 0.05f, y - 0.02f, z);
				//glTexCoord2d(0, 0);
				glVertex3f(x - 0.05f, y - 0.02f, z);
				glEnd();

				glDisable(GL_BLEND);

				particle[loop].x += particle[loop].xi / (slowdown * 500);	// ¸üÐÂX×ø±êµÄÎ»ÖÃ
				particle[loop].y += particle[loop].yi / (slowdown * 500);	// ¸üÐÂY×ø±êµÄÎ»ÖÃ
				particle[loop].z += particle[loop].zi / (slowdown * 500);	// ¸üÐÂZ×ø±êµÄÎ»ÖÃ

				if (y < center.y)
					particle[loop].life = -1.0f;


				particle[loop].xi += particle[loop].xg;
				particle[loop].yi += particle[loop].yg;
				particle[loop].zi += particle[loop].zg;

				particle[loop].life -= particle[loop].fade;



				if (particle[loop].life < 0.0f)
				{

					particle[loop].life = 30.0f - float(rand() % 10);				// ²úÉúÒ»¸öÐÂµÄÁ£×Ó
					particle[loop].fade = float(rand() % 100) / 1000.0f + 0.003f;	// Ëæ»úÉú³ÉË¥¼õËÙÂÊ

					int j = loop % 36;
					particle[loop].x = center.x;
					particle[loop].y = center.y;
					particle[loop].z = center.z;


					particle[loop].xi = float((rand() % 100) - 50.0f)*1.0f;
					particle[loop].yi = 200 - float(rand() % 10);
					particle[loop].zi = float((rand() % 100) - 50.0f)*1.0f;;



				}

			}
		}
		//强制执行

		glFlush();
	}
}


