
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <GL/glut.h>

//#include "interaction.h"
#include "draw.h"
#define PI 3.14159265358979323846

#define Ysize 3
#define Xsize 2
#define MAX 100
class save{
public:
	int x;
	int y;
	scrPt type;
	float r;
};

////1///////////////////////////
void sideGlutDisplay( void );
void Control();
void defaults();
scrPt check(int x, int y);
void fresh(int x , int y,int rotate);
void saving(int x, int y, int updates);
int find(int x, int y);
void Rotate(float px, float py, float cx, float cy,int loc);

void Translate( float tx, float ty,int num);
void nScale(float px, float py, float tx, float ty,scrPt type,int loc);
void update(int mx, int my,scrPt pick,float r,int loc);
////////////////////////////////

int side_window;
bool first = true;
range controlP[Xsize][Ysize];
range currrent;
scrPt pick,  curPt, finPt, curtype;
save proj[MAX];
int total=0;
int state1,button1;
float theta;
void redraw_func(int id) {

    glutSetWindow(side_window);  
	glutPostRedisplay();
}

/***************************************** myGlutIdle() ***********/

void myGlutIdle( void )
{

	
}


void myGlutDisplay( void )
{
	
	glClearColor(1,1,1,0);
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0.0,600,0.0,400);
			// left, right, bottom, top
	glViewport(0,0,600,400);
			// startx, starty, xsize, ysize
			// coordinates begin from lower left corner of window		
    glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();	
	Control();



	glutSwapBuffers(); 

}
/*******Control*************/
void Control(){
	//set table
	drawTable();
	//set the button position	
	for( int y = 0; y< 3 ; ++ y){
		for (int x=0;x< 2; ++ x){
		controlP[x][y].pt1.x =400+ 100* x;
		controlP[x][y].pt1.y =133*y;
		controlP[x][y].pt2.x =400+ 100* (x+1);
		controlP[x][y].pt2.y =133*y;
		controlP[x][y].pt3.x =400+ 100*(x+1);
		controlP[x][y].pt3.y =133*(y+1);
		controlP[x][y].pt4.x =400+ 100*x;
		controlP[x][y].pt4.y =133*(y+1);
		}
	}
	defaults();
}
/***************************************/
void defaults(){
	//draw circle
		int Xc = 450;
		int Yc = 333;
		setCicrle(Xc, Yc,-1);
	//draw Hexagon
		Xc = 450;
		Yc = 200;
		setHexagon(Xc,Yc,-1);
	//draw Square
		Xc = 450;
		Yc = 66;
		setSquare(Xc ,Yc,-1);
	//draw Scale
		Xc = 550;
		Yc = 333;
		setScale(Xc,Yc);
	//draw translate
		Xc = 550;
		Yc = 200;
		setTrans(Xc,Yc);
	//draw Rotate
		Xc = 550;
		Yc = 66 ;
		setRotate(Xc, Yc);
}

/***************************************** myGlutMouse() **********/

void myGlutMouse(int button, int state, int x, int y )
{
	state1 = state;
	button1= button;
	glClearColor(1,1,1,0);
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
	
	glReadBuffer(GL_BACK);
	if(button ==GLUT_RIGHT_BUTTON && state == GLUT_UP ){
		 y = 400-y;
		 if(x > 400 ){
	  
				 
					pick = check(x,y);
					if(pick.x >= 0 && pick.y >= 0){
					if(first){
						currrent = controlP[pick.x][pick.y];
						highlight( currrent,first);
						first = false;
		
					}
					else		
						fresh(x,y,-1);

		
					}
				fresh(x,y,-1);
				glutSwapBuffers();
		 }

	
	}
	else if(button ==GLUT_LEFT_BUTTON && state == GLUT_UP){
		  y = 400-y;
		  if(!first){
			saving(x,y,-1);
			fresh( x ,  y,-1);	  
			glutSwapBuffers();
		  }
	}
}
void fresh(int x , int y,int rotate){
	currrent = controlP[pick.x][pick.y];			
    highlight( currrent,true);
	defaults();
	if(total !=0)
		for(int i =0; i<total; ++i){
			if(proj[i].r == 20)
				switchs(proj[i].x, proj[i].y,proj[i].type);
			else if (proj[i].r != 20)
				update(proj[i].x, proj[i].y,proj[i].type,proj[i].r,i);
			else if (rotate ==0 ){
			    ;			}

		}
}


void saving(int x, int y, int updates){
	 bool repeat = false;
	
//interaction
// upadtae origonal 
if(updates >= 0){
	//translate
		 proj[updates].x = x;
		 proj[updates].y = y;
		 //proj[updates].type = pick;
		 
}
// draw
//save to new;
else if(pick.x ==0){
	if (!repeat){
	 proj[total].x = x;
	 proj[total].y = y;
	 proj[total].type = pick;
	 proj[total].r= 20;
	 ++total;
	 repeat = false;
	}
}

}
		

