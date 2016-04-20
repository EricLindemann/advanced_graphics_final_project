#include "CSCIx239.h"

void LightPostCone(double x, double y, double z, double dx, double dy, double dz, double th)
{

	glPushMatrix();

	glTranslated(x,y,z);
	glRotated(th,1,0,0);
	glRotated(10,0,1,0);
	glScaled(dx,dy,dz);
	glutSolidCone(3,3,10,10);
	glPopMatrix();

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

void Lightpost(double x, double y, double z, double dx, double dy, double dz, double th, int whichLight)
{
	int k;
	glPushMatrix();

	glTranslated(x,y,z);
	glRotated(th,0,1,0);
	glScaled(dx,dy,dz);

	glColor3f(.1,.1,.1);
	for (k=0;k<=160;k+=1){
		Cylinder(Cos(k),4+Sin(k),0,.1,.1,.1,90,0);
	}

	glColor3f(.47,.23,.08);
	Cylinder(1,0,0,.2,.2,4,90,0);

	glColor3f(.1,.1,.1);
	LightPostCone(-1,4,0,.2,.2,.2,270);


	glColor3f(1,1,1);





	glColor3f(1,1,1);
	ball(-1,4,0,.2);

	glPopMatrix();
}
