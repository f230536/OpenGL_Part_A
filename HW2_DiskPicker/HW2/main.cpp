
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <GL/glut.h>
#define PI 3.14159265358979323846

#define TWO_PI	(2*PI)
#define Xc 256
#define Yc 256
#define r1 240
#define r2 100
#define addnum 0.05
class colors{
public:
	int R, G, B;	
};

static	colors colorList[6];

int side_window;


void sideGlutDisplay( void );
void setColor (int n, int x, int y, int z);




void redraw_func(int id) {

    glutSetWindow(side_window);  
	glutPostRedisplay();
}




/***************************************** myGlutIdle() ***********/

void myGlutIdle( void )
{

	
}


void Display( void )
{
	double theta;

	glClearColor(0,0,0,0);  	
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA); 

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0.0,512.0,0.0,512.0);
	// left, right, bottom, top
	glViewport(0,0,512,512);
	// startx, starty, xsize, ysize
	// coordinates begin from lower left corner of window
  //Set Color
	setColor(0,1,0,0);
	setColor(1,1,1,0);
	setColor(2,0,1,0);
	setColor(3,0,1,1);
	setColor(4,0,0,1);
	setColor(5,1,0,1);
	setColor(6,1,0,0);
	setColor(7,1,0,0);
	
	int i;
	int l = r1;
	
					 
  //Wheel 
	glShadeModel(GL_POINT_SMOOTH);	
	glShadeModel(GL_SMOOTH);	  

	 glBegin(GL_POLYGON  );
		glColor4f(1,1,1,1.1);
		for (theta=0; theta<TWO_PI; theta+=0.01) {
			glVertex3f(Xc+r1*cos(theta),Yc+r1*sin(theta),0.0);	
		}	
		glEnd(); 

	glBegin(GL_POLYGON  );
		glColor4f(0,0,0,0.8);
		for (theta=0; theta<TWO_PI; theta+=0.01) {
			glVertex3f(Xc+r2*cos(theta),Yc+r2*sin(theta),0.0);	
		}	
		glEnd(); 

	//Color pad 	
	// glShadeModel(GL_FLAT);	   
	   
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(256, 256);  
    for(i=0; i<6; ++i){  
		float dR,dG,dB;
		float nexR,nexG,nexB;
		float num= 0.1;
		if(i== 3)
			i=3;
					dR =colorList[i+1].R - colorList[i].R;
					dG =colorList[i+1].G - colorList[i].G;
					dB =colorList[i+1].B - colorList[i].B;
		

	for(int n = 0; n<=20; ++n){
					if(dR!=0){
						if(dR >0){
							glColor3f(colorList[i].R+n*addnum,colorList[i].G,colorList[i].B);
							glVertex3f(Xc+(r1-10)*cos((i*20+n)*TWO_PI/120),Yc+(r1-10)*sin((i*20+n)*TWO_PI/120),0.0);	
						}
						else if(dR < 0){
							glColor3f(colorList[i].R-n*addnum,colorList[i].G,colorList[i].B);
							glVertex3f(Xc+(r1-10)*cos((i*20+n)*TWO_PI/120),Yc+(r1-10)*sin((i*20+n)*TWO_PI/120),0.0);	
						}
					}
					else if (dG!=0){
						if(dG> 0){
						glColor3f(colorList[i].R,colorList[i].G+n*addnum,colorList[i].B);
						glVertex3f(Xc+(r1-10)*cos((i*20+n)*TWO_PI/120),Yc+(r1-10)*sin((i*20+n)*TWO_PI/120),0.0);	
						}
						else if(dG<0){
							glColor3f(colorList[i].R,colorList[i].G-n*addnum,colorList[i].B);
							glVertex3f(Xc+(r1-10)*cos((i*20+n)*TWO_PI/120),Yc+(r1-10)*sin((i*20+n)*TWO_PI/120),0.0);	
						
						}
					}
					else if(dB!=0)	{
						if(dB>0){
							glColor3f(colorList[i].R,colorList[i].G,colorList[i].B+n*addnum);
							glVertex3f(Xc+(r1-10)*cos((i*20+n)*TWO_PI/120),Yc+(r1-10)*sin((i*20+n)*TWO_PI/120),0.0);	
						}
						else if(dB<0){
							glColor3f(colorList[i].R,colorList[i].G,colorList[i].B-n*addnum);
							glVertex3f(Xc+(r1-10)*cos((i*20+n)*TWO_PI/120),Yc+(r1-10)*sin((i*20+n)*TWO_PI/120),0.0);	
						}
					}
		}
	}
	
    glEnd();  
   
	
	
   

  
	glutSwapBuffers(); 

}



/******************************************************************/
void setColor (int n, int x, int y, int z){
	colorList[n].R = x;
	colorList[n].G = y;
	colorList[n].B = z;

}
/***************************************** myGlutMouse() **********/

void myGlutMouse(int button, int state, int x, int y )
{
	// float pixel[3];
	// unsigned char pixel[3]; 
	GLubyte *pixel = (GLubyte *)malloc(3);

	if(button ==GLUT_LEFT_BUTTON ){
		// glpixels store *
		//glReadPixels(x , y , 1 , 1 , GL_RGB , GL_UNSIGNED_BYTE , pixel);
		glPixelStorei(GL_PACK_ALIGNMENT, 1);
		glReadPixels(x, y, 1, 1, GL_RGB, GL_UNSIGNED_BYTE, pixel);
		float r,g,b;
		r= (float)pixel[0];
		g= (float)pixel[1];
		b= (float)pixel[2];
		
		glBegin(GL_QUADS);
		glColor3f(r,g,b);
		glVertex3f(200.0,200.0,0);
		glVertex3f(300.0,200.0,0);
		glVertex3f(300.0,300.0,0);
		glVertex3f(200.0,300.0,0);
		glEnd(); 
	}
	

	glutSwapBuffers();
}


/***************************************** myGlutMotion() **********/

void myGlutMotion(int x, int y )
{
	glutPostRedisplay();
}

/**************************************** myGlutReshape() *************/

void myGlutReshape( int x, int y )
{

  glutPostRedisplay();
}

/********************* myGlutKeyboard() **********/

void myGlutKeyboard(unsigned char Key, int x, int y)
{
  switch(Key)
  {
  case 27: 
  case 'q':
    exit(0);
    break;
  };
  
  glutPostRedisplay();
}





/**************************************** main() ********************/

int main(int argc, char* argv[])
{

	glutInitDisplayMode( GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH );
  
	side_window = glutCreateWindow( "HW2" );
	glutPositionWindow( 100, 30 );
	glutReshapeWindow( 512, 512);

	glutDisplayFunc( Display );	
	glutReshapeFunc( myGlutReshape );  
//	glutKeyboardFunc( myGlutKeyboard );
//	glutMotionFunc( myGlutMotion );
	glutMouseFunc( myGlutMouse );


	glutMainLoop();

	return 0;

}

