/*
 *  Shadow Map with Shaders
 *    with Frame Buffer Depth Texture by Jay Kominek
 *
 *  Demonstate shadows using the shadow map algorithm using a shader.
 *
 *  Key bindings:
 *  m/M        Show/hide shadow map
 *  o/O        Cycle through objects
 *  +/-        Change light elevation
 *  []         Change lightZ position
 *  s/S        Start/stop light movement
 *  l/L        Toggle teapot lid stretch
 *  <>         Decrease/increase number of slices in objects
 *  b/B        Toggle room box
 *  a          Toggle axes
 *  arrows     Change view angle
 *  PgDn/PgUp  Zoom in and out
 *  0          Reset view angle
 *  ESC        Exit
 */
#include "CSCIx239.h"
typedef struct {float x,y,z;} Point;
//  Global variables
int          mode=0;    // Display mode
int          obj=15;    // Display objects (bitmap)
int          move=1;    // Light movement
int          axes=1;    // Display axes
int          box=0;     // Display enclosing box
int          n=8;       // Number of slices
int          th=-26;    // Azimuth of view angle
int          ph=+23;    // Elevation of view angle
int          tex2d[25];  // Textures (names)
int          dt=50;     // Timer period (ms)
double       asp=1;     // Aspect ratio
double       dim=3;     // Size of world
int          zh=0;      // Light azimuth
float        Ylight=2;  // Elevation of light
float        Lpos[4];   // Light0 position
float        Lpos1[4];   // Light1 position
float        Lpos2[4];   // Light1 position

float        time1;

unsigned int framebuf=0;// Frame buffer id
double       Svec[4];   // Texture planes S
double car1Color[3][3] = {{0,0,.7},{1,0,0},{0,1,1}}; //car 1 color
double       Tvec[4];   // Texture planes T
double       Rvec[4];   // Texture planes R
double       Qvec[4];   // Texture planes Q
int          Width;     // Window width
int          Height;    // Window height
int          shadowdim; // Size of shadow map textures
int          shader;    // Shader
int          shader2;   //particle shader
char* text[]={"Shadows","Shadow Map"};

#define MAXN 64    // Maximum number of slices (n) and points in a polygon



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


/*
 *  Draw a wall
 */
static void Wall(float x,float y,float z, float th,float ph , float Sx,float Sy,float Sz , float St)
{
   int   i,j;
   float s=1.0/n;
   float t=0.5*St/n;

   //  Transform
   glPushMatrix();
   glTranslated(x,y,z);
   glRotated(ph,1,0,0);
	 glRotated(th,0,0,1);
   glScaled(Sx,Sy,Sz);

   //  Draw walls
   glNormal3f(0,0,1);
   for (j=-n;j<n;j++)
   {
      glBegin(GL_QUAD_STRIP);
      for (i=-n;i<=n;i++)
      {
         glTexCoord2f((i+n)*t,(j  +n)*t); glVertex3f(i*s,    j*s,-1);
         glTexCoord2f((i+n)*t,(j+1+n)*t); glVertex3f(i*s,(j+1)*s,-1);
      }
      glEnd();
   }

   //  Restore
   glPopMatrix();
}

/*
 *  Set light
 *    light>0 bright
 *    light<0 dim
 *    light=0 off
 */
static void Light(int light)
{
	//  Set light position (close lightpost)
	Lpos1[0] = 1.5;
	Lpos1[1] = 3.5;
	Lpos1[2] = 2;
	Lpos1[3] = 1;

	//  Set light position (back right lightpost)
	Lpos[0] = 1.5;
	Lpos[1] = 3.5;
	Lpos[2] = -6.1;
	Lpos[3] = 1;

  //back left lightpost
  Lpos2[0] = -10;
  Lpos2[1] = 3.5;
  Lpos2[2] = -6.1;
  Lpos2[3] = 1;
	 /*
   Lpos[0] = 2*Cos(zh);
   Lpos[1] = Ylight;
   Lpos[2] = 2*Sin(zh);
   Lpos[3] = 1;*/

   //  Enable lighting
   if (light)
   {
      float Med[]  = {0.2,0.2,0.2,1.0};
      float High[] = {1.0,1.0,1.0,1.0};
      //  Enable lighting with normalization
      glEnable(GL_LIGHTING);
      glEnable(GL_NORMALIZE);
      //  glColor sets ambient and diffuse color materials
      glColorMaterial(GL_FRONT_AND_BACK,GL_AMBIENT_AND_DIFFUSE);
      glEnable(GL_COLOR_MATERIAL);
      //  Enable light 0
      glEnable(GL_LIGHT0);
      glLightfv(GL_LIGHT0,GL_POSITION,Lpos);
      glLightfv(GL_LIGHT0,GL_AMBIENT,Med);
      glLightfv(GL_LIGHT0,GL_DIFFUSE,High);
			glEnable(GL_LIGHT1);
      glLightfv(GL_LIGHT1,GL_POSITION,Lpos1);
      glLightfv(GL_LIGHT1,GL_AMBIENT,Med);
      glLightfv(GL_LIGHT1,GL_DIFFUSE,High);
	 }
   else
   {
      glDisable(GL_LIGHTING);
      glDisable(GL_COLOR_MATERIAL);
      glDisable(GL_NORMALIZE);
   }
}

/*
 *  Draw scene
 *    light (true enables lighting)
 */
