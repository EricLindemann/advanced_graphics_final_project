#include "final.h"

//Draw trashcan
void Trash(double x, double y, double z, double dx, double dy, double dz, double th)
{
	int k;

	glPushMatrix();

	glTranslated(x,y,z);
	glRotated(th,0,1,0);
	glScaled(dx,dy,dz);

	glRotated(90,1,0,0);

	glEnable(GL_TEXTURE_2D);
	//glTexEnvi(GL_TEXTURE_ENV , GL_TEXTURE_ENV_MODE ,GL_MODULATE);
	//glBindTexture(GL_TEXTURE_2D,trashTexture);

	//bottom
	glNormal3f(0,0,-1);
	glColor3f(1,1,1);
	glBegin(GL_TRIANGLE_FAN);
	glTexCoord2f(.5,.5);
	glVertex3f(0,0,1);
	for (k=0;k<=360;k+=10){
		glTexCoord2f(.5*Cos(k)+.5,.5*Sin(k)+.5);
		glVertex3f(Cos(k),Sin(k),1);
	}

	glEnd();

	//Edge
	glBegin(GL_QUAD_STRIP);
	for (k=0;k<=360;k+=10){
		glNormal3f(Cos(k),Sin(k),0);
		glTexCoord2f(0,0.5*k); glVertex3f(Cos(k),Sin(k),1);
		glTexCoord2f(1,.5*k); glVertex3f(Cos(k),Sin(k),-1);
	}
	glEnd();
	glPopMatrix();
	glDisable(GL_TEXTURE_2D);
}
