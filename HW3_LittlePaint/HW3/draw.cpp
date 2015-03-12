#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <GL/glut.h>
#include "draw.h"

#define PI 3.14159265358979323846
#define TWO_PI	(2*PI)
#define r 20
#define l 20



void setCicrle(double Xc, double Yc,float Length){
	double theta;
	int r1;
	if(Length == -1)
		r1 = r;
	else
		r1 = Length;

		glShadeModel(GL_POINT_SMOOTH);	
		glShadeModel(GL_SMOOTH);
		glBegin(GL_POLYGON  );
		glColor3f(0,0,0);
		for (theta=0; theta<TWO_PI; theta+=0.01) {
			glVertex3f(Xc+r1*cos(theta),Yc+r1*sin(theta),0.0);	
		}	
		glEnd(); 
}




void setHexagon(double Xc, double Yc,float Length){
	int r1;
	if(Length == -1)
		r1 = r;
	else
		r1 = Length;
	glBegin(GL_POLYGON);
	glColor3f(1,0,0);
for(int i = 0; i < 6; ++i) {
    glVertex2d(Xc+r1*sin(i/6.0*TWO_PI),
               Yc+r1*cos(i/6.0*TWO_PI));
}
glEnd();
}

void setSquare(double Xc, double Yc,float Length){
	int r1;
	if(Length == -1)
		r1 = r;
	else
		r1 = Length;
	glBegin(GL_QUADS);
        glColor3f(1,0,1);
        glVertex2f(Xc-r1,Yc-r1);
        glVertex2f(Xc+r1,Yc-r1);
        glVertex2f(Xc+r1,Yc+r1);
        glVertex2f(Xc-r1,Yc+r1);
    glEnd();

}
void setScale(double Xc, double Yc){
		int		r1 = r;
	
		glLineWidth(2.0);
		glBegin(GL_LINES);		
		glColor3f(0.0,0.0,0.0);
		glVertex2f(Xc-r1,Yc+l); 
		glVertex2f(Xc+r1,Yc-l);
		glEnd();

		glBegin(GL_TRIANGLES);
		glVertex2f(Xc-r1,Yc+l); 
		glVertex2f(Xc-r1,Yc+l-15);
		glVertex2f(Xc-r1+15,Yc+l);
		glEnd();

		glBegin(GL_TRIANGLES);
		glVertex2f(Xc+r1,Yc-l); 
		glVertex2f(Xc+r1,Yc-l+15);
		glVertex2f(Xc+r1-15,Yc-l);
		glEnd();

}
void setTrans(double Xc, double Yc){
		int r1=r;
		glLineWidth(2.0);
		glBegin(GL_LINES);		
		glColor3f(0.0,0.0,0.0);
		glVertex2f(Xc,Yc+r1); 
		glVertex2f(Xc,Yc-r1);
		glEnd();

		glBegin(GL_TRIANGLES);
		glVertex2f(Xc,Yc+r1); 
		glVertex2f(Xc-10,Yc+r1-10);
		glVertex2f(Xc+10,Yc+r1-10);
		glEnd();

		glBegin(GL_TRIANGLES);
		glVertex2f(Xc,Yc-r1); 
		glVertex2f(Xc-10,Yc-r1+10);
		glVertex2f(Xc+10,Yc-r1+10);
		glEnd();

			
		glLineWidth(2.0);
		glBegin(GL_LINES);		
		glColor3f(0.0,0.0,0.0);
		glVertex2f(Xc +r1,Yc); 
		glVertex2f(Xc -r1,Yc);
		glEnd();

		glBegin(GL_TRIANGLES);
		glVertex2f(Xc+r1,Yc); 
		glVertex2f(Xc+r1-10,Yc+10);
		glVertex2f(Xc+r1-10,Yc+-10);
		glEnd();

		glBegin(GL_TRIANGLES);
		glVertex2f(Xc-r1,Yc); 
		glVertex2f(Xc-r1+10,Yc-10);
		glVertex2f(Xc-r1+10,Yc+10);
		glEnd();


}
void setRotate(double Xc, double Yc){
		double theta;
		int r1=r;
		glBegin(GL_LINE_STRIP);
		for (theta=0; theta<TWO_PI; theta+=0.01) {
			glVertex3f(Xc+r1*cos(theta),Yc+r1*sin(theta),0.0);
		}
		glEnd();


		glBegin(GL_TRIANGLES);
		glVertex2f(Xc+r1,   Yc+10); 
		glVertex2f(Xc+r1-10,Yc);
		glVertex2f(Xc+r1+10,Yc);
		glEnd();

		glBegin(GL_TRIANGLES);
		glVertex2f(Xc-r1,Yc-10); 
		glVertex2f(Xc-r1-10,Yc);
		glVertex2f(Xc-r1+10,Yc);
		glEnd();
}
void highlight(range currrent,bool first){
	if(first== true)
        glColor3f(1,1,0);
		else
		glColor3f(1,1,1);

	glBegin(GL_QUADS);
		
		glVertex2f(currrent.pt1.x ,currrent.pt1.y);
        glVertex2f(currrent.pt2.x ,currrent.pt2.y);
        glVertex2f(currrent.pt3.x ,currrent.pt3.y);
        glVertex2f(currrent.pt4.x ,currrent.pt4.y);
    glEnd();
	drawTable();
//	glClearColor(1,1,1,0);


}
void drawTable(){
	for(int i = 0, n = 1;i<2;++i,++n){
		glBegin(GL_LINES);
		glColor3f(0.0,0.0,0.0);
		glVertex3f(400+100*i,0,0.0); 
		glVertex3f(400+100*i,400,0.0);
		glEnd();

		glBegin(GL_LINES);
		glColor3f(0.0,0.0,0.0);
		glVertex3f(400,n*133,0.0); 
		glVertex3f(600,n*133,0.0);
		glEnd();
	}
}


void switchs(int x, int y,scrPt pick){
	if(x+r < 400){
			switch(pick.x){ 
			case 0:
				switch(pick.y){
					case 0:
						setSquare(x,y,-1);
						break;
					case 1:
						setHexagon(x,y,-1);
						
						break;
					case 2:
						setCicrle(x,y,-1);
						
						break;
				}
				break;
		
			}
	}
}