void Scene(int light)
{
   int k;  // Counters used to draw floor

   //  Set light position and properties
   Light(light);

   //  Enable textures if lit
   if (light)
   {
      glEnable(GL_TEXTURE_2D);
      glBindTexture(GL_TEXTURE_2D,tex2d[2]);
   }


	 glActiveTexture(GL_TEXTURE0);
	 glBindTexture(GL_TEXTURE_2D,tex2d[6]);
	 glActiveTexture(GL_TEXTURE2);
	 glBindTexture(GL_TEXTURE_2D,tex2d[10]);
	 FireHydrant(-1,-1.9,-6.8,.3,.3,.3,90);
   FireHydrant(-13.5,-1.9,-6.8,.3,.3,.3,90);

   glActiveTexture(GL_TEXTURE0);
   glBindTexture(GL_TEXTURE_2D, tex2d[5]);

   Trash(-5,-1.9,-7.8,.2,.6,.2,90);
   Trash(-2.7,-1.9,2.2,.2,.6,.2,90);

	// FireHydrant(0,0,2,.3,.3,.3,90);
	 glActiveTexture(GL_TEXTURE0);
	 glBindTexture(GL_TEXTURE_2D,tex2d[12]);
	 glActiveTexture(GL_TEXTURE2);
	 glBindTexture(GL_TEXTURE_2D,tex2d[13]);
	 Door(1.5,-1.9,-8.5,.1,.1,.1,0,0);
	 Door(-2.9,-1.9,-8.5,.1,.1,.1,0,0);
	 Door(-7.3,-1.9,-8.5,.1,.1,.1,0,0);
	 Door(-11.7,-1.9,-8.5,.1,.1,.1,0,0);
	 Door(-16.2,-1.9,-8.5,.1,.1,.1,0,0);
	 Door(-20.7,-1.9,-8.5,.1,.1,.1,0,0);

	 glActiveTexture(GL_TEXTURE2);
	 glBindTexture(GL_TEXTURE_2D,tex2d[17]);
	 glActiveTexture(GL_TEXTURE0);
	 glBindTexture(GL_TEXTURE_2D,tex2d[16]);
	 Building(-.3,-1.9,-9.5,1,.5,1,0,0);
	 Building(-9.1,-2.1,-9.5,1,.5,1,0,0);
	 Building(-22.5,-1.9,-9.5,1,.5,1,0,0);

	 glActiveTexture(GL_TEXTURE2);
	 glBindTexture(GL_TEXTURE_2D,tex2d[11]);
	 glActiveTexture(GL_TEXTURE0);
	 glBindTexture(GL_TEXTURE_2D,tex2d[9]);
	 Building(-4.7,-2.9,-9.5,1,.5,1,0,0);
	 Building(-13.5,-1.9,-9.5,1,.5,1,0,0);
	 Building(-18,-2.0,-9.5,1,.5,1,0,0);

	 glActiveTexture(GL_TEXTURE0);
	 glBindTexture(GL_TEXTURE_2D,tex2d[6]);
   glActiveTexture(GL_TEXTURE2);
   glBindTexture(GL_TEXTURE_2D,tex2d[6]);
   float x = -10 + time1*4;
   //printf ("%f\n", x);
   while (x > 10) x -= 20;
   Car(x,-1.68,-1,.08,.08,.08,270,.5*zh,car1Color[0], tex2d[19], tex2d[20]);
	 //Car(0,-1.68,-1,.08,.08,.08,270,.5*zh,car1Color[0], tex2d[19], tex2d[20]);
   //get dt
	 Bicycle(-2.5,-1.85,-5.5,.45,.45,.45,300,car1Color[1],70);
   Bicycle(-2.5,-1.45,2.5,.45,.45,.45,0,car1Color[2],15);
   glColor3f(0,0,0);
   Cylinder(-2,2.8,-9,.02,.02,1,90,0);

   glActiveTexture(GL_TEXTURE0);
   glBindTexture(GL_TEXTURE_2D,tex2d[6]);
   glActiveTexture(GL_TEXTURE2);
	 glBindTexture(GL_TEXTURE_2D,tex2d[10]);
	 Lightpost(1.5,-1.2,-6.6,.5,.5,.5,90,1);
	 Lightpost(1.5,-1.2,1.4,.4,.4,.4,270,1);
	 Lightpost(-11.85,-1.2,-6.6,.5,.5,.5,90,1);
   glColor3f(1,1,1);
	 glActiveTexture(GL_TEXTURE0);
	 glBindTexture(GL_TEXTURE_2D, tex2d[14]);
	 glActiveTexture(GL_TEXTURE2);
	 glBindTexture(GL_TEXTURE_2D, tex2d[15]);
	 Window(.4,3,-8.5,.55,.55,.55,0,0);
	 Window(.4,2,-8.5,.55,.55,.55,0,0);
	 Window(.4,1,-8.5,.55,.55,.55,0,0);
	 Window(.4,0,-8.5,.55,.55,.55,0,0);
	 Window(.4,-1,-8.5,.55,.55,.55,0,0);
	 Window(2.7,3,-8.5,.55,.55,.55,0,0);
	 Window(2.7,2,-8.5,.55,.55,.55,0,0);
	 Window(2.7,1,-8.5,.55,.55,.55,0,0);
	 Window(2.7,0,-8.5,.55,.55,.55,0,0);
	 Window(2.7,-1,-8.5,.55,.55,.55,0,0);
	 Window(1.55,3,-8.5,.55,.55,.55,0,0);
	 Window(1.55,2,-8.5,.55,.55,.55,0,0);
	 Window(1.55,1,-8.5,.55,.55,.55,0,0);
	 Window(1.55,0,-8.5,.55,.55,.55,0,0);
	 //Window(-4.0,3,-8.5,.55,.55,.55,0,0);
	 Window(-4.0,2,-8.5,.55,.55,.55,0,0);
	 Window(-4.0,1,-8.5,.55,.55,.55,0,0);
	 Window(-4.0,0,-8.5,.55,.55,.55,0,0);
	 Window(-4.0,-1,-8.5,.55,.55,.55,0,0);
	 //Window(-1.7,3,-8.5,.55,.55,.55,0,0);
	 Window(-1.7,2,-8.5,.55,.55,.55,0,0);
	 Window(-1.7,1,-8.5,.55,.55,.55,0,0);
	 Window(-1.7,0,-8.5,.55,.55,.55,0,0);
	 Window(-1.7,-1,-8.5,.55,.55,.55,0,0);
	 //Window(-2.85,3,-8.5,.55,.55,.55,0,0);
	 Window(-2.85,2,-8.5,.55,.55,.55,0,0);
	 Window(-2.85,1,-8.5,.55,.55,.55,0,0);
	 Window(-2.85,0,-8.5,.55,.55,.55,0,0);
	 Window(-8.4,3,-8.5,.55,.55,.55,0,0);
	 Window(-8.4,2,-8.5,.55,.55,.55,0,0);
	 Window(-8.4,1,-8.5,.55,.55,.55,0,0);
	 Window(-8.4,0,-8.5,.55,.55,.55,0,0);
	 Window(-8.4,-1,-8.5,.55,.55,.55,0,0);
	 Window(-6.1,3,-8.5,.55,.55,.55,0,0);
	 Window(-6.1,2,-8.5,.55,.55,.55,0,0);
	 Window(-6.1,1,-8.5,.55,.55,.55,0,0);
	 Window(-6.1,0,-8.5,.55,.55,.55,0,0);
	 Window(-6.1,-1,-8.5,.55,.55,.55,0,0);
	 Window(-7.25,3,-8.5,.55,.55,.55,0,0);
	 Window(-7.25,2,-8.5,.55,.55,.55,0,0);
	 Window(-7.25,1,-8.5,.55,.55,.55,0,0);
	 Window(-7.25,0,-8.5,.55,.55,.55,0,0);
	 Window(-12.8,3,-8.5,.55,.55,.55,0,0);
	 Window(-12.8,2,-8.5,.55,.55,.55,0,0);
	 Window(-12.8,1,-8.5,.55,.55,.55,0,0);
	 Window(-12.8,0,-8.5,.55,.55,.55,0,0);
	 Window(-12.8,-1,-8.5,.55,.55,.55,0,0);
	 Window(-10.5,3,-8.5,.55,.55,.55,0,0);
	 Window(-10.5,2,-8.5,.55,.55,.55,0,0);
	 Window(-10.5,1,-8.5,.55,.55,.55,0,0);
	 Window(-10.5,0,-8.5,.55,.55,.55,0,0);
	 Window(-10.5,-1,-8.5,.55,.55,.55,0,0);
	 Window(-11.65,3,-8.5,.55,.55,.55,0,0);
	 Window(-11.65,2,-8.5,.55,.55,.55,0,0);
	 Window(-11.65,1,-8.5,.55,.55,.55,0,0);
	 Window(-11.65,0,-8.5,.55,.55,.55,0,0);
	 Window(-17.3,3,-8.5,.55,.55,.55,0,0);
	 Window(-17.3,2,-8.5,.55,.55,.55,0,0);
	 Window(-17.3,1,-8.5,.55,.55,.55,0,0);
	 Window(-17.3,0,-8.5,.55,.55,.55,0,0);
	 Window(-17.3,-1,-8.5,.55,.55,.55,0,0);
	 Window(-15,3,-8.5,.55,.55,.55,0,0);
	 Window(-15,2,-8.5,.55,.55,.55,0,0);
	 Window(-15,1,-8.5,.55,.55,.55,0,0);
	 Window(-15,0,-8.5,.55,.55,.55,0,0);
	 Window(-15,-1,-8.5,.55,.55,.55,0,0);
	 Window(-16.05,3,-8.5,.55,.55,.55,0,0);
	 Window(-16.05,2,-8.5,.55,.55,.55,0,0);
	 Window(-16.05,1,-8.5,.55,.55,.55,0,0);
	 Window(-16.05,0,-8.5,.55,.55,.55,0,0);
	 Window(-19.5,3,-8.5,.55,.55,.55,0,0);
	 Window(-19.5,2,-8.5,.55,.55,.55,0,0);
	 Window(-19.5,1,-8.5,.55,.55,.55,0,0);
	 Window(-19.5,0,-8.5,.55,.55,.55,0,0);
	 Window(-19.5,-1,-8.5,.55,.55,.55,0,0);
	 //Building(-10,-1.9,-8.5,1,.5,1,90,color,0);



   //  Disable textures
   if (light) glDisable(GL_TEXTURE_2D);

   //  The floor, ceiling and walls don't cast a shadow, so bail here
   if (!light) return;

   //  Enable textures for floor, ceiling and walls
   glEnable(GL_TEXTURE_2D);

   //  Water texture for floor and ceiling
	 glActiveTexture(GL_TEXTURE0);
   glBindTexture(GL_TEXTURE_2D,tex2d[7]);
	 glActiveTexture(GL_TEXTURE2);
	 glBindTexture(GL_TEXTURE_2D,tex2d[8]);
   glColor3f(1.0,1.0,1.0);
   for (k=-1;k<=box;k+=2)
      Wall(-4,0,1.5, 90,90*k , 2*8,2*8,2*box?6:2 , 4);
   //  Crate texture for walls
	 glActiveTexture(GL_TEXTURE0);
	 glBindTexture(GL_TEXTURE_2D, tex2d[3]);
	 glActiveTexture(GL_TEXTURE2);
	 glBindTexture(GL_TEXTURE_2D,tex2d[4]);
	 Sidewalk(-8,-1.9,1.5,5,5,5,270,270);
	 Sidewalk(5,-1.9,-6.5,5,5,5,270,90);
	 Sidewalk(5,-1.9,-8.5,5,5,5,270,90);
	 Sidewalk(5,-1.9,-10.5,5,5,5,270,90);

   glActiveTexture(GL_TEXTURE2);
   glBindTexture(GL_TEXTURE_2D, tex2d[6]);
   int color[3] = {1,1,1};

   //double quad1[4][4][3] = {{{0,-2,0},{0,-1.4,0},{-3.7,-1.4,0},{-3.7,-2,0}},{{-1.7,-1,0},{-1.3,-1.4,0},{-3.2,-1.4,0},{-2.65,-1,0}},{{-3.7,-2,0},{-3.7,-1.4,0},{-3.7,-1.4,-.8},{-3.7,-2,-.8}},{{0,-2,0},{0,-1.4,0},{0,-1.4,-.8},{0,-2,-.8}}}; //quads for light 1/3
   //double quad2[4][4][3] = {{{0,-2,-.8},{0,-1.4,-.8},{-3.7,-1.4,-.8},{-3.7,-2,-.8}},{{-1.7,-1,-.8},{-1.3,-1.4,-.8},{-3.2,-1.4,-.8},{-2.65,-1,-.8}},{{-3.7,-2,0},{-3.7,-1.4,0},{-3.7,-1.4,-.8},{-3.7,-2,-.8}},{{0,-2,0},{0,-1.4,0},{0,-1.4,-.8},{0,-2,-.8}}}; //quads for light 2

   double quad1[4][4][3] = {{{x,-2,0},{x,-1.4,0},{-3.7+x,-1.4,0},{-3.7+x,-2,0}},{{-1.7 + x,-1,0},{-1.3+x,-1.4,0},{-3.2+x,-1.4,0},{-2.65+x,-1,0}},{{-3.7+x,-2,0},{-3.7+x,-1.4,0},{-3.7+x,-1.4,-.8},{-3.7+x,-2,-.8}},{{0+x,-2,0},{0+x,-1.4,0},{0+x,-1.4,-.8},{0+x,-2,-.8}}}; //quads for light 1/3
   double quad2[4][4][3] = {{{x,-2,-.8},{x,-1.4,-.8},{-3.7+x,-1.4,-.8},{-3.7+x,-2,-.8}},{{-1.7 +x,-1,-.8},{-1.3+x,-1.4,-.8},{-3.2+x,-1.4,-.8},{-2.65+x,-1,-.8}},{{-3.7+x,-2,0},{-3.7+x,-1.4,0},{-3.7+x,-1.4,-.8},{-3.7+x,-2,-.8}},{{0+x,-2,0},{0+x,-1.4,0},{0+x,-1.4,-.8},{0+x,-2,-.8}}}; //quads for light 2

   double shadow[4][3];
   int i;
   int j;
   double O1[3] = {Lpos[0],Lpos[1],Lpos[2]};

   for (i = 0; i < 4; i++){ //quads
      for (j = 0; j < 4; j++){ //points
         double D1[3] = {quad1[i][j][0] - O1[0], quad1[i][j][1] - O1[1],quad1[i][j][2] - O1[2]};
         double lengthVec = sqrt(D1[0]*D1[0] + D1[1]*D1[1] + D1[2]*D1[2]);
         double D1Normal[3] = {D1[0]/lengthVec, D1[1]/lengthVec, D1[2]/lengthVec};
         double vectorTime = (-1.99 - O1[1])/D1[1];
         double P1[3] = {O1[0] + D1[0]*vectorTime, -1.99, O1[2] + D1[2]*vectorTime};
         shadow[j][0] = P1[0];
         shadow[j][1] = P1[1];
         shadow[j][2] = P1[2];
      }
      //glDisable(GL_DEPTH_TEST);
      glColor4f(0,0,0,0);

      glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
      glEnable(GL_BLEND);
      glClearColor(0.0,0.0,0.0,0.0);
      glBegin(GL_QUADS);

      glVertex3f(shadow[0][0],shadow[0][1],shadow[0][2]);
      glVertex3f(shadow[1][0],shadow[1][1],shadow[1][2]);
      glVertex3f(shadow[2][0],shadow[2][1],shadow[2][2]);
      glVertex3f(shadow[3][0],shadow[3][1],shadow[3][2]);
      glEnd();
      glDisable(GL_BLEND);
      //glEnable(GL_DEPTH_TEST);

   }

   double O2[3] = {Lpos1[0],Lpos1[1],Lpos1[2]};

   for (i = 0; i < 4; i++){ //quads
      for (j = 0; j < 4; j++){ //points
         double D2[3] = {quad2[i][j][0] - O2[0], quad2[i][j][1] - O2[1],quad2[i][j][2] - O2[2]};
         double lengthVec = sqrt(D2[0]*D2[0] + D2[1]*D2[1] + D2[2]*D2[2]);
         double D2Normal[3] = {D2[0]/lengthVec, D2[1]/lengthVec, D2[2]/lengthVec};
         double vectorTime = (-1.99 - O2[1])/D2[1];
         double P2[3] = {O2[0] + D2[0]*vectorTime, -1.99, O2[2] + D2[2]*vectorTime};
         shadow[j][0] = P2[0];
         shadow[j][1] = P2[1];
         shadow[j][2] = P2[2];
      }
      //glDisable(GL_DEPTH_TEST);
      glColor3f(0,0,0);
      glEnable(GL_BLEND);
      glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
      glBegin(GL_QUADS);

      glVertex3f(shadow[0][0],shadow[0][1],shadow[0][2]);
      glVertex3f(shadow[1][0],shadow[1][1],shadow[1][2]);
      glVertex3f(shadow[2][0],shadow[2][1],shadow[2][2]);
      glVertex3f(shadow[3][0],shadow[3][1],shadow[3][2]);
      glEnd();
      //glDisable(GL_BLEND);
      //glEnable(GL_DEPTH_TEST);

   }
/*
   double O3[3] = {Lpos2[0],Lpos2[1],Lpos2[2]};

   for (i = 0; i < 4; i++){ //quads
      for (j = 0; j < 4; j++){ //points
         double D3[3] = {quad1[i][j][0] - O3[0], quad1[i][j][1] - O3[1],quad1[i][j][2] - O3[2]};
         double lengthVec = sqrt(D3[0]*D3[0] + D3[1]*D3[1] + D3[2]*D3[2]);
         double D3Normal[3] = {D3[0]/lengthVec, D3[1]/lengthVec, D3[2]/lengthVec};
         double vectorTime = (-1.99 - O3[1])/D3[1];
         double P3[3] = {O3[0] + D3[0]*vectorTime, -1.99, O3[2] + D3[2]*vectorTime};
         shadow[j][0] = P3[0];
         shadow[j][1] = P3[1];
         shadow[j][2] = P3[2];
      }
      //glDisable(GL_DEPTH_TEST);
      glColor4f(0,0,0,0);
      glEnable(GL_BLEND);
      glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
      glBegin(GL_QUADS);

      glVertex3f(shadow[0][0],shadow[0][1],shadow[0][2]);
      glVertex3f(shadow[1][0],shadow[1][1],shadow[1][2]);
      glVertex3f(shadow[2][0],shadow[2][1],shadow[2][2]);
      glVertex3f(shadow[3][0],shadow[3][1],shadow[3][2]);
      glEnd();
      glDisable(GL_BLEND);
      //glEnable(GL_DEPTH_TEST);

   }
*/

  /*

   glBegin(GL_QUADS);
   glVertex3f(quad1[0][0][0],quad1[0][0][1],quad1[0][0][2]);
   glVertex3f(quad1[0][1][0],quad1[0][1][1],quad1[0][1][2]);
   glVertex3f(quad1[0][2][0],quad1[0][2][1],quad1[0][2][2]);
   glVertex3f(quad1[0][3][0],quad1[0][3][1],quad1[0][3][2]);

   glVertex3f(quad1[1][0][0],quad1[1][0][1],quad1[1][0][2]);
   glVertex3f(quad1[1][1][0],quad1[1][1][1],quad1[1][1][2]);
   glVertex3f(quad1[1][2][0],quad1[1][2][1],quad1[1][2][2]);
   glVertex3f(quad1[1][3][0],quad1[1][3][1],quad1[1][3][2]);

   glVertex3f(quad2[0][0][0],quad2[0][0][1],quad2[0][0][2]);
   glVertex3f(quad2[0][1][0],quad2[0][1][1],quad2[0][1][2]);
   glVertex3f(quad2[0][2][0],quad2[0][2][1],quad2[0][2][2]);
   glVertex3f(quad2[0][3][0],quad2[0][3][1],quad2[0][3][2]);

   glVertex3f(quad2[1][0][0],quad2[1][0][1],quad2[1][0][2]);
   glVertex3f(quad2[1][1][0],quad2[1][1][1],quad2[1][1][2]);
   glVertex3f(quad2[1][2][0],quad2[1][2][1],quad2[1][2][2]);
   glVertex3f(quad2[1][3][0],quad2[1][3][1],quad2[1][3][2]);

   glEnd();

  */

   glActiveTexture(GL_TEXTURE0);
	 glBindTexture(GL_TEXTURE_2D, tex2d[18]);
   glActiveTexture(GL_TEXTURE2);
   glBindTexture(GL_TEXTURE_2D,tex2d[6]);
	 SkyBox(20);

	 //Sidewalk(-8,-1.9,-8,5,5,5,270,90);


   //  Disable textures
   glDisable(GL_TEXTURE_2D);
}

