#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include "gfx.h"


//function prototypes
void fractal_snowflake(int x, int y, double radius, double theta, int n, int c) ;
void draw_spokes(int x, int y, double radius, double theta, int n) ;



//begin main
int main (void) {

	int xsize = 600 ;
	int ysize = 600 ;

	gfx_open(xsize, ysize, "Fractal Snowflake Gallery") ;

	int stillgoing = 1 ;

	while (stillgoing) {
		gfx_clear() ;
		int counter ;
		int xpos, ypos, n ;
		double rad, t ;
		int c ;

		for (counter = 0 ; counter < 500 ; counter++) {
			srand(100*time(0)*counter) ;
			xpos = rand() % (xsize) ;
			ypos = rand() % (ysize) ;
			rad = fmod(rand(), (xsize/50)) + 10 ; 
			t = fmod(rand(), M_PI/3) ;
			n = rand() % 6 + 5 ; 
			c = rand() % 200 + 55 ;
			fractal_snowflake(xpos, ypos, rad, t, n, c) ;

		}

		char user = gfx_wait() ;
		if (user == 'q') stillgoing = 0 ;
			 	
	}

	return 0 ;

}	//end main






void fractal_snowflake(int x, int y, double radius, double theta, int n, int c) {
	//base case
	if (radius < 3 ) {
		return ;
	}

	//drawing step
	gfx_color(c, c, c) ;	//gives a color in grayscale
	draw_spokes(x, y, radius, theta, n) ;

	//recursive step
	int newradius ;
	if (n > 6) newradius = radius/4 + ((rand()%10 < 6) ? 0 : radius/10)  ;
	else newradius = radius/3 + ((rand()%10 < 7) ? 0 : radius/5) ;
	double i ; 
	double dt = 2*M_PI/n ;
	double xr, yr ;
	for (i = theta ; i < 2*M_PI + theta ; i+=dt ) {
		if (log10(rand()%10000 + 1) > 1) {
			xr = radius*cos(i) + x ;
			yr = -radius*sin(i) + y;
			if (log10(rand()%100 + 1) < 1) n++ ;
			fractal_snowflake(xr, yr, newradius, theta + fmod(rand(), M_PI/n), n, c) ;
		} else return ;
	}

}


void draw_spokes(int x, int y, double radius, double theta, int n) {
	double t;
	double dt = 2*M_PI/n ;
	double xr, yr ;	
	for ( t = theta ; t < (theta + 2*M_PI) ; t+= dt) {
		xr = radius*cos(t) + x ;
		yr = -radius*sin(t) + y ;
		gfx_line(x, y, xr, yr) ;
	}
}










