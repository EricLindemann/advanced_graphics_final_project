#include "CSCIx239.h"
/*
 *  *  Draw sky box
 *   */
void SkyBox(double D)
{


	glPushMatrix();

	glTranslated(0,-3.2,0);
//	glRotated(rotate,0,1,0);

	glRotated(90,0,1,0);


	glColor3f(1,1,1);
	//  Sides
	//glBindTexture(GL_TEXTURE_2D,nightTexture);
	glBegin(GL_QUADS);
	glTexCoord2f(0.00,.222); glVertex3f(-D,-D,-D);
	glTexCoord2f(0.25,.222); glVertex3f(+D,-D,-D);
	glTexCoord2f(0.25,.666); glVertex3f(+D,+D,-D);
	glTexCoord2f(0.00,.666); glVertex3f(-D,+D,-D);

	glTexCoord2f(0.25,.222); glVertex3f(+D,-D,-D);
	glTexCoord2f(0.50,.222); glVertex3f(+D,-D,+D);
	glTexCoord2f(0.50,.666); glVertex3f(+D,+D,+D);
	glTexCoord2f(0.25,.666); glVertex3f(+D,+D,-D);

	glTexCoord2f(0.50,.222); glVertex3f(+D,-D,+D);
	glTexCoord2f(0.75,.222); glVertex3f(-D,-D,+D);
	glTexCoord2f(0.75,.666); glVertex3f(-D,+D,+D);
	glTexCoord2f(0.50,.666); glVertex3f(+D,+D,+D);

	glTexCoord2f(0.75,.222); glVertex3f(-D,-D,+D);
	glTexCoord2f(1.00,.222); glVertex3f(-D,-D,-D);
	glTexCoord2f(1.00,.666); glVertex3f(-D,+D,-D);
	glTexCoord2f(0.75,.666); glVertex3f(-D,+D,+D);
	//glEnd();

	//  Top and bottom
//	glBindTexture(GL_TEXTURE_2D,nightTexture);
	//glBegin(GL_QUADS);
	glTexCoord2f(0.25,.666); glVertex3f(+D,+D,-D);
	glTexCoord2f(0.5,.666); glVertex3f(+D,+D,+D);
	glTexCoord2f(0.5,1); glVertex3f(-D,+D,+D);
	glTexCoord2f(0.25,1); glVertex3f(-D,+D,-D);

	/*glTexCoord2f(1.0,1); glVertex3f(-D,-D,+D);
	  glTexCoord2f(0.5,1); glVertex3f(+D,-D,+D);
	  glTexCoord2f(0.5,0); glVertex3f(+D,-D,-D);
	  glTexCoord2f(1.0,0); glVertex3f(-D,-D,-D);*/
	glEnd();

	glDisable(GL_TEXTURE_2D);
	glPopMatrix();
}