/*
 *  OpenGL (GLUT) calls this routine to display the scene
 */
void display()
{
   int id;
   const double len=2.0;
   //  Eye position
   float Ex = -2*dim*Sin(th)*Cos(ph);
   float Ey = +2*dim        *Sin(ph);
   float Ez = +2*dim*Cos(th)*Cos(ph);

   //  Erase the window and the depth buffers
   glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
   //  Disable lighting
   glDisable(GL_LIGHTING);

   //
   //  Draw the scene with shadows
   //
   //  Set perspective view
   if (mode)
   {
      //  Half width for shadow map display
      Project(60,asp/2,dim);
      glViewport(0,0,Width/2,Height);
   }
   else
   {
      //  Full width
      Project(60,asp,dim);
      glViewport(0,0,Width,Height);
   }
   gluLookAt(Ex,Ey,Ez , 0,0,0 , 0,Cos(ph),0);

   //  Draw light position as sphere (still no lighting here)
   glColor3f(1,1,1);
   glPushMatrix();
   glTranslated(Lpos[0],Lpos[1],Lpos[2]);
   glutSolidSphere(0.03,10,10);
   glPopMatrix();

	 glPushMatrix();
   glTranslated(Lpos1[0],Lpos1[1],Lpos1[2]);
   glutSolidSphere(0.03,10,10);
   glPopMatrix();

   glPushMatrix();
   glTranslated(Lpos2[0],Lpos2[1],Lpos2[2]);
   glutSolidSphere(0.03,10,10);
   glPopMatrix();
   glUseProgram(shader2);

   //  Enable shader program
   glUseProgram(shader);
   id = glGetUniformLocation(shader,"tex");
   if (id>=0) glUniform1i(id,0);
   id = glGetUniformLocation(shader,"depth");
   if (id>=0) glUniform1i(id,1);
	 id = glGetUniformLocation(shader,"normalTex");
	 if (id>=0) glUniform1i(id,2);
	 // Draw objects in the scene (including walls)
   Scene(-1);
   // Set up the eye plane for projecting the shadow map on the scene

   glActiveTexture(GL_TEXTURE1);
   glTexGendv(GL_S,GL_EYE_PLANE,Svec);
   glTexGendv(GL_T,GL_EYE_PLANE,Tvec);
   glTexGendv(GL_R,GL_EYE_PLANE,Rvec);
   glTexGendv(GL_Q,GL_EYE_PLANE,Qvec);
   glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_COMPARE_MODE,GL_COMPARE_R_TO_TEXTURE);
   glActiveTexture(GL_TEXTURE0);




   //  Disable shader program
   glUseProgram(0);

   //  Draw axes (white)
   glColor3f(1,1,1);
   if (axes)
   {
      glBegin(GL_LINES);
      glVertex3d(0.0,0.0,0.0);
      glVertex3d(len,0.0,0.0);
      glVertex3d(0.0,0.0,0.0);
      glVertex3d(0.0,len,0.0);
      glVertex3d(0.0,0.0,0.0);
      glVertex3d(0.0,0.0,len);
      glEnd();
      //  Label axes
      glRasterPos3d(len,0.0,0.0);
      Print("X");
      glRasterPos3d(0.0,len,0.0);
      Print("Y");
      glRasterPos3d(0.0,0.0,len);
      Print("Z");
   }

   //
   //  Show the shadow map
   //
   if (mode)
   {
      int n,ix=Width/2+5,iy=Height-5;
      //  Orthogonal view (right half)
      Project(0,asp/2,1);
      glViewport(Width/2+1,0,Width/2,Height);
      //  Disable any manipulation of textures
      glActiveTexture(GL_TEXTURE1);
      glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_COMPARE_MODE,GL_NONE);
      //  Display texture by drawing quad
      glEnable(GL_TEXTURE_2D);
      glColor3f(1,1,1);
      glBegin(GL_QUADS);
      glMultiTexCoord2f(GL_TEXTURE1,0,0);glVertex2f(-1,-1);
      glMultiTexCoord2f(GL_TEXTURE1,1,0);glVertex2f(+1,-1);
      glMultiTexCoord2f(GL_TEXTURE1,1,1);glVertex2f(+1,+1);
      glMultiTexCoord2f(GL_TEXTURE1,0,1);glVertex2f(-1,+1);
      glEnd();
      glDisable(GL_TEXTURE_2D);
      //  Switch back to default texture unit
      glActiveTexture(GL_TEXTURE0);
      //  Show buffer info
      glColor3f(1,0,0);
      glWindowPos2i(ix,iy-=20);
      glGetIntegerv(GL_MAX_TEXTURE_UNITS,&n);
      Print("Maximum Texture Units %d\n",n);
      glGetIntegerv(GL_MAX_TEXTURE_SIZE,&n);
      glWindowPos2i(ix,iy-=20);
      Print("Maximum Texture Size %d\n",n);
      glGetIntegerv(GL_MAX_RENDERBUFFER_SIZE,&n);
      glWindowPos2i(ix,iy-=20);
      Print("Maximum Buffer Size  %d\n",n);
      glWindowPos2i(ix,iy-=20);
      Print("Shadow Texture Size %dx%d\n",shadowdim,shadowdim);
   }

   //  Display parameters
   glColor3f(1,1,1);
   glWindowPos2i(5,5);
   Print("Ylight=%.1f Angle=%d,%d,%d  Dim=%.1f Slices=%d Mode=%s",
     Ylight,th,ph,zh,dim,n,text[mode]);

   //  Render the scene and make it visible
   ErrCheck("display");
   glFlush();
   glutSwapBuffers();
}

