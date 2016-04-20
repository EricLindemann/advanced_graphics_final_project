#include "CSCIx239.h"

static void Vertex(double th,double ph)
{
	double x = Sin(th)*Cos(ph);
	double y = Cos(th)*Cos(ph);
	double z =         Sin(ph);
	//  For a sphere at the origin, the position
	//  and normal vectors are the same
	glNormal3d(x,y,z);
	glVertex3d(x,y,z);
}

static void Cylinder(double x, double y, double z, double dx, double dy, double dz, double th,double xh)
{

	int i,k;
	glPushMatrix();

	glTranslated(x,y,z);
	glRotated(th,1,0,0);
	glRotated(xh,0,1,0);
	glScaled(dx,dy,dz);

	//front and back
	for (i=1;i>=-1;i-=2){
		glNormal3f(0,0,i);
		glBegin(GL_TRIANGLE_FAN);
		glTexCoord2f(.5,.5);
		glVertex3f(0,0,i);
		for (k=0;k<=360;k+=10){
			glTexCoord2f(0.5*Cos(k)+.5,.5*Sin(k)+.5);
			glVertex3f(i*Cos(k),Sin(k),i);
		}

		glEnd();
	}
	//Edge
	glBegin(GL_QUAD_STRIP);
	for (k=0;k<=360;k+=10){
		glNormal3f(Cos(k),Sin(k),0);
		glTexCoord2f(0,0.5*k); glVertex3f(Cos(k),Sin(k),1);
		glTexCoord2f(1,.5*k); glVertex3f(Cos(k),Sin(k),-1);
	}
	glEnd();
	glPopMatrix();

}

static void ball(double x,double y,double z,double r)
{
	int th,ph;
	int inc = 10;
	//float yellow[] = {1.0,1.0,0.0,1.0};
	//float Emission[]  = {0.0,0.0,0.01*emission,1.0};
	// Save transformation
	glPushMatrix();
	//        //  Offset, scale and rotate
	glTranslated(x,y,z);
	glScaled(r,r,r);
	//glMaterialfv(GL_FRONT,GL_SHININESS,shinyvec);
	//glMaterialfv(GL_FRONT,GL_SPECULAR,yellow);
	//glMaterialfv(GL_FRONT,GL_EMISSION,Emission);
	//  Bands of latitude
	for (ph=-90;ph<90;ph+=inc)
	{
		glBegin(GL_QUAD_STRIP);
		for (th=0;th<=360;th+=2*inc)
		{
			Vertex(th,ph);
			Vertex(th,ph+inc);
		}
		glEnd();
	}
	//  Undo transofrmations
	glPopMatrix();
}



void FireHydrant(double x, double y, double z, double dx, double dy, double dz, double th)
{

	glPushMatrix();

	glTranslated(x,y,z);
	glRotated(th,0,1,0);
	glScaled(dx,dy,dz);

	glColor3f(.2,.2,.2);
	Cylinder(0,0,0,.7,.7,.1,90,0);
	glColor3f(1,0,0);
	Cylinder(0,.8,0,.4,.4,.8,90,0);
	Cylinder(0,1.6,0,.65,.65,.1,90,0);

	ball(0,1.7,0,.4);
	Cylinder(-.4,1,0,.3,.3,.1,0,90);
	Cylinder(0,1.1,-.5,.2,.2,.1,0,0);
	Cylinder(0,1.1,.5,.2,.2,.1,0,0);
	Cylinder(0,1.1,0,.05,.05,.68,0,0);
	Cylinder(-.5,1,0,.05,.05,.05,0,90);
	Cylinder(0,2.1,0,.05,.05,.05,90,0);
	glPopMatrix();
	glColor3f(1,1,1);

}
