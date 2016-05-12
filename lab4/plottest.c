#include <stdio.h>
#include <math.h>
#include "gfx.h"


void plot_function(int xsize, int ysize, float xl, float xu, float dx) {
	double x = xl, y1, y2 ;

	int xpos = 0 ;	//original position in terms of coordinates of pixels
	int ypos1, ypos2; 	//positions of y in terms of coordinates of pixels


	while (x <= xu ) {
		y1 = x*x ;
		x+= dx ;
		y2 = x*x ;

		xpos = xpos + dx*xsize/(xu-xl) ;
		
		ypos1 = ysize/2 - (y1*ysize/(2*(xu-xl))) ;
		ypos2 = ysize/2 - (y2*ysize/(2*(xu-xl))) ;

		gfx_line(xpos - dx*xsize/(xu-xl) , ypos1, xpos, ypos2) ;		

	printf("plot f should have executed\n\n") ;
	printf("(%d, %d)\n", x, y2) ;
	}

}




int main (void) 
{		
	int xsize = 800, ysize = 800 ;
	gfx_open( xsize, ysize, "Test of plot_function with x^2" ) ;

	int stillgoing = 1;

	while (stillgoing) {
		gfx_color(200, 0, 255) ;		
		plot_function(xsize, ysize, -10, 10, .1) ;
		gfx_flush() ;

		char c = gfx_wait() ;
	}
	return 0 ;
}		