/*
 *  Build Shadow Map
 */
void ShadowMap(void)
{
   double Lmodel[16];  //  Light modelview matrix
   double Lproj[16];   //  Light projection matrix
   double Tproj[16];   //  Texture projection matrix
   double Dim=7.0;     //  Bounding radius of scene
   double Ldist;       //  Distance from light to scene center
	 double Ldist1; 		 // Distance from light 1 to scene center
   //  Save transforms and modes
   glPushMatrix();
   glPushAttrib(GL_TRANSFORM_BIT|GL_ENABLE_BIT);
   //  No write to color buffer and no smoothing
   glShadeModel(GL_FLAT);
   glColorMask(0,0,0,0);
   // Overcome imprecision
   glEnable(GL_POLYGON_OFFSET_FILL);

   //  Turn off lighting and set light position
   Light(0);

   //  Light distance
   Ldist = sqrt(Lpos[0]*Lpos[0] + Lpos[1]*Lpos[1] + Lpos[2]*Lpos[2]);
   if (Ldist<1.1*Dim) Ldist = 1.1*Dim;

   //  Set perspective view from light position
   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();
   gluPerspective(114.6*atan(Dim/Ldist),1,Ldist-Dim,Ldist+Dim);
   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity();
   gluLookAt(Lpos[0],Lpos[1],Lpos[2] , 0,0,0 , 0,1,0);
   //  Size viewport to desired dimensions
   glViewport(0,0,shadowdim,shadowdim);

   // Redirect traffic to the frame buffer
   glBindFramebuffer(GL_FRAMEBUFFER,framebuf);

   // Clear the depth buffer
   glClear(GL_DEPTH_BUFFER_BIT);
   // Draw all objects that can cast a shadow
   Scene(0);

   //  Retrieve light projection and modelview matrices
   glGetDoublev(GL_PROJECTION_MATRIX,Lproj);
   glGetDoublev(GL_MODELVIEW_MATRIX,Lmodel);

   // Set up texture matrix for shadow map projection,
   // which will be rolled into the eye linear
   // texture coordinate generation plane equations
   glLoadIdentity();
   glTranslated(0.5,0.5,0.5);
   glScaled(0.5,0.5,0.5);
   glMultMatrixd(Lproj);
   glMultMatrixd(Lmodel);

   // Retrieve result and transpose to get the s, t, r, and q rows for plane equations
   glGetDoublev(GL_MODELVIEW_MATRIX,Tproj);
   Svec[0] = Tproj[0];    Tvec[0] = Tproj[1];    Rvec[0] = Tproj[2];    Qvec[0] = Tproj[3];
   Svec[1] = Tproj[4];    Tvec[1] = Tproj[5];    Rvec[1] = Tproj[6];    Qvec[1] = Tproj[7];
   Svec[2] = Tproj[8];    Tvec[2] = Tproj[9];    Rvec[2] = Tproj[10];   Qvec[2] = Tproj[11];
   Svec[3] = Tproj[12];   Tvec[3] = Tproj[13];   Rvec[3] = Tproj[14];   Qvec[3] = Tproj[15];

   // Restore normal drawing state
   glShadeModel(GL_SMOOTH);
   glColorMask(1,1,1,1);
   glDisable(GL_POLYGON_OFFSET_FILL);
   glPopAttrib();
   glPopMatrix();
   glBindFramebuffer(GL_FRAMEBUFFER,0);
/*
	 //Now for light 1
	 //  Save transforms and modes
	 glPushMatrix();
	 glPushAttrib(GL_TRANSFORM_BIT|GL_ENABLE_BIT);
	 //  No write to color buffer and no smoothing
	 glShadeModel(GL_FLAT);
	 glColorMask(0,0,0,0);
	 // Overcome imprecision
	 glEnable(GL_POLYGON_OFFSET_FILL);

	 //  Turn off lighting and set light position
	 Light(0);

	 //  Light distance
	 Ldist1 = sqrt(Lpos1[0]*Lpos1[0] + Lpos1[1]*Lpos1[1] + Lpos1[2]*Lpos1[2]);
	 if (Ldist1<1.1*Dim) Ldist1 = 1.1*Dim;

	 //  Set perspective view from light position
	 glMatrixMode(GL_PROJECTION);
	 glLoadIdentity();
	 gluPerspective(114.6*atan(Dim/Ldist1),1,Ldist1-Dim,Ldist1+Dim);
	 glMatrixMode(GL_MODELVIEW);
	 glLoadIdentity();
	 gluLookAt(Lpos1[0],Lpos1[1],Lpos1[2] , 0,0,0 , 0,1,0);
	 //  Size viewport to desired dimensions
	 glViewport(0,0,shadowdim,shadowdim);

	 // Redirect traffic to the frame buffer
	 glBindFramebuffer(GL_FRAMEBUFFER,framebuf);

	 // Clear the depth buffer
	 glClear(GL_DEPTH_BUFFER_BIT);
	 // Draw all objects that can cast a shadow
	 Scene(0);

	 //  Retrieve light projection and modelview matrices
	 glGetDoublev(GL_PROJECTION_MATRIX,Lproj);
	 glGetDoublev(GL_MODELVIEW_MATRIX,Lmodel);

	 // Set up texture matrix for shadow map projection,
	 // which will be rolled into the eye linear
	 // texture coordinate generation plane equations
	 glLoadIdentity();
	 glTranslated(0.5,0.5,0.5);
	 glScaled(0.5,0.5,0.5);
	 glMultMatrixd(Lproj);
	 glMultMatrixd(Lmodel);

	 // Retrieve result and transpose to get the s, t, r, and q rows for plane equations
	 glGetDoublev(GL_MODELVIEW_MATRIX,Tproj);
	 Svec[0] = Tproj[0];    Tvec[0] = Tproj[1];    Rvec[0] = Tproj[2];    Qvec[0] = Tproj[3];
	 Svec[1] = Tproj[4];    Tvec[1] = Tproj[5];    Rvec[1] = Tproj[6];    Qvec[1] = Tproj[7];
	 Svec[2] = Tproj[8];    Tvec[2] = Tproj[9];    Rvec[2] = Tproj[10];   Qvec[2] = Tproj[11];
	 Svec[3] = Tproj[12];   Tvec[3] = Tproj[13];   Rvec[3] = Tproj[14];   Qvec[3] = Tproj[15];

	 // Restore normal drawing state
	 glShadeModel(GL_SMOOTH);
	 glColorMask(1,1,1,1);
	 glDisable(GL_POLYGON_OFFSET_FILL);
	 glPopAttrib();
	 glPopMatrix();
	 //glBindFramebuffer(GL_FRAMEBUFFER,0);

*/
   //  Check if something went wrong
   ErrCheck("ShadowMap");
}

