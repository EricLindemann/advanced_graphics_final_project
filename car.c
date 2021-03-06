#include "final.h"


static void Wheel(double x, double y, double z, double dx, double dy, double dz, double th,double zh, int texSide, int texEdge)
{
	int i,k;
	glPushMatrix();

	glTranslated(x,y,z);
	glRotated(th,0,1,0);
	glRotated(zh,0,0,-1);
	glScaled(dx,dy,dz);

	glEnable(GL_TEXTURE_2D);
	glTexEnvi(GL_TEXTURE_ENV , GL_TEXTURE_ENV_MODE ,GL_MODULATE);
	//glBindTexture(GL_TEXTURE_2D,wheelFrontTexture);
	glBindTexture(GL_TEXTURE_2D,texSide);

	glColor3f(1,1,1);
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
	//glBindTexture(GL_TEXTURE_2D,wheelEdgeTexture);
	glBindTexture(GL_TEXTURE_2D,texEdge);
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


void Car(double x, double y, double z, double dx, double dy, double dz, double th, double rot,double color[3], int texSide, int texEdge){

	int k;
  int zh = 90;
	glPushMatrix();

	glTranslated(x,y,z);
	glRotated(th,0,1,0);
	glScaled(dx,dy,dz);

	glNormal3f(1,0,0);
	//Cylinder(0,0,0,.1,2,16,0);
	glBegin(GL_QUADS);
	//Front Bumper
	glNormal3f(0,1,0);
	glColor3f(.2,.2,.2);
	glVertex3f(-.3,.5,0);//front bumper coming off car
	glVertex3f(16.3,.5,0);
	glVertex3f(16.1,.5,-1.6);
	glVertex3f(-.1,.5,-1.6);

	glNormal3f(0,-.1,-1);
	glVertex3f(-.1,.5,-1.6);//first downslop in bumper (mostly y)
	glVertex3f(16.1,.5,-1.6);
	glVertex3f(16.1,-.1,-1.4);
	glVertex3f(-.1,-.1,-1.4);

	glNormal3f(0,-1,-1);
	glVertex3f(-.1,-.1,-1.4);
	glVertex3f(16.1,-.1,-1.4);//second downslope 45 deg
	glVertex3f(16.1,-1.4,0);
	glVertex3f(-.1,-1.4,0);

	glNormal3f(0,-1,0); //in shadow
	glVertex3f(-.1,-1.4,0); //straight down bottom of front bumper
	glVertex3f(16.1,-1.4,0);
	glVertex3f(16.1,-1.7,0);
	glVertex3f(-.1,-1.7,0);
	glEnd();
	//Front
	glBegin(GL_QUADS);
	glNormal3f(0,0,-1);
	glColor3f(color[0],color[1],color[2]);
	glVertex3f(0,.5,0);
	glVertex3f(0,3.5,.1);//front quad (lights go here)
	glVertex3f(16,3.5,.1);
	glVertex3f(16,.5,0);

	glNormal3f(0,1,.04);
	glVertex3f(0,3.5,.1);
	glVertex3f(16,3.5,.1);//top quad of front
	glVertex3f(16,4.2,17);
	glVertex3f(0,4.2,17);
	glEnd();


	//Right Side
	glBegin(GL_QUADS);
	glNormal3f(1,0,0);
	glVertex3f(16,.5,0); //Quad to wheel from front
	glVertex3f(16,3.5,0);
	glVertex3f(16,3.733,5.666);
	glVertex3f(16,.5,5.666);
	glEnd();


	//Makes the front wheel space
	glBegin(GL_QUAD_STRIP);
	for (k=0;k<=180;k+=10){
		glNormal3f(0,-Sin(k),-Cos(k));
		glVertex3f(16.2,3.5*Sin(k)-1,3.5*Cos(k)+9.5);
		glVertex3f(14,3.5*Sin(k)-1,3.5*Cos(k)+9.5);
	}
	glEnd();

	//Next 3 fans cover some of the space
	glBegin(GL_TRIANGLE_FAN);
	glNormal3f(1,0,0);
	glVertex3f(16,3.7,5);
	for(k=90;k<=190;k+=10){
		glVertex3f(16,3.5*Sin(k)-1,3.5*Cos(k)+9.5);
	}
	glEnd();

	glBegin(GL_TRIANGLE_FAN);
	glVertex3f(16,3.8,9);
	for(k=45;k<=135;k+=10){
		glVertex3f(16,3.5*Sin(k)-1,3.5*Cos(k)+9.5);
	}
	glEnd();

	glBegin(GL_TRIANGLE_FAN);
	glVertex3f(16,3.9,13);
	for(k=0;k<=90;k+=10){
		glVertex3f(16,3.5*Sin(k)-1,3.5*Cos(k)+9.5);
	}
	glEnd();



	glBegin(GL_QUADS);
	glNormal3f(1,0,0);
	glVertex3f(16.3,.5,5.666);//covers small space between wheel well and car
	glVertex3f(16.1,-1.4,5.666);
	glVertex3f(16.2,-1.4,6.1);
	glVertex3f(16.2,1.5,6.1);

	glVertex3f(0,.5,0);
	glVertex3f(0,3.5,.1);//front quad (lights go here)
	glVertex3f(16,3.5,.1);
	glVertex3f(16,.5,0);

	glNormal3f(0,1,.04);
	glVertex3f(0,3.5,.1);
	glVertex3f(16,3.5,.1);//top quad of front
	glVertex3f(16,4.2,17);
	glVertex3f(0,4.2,17);

	glNormal3f(1,0,0);
	glVertex3f(16.0,3.5,.1);
	glVertex3f(16.0,2.5,.1);
	glVertex3f(16.0,2.5,17);//covers triangle fans
	glVertex3f(16.0,4.2,17);

	glNormal3f(1,0,0);
	glVertex3f(16,4,13);
	glVertex3f(16,-1.5,13); //big right side through door
	glVertex3f(16,-1.5,33);
	glVertex3f(16,4,33);

	glNormal3f(1,0,0);
	glVertex3f(16,2.5,33); //covers triangle fans below for back wheel
	glVertex3f(16,4,33);
	glVertex3f(16,4,40);
	glVertex3f(16,2.5,40);
	glEnd();
	//Right Side
	glBegin(GL_QUADS);
	glNormal3f(1,0,0);
	glVertex3f(16,.5,0); //Quad to wheel from front
	glVertex3f(16,3.5,0);
	glVertex3f(16,3.733,5.666);
	glVertex3f(16,.5,5.666);
	glEnd();


	//Makes the front wheel space
	glBegin(GL_QUAD_STRIP);
	for (k=0;k<=180;k+=10){
		glNormal3f(0,-Sin(k),-Cos(k));
		glVertex3f(16.2,3.5*Sin(k)-1,3.5*Cos(k)+9.5);
		glVertex3f(14,3.5*Sin(k)-1,3.5*Cos(k)+9.5);
	}
	glEnd();

	//Next 3 fans cover some of the space
	glBegin(GL_TRIANGLE_FAN);
	glNormal3f(1,0,0);
	glVertex3f(16,3.7,5);
	for(k=90;k<=190;k+=10){
		glVertex3f(16,3.5*Sin(k)-1,3.5*Cos(k)+9.5);
	}
	glEnd();

	glBegin(GL_TRIANGLE_FAN);
	glVertex3f(16,3.8,9);
	for(k=45;k<=135;k+=10){
		glVertex3f(16,3.5*Sin(k)-1,3.5*Cos(k)+9.5);
	}
	glEnd();

	glBegin(GL_TRIANGLE_FAN);
	glVertex3f(16,3.9,13);
	for(k=0;k<=90;k+=10){
		glVertex3f(16,3.5*Sin(k)-1,3.5*Cos(k)+9.5);
	}
	glEnd();


	//Back right wheel well
	glBegin(GL_QUAD_STRIP);
	for (k=0;k<=180;k+=10){
		glNormal3f(16,-Sin(k),-Cos(k));
		glVertex3f(16.2,3.5*Sin(k)-1,3.5*Cos(k)+36.5);
		glVertex3f(16,3.5*Sin(k)-1,3.5*Cos(k)+36.5);
	}
	glEnd();

	glNormal3f(1,0,0);
	glBegin(GL_TRIANGLE_FAN);
	glVertex3f(16,3.7,32);
	for(k=90;k<=190;k+=10){
		glVertex3f(16,3.5*Sin(k)-1,3.5*Cos(k)+36.5);
	}
	glEnd();

	glBegin(GL_TRIANGLE_FAN);
	glVertex3f(16,3.8,36);
	for(k=45;k<=135;k+=10){
		glVertex3f(16,3.5*Sin(k)-1,3.5*Cos(k)+36.5);
	}
	glEnd();

	glBegin(GL_TRIANGLE_FAN);
	glVertex3f(16,3.9,40);
	for(k=0;k<=90;k+=10){
		glVertex3f(16,3.5*Sin(k)-1,3.5*Cos(k)+36.5);
	}
	glEnd();

	//Back right side
	glBegin(GL_QUADS);
	glNormal3f(1,0,0);
	glVertex3f(16,4,40);
	glVertex3f(16,-1,40);
	glVertex3f(15,-1,46);
	glVertex3f(15,4,46);
	glEnd();

	//Left Side
	glBegin(GL_QUADS);
	glNormal3f(-1,0,0);
	glVertex3f(0,.5,0); //Quad to wheel from front
	glVertex3f(0,3.5,0);
	glVertex3f(0,3.733,5.666);
	glVertex3f(0,.5,5.666);
	glEnd();

	//Makes the front wheel space
	glBegin(GL_QUAD_STRIP);
	for (k=0;k<=180;k+=10){
		glNormal3f(0,-Sin(k),-Cos(k));
		glVertex3f(-.2,3.5*Sin(k)-1,3.5*Cos(k)+9.5);
		glVertex3f(2,3.5*Sin(k)-1,3.5*Cos(k)+9.5);
	}
	glEnd();

	//Next 3 fans cover some of the space
	glBegin(GL_TRIANGLE_FAN);
	glNormal3f(-1,0,0);
	glVertex3f(0,3.7,5);
	for(k=90;k<=190;k+=10){
		glVertex3f(0,3.5*Sin(k)-1,3.5*Cos(k)+9.5);
	}
	glEnd();

	glBegin(GL_TRIANGLE_FAN);
	glVertex3f(0,3.8,9);
	for(k=45;k<=135;k+=10){
		glVertex3f(0,3.5*Sin(k)-1,3.5*Cos(k)+9.5);
	}
	glEnd();

	glBegin(GL_TRIANGLE_FAN);
	glVertex3f(0,3.9,13);
	for(k=0;k<=90;k+=10){
		glVertex3f(0,3.5*Sin(k)-1,3.5*Cos(k)+9.5);
	}
	glEnd();

	glBegin(GL_QUADS);
	glNormal3f(-1,0,0);
	glVertex3f(-.3,.5,5.666);//covers small space between wheel well and car
	glVertex3f(-.1,-1.4,5.666);
	glVertex3f(-.2,-1.4,6.1);
	glVertex3f(-.2,1.5,6.1);

	glNormal3f(0,1,0);
	glVertex3f(0,4,39);
	glVertex3f(16,4,39);
	glVertex3f(15,4,46);//top back quad
	glVertex3f(1,4,46);

	glNormal3f(0,0,1);
	glVertex3f(1,4,46);//back back quad
	glVertex3f(1,-1,46);
	glVertex3f(15,-1,46);
	glVertex3f(15,4,46);

	glNormal3f(-1,0,0);
	glVertex3f(0,3.5,.1);
	glVertex3f(0,2.5,.1);
	glVertex3f(0,2.5,17);//covers triangle fans
	glVertex3f(0,4.2,17);

	glNormal3f(-1,0,0);
	glVertex3f(0,4,13);
	glVertex3f(0,-1.5,13); //big left side through door
	glVertex3f(0,-1.5,33);
	glVertex3f(0,4,33);

	glNormal3f(-1,0,0);
	glVertex3f(0,2.5,33); //covers triangle fans below for back wheel
	glVertex3f(0,4,33);
	glVertex3f(0,4,40);
	glVertex3f(0,2.5,40);
	glEnd();

	//Back left wheel well
	glBegin(GL_QUAD_STRIP);
	for (k=0;k<=180;k+=10){
		glNormal3f(0,-Sin(k),-Cos(k));
		glVertex3f(-.2,3.5*Sin(k)-1,3.5*Cos(k)+36.5);
		glVertex3f(2,3.5*Sin(k)-1,3.5*Cos(k)+36.5);
	}
	glEnd();

	glBegin(GL_TRIANGLE_FAN);

	glNormal3f(-1,0,0);
	glVertex3f(0,3.7,32);
	for(k=90;k<=190;k+=10){
		glVertex3f(0,3.5*Sin(k)-1,3.5*Cos(k)+36.5);
	}
	glEnd();

	glBegin(GL_TRIANGLE_FAN);
	glVertex3f(0,3.8,36);
	for(k=45;k<=135;k+=10){
		glVertex3f(0,3.5*Sin(k)-1,3.5*Cos(k)+36.5);
	}
	glEnd();

	glBegin(GL_TRIANGLE_FAN);
	glVertex3f(0,3.9,40);
	for(k=0;k<=90;k+=10){
		glVertex3f(0,3.5*Sin(k)-1,3.5*Cos(k)+36.5);
	}
	glEnd();

	//Back left side
	glBegin(GL_QUADS);
	glNormal3f(-1,0,0);
	glVertex3f(0,4,40);
	glVertex3f(0,-1,40);
	glVertex3f(1,-1,46);
	glVertex3f(1,4,46);
	glEnd();


	//Right Bumper Front
	glColor3f(.2,.2,.2);
	glBegin(GL_TRIANGLES);
	glNormal3f(1,-.1,-.1);
	glVertex3f(16.1,.5,-1.6);//fills in gap at front of side bumper
	glVertex3f(16.1,-.1,-1.4);
	glVertex3f(16.12,.5,-1.4);

	glNormal3f(1,.1,0);
	glVertex3f(16.1,-1.7,0);//low part of front side bumper
	glVertex3f(16.1,-1.4,0);
	glVertex3f(16.1,-1.4,5.666);
	glEnd();

	glBegin(GL_QUADS);
	glNormal3f(1,.1,0);
	glVertex3f(16.1,-1.4,0);
	glVertex3f(16.1,-.1,-1.4);//connect front bumer to side
	glVertex3f(16.12,.5,-1.4);
	glVertex3f(16.3,.5,0);
	glColor3f(.2,.2,.2);
	glVertex3f(-.3,.5,0);//front bumper coming off car
	glVertex3f(16.3,.5,0);
	glVertex3f(16.1,.5,-1.6);
	glVertex3f(-.1,.5,-1.6);

	glNormal3f(0,-.1,-1);
	glVertex3f(-.1,.5,-1.6);//first downslop in bumper (mostly y)
	glVertex3f(16.1,.5,-1.6);
	glVertex3f(16.1,-.1,-1.4);
	glVertex3f(-.1,-.1,-1.4);

	glNormal3f(0,-1,-1);
	glVertex3f(-.1,-.1,-1.4);
	glVertex3f(16.1,-.1,-1.4);//second downslope 45 deg
	glVertex3f(16.1,-1.4,0);
	glVertex3f(-.1,-1.4,0);

	glNormal3f(0,-1,0); //in shadow
	glVertex3f(-.1,-1.4,0); //straight down bottom of front bumper
	glVertex3f(16.1,-1.4,0);
	glVertex3f(16.1,-1.7,0);
	glVertex3f(-.1,-1.7,0);
	glVertex3f(16.3,.5,0);
	glVertex3f(16.3,.5,5.666);//connect side bumper to wheel
	glVertex3f(16.1,-1.4,5.666);
	glVertex3f(16.1,-1.4,0);

	glNormal3f(0,1,0);
	glVertex3f(16.3,.5,0);
	glVertex3f(16.3,.5,5.666);//connects top of bumper to car
	glVertex3f(16,.5,5.666);
	glVertex3f(16,.5,0);

	//right Middle low bumper
	glNormal3f(1,0,0);
	glVertex3f(16.1,-1.4,13);
	glVertex3f(16.1,-1.4,33);
	glVertex3f(16.1,-.8,33);
	glVertex3f(16.1,-.8,13);


	//right back bumper
	glNormal3f(1,0,0);
	glVertex3f(16.5,-.2,40);
	glVertex3f(16.5,-1.8,40);
	glVertex3f(15.5,-1.8,46.5);
	glVertex3f(15.5,-.2,46.5);

	glNormal3f(0,1,0);
	glVertex3f(15.5,-.2,46.5);
	glVertex3f(15,-.2,46.5);
	glVertex3f(16,-.2,40);
	glVertex3f(16.5,-.2,40);
	glEnd();


	//Right Top
	glBegin(GL_QUADS);
	glNormal3f(1,.7,0);
	glVertex3f(16,4,17); //front right bar connecting windows
	glVertex3f(16,4,18);
	glNormal3f(0,.7,-1);
	glVertex3f(14.5,8,22);
	glVertex3f(14,8,22);


	glNormal3f(0,.7,1);
	glVertex3f(14.5,8,34); //back right bar connecting windows
	glVertex3f(14,8,34);
	glNormal3f(1,0,0);
	glVertex3f(16,4,39);
	glVertex3f(16,4,38);


	glNormal3f(1,.2,0);
	glVertex3f(14.5,8,31);//window seperator
	glVertex3f(14.5,8,30.4);
	glVertex3f(16,4,30.4);
	glVertex3f(16,4,31);
	glEnd();


	//Left Bumper Front
	glColor3f(.2,.2,.2);
	glBegin(GL_TRIANGLES);
	glNormal3f(-1,-.1,-.1);
	glVertex3f(-.1,.5,-1.6);//fills in gap at front of side bumper
	glVertex3f(-.1,-.1,-1.4);
	glVertex3f(-.12,.5,-1.4);

	glNormal3f(-1,.1,0);
	glVertex3f(-.1,-1.7,0);//low part of front side bumper
	glVertex3f(-.1,-1.4,0);
	glVertex3f(-.1,-1.4,5.666);
	glEnd();

	glBegin(GL_QUADS);
	glNormal3f(-1,.1,0);
	glVertex3f(-.1,-1.4,0);
	glVertex3f(-.1,-.1,-1.4);//connect front bumer to side
	glVertex3f(-.12,.5,-1.4);
	glVertex3f(-.3,.5,0);

	glVertex3f(-.3,.5,0);
	glVertex3f(-.3,.5,5.666);//connect side bumper to wheel
	glVertex3f(-.1,-1.4,5.666);
	glVertex3f(-.1,-1.4,0);

	glNormal3f(0,1,0);
	glVertex3f(-.3,.5,0);
	glVertex3f(-.3,.5,5.666);//connects top of bumper to car
	glVertex3f(0,.5,5.666);
	glVertex3f(0,.5,0);


	//Left Middle low bumper
	glNormal3f(-1,0,0);
	glVertex3f(-.1,-1.4,13);
	glVertex3f(-.1,-1.4,33);
	glVertex3f(-.1,-.8,33);
	glVertex3f(-.1,-.8,13);


	//Left back bumper
	glNormal3f(-1,0,0);
	glVertex3f(-.5,-.2,40);
	glVertex3f(-.5,-1.8,40);
	glVertex3f(.5,-1.8,46.5);
	glVertex3f(.5,-.2,46.5);

	glNormal3f(0,-1,0);
	glVertex3f(.5,-.2,46.5);
	glVertex3f(1,-.2,46.5);
	glVertex3f(0,-.2,40);
	glVertex3f(-.5,-.2,40);
	glEnd();


	//Left Top
	glBegin(GL_QUADS);
	glNormal3f(-1,0,0);
	glVertex3f(0,4,17); //front left bar connecting windows
	glVertex3f(0,4,18);
	glVertex3f(1.5,8,22);
	glVertex3f(2,8,22);

	glNormal3f(0,.7,1);
	glVertex3f(1.5,8,34); //back left bar connecting windows
	glVertex3f(2,8,34);
	glNormal3f(-1,.7,0);
	glVertex3f(0,4,39);
	glVertex3f(0,4,38);

	glNormal3f(-1,.2,0);
	glVertex3f(1.5,8,31);//window seperator
	glVertex3f(1.5,8,30.4);
	glVertex3f(0,4,30.4);
	glVertex3f(0,4,31);

	//Top
	glNormal3f(0,1,0);
	glVertex3f(14.5,8,22);//main top quad on bottom
	glVertex3f(1.5,8,22);
	glVertex3f(1.5,8,34);
	glVertex3f(14.5,8,34);

	glNormal3f(-.6,1,0);
	glVertex3f(1.5,8,22);//left top
	glVertex3f(1.5,8,34);
	glVertex3f(8,9,33);
	glVertex3f(8,9,23);

	glNormal3f(.6,1,0);
	glVertex3f(8,9,23);
	glVertex3f(8,9,33);//right top
	glVertex3f(14.5,8,34);
	glVertex3f(14.5,8,22);

	glEnd();

	glNormal3f(0,.3,-1);
	glBegin(GL_TRIANGLES);
	glVertex3f(14.5,8,22);
	glVertex3f(8,9,23);//front top
	glVertex3f(1.5,8,22);


	glVertex3f(14.5,8,34);
	glVertex3f(8,8,33);//back top
	glVertex3f(1.5,8,34);

	glEnd();

	//Back
	glBegin(GL_QUADS);

	//Back lights
	glColor3f(1,.1,.1);
	glNormal3f(0,0,1);
	glVertex3f(2,2.75,46.01);
	glVertex3f(2,.75,46.01);
	glVertex3f(6,.75,46.01);//left light
	glVertex3f(6,2.75,46.01);

	glVertex3f(14,2.75,46.01);
	glVertex3f(14,.75,46.01);
	glVertex3f(10,.75,46.01);//right light
	glVertex3f(10,2.75,46.01);

	//Back bumper

	glColor3f(.2,.2,.2);
	glNormal3f(0,0,1);
	glVertex3f(.5,-1.8,46.5);
	glVertex3f(.5,-.2,46.5);
	glVertex3f(15.5,-.2,46.5);
	glVertex3f(15.5,-1.8,46.5);

	glNormal3f(0,1,0);
	glVertex3f(15.5,-.2,46.5);
	glVertex3f(15.5,-.2,46);
	glVertex3f(.5,-.2,46);
	glVertex3f(.5,-.2,46.5);
	//Left Door
	glColor3f(0,0,0);
	glNormal3f(-1,0,0);
	glVertex3f(0,4,17.5);
	glVertex3f(0,4,17.6);//front side
	glVertex3f(-.1,-.8,17.6);
	glVertex3f(-.1,-.8,17.5);

	glVertex3f(-.1,-.8,17.6);
	glVertex3f(-.1,-.7,17.6);
	glVertex3f(-.1,-.7,30.6);//bottom
	glVertex3f(-.1,-.8,30.6);

	glVertex3f(-.1,-.8,30.7);//back
	glVertex3f(-.1,-.8,30.6);
	glVertex3f(0,4,30.6);
	glVertex3f(0,4,30.7);

	glVertex3f(-.05,2.7,26.5);
	glVertex3f(-.05,3.2,26.5);//handle
	glVertex3f(-.05,3.2,28.5);
	glVertex3f(-.05,2.7,28.5);

	//Right Door
	glColor3f(0,0,0);
	glNormal3f(1,0,0);
	glVertex3f(0,4,17.5);
	glVertex3f(0,4,17.6);//front side
	glVertex3f(-.1,-.8,17.6);
	glVertex3f(-.1,-.8,17.5);

	glVertex3f(-.1,-.8,17.6);
	glVertex3f(-.1,-.7,17.6);
	glVertex3f(-.1,-.7,30.6);//bottom
	glVertex3f(-.1,-.8,30.6);

	glVertex3f(-.1,-.8,30.7);//back
	glVertex3f(-.1,-.8,30.6);
	glVertex3f(0,4,30.6);
	glVertex3f(0,4,30.7);

	glVertex3f(-.05,2.7,26.5);
	glVertex3f(-.05,3.2,26.5);//handle
	glVertex3f(-.05,3.2,28.5);
	glVertex3f(-.05,2.7,28.5);

	//Grill
	glColor3f(0,0,0);
	glNormal3f(0,0,-1);
	glVertex3f(4,.7,0);
	glVertex3f(12,.7,0);
	glVertex3f(12,2.7,0);//background black
	glVertex3f(4,2.7,0);

	//Grill grate (vertical)
	glColor3f(.7,.7,.7);
	glVertex3f(4,.7,-0.1);
	glVertex3f(4,2.7,-.1);
	glVertex3f(4.32,2.7,-0.1);
	glVertex3f(4.32,.7,-0.1);

	glVertex3f(4.64,.7,-0.1);
	glVertex3f(4.64,2.7,-.1);
	glVertex3f(4.96,2.7,-0.1);
	glVertex3f(4.96,.7,-0.1);

	glVertex3f(5.28,.7,-0.1);
	glVertex3f(5.28,2.7,-.1);
	glVertex3f(5.6,2.7,-0.1);
	glVertex3f(5.6,.7,-0.1);

	glVertex3f(5.92,.7,-0.1);
	glVertex3f(5.92,2.7,-.1);
	glVertex3f(6.24,2.7,-0.1);
	glVertex3f(6.24,.7,-0.1);

	glVertex3f(6.56,.7,-0.1);
	glVertex3f(6.56,2.7,-.1);
	glVertex3f(6.88,2.7,-0.1);
	glVertex3f(6.88,.7,-0.1);

	glVertex3f(7.20,.7,-0.1);
	glVertex3f(7.20,2.7,-.1);
	glVertex3f(7.52,2.7,-0.1);
	glVertex3f(7.52,.7,-0.1);

	glVertex3f(7.84,.7,-0.1);
	glVertex3f(7.84,2.7,-.1);
	glVertex3f(8.16,2.7,-0.1);
	glVertex3f(8.16,.7,-0.1);

	glVertex3f(8.48,.7,-0.1);
	glVertex3f(8.48,2.7,-.1);
	glVertex3f(8.8,2.7,-0.1);
	glVertex3f(8.8,.7,-0.1);

	glVertex3f(9.12,.7,-0.1);
	glVertex3f(9.12,2.7,-.1);
	glVertex3f(9.44,2.7,-0.1);
	glVertex3f(9.44,.7,-0.1);

	glVertex3f(9.76,.7,-0.1);
	glVertex3f(9.76,2.7,-.1);
	glVertex3f(10.08,2.7,-0.1);
	glVertex3f(10.08,.7,-0.1);

	glVertex3f(10.4,.7,-0.1);
	glVertex3f(10.4,2.7,-.1);
	glVertex3f(10.72,2.7,-0.1);
	glVertex3f(10.72,.7,-0.1);

	glVertex3f(11.04,.7,-0.1);
	glVertex3f(11.04,2.7,-.1);
	glVertex3f(11.36,2.7,-0.1);
	glVertex3f(11.36,.7,-0.1);

	glVertex3f(11.68,.7,-0.1);
	glVertex3f(11.68,2.7,-.1);
	glVertex3f(12,2.7,-0.1);
	glVertex3f(12,.7,-0.1);

	glVertex3f(12,.7,-.1);
	glVertex3f(12,.8,-.1);//bottom of grill
	glVertex3f(4,.8,-.1);
	glVertex3f(4,.7,-.1);

	glVertex3f(12,2.7,-.1);//top of grill
	glVertex3f(12,2.6,-.1);
	glVertex3f(4,2.6,-.1);
	glVertex3f(4,2.7,-.1);
	glEnd();

	//Lights
	glColor3f(1,1,1);
	glBegin(GL_TRIANGLE_FAN);
	glTexCoord2f(.5,.5); //Right light
	glVertex3f(14,1.75,.01);
	for (k=0;k<=360;k+=10){
		glVertex3f(Cos(k)+14,Sin(k)+1.8,-.01);
	}
	glEnd();


	glBegin(GL_TRIANGLE_FAN);
	glTexCoord2f(.5,.5); //left light
	glVertex3f(2,1.75,.01);
	for (k=0;k<=360;k+=10){
		glVertex3f(Cos(k)+2,Sin(k)+1.8,-.01);
	}
	glEnd();
	//Right front window
	glBegin(GL_QUADS);
	glColor3f(.1,.1,.1);
	glNormal3f(1,.2,0);
	glVertex3f(16,4,18);
	glVertex3f(14.5,8,22);
	glVertex3f(14.5,8,30.4);
	glVertex3f(16,4,30.4);

	//Back Right window
	glVertex3f(16,4,38);
	glVertex3f(14.5,8,34);
	glVertex3f(14.5,8,31);
	glVertex3f(16,4,31);

	//Left front window
	glColor3f(.1,.1,.1);
	glNormal3f(-1,.2,0);
	glVertex3f(0,4,18);
	glVertex3f(1.5,8,22);
	glVertex3f(1.5,8,30.4);
	glVertex3f(0,4,30.4);

	//Back Left window
	glVertex3f(0,4,38);
	glVertex3f(1.5,8,34);
	glVertex3f(1.5,8,31);
	glVertex3f(0,4,31);

	//Front window

	glNormal3f(0,1,-1);
	glVertex3f(16,4,17);
	glVertex3f(14,8,22);
	glVertex3f(2,8,22);
	glVertex3f(0,4,17);

	//Back window
	glNormal3f(0,1,1);
	glVertex3f(14.5,8,34);
	glVertex3f(16,4,39);
	glVertex3f(0,4,39);
	glVertex3f(1.5,8,34);;

	glEnd();

	Wheel(15.0,-1,9.5,3.05,3.05,1,90,2*zh, texSide, texEdge);
	Wheel(15.0,-1,36.5,3.05,3.05,1,90,2*zh, texSide, texEdge);

	Wheel(1.0,-1,9.5,3.05,3.05,1,90,2*zh,texSide, texEdge);
	Wheel(1.0,-1,36.5,3.05,3.05,1,90,2*zh, texSide,texEdge);

	glPopMatrix();


}
