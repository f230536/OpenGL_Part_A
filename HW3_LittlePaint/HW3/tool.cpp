#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <GL/glut.h>
#include "draw.h"
#include "interaction.h"

scrPt Translate(float px, float py, float tx, float ty) {
	scrPt newP; 
	if(tx < 400){
		 px += tx;
		 py += ty;
	}
  newP.x = px;
  newP.y = py;
  return newP;
}

scrPt Rotate(float px, float py, float theta, float cx, float cy) {
  float tempx;
  scrPt newP;
  	if(cx < 400){
	  tempx = cx + (px - cx) * cos(theta) - (py - cy) * sin(theta);
	  py = cy + (px - cx) * cos(theta) + (py - cy) * sin(theta);
	  px = tempx;
	}
	
		newP.x = px;
		newP.y = py;	
		 return newP;
		 
}
float Scale(float px, float py, float tx, float ty,scrPt type) {
		
	
	 float r ;
	 if(px < 400){
		 r = sqrt((tx-px)*(tx-px)+(ty-py)*(ty-py));
		 renew(px, py,  type, r);


	 }
	 return r;
}
void renew(int mx, int my,scrPt pick,float r){
	if(mx+30 < 400){
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