/*
 *
 */
void InitMap()
{
   unsigned int shadowtex; //  Shadow buffer texture id
	 unsigned int shadowtex1;
   int n;

   //  Make sure multi-textures are supported
   glGetIntegerv(GL_MAX_TEXTURE_UNITS,&n);
   if (n<2) Fatal("Multiple textures not supported\n");

   //  Get maximum texture buffer size
   glGetIntegerv(GL_MAX_TEXTURE_SIZE,&shadowdim);
   //  Limit texture size to maximum buffer size
   glGetIntegerv(GL_MAX_RENDERBUFFER_SIZE,&n);
   if (shadowdim>n) shadowdim = n;
   //  Limit texture size to 2048 for performance
   if (shadowdim>2048) shadowdim = 2048;
   if (shadowdim<512) Fatal("Shadow map dimensions too small %d\n",shadowdim);

   //  Do Shadow textures in MultiTexture 1
   glActiveTexture(GL_TEXTURE1);

   //  Allocate and bind shadow texture
   glGenTextures(1,&shadowtex);
   glBindTexture(GL_TEXTURE_2D,shadowtex);
   glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT24, shadowdim, shadowdim, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);

   //  Map single depth value to RGBA (this is called intensity)
   glTexParameteri(GL_TEXTURE_2D,GL_DEPTH_TEXTURE_MODE,GL_INTENSITY);

   //  Set texture mapping to clamp and linear interpolation
   glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_CLAMP_TO_EDGE);
   glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_CLAMP_TO_EDGE);
   glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
   glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);

   //  Set automatic texture generation mode to Eye Linear
   glTexGeni(GL_S,GL_TEXTURE_GEN_MODE,GL_EYE_LINEAR);
   glTexGeni(GL_T,GL_TEXTURE_GEN_MODE,GL_EYE_LINEAR);
   glTexGeni(GL_R,GL_TEXTURE_GEN_MODE,GL_EYE_LINEAR);
   glTexGeni(GL_Q,GL_TEXTURE_GEN_MODE,GL_EYE_LINEAR);

   // Switch back to default textures
   glActiveTexture(GL_TEXTURE0);

   // Attach shadow texture to frame buffer
   glGenFramebuffers(1,&framebuf);
   glBindFramebuffer(GL_FRAMEBUFFER,framebuf);
   glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, shadowtex, 0);
   //  Don't write or read to visible color buffer
   glDrawBuffer(GL_NONE);
   glReadBuffer(GL_NONE);
   //  Make sure this all worked
   if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) Fatal("Error setting up frame buffer\n");
   glBindFramebuffer(GL_FRAMEBUFFER,0);
   //  Check if something went wrong
   ErrCheck("InitMap");

   //  Create shadow map
   ShadowMap();
}

