#include <stdio.h>
#include <math.h>
#include "gfx.h"

main (void) {
	
	int xdim = 600 , ydim = 400 ;
	gfx_open( xdim, ydim, "Racetrack" ) ; 

	int cx = xdim / 2 , cy = ydim / 2 ; 	//location of center of the racetrack
	int r1 = 125 , r2 = 220 ;		//radii for elliptical path of car, r2 is x direction, r1 is y direction
	int stillgoing = 1 ;
	float omega = 1.5 ;			//angular velocity of the car
	float t = 0, dt = .01 ;				

	//initial locations of vertices of car	
	int x1 = cx + (r2 - 10), y1 = cy + 10 ;
	int x2 = cx + (r2 + 10), y2 = cy + 10 ;
	int x3 = cx + (r2 + 10), y3 = cy - 10 ;
	int x4 = cx + (r2 - 10), y4 = cy - 10 ;

	//parameters for stationary racetrack
	float a , da = 2 * M_PI / 50 ;
	int r1i = r1 - 40, r2i = r2 - 40 ;	//radii for inner ellipse of track
	int r1o = r1 + 40, r2o = r2 + 40 ; 	//radii for outer ellipse of track
	
	int adj = 0 ;
	int r1c, r2c ;		//radii of location of the car


	int car_r = 255 , car_g = 0 , car_b = 0 ;	//parameters for car color


	while (stillgoing == 1) {
	
		gfx_clear() ;
				
		
		//draw car
		gfx_color(car_r, car_b, car_g) ;
		gfx_line(x1, y1, x2, y2) ;
		gfx_line(x2, y2, x3, y3) ;
		gfx_line(x3, y3, x4, y4) ;
		gfx_line(x1, y1, x4, y4) ;

		//draw inner ellipse of racetrack
		gfx_color(0, 150, 255) ;
		float x1i, x2i, y1i, y2i ;		
		for( a = 0 ; a < 2 * M_PI ; a += da ) {
			x1i = r2i * cos(a) + cx ;
			x2i = r2i * cos(a+da) + cx ;
			y1i = -r1i * sin(a) + cy ;
			y2i = -r1i * sin(a+da) + cy;
			gfx_line(x1i, y1i, x2i, y2i) ;
		}	

		//draw outer ellipse of racetrack
		float x1o, x2o, y1o, y2o ;		
		for( a = 0 ; a < 2 * M_PI ; a += da ) {
			x1o = r2o * cos(a) + cx ;
			x2o = r2o * cos(a+da) + cx ;
			y1o = -r1o * sin(a) + cy ;
			y2o = -r1o * sin(a+da) + cy;
			gfx_line(x1o, y1o, x2o, y2o) ;
		}	

		gfx_flush() ;

		usleep (10000) ;

		r1c = r1 + adj;
		r2c = r2 + adj;

		//adjust location of car
		if (omega != 0) {		

			x1 = r2c * cos(omega*t) + (cx - 10) ;
			x2 = r2c * cos(omega*t) + (cx + 10) ;
			x3 = r2c * cos(omega*t) + (cx + 10) ;
			x4 = r2c * cos(omega*t) + (cx - 10) ;
			y1 = -r1c * sin(omega*t) + (cy + 10) ;
			y2 = -r1c * sin(omega*t) + (cy + 10) ;
			y3 = -r1c * sin(omega*t) + (cy - 10) ;
			y4 = -r1c * sin(omega*t) + (cy - 10) ;

			t += dt ;	//increment time only if the car is moving
		}

		//check to see if the car has crashed
		if ( r2c-10 == r2i || r2c+10 == r2o || r1c-10 == r1i || r1c+10 == r1o ) {
			gfx_clear() ;
			gfx_color(255, 0, 0);
						
			//draw C
			gfx_line( (cx-95), (cy+25), (cx-135), (cy+25) );
			gfx_line( (cx-135), (cy+25), (cx-135), (cy-25) );
			gfx_line( (cx-135), (cy-25), (cx-95), (cy-25) );
			//draw R
			gfx_line( (cx-35), (cy+25), (cx-85), cy) ;
			gfx_line( (cx-85), cy, (cx-45), (cy-10) ) ;
			gfx_line( (cx-45), (cy-10), (cx-85), (cy-25) );
			gfx_line( (cx-85), (cy-25), (cx-85), (cy+25) );	
			//draw A
			gfx_line( (cx-25), (cy+25), cx, (cy-25) ) ;
			gfx_line( (cx+25), (cy+25), cx, (cy-25) ) ;
			gfx_line( (cx-10), cy, (cx+10), cy) ;
			//draw S
			gfx_line( (cx+35), (cy+25), (cx+75), (cy+25) );
			gfx_line( (cx+75), (cy+25), (cx+75), cy);
			gfx_line( (cx+75), cy, (cx+35), cy);
			gfx_line( (cx+35), cy, (cx+35), (cy-25) );
			gfx_line( (cx+35), (cy-25), (cx+75), (cy-25) );
			//draw H
			gfx_line( (cx+85), (cy+25), (cx+85), (cy-25) );
			gfx_line( (cx+85), cy, (cx+125), cy);
			gfx_line( (cx+125), (cy+25), (cx+125), (cy-25) );
			//draw !
			gfx_line( (cx+135), (cy+10), (cx+135), (cy-25) );
			gfx_line( (cx+140), (cy+25), (cx+140), (cy+15) );
			gfx_line( (cx+130), (cy+15), (cx+140), (cy+15) );
			gfx_line( (cx+130), (cy+15), (cx+130), (cy+25) );
			gfx_line( (cx+130), (cy+25), (cx+140), (cy+25) );

			gfx_flush() ;			
			sleep(2) ;
			stillgoing = 0 ;

		}
		
		//resets time to reduce differences when omega is changed
		if ((sin(omega*t) < .01) && (sin(omega*t) > -.01) && (t > 1) && (x1 > cx)) {	//t>1 so car can start, x1>cx so resets only on +x axis
			t = 0 ; 	
		}

		//check for user input
		if ( gfx_event_waiting() ) {
			char c = gfx_wait() ;
			
			switch(c) {
				//pressing c changes car to random color (that is not black)
				case 'c' :
					car_r = rand() % 235 + 21 ;
					car_g = rand() % 235 + 21 ;
					car_b = rand() % 235 + 21 ;
					break ;
		
				//pressing u or d speeds up (u) or slows down (d) the car
				case 'u' :
					omega+= .01;
					break ;
				case 'd' :
					omega-= .01;
					break ;

				//pressing l or r moves the car closer (l) to the inside turns or further away (r)
				case 'l' :
					adj -= 1 ;
					break ;
				case 'r' :
					adj += 1 ;
					break ;

				case 'q':
					stillgoing = 0 ;
					break ;
				
				
			}
		} 

	}	

	return 0 ;
}
