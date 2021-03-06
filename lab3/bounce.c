#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "gfx.h"
#include <math.h>
#include <time.h>

int main (void) {
	
	int xdim = 500 , ydim = 500 ;		//initialzies dimensions of window
	gfx_open(xdim, ydim, "Bouncing Ball") ;

	int keepgoing = 1 ;
	int x = xdim/2 , y = ydim/2 ;	//x and y position of the ball, initially center of window
	float vx = 2, vy = 7; 		//x and y components of velocity
	
	float dt = .01 ;

	gfx_color(255, 255, 255) ; 	//sets color to white

	//initialize ball parameters
	float da = 2 * M_PI / 15 ;   //angle spanned by each line drawn
	float a ;
	float r = 10 ;	  //radius of ball
	float xp1, yp1, xp2, yp2 ;	//location of enpoints of each line
	
	int t = time( 0 ) ;
	srand(t) ;
		
	while ( keepgoing == 1 ) {

		gfx_clear() ;

		//draw circle
		for ( a = 0 ; a < 2 * M_PI ; a += da) {
			xp1 = r * cos(a) + x ;
			yp1 = -r * sin(a) + y ;
			xp2 = r * cos(a + da) + x ;
			yp2 = -r * sin(a + da) + y ;
			gfx_line(xp1, yp1, xp2, yp2) ;
		}

		gfx_flush() ;
				
		usleep (dt * pow(10, 6)) ;  		

		//update position of the ball
		x = x + vx * (dt * 100) ; 	//multiply dt to make location of x a whole number
		y = y + vy * (dt * 100) ;


		//ensure ball is within boundaries of window
		if ( x >= xdim || x <= 0) {
			vx = -vx ;	//switches direction of x component of velocity
		}

		if ( y >= ydim || y <= 0) {
			vy = -vy ;
		}


		//executes when user does something
		if ( gfx_event_waiting() ) {
			char c = gfx_wait() ;	

			switch(c) {
				case 1:
					x = gfx_xpos() ;
					y = gfx_ypos() ; //replaces current location of ball with place of click
					vx = rand() % 20 - 10  ;  //randomly gives x velocity as an integer from -10 - 9 
					vy = rand() % 20 - 10 ;  //randomly gives y velocity as an integer from -10 - 9
					break;

				case 'q':
					keepgoing = 0 ;
					break;

				}
		}
		
	}
	return 0;
}