/*
 *  GLUT calls this routine when nothing else is going on
 */
void idle(int k)
{
   static float lastTime = -1;
   double t = glutGet(GLUT_ELAPSED_TIME)/1000.0;

   //  Elapsed time in seconds
   if (lastTime == -1){
     lastTime = t;
   }
   float dt2 = t - lastTime;
   zh = fmod(90*t,1440.0);

   //  Update shadow map
   ShadowMap();
   //  Tell GLUT it is necessary to redisplay the scene
   glutPostRedisplay();
   //  Schedule update
   if (move) glutTimerFunc(dt,idle,0);
   time1 = t;
   lastTime = t;
}

/*
 *  GLUT calls this routine when an arrow key is pressed
 */
void special(int key,int x,int y)
{
   //  Right arrow key - increase angle by 5 degrees
   if (key == GLUT_KEY_RIGHT)
      th += 1;
   //  Left arrow key - decrease angle by 5 degrees
   else if (key == GLUT_KEY_LEFT)
      th -= 1;
   //  Up arrow key - increase elevation by 5 degrees
   else if (key == GLUT_KEY_UP)
      ph += 1;
   //  Down arrow key - decrease elevation by 5 degrees
   else if (key == GLUT_KEY_DOWN)
      ph -= 1;
   //  PageUp key - increase dim
   else if (key == GLUT_KEY_PAGE_DOWN)
      dim += 0.1;
   //  PageDown key - decrease dim
   else if (key == GLUT_KEY_PAGE_UP && dim>1)
      dim -= 0.1;
   //  Keep angles to +/-360 degrees
   th %= 360;
   ph %= 360;
   //  Tell GLUT it is necessary to redisplay the scene
   glutPostRedisplay();
}

