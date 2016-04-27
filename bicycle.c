#include "final.h"


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


static void BikeSeat(double x, double y, double z, double dx, double dy, double dz, double th)
{

	glPushMatrix();

	glTranslated(x,y,z);
	glRotated(th,0,1,0);
	glScaled(dx,dy,dz);
	glBegin(GL_POLYGON);
	glColor3f(.05,.05,.05);
	glNormal3f(0,-1,0);
	glVertex3f(0,-.15,-1);
	glVertex3f(-.35,-.15,-.3);
	glVertex3f(-.1,-.15,0);
	glVertex3f(.1,-.15,0);
	glVertex3f(.35,-.15,-.3);
	glEnd();

	glBegin(GL_TRIANGLES);
	glNormal3f(-1,1,-.5);
	glVertex3f(0,0,-1);
	glVertex3f(-.05,.2,-.3);
	glVertex3f(-.35,0,-.3);

	glNormal3f(-1,1,.5);
	glVertex3f(-.05,.2,-.3);
	glVertex3f(-.35,0,-.3);
	glVertex3f(-.1,0,0);

	glNormal3f(1,1,-.5);
	glVertex3f(0,0,-1);
	glVertex3f(.05,.2,-.3);
	glVertex3f(.35,0,-.3);

	glNormal3f(1,1,.5);
	glVertex3f(.05,.2,-.3);
	glVertex3f(.35,0,-.3);
	glVertex3f(.1,0,0);

	glNormal3f(0,1,-.5);
	glVertex3f(0,0,-1);
	glVertex3f(.05,.2,-.3);
	glVertex3f(-.05,.2,-.3);
	glEnd();

	glBegin(GL_QUADS);
	glNormal3f(0,.8,1);
	glVertex3f(.05,.2,-.3);
	glVertex3f(-.05,.2,-.3);
	glVertex3f(-.1,0,0);
	glVertex3f(.1,0,0);
	glEnd();

	glBegin(GL_QUADS);
	glNormal3f(-1,0,-.5);
	glVertex3f(0,0,-1);
	glVertex3f(0,-.15,-1);
	glVertex3f(-.35,-.15,-.3);
	glVertex3f(-.35,0,-.3);

	glNormal3f(-1,0,.5);
	glVertex3f(-.35,0,-.3);
	glVertex3f(-.35,-.15,-.3);
	glVertex3f(-.1,-.15,0);
	glVertex3f(-.1,0,0);

	glNormal3f(1,0,-.5);
	glVertex3f(0,0,-1);
	glVertex3f(0,-.15,-1);
	glVertex3f(.35,-.15,-.3);
	glVertex3f(.35,0,-.3);

	glNormal3f(1,0,.5);
	glVertex3f(.35,0,-.3);
	glVertex3f(.35,-.15,-.3);
	glVertex3f(.1,-.15,0);
	glVertex3f(.1,0,0);

	glNormal3f(0,0,1);
	glVertex3f(.1,-.15,0);
	glVertex3f(.1,0,0);
	glVertex3f(-.1,0,0);
	glVertex3f(-.1,-.15,0);
	glEnd();
	glPopMatrix();
}

