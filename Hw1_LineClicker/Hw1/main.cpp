
#include <stdio.h>
#include <math.h>
 #include <GL/glut.h>
#define SIZE 100

GLsizei winWidth = 512, winHeight = 512; //Window Size
GLint endPtCtr = 0 ; // Ini line endpoint counter.
int button1;
int state1;
int side_window;
int number ;
static int current=0;

class scrPt{
public:
	GLint x, y;
	
};
class groupL{
public:
	scrPt pt1;
	scrPt pt2;
};

static groupL gList[SIZE];
static scrPt orgPt, finlPt;
void inti(void){
 glClearColor(1.0, 1.0, 1.0, 1.0); // set to black
 glMatrixMode(GL_PROJECTION);
 gluOrtho2D(0.0, 200.0 ,0.0 ,150.0); //sets up a two-dimensional orthographic viewing region. 
}


/*sideGlutDisplay*/
void displayFcn( void )
{
  glClear( GL_COLOR_BUFFER_BIT);
  glColor3f(0.0, 0.0, 0.0);
  glPointSize(4.0);
}


/**************************************** myGlutReshape() *************/

void winReshapeFcn( GLint newWidth, GLint newHeight )
{
	/*Reset viewport and projection parameters */

  glViewport(0,0, newWidth, newHeight);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluOrtho2D(0.0,GLdouble(newWidth),0.0,GLdouble(newHeight));

  //Reset display -window size parameters
  winWidth = newWidth;
  winHeight = newHeight;
}
/*Draw Line*/
void drawLine(scrPt endPt1,scrPt endPt2,int color){

	glBegin(GL_LINES);
		glVertex2i(endPt1.x, endPt1.y);
		glVertex2i(endPt2.x, endPt2.y);
		if (color == 0)//black
			glColor3f(0.0, 0.0, 0.0);
		else
			glColor3f(1.0,1.0, 1.0); //white
	glEnd();
}
/*plotpoin*/
void plotPoint(GLint x, GLint y,int color){
 glBegin(GL_POINTS);
 if (color == 0)//black
	glColor3f(0.0, 0.0, 0.0);
 else
	 glColor3f(1.0,1.0, 1.0); //white
	glVertex2i(x,y);
	
 glEnd();
}

/*****************************************************/
void polyline (GLint button, GLint state, GLint xMouse, GLint yMouse){
	static scrPt endPt1, endPt2;
	static groupL gLine;
	static scrPt newPt;
	static scrPt ptList[SIZE];
	
	bool find= false;


	if (endPtCtr == 0){
		if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN ){
			
			endPt1.x= xMouse;
			endPt1.y= winHeight - yMouse;
			endPtCtr = 1 ; 	
			
			plotPoint(endPt1.x,endPt1.y,0);
			button1= button;
		}
		
		else {
			if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN) {
				newPt.x =xMouse;
				newPt.y =winHeight - yMouse;;
				for (int i=0; i< current && !find;++i)
					if (gList[i].pt1.x <= xMouse +3 && gList[i].pt1.x >=xMouse -3){
					
						int yP = winHeight - yMouse;
						if (gList[i].pt1.y<=yP+3 && gList[i].pt1.y>=yP-3){							
							printf("find\n");
							//clear the lane
							plotPoint(gList[i].pt2.x , gList[i].pt2.y,1);
							plotPoint(gList[i].pt1.x,gList[i].pt1.y,1);
							drawLine (gList[i].pt1,gList[i].pt2,1);
							//begin point
								plotPoint(gList[i].pt2.x , gList[i].pt2.y,0);
					
									//swap
								scrPt temp;
								temp.x = gList[i].pt2.x;
								temp.y = gList[i].pt2.y;

								gList[i].pt2.x = gList[i].pt1.x;
								gList[i].pt2.y = gList[i].pt1.y;
								gList[i].pt1.x = temp.x;
								gList[i].pt1.y =temp.y;
								//orgPt.y=gList[i].pt2.y;
								orgPt.x = temp.x;
								orgPt.y=  temp.y;
							number = i;
							button1 = button;
							state1 = state;
							find = true;
							
							
						}
					}
					if(!find){
						for (int i=0; i< current && !find;++i)
							if (gList[i].pt2.x <= xMouse +3 && gList[i].pt2.x >=xMouse -3 ){
									int yP = winHeight - yMouse;
									if (gList[i].pt2.y<=yP+3 && gList[i].pt2.y>=yP-3){

										printf("find\n");

										//clear the lane								
										plotPoint(gList[i].pt1.x,gList[i].pt1.y,1);
										plotPoint(gList[i].pt2.x , gList[i].pt2.y,1);
										drawLine (gList[i].pt1, gList[i].pt2,1);
										//begin point
										plotPoint(gList[i].pt1.x , gList[i].pt1.y,0);
										//	plotPoint(newPt.x,newPt.y,0);
									
										orgPt.x = gList[i].pt1.x;
										orgPt.y =gList[i].pt1.y;
										
										number = i;
										button1 = button;
										state1 = state;
										find = true;
									}
							}
								
					}	
			
			}
			
		}
			
		
							
	}
	else
		if(button ==GLUT_LEFT_BUTTON && state ==GLUT_DOWN){
			endPt2.x = xMouse;
			endPt2.y = winHeight-yMouse;
			glLineWidth(1.0);
			drawLine (endPt1, endPt2,0);

			gList[current].pt1 = endPt1;
			gList[current].pt2 = endPt2;
			current += 1;
			
			endPt1 = endPt2;
			endPtCtr  = 0;	
			
			
			plotPoint(endPt2.x,endPt2.y,0);
			button1 = button;
		}
		

	glFlush();

}




/*
/******mouseMotion*/
void  MouseMotion(GLint xMouse, GLint yMouse)	{
	
	finlPt.x = xMouse;
	finlPt.y = winHeight-yMouse;
		if (state1 == GLUT_DOWN ){
			if ( button1 == GLUT_RIGHT_BUTTON ){

		gList[number].pt2 = finlPt;
		
			}
		}
	if (state1 = GLUT_UP){		
		if ( button1 == GLUT_RIGHT_BUTTON ){
		drawLine (orgPt, gList[number].pt2,0);
		plotPoint(	gList[number].pt2.x,gList[number].pt2.y,0);
		
	}
	}



	glFlush();	
	

}



	


					





/********************* myGlutKeyboard() **********/

void sideGlutKeyboard(unsigned char Key, int x, int y)
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

int main(int argc, char** argv)
{
	glutInit(&argc,argv);
	glutInitDisplayMode( GLUT_RGB | GLUT_SINGLE );
  
	
	glutInitWindowPosition( 100, 100 );  // starting x, y of window (left top ) /10 ,30
	glutInitWindowSize(winWidth,winHeight); // x, y size of window
	side_window = glutCreateWindow( "HW 1" ); 


	inti();
	glutDisplayFunc( displayFcn );
    glutReshapeFunc( winReshapeFcn );  
    glutKeyboardFunc( sideGlutKeyboard );
    glutPassiveMotionFunc( MouseMotion );
    glutMouseFunc( polyline );



	glutMainLoop();

	return 0;

}

	