/*
 *  GLUT calls this routine when a key is pressed
 */
void key(unsigned char ch,int x,int y)
{
   //  Exit on ESC
   if (ch == 27)
      exit(0);
   //  Reset view angle
   else if (ch == '0')
      th = ph = 0;
   //  Toggle axes
   else if (ch == 'a' || ch == 'A')
      axes = 1-axes;
   //  Toggle display modes
   else if (ch == 'm' || ch == 'M')
      mode = 1-mode;
   //  Toggle light movement
   else if (ch == 's' || ch == 'S')
      move = 1-move;
   //  Toggle box
   else if (ch == 'b' || ch == 'B')
      box = 1-box;
   //  Toggle objects
   else if (ch == 'o')
      obj = (obj+1)%16;
   else if (ch == 'O')
      obj = (obj+15)%16;
   //  Light elevation
   else if (ch=='-')
      Ylight -= 0.1;
   else if (ch=='+')
      Ylight += 0.1;
   //  Light azimuth
   else if (ch=='[')
      zh -= 1;
   else if (ch==']')
      zh += 1;
   //  Number of patches
   else if (ch=='<' && n>1)
      n--;
   else if (ch=='>' && n<MAXN)
      n++;
   //  Restart animation
   if ((ch =='s' || ch == 'S') && move) glutTimerFunc(dt,idle,0);
   //  Update screen size when mode changes
   if (ch == 'm' || ch == 'M') glutReshapeWindow(mode?2*Width:Width/2,Height);
   //  Update shadow map if light position or objects changed
   if (strchr("<>oO-+[]",ch)) ShadowMap();
   //  Tell GLUT it is necessary to redisplay the scene
   glutPostRedisplay();
}