void Bicycle(double x, double y, double z, double dx, double dy, double dz, double th,double color[3],double rot)
{

	int k;
	glPushMatrix();

	glTranslated(x,y,z);
	glRotated(th,0,1,0);
	glRotated(rot,0,0,1);
	glScaled(dx,dy,dz);

	glColor3f(color[0],color[1],color[2]);
	Cylinder(0,.13,.05,.05,.05,.72,108,0);
	Cylinder(0,.47,-.75,.05,.05,.9,5,0);
	Cylinder(0,.55,-1.67,.05,.05,.3,115,0);


	//glColor3f(.7,.7,.7);
	Cylinder(0,-.1,-.95,.05,.05,.95,30,0);

	glColor3f(.05,.05,.05);
	for (k=0;k<=360;k+=1){
		Cylinder(0,(.6*Sin(k))-.4,(.6*Cos(k))+.75,.05,.05,.05,90,0);
		if (k%12 == 0){
			glColor3f(.7,.7,.7);
			glBegin(GL_QUADS);
			glVertex3f(-.02,-.4,.75);
			glVertex3f(-.02,(.6*Sin(k))-.4,(.6*Cos(k))+.75);
			glVertex3f(.02,(.6*Sin(k))-.4,(.6*Cos(k))+.75);
			glVertex3f(.02,-.4,.75);
			glEnd();
			glColor3f(.05,.05,.05);
		}
	}
	for (k=0;k<=360;k+=1){
		Cylinder(0,(.6*Sin(k))-.4,(.6*Cos(k))-2,.05,.05,.05,90,0);
		if (k%12 == 0){
			glColor3f(.7,.7,.7);
			glBegin(GL_QUADS);
			glVertex3f(-.02,-.4,-2);
			glVertex3f(-.02,(.6*Sin(k))-.4,(.6*Cos(k))-2);
			glVertex3f(.02,(.6*Sin(k))-.4,(.6*Cos(k))-2);
			glVertex3f(.02,-.4,-2);
			glEnd();
			glColor3f(.05,.05,.05);
		}
	}

	//front wheel cylinders
	glColor3f(color[0],color[1],color[2]);
	Cylinder(0,-.4,-2,.03,.03,.16,90,90);
	Cylinder(.14,-.04,-1.9,.03,.03,.35,107,0);
	Cylinder(-.14,-.04,-1.9,.03,.03,.35,107,0);
	Cylinder(0,.31,-1.79,.03,.03,.165,0,90);
	//Cylinder(.07,.2,-1.72,.03,.03,.1,100,25);
	//Cylinder(-.07,.2,-1.72,.03,.03,.1,100,-25);*/

	//back wheel cylinders
	Cylinder(0,-.4,.75,.03,.03,.165,90,90);
	Cylinder(0,.4,.15,.03,.03,.165,90,90);
	Cylinder(.14,0,.44,.03,.03,.49,53,0);
	Cylinder(-.14,0,.44,.03,.03,.49,53,0);
	Cylinder(0,-.545,-.175,.03,.03,.165,90,90);
	Cylinder(.14,-.47,.265,.03,.03,.46,-10,0);
	Cylinder(-.14,-.47,.265,.03,.03,.46,-10,0);

	//Handlebars
	Cylinder(0,.82,-1.55,.05,.05,.6,0,90);
	glColor3f(.05,.05,.05);
	Cylinder(.51,.82,-1.55,.06,.06,.1,0,90);
	Cylinder(-.51,.82,-1.55,.06,.06,.1,0,90);

   	//pedal circle
	Cylinder(.188,-.5,-.2,.25,.25,.01,0,90);

	//pedals
	glColor3f(.4,.4,.4);
	Cylinder(0,-.545,-.175,.02,.02,.3,90,90);
	Cylinder(.3,-.645,-.175,.02,.02,.1,90,0);
	Cylinder(-.3,-.445,-.175,.02,.02,.1,90,0);
	glColor3f(0,0,0);
	glBegin(GL_QUADS);
	//left pedal
	glVertex3f(.32,-.715,-.085);
	glVertex3f(.32,-.775,-.085);
	glVertex3f(.32,-.775,-.265);
	glVertex3f(.32,-.715,-.265);

	glVertex3f(.32,-.715,-.085);
	glVertex3f(.32,-.775,-.085);
	glVertex3f(.55,-.775,-.085);
	glVertex3f(.55,-.715,-.085);

	glVertex3f(.32,-.775,-.085);
	glVertex3f(.55,-.775,-.085);
	glVertex3f(.55,-.775,-.265);
	glVertex3f(.32,-.775,-.265);

	glVertex3f(.55,-.715,-.085);
	glVertex3f(.32,-.715,-.085);
	glVertex3f(.32,-.715,-.265);
	glVertex3f(.55,-.715,-.265);

	glVertex3f(.32,-.775,-.265);
	glVertex3f(.55,-.775,-.265);
	glVertex3f(.55,-.715,-.265);
	glVertex3f(.32,-.715,-.265);

	glVertex3f(.55,-.715,-.265);
	glVertex3f(.55,-.775,-.265);
	glVertex3f(.55,-.775,-.085);
	glVertex3f(.55,-.715,-.085);

	//right pedal
	glVertex3f(-.32,-.315,-.085);
	glVertex3f(-.32,-.375,-.085);
	glVertex3f(-.32,-.375,-.265);
	glVertex3f(-.32,-.315,-.265);

	glVertex3f(-.32,-.315,-.085);
	glVertex3f(-.32,-.375,-.085);
	glVertex3f(-.55,-.375,-.085);
	glVertex3f(-.55,-.315,-.085);

	glVertex3f(-.32,-.375,-.085);
	glVertex3f(-.55,-.375,-.085);
	glVertex3f(-.55,-.375,-.265);
	glVertex3f(-.32,-.375,-.265);

	glVertex3f(-.55,-.315,-.085);
	glVertex3f(-.32,-.315,-.085);
	glVertex3f(-.32,-.315,-.265);
	glVertex3f(-.55,-.315,-.265);

	glVertex3f(-.32,-.375,-.265);
	glVertex3f(-.55,-.375,-.265);
	glVertex3f(-.55,-.315,-.265);
	glVertex3f(-.32,-.315,-.265);

	glVertex3f(-.55,-.315,-.265);
	glVertex3f(-.55,-.375,-.265);
	glVertex3f(-.55,-.375,-.085);
	glVertex3f(-.55,-.315,-.085);

	glEnd();


	//Gears`
	glColor3f(.6,.6,.6);
	Cylinder(.17,-.4,.75,.2,.2,.009,0,90);
	Cylinder(.19,-.4,.75,.15,.15,.009,0,90);
	Cylinder(.21,-.4,.75,.1,.1,.009,0,90);

	//chain
	glBegin(GL_QUADS);

	for (k=-90;k<=90;k+=10){
		glNormal3f(Cos(k),Sin(k),0);
		glVertex3f(.18,.2*Sin(k)-.4,.2*Cos(k)+.75);
		glVertex3f(.16,.201*Sin(k)-.4,.201*Cos(k)+.75);
	}
	glEnd();
	glBegin(GL_QUADS);//Top chain
	glNormal3f(0,1,0);
	glVertex3f(.18,-.2,.70);
	glVertex3f(.16,-.2,.70);
	glVertex3f(.16,-.20625,.65);
	glVertex3f(.18,-.20625,.65);
	glVertex3f(.18,-.2125,.60);
	glVertex3f(.16,-.2125,.60);
	glVertex3f(.16,-.21875,.55);
	glVertex3f(.18,-.21875,.55);
	glVertex3f(.18,-.225,.50);
	glVertex3f(.16,-.225,.50);
	glVertex3f(.16,-.23125,.45);
	glVertex3f(.18,-.23125,.45);
	glVertex3f(.18,-.2375,.40);
	glVertex3f(.16,-.2375,.40);
	glVertex3f(.16,-.24375,.35);
	glVertex3f(.18,-.24375,.35);
	glVertex3f(.18,-.25,.30);
	glVertex3f(.16,-.25,.30);
	glVertex3f(.16,-.25625,.25);
	glVertex3f(.18,-.25625,.25);
	glVertex3f(.18,-.2625,.20);
	glVertex3f(.16,-.2625,.20);
	glVertex3f(.16,-.26875,.15);
	glVertex3f(.18,-.26875,.15);
	glVertex3f(.18,-.275,.10);
	glVertex3f(.16,-.275,.10);
	glVertex3f(.16,-.28125,.5);
	glVertex3f(.18,-.28125,.5);
	glVertex3f(.18,-.2875,0);
	glVertex3f(.16,-.2875,0);
	glVertex3f(.16,-.29375,-.05);
	glVertex3f(.18,-.29375,-.05);
	glEnd();
	glBegin(GL_QUADS);
	glNormal3f(0,-1,0);
	glVertex3f(.18,-.6,.7);
	glVertex3f(.16,-.6,.7);
	glVertex3f(.16,-.6,.65);
	glVertex3f(.18,-.6,.65);
	glVertex3f(.18,-.6,.6);
	glVertex3f(.16,-.6,.6);
	glVertex3f(.16,-.6,.55);
	glVertex3f(.18,-.6,.55);
	glVertex3f(.18,-.6,.5);
	glVertex3f(.16,-.6,.5);
	glVertex3f(.16,-.6,.45);
	glVertex3f(.18,-.6,.45);
	glVertex3f(.18,-.6,.4);
	glVertex3f(.16,-.6,.4);
	glVertex3f(.16,-.6,.35);
	glVertex3f(.18,-.6,.35);
	glVertex3f(.18,-.6,.3);
	glVertex3f(.16,-.6,.3);
	glVertex3f(.16,-.6,.25);
	glVertex3f(.18,-.6,.25);
	glVertex3f(.18,-.6,.2);
	glVertex3f(.16,-.6,.2);
	glVertex3f(.16,-.6,.15);
	glVertex3f(.18,-.6,.15);
	glVertex3f(.18,-.6,.1);
	glVertex3f(.16,-.6,.1);
	glVertex3f(.16,-.6,.05);
	glVertex3f(.18,-.6,.05);
	glVertex3f(.18,-.6,0);
	glVertex3f(.16,-.6,0);
	glVertex3f(.16,-.6,-.05);
	glVertex3f(.18,-.6,-.05);
	glEnd();

	BikeSeat(0,.75,.45,.7,.7,.7,0);

	glColor3f(1,1,1);
	glPopMatrix();

}
