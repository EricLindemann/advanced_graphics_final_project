#include "final.h"

void Window(double x, double y, double z, double dx, double dy, double dz, double th, double rot){
  glPushMatrix();

	glTranslated(x,y,z);
	glRotated(th,0,1,0);
	glRotated(rot,0,0,-1);
	glScaled(dx,dy,dz);

	glEnable(GL_TEXTURE_2D);
	glTexEnvi(GL_TEXTURE_ENV , GL_TEXTURE_ENV_MODE ,GL_MODULATE);

  glBegin(GL_QUADS);
  glNormal3f(-1,0,0);
  glTexCoord3f(0,0,.5); glVertex3f(0,0,.1);
  glTexCoord3f(0,.5,.5); glVertex3f(0,1,.1);
  glTexCoord3f(0,.5,0); glVertex3f(0,1,-.1);
  glTexCoord3f(0,0,0); glVertex3f(0,0,-.1);

  glNormal3f(0,0,1);
  glTexCoord3f(0,0,0); glVertex3f(0,0,.1);
  glTexCoord3f(0,.5,0); glVertex3f(0,1,.1);
  glTexCoord3f(.5,.5,0); glVertex3f(1,1,.1);
  glTexCoord3f(.5,0,0); glVertex3f(1,0,.1);

  glNormal3f(0,0,-1);
  glTexCoord3f(.5,0,0); glVertex3f(0,0,-.1);
  glTexCoord3f(.5,.5,0); glVertex3f(0,1,-.1);
  glTexCoord3f(0,.5,0); glVertex3f(1,1,-.1);
  glTexCoord3f(0,0,0); glVertex3f(1,0,-.1);

  glNormal3f(1,0,0);
  glTexCoord3f(0,0,0); glVertex3f(1,0,.1);
  glTexCoord3f(0,.5,0); glVertex3f(1,1,.1);
  glTexCoord3f(.5,.5,0); glVertex3f(1,1,-.1);
  glTexCoord3f(.5,0,0); glVertex3f(1,0,-.1);

  glNormal3f(0,1,0);
  glTexCoord3f(0,0,0); glVertex3f(0,1,.1);
  glTexCoord3f(0,.5,0); glVertex3f(0,1,-.1);
  glTexCoord3f(.5,.5,0); glVertex3f(1,1,-.1);
  glTexCoord3f(.5,0,0); glVertex3f(1,1,.1);

  glNormal3f(0,1,0);
  glTexCoord3f(0,0,0); glVertex3f(0,0,.1);
  glTexCoord3f(0,.5,0); glVertex3f(0,0,-.1);
  glTexCoord3f(.5,.5,0); glVertex3f(1,0,-.1);
  glTexCoord3f(.5,0,0); glVertex3f(1,0,.1);

  glEnd();
	glPopMatrix();
}