/*******************************************************/
scrPt check(int x, int y){
	scrPt p;
	
	for (int i = 0; i< Ysize ; ++i ){
		for (int n = 0; n< Xsize ; ++n ){
			if ( 400 <x && x < controlP[n][i].pt3.x)
				if (y <controlP[n][i].pt3.y){
					p.x= n;
					p.y= i;
					return p;
				}
			
		}
	
	}
	p.x = -1;
	p.y = -1;
	return p;

}

/***************************************** myGlutMotion() **********/

void myGlutMotion(int x, int y )
{
	int num= -1;
	y= 400 -y;
	finPt.x = x;
	finPt.y = y;
	glClearColor(1,1,1,0);
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
	
	if(state1 ==GLUT_DOWN && pick.x>0 ){		
		  if(!first){
			 num =  find(finPt.x,finPt.y);
		switch(pick.x)	  {
			case 1:
				switch(pick.y){
					case 0:		
						if(curtype.y != 3){
							


							//glRotated(
							 Rotate(curPt.x,curPt.y,finPt.x,finPt.y,num);
							fresh( x ,  y ,0);
					     	glutSwapBuffers();
					//		 Rotate(curPt.x,curPt.y,theta,finPt.x,finPt.y);
						}
					
						break;
					case 1:					
						Translate(x,y,num);
						fresh( x ,  y,-1);
						glutSwapBuffers();
						break;
					case 2:
						nScale(curPt.x,curPt.y,  finPt.x,finPt.y, curtype,num) ;
					
						fresh(x,y,-1);
						glutSwapBuffers();
						break;
				}
				break;
		}
			
		  }
	}
}
void Rotate(float px, float py, float cx, float cy,int loc) {
  float tempx;
  float theta = atan2(cy,cx)-atan2(py,px);
 // float theta = atan((cy-px)/(cx-px));
  theta = (theta * 180)/PI;
  /*
  	if(cx < 400){
	  tempx = cx + (px - cx) * cos(theta) - (py - cy) * sin(theta);
	  py = cy + (px - cx) * cos(theta) + (py - cy) * sin(theta);
	  px = tempx;
	}
	proj[loc].x= px;
	proj[loc].x= py;
	*/
  glPushMatrix();
   glTranslated(proj[loc].x,proj[loc].y,0);
  glRotated (theta,  0, 0,1);
    glTranslated(0,0,0);

  setSquare(proj[loc].x,proj[loc].y,proj[loc].r);
  glPopMatrix();
  
	
		
}


void Translate(float tx, float ty,int num) {
	if(tx < 400){
	
		  proj[num].x = tx;
		  proj[num].y = ty;
	} 
}
void nScale(float px, float py, float tx, float ty,scrPt type, int loc){

	
	 float r ;
	 if(tx <=400){
		  r = sqrt((tx-px)*(tx-px)+(ty-py)*(ty-py));
	
		if(proj[loc].x+r > 400)
		 proj[loc].r =  400 - 	 proj[loc].x ;
		 else
		 proj[loc].r = r;
			  
		// update(px, py,  type, r, loc);


	 }

}

void update(int mx, int my,scrPt pick,float r,int loc){
	if(mx < 400){

			switch(pick.x){ 
			case 0:
				switch(pick.y){
					case 0:
						setSquare(mx,my,r);
						break;
					case 1:
						setHexagon(mx,my,r);
						
						break;
					case 2:
						setCicrle(mx,my,r);
						
						break;
				}
				break;
		
			}
	}
}
 





/************************************************************************/
int find(int x, int y){
	//interaction 
	 int i;
if(pick.x ==1){
	for( i = 0; i<total;++i){
		if(x <= proj[i].x+proj[i].r && x>= proj[i].x-proj[i].r){
			if (y<= proj[i].y+20 && y>= proj[i].y-proj[i].r){
				curPt.x = proj[i].x ;
				curPt.y = proj[i].y;
				curtype = proj[i].type;
		 
				 break;
			}
		}
	}
}
return i;
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
  
	side_window = glutCreateWindow( "HW3" );
	glutPositionWindow( 10, 30 );
	glutReshapeWindow( 600 , 400 );

	glutDisplayFunc( myGlutDisplay );
	glutReshapeFunc( myGlutReshape );  
	glutKeyboardFunc( myGlutKeyboard );
	glutMotionFunc( myGlutMotion );
	glutMouseFunc( myGlutMouse );


	glutMainLoop();

	return 0;

}

