#include "final.h"

//Draw Sidewalk
void Sidewalk(double x, double y, double z, double dx, double dy, double dz, double th,double rotate)
{
	glPushMatrix();

	glTranslated(x,y,z);
	glRotated(rotate,0,1,0);

	glRotated(th,1,0,0);
	glScaled(dx,dy,dz);

	glEnable(GL_TEXTURE_2D);
	glTexEnvi(GL_TEXTURE_ENV , GL_TEXTURE_ENV_MODE ,GL_MODULATE);
	//glBindTexture(GL_TEXTURE_2D,sidewalkTexture);

	glBegin(GL_QUADS);
	glNormal3f(-1,0,0);
	glColor3f(.6,.6,.6);
	glVertex3f(0,0,-.2);
	glVertex3f(0,0,0);
	glVertex3f(0,10,0);
	glVertex3f(0,10,-.2);

	glNormal3f(0,0,1);
	glTexCoord3f(1,20,0); glVertex3f(.5,10,0);
	glTexCoord3f(0,20,0); glVertex3f(0,10,0);
	glTexCoord3f(0,0,0);  glVertex3f(0,0,0);
	glTexCoord3f(1,0,0);  glVertex3f(.5,0,0);

	glEnd();

	glPopMatrix();

	glDisable(GL_TEXTURE_2D);

}