/*
 *  GLUT calls this routine when the window is resized
 */
void reshape(int width,int height)
{
   //  Ratio of the width to the height of the window
   asp = (height>0) ? (double)width/height : 1;
   //  Store window dimensions
   Width  = width;
   Height = height;
}

/*
 *  Start up GLUT and tell it what to do
 */
int main(int argc,char* argv[])
{
   //  Initialize GLUT
   glutInit(&argc,argv);
   //  Request double buffered, true color window with Z buffering at 600x600
   glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE);
   glutInitWindowSize(600,600);
   glutCreateWindow("Shadow Map Shader");
#ifdef USEGLEW
   //  Initialize GLEW
   if (glewInit()!=GLEW_OK) Fatal("Error initializing GLEW\n");
   if (!GLEW_VERSION_2_0) Fatal("OpenGL 2.0 not supported\n");
#endif
   //  Set callbacks
   glutDisplayFunc(display);
   glutReshapeFunc(reshape);
   glutSpecialFunc(special);
   glutKeyboardFunc(key);
   glutTimerFunc(dt,idle,0);
   //  Load textures
   tex2d[0] = LoadTexBMP("water.bmp");
   tex2d[1] = LoadTexBMP("crate.bmp");
   tex2d[2] = LoadTexBMP("pi.bmp");
	 tex2d[3] = LoadTexBMP("sidewalk.bmp");
	 tex2d[4] = LoadTexBMP("sidewalkNormal.bmp");
	 tex2d[5] = LoadTexBMP("trash.bmp");
	 tex2d[6] = LoadTexBMP("noNormal.bmp");
	 tex2d[7] = LoadTexBMP("road.bmp");
	 tex2d[8] = LoadTexBMP("roadNormal.bmp");
	 tex2d[9] = LoadTexBMP("brick.bmp");
	 tex2d[10] = LoadTexBMP("hydrantNormal.bmp");
	 tex2d[11] = LoadTexBMP("brickNormal.bmp");
	 tex2d[12] = LoadTexBMP("door.bmp");
	 tex2d[13] = LoadTexBMP("doorNormal.bmp");
	 tex2d[14] = LoadTexBMP("window.bmp");
	 tex2d[15] = LoadTexBMP("windowNormal.bmp");
	 tex2d[16] = LoadTexBMP("building2.bmp");
	 tex2d[17] = LoadTexBMP("building2Normal.bmp");
   tex2d[18] = LoadTexBMP("night.bmp");
   tex2d[19] = LoadTexBMP("wheel.bmp");
   tex2d[20] = LoadTexBMP("wheeledge.bmp");

   // Enable Z-buffer
   glEnable(GL_DEPTH_TEST);
   glDepthFunc(GL_LEQUAL);
   glPolygonOffset(4,0);

   //  Initialize texture map
   shader = CreateShaderProg("shadow.vert","shadow.frag");
   //  Initialize texture map
   InitMap();
   //  Pass control to GLUT so it can interact with the user
   ErrCheck("init");
   glutMainLoop();
   return 0;
}
