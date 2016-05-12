#include <stdio.h>
#include "gfx.h"
#include <math.h>

int main(void) {
	int xsize = 500, ysize = 500, shouldcontinue = 1 ;

	gfx_open( xsize, ysize, "Symbolic Typewriter") ;
	
	int x, y ;
	int sides ;
	while (shouldcontinue == 1) {
		char c = gfx_wait() ;    //executes when user clicks
		x = gfx_xpos() ;  //x location of mouse when clicked
		y = gfx_ypos() ;  //y location of mouse when clicked
		sides = 0 ;   //resets number of sides for cases '3'-'9'
		double pi = M_PI ;  //defines pi
		switch(c) {
			case 1:
			   gfx_color(0, 0, 255) ;	//blue color
			   gfx_line(x-10, y-10, x-10, y+10) ;
			   gfx_line(x-10, y-10, x+10, y-10) ;
			   gfx_line(x+10, y-10, x+10, y+10) ;
			   gfx_line(x-10, y+10, x+10, y+10) ;	
			   break ;

			case 't':
			   gfx_color(0, 255, 0) ;	//green color
			   gfx_line(x-8, y+8, x, y-8*sqrt(2)) ;
			   gfx_line(x-8, y+8, x+8, y+8) ;
			   gfx_line(x+8, y+8, x, y-8*sqrt(2)) ;
			   break ;

			case 'c':
			   gfx_color(255, 255, 255) ; 	//white
			   
			   float da = .001; //angle spanned by each lines drawn
			   float a ;	//current angle
			   float r = 10 ;  //radius of circle 
			   float xp1, yp1, xp2, yp2 ;  //locations of endpoints of each line
			   
			   for(a = 0; a < 2*pi ; a += da ) {
				xp1 = r * cos(a) + x ;
				yp1 = -r * sin(a) + y ;
				xp2 = r * cos(a+da) + x ;
				yp2 = -r * sin(a+da) + y ;
				gfx_line(xp1, yp1, xp2, yp2) ;
			   }
			   break ;
			
			//each of the following cases will fall through to case '9'
			case '3':
			   sides = 3 ;
			case '4':
			   //if statement that excludes '3' case
			   if (sides == 0) {
				sides = 4 ;
			   }
			case '5':
			  //if statement excludes '3' and '4' case
			   if (sides == 0) {
				sides = 5 ;
			   }
			case '6':
			   if (sides == 0) {
				sides = 6 ;
			   }
			case '7':
			   if (sides == 0) {
				sides = 7 ;
			   }
			case '8':
			   if (sides == 0) {
				sides = 8 ;
			   }
			case '9':
			  //cases '3' through '9' execute the following code
			   if (sides == 0) {
				sides = 9 ;
			   }
			   
			   gfx_color(255, 0, 255) ; //purple
			   
			   float b, db ;  //angle and change in angle
			   float x1, y1, x2, y2 ; //positions of endpoints of each line
			   r = 10 ;   //radius of the polygon
			   db = 2*pi / sides ; //angle spanned by each line
			   
			   for( b = 0 ; b < 2*pi ; b+=db ) {
				x1 = r * cos(b) + x ;
				y1 = -r * sin(b) + y ;
				x2 = r * cos(b+db) + x ;
				y2 = -r * sin(b+db) + y ;
				gfx_line(x1, y1, x2, y2) ;
			   }
			   break ;

			case 'q':
			   shouldcontinue = 0 ;
			   break ;
		}
	}
}
