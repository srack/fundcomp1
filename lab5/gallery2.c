#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include "gfx.h"


//function prototypes
void fractal_tree(int x, int y, int length, double theta, double dt, int g) ;	//theta refers to the inital angle (pi/2), dt is the radians moved away from this initial angle each time the function recurses
void draw_branch(int x, int y, int length, double theta, double dt) ;	



//begin main
int main (void) {


	int xsize = 800, ysize = 800 ;
	gfx_open(xsize, ysize, "Fractal Tree Gallery" ) ;

	int stillgoing = 1 ;
	

	while (stillgoing) {
		gfx_clear() ;
		int xpos, ypos, l, g ;
		double theta, dt ;
		int counter ;
		for (counter = 0 ; counter < 20 ; counter++ ) {
			srand(time(0)*5*counter) ;
			xpos = rand() % xsize*15/16 + xsize/32 ;
			ypos = rand() % ysize*3/4 + ysize/4 ;
			l = rand() % xsize/20 + 20 ;
			theta = M_PI/2 ;
			theta += ((rand()%10) < 7) ? 0.0 : (pow(-1, rand())*M_PI/15) ;
			dt = fmod(rand(), M_PI/8) + M_PI/12 ;
			g = rand() % 150 + 30 ;
			fractal_tree(xpos, ypos, l, theta, dt, g) ;
			gfx_color(0, g, 0 ) ;			
			gfx_line(xpos, ypos, xpos, ysize) ;
		}
		char c = gfx_wait() ;
		if (c == 'q') stillgoing = 0 ;	
	}
	
	return 0 ;
}





void fractal_tree(int x, int y, int length, double theta, double dt, int g) {
	//base case
	if(length < 3) {		
		return ;
	}

	//drawing step
	gfx_color(0, g, 0) ;
	draw_branch(x, y, length, theta, dt) ;
	
	//recursive step
	int newlength = length*(-log10((rand()%100)+1) + 15) / 16 ;		//change in length is ratio between 15/16 and 12/16
	
	if (log10((rand()%1000)+1) > 1) {
		fractal_tree(length*cos(theta-dt)+x, -length*sin(theta-dt)+y, newlength, theta - dt, dt, g ) ;
	} 

	if (log10((rand()%10000) + 1) > 1) {
		fractal_tree(length*cos(theta+dt)+x, -length*sin(theta+dt)+y, newlength, theta + dt, dt, g ) ;
	}

}



void draw_branch(int x, int y, int length, double theta, double dt) {
	double x1, x2, y1, y2 ;	
	double t1, t2; 

	t1 = theta - dt ;
	t2 = theta + dt ;
	
	x1 = length*cos(t1) + x ;
	x2 = length*cos(t2) + x ;
	y1 = -length*sin(t1) + y ;
	y2 = -length*sin(t2) + y ;
	
	gfx_line(x, y, x1, y1) ;
	gfx_line(x, y, x2, y2) ;
}

