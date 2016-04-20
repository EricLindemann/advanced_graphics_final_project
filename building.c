#include "CSCIx239.h"


void Building(double x, double y, double z, double dx, double dy, double dz, double th, int which)
{
	glPushMatrix();

	glTranslated(x,y,z);
	glRotated(th,0,1,0);
	glScaled(dx,dy,dz);

	//glEnable(GL_TEXTURE_2D);
/*	glTexEnvi(GL_TEXTURE_ENV , GL_TEXTURE_ENV_MODE ,GL_MODULATE);
	if(which == 0)
		glBindTexture(GL_TEXTURE_2D,buildingTexture);
	else if (which == 1)
		glBindTexture(GL_TEXTURE_2D, buildingTexture1);
	else if (which == 2)
		glBindTexture(GL_TEXTURE_2D, buildingTexture2);
	else if (which == 3)
		glBindTexture(GL_TEXTURE_2D, buildingTexture3);
*/
//	glEnable(GL_TEXTURE_2D);
	//glTexEnvi(GL_TEXTURE_ENV , GL_TEXTURE_ENV_MODE ,GL_MODULATE);
	glBegin(GL_QUADS);
	glNormal3f(-1,0,0);
	//glColor3f(color[0],color[1],color[2]);
	glTexCoord3f(0,0,1); glVertex3f(0,0,1);
	glTexCoord3f(0,1,1); glVertex3f(0,12,1);
	glTexCoord3f(0,1,0); glVertex3f(0,12,-1);
	glTexCoord3f(0,0,0); glVertex3f(0,0,-1);

	glNormal3f(0,0,1);
	glTexCoord3f(0,0,0); glVertex3f(0,0,1);
	glTexCoord3f(0,4,0); glVertex3f(0,12,1);
	glTexCoord3f(2,4,0); glVertex3f(4,12,1);
	glTexCoord3f(2,0,0); glVertex3f(4,0,1);

	glNormal3f(0,0,-1);
	glTexCoord3f(1,0,0); glVertex3f(0,0,-1);
	glTexCoord3f(1,1,0); glVertex3f(0,12,-1);
	glTexCoord3f(0,1,0); glVertex3f(4,12,-1);
	glTexCoord3f(0,0,0); glVertex3f(4,0,-1);

	glNormal3f(1,0,0);
	glTexCoord3f(0,0,0); glVertex3f(4,0,1);
	glTexCoord3f(0,4,0); glVertex3f(4,12,1);
	glTexCoord3f(2,4,0); glVertex3f(4,12,-1);
	glTexCoord3f(2,0,0); glVertex3f(4,0,-1);
	glEnd();

	glBegin(GL_QUADS);
	glNormal3f(0,1,0);
	glVertex3f(2,8,1);
	glVertex3f(2,8,-1);
	glVertex3f(0,8,-1);
	glVertex3f(0,8,1);
	glEnd();
	glPopMatrix();
//	glDisable(GL_TEXTURE_2D);


}
