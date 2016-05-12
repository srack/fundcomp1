#include <stdio.h>
#include "gfx.h"
#include <math.h>



//function prototypes
void draw_circle(int x, int y, int radius) ;
void draw_people(int x, int y, int radius) ;
void draw_car(int x, int y, int height, int width) ;
void draw_little_spinner(int x, int y, double radius, double theta) ;
void draw_spinner(int x, int y, double radius, double theta) ;
void draw_horiz_slider(int x, int y, double radius, double length, double theta) ;
void draw_vert_slider(int x, int y, int ymax, double radius, double length, double theta) ;



//begin main function

int main(void) {
	int xsize = 1200, ysize = 900 ;
	gfx_open(xsize, ysize, "Carnival Ride" ) ;
	
	double t = 0, dt = .01; 
	int xpos = xsize/2, ypos = ysize*2/3 ;
	int stillgoing = 1 ;
	int red = 100, blue = 100, green = 255 ; //initial parameters for color of ride

	double r = ysize/3 ; 
	double l = r/2 ;


	while (stillgoing == 1){
		gfx_clear() ;
		gfx_color(red, blue, green) ;

		draw_vert_slider(xpos, ypos, ysize, r, l, t) ;
		gfx_flush() ;
		usleep(10000) ;
		t+= dt ;

		if (gfx_event_waiting()) {
			char c = gfx_wait() ;
			if (c == 'q') {
				stillgoing = 0 ;
			} else if (c == 'p') {
				sleep(3) ;
			}
		}
		red = rand() % 150 + 50 ;		//the ride will appear to be flashing because of color change with each updated position
		blue = rand() % 150 + 50;
		green = rand() % 150 + 50 ;
		
	}	
	return 0 ;

}




void draw_circle(int x, int y, int radius) {
	double t, dt = .1 ;	
	double x1, x2, y1, y2 ;
	for (t = 0 ; t<2*M_PI ; t+=dt) {
		x1 = radius*cos(t) + x ;
		x2 = radius*cos(t+dt) + x ;
		y1 = -radius*sin(t) + y ;
		y2 = -radius*sin(t+dt) + y;
		gfx_line(x1, y1, x2, y2) ;
	}
}

void draw_people(int x, int y, int radius) {		//people are represented as circles
	//draw heads	
	draw_circle(x, y, radius) ;
	//draw arms
	gfx_line(x+radius*2/3, y+1.5*radius, x+2*radius, y-2*radius) ;
	gfx_line(x-radius*2/3, y+1.5*radius, x-2*radius, y-2*radius) ;
	//draw neck
	gfx_line(x, y+radius, x, y+1.5*radius) ; 
}
	



void draw_car(int x, int y, int height, int width) {
	gfx_line(x-width/2, y+height/2, x+width/2, y+height/2) ;
	gfx_line(x+width/2, y+height/2, x+width/2, y-height/2) ;
	gfx_line(x+width/2, y-height/2, x-width/2, y-height/2) ;
	gfx_line(x-width/2, y-height/2, x-width/2, y+height/2) ;
	
	draw_people(x-width/3, (y-height/2)-height/3, height/6) ;
	draw_people(x+width/3, (y-height/2)-height/3, height/6) ;
	draw_people(x, (y-height/2)-height/3, height/6) ;

}




void draw_little_spinner(int x, int y, double radius, double theta) {
	double xend, yend ;
	double angle, da = .01 ;
	int counter ;
	for (counter = 0 , angle = theta ; counter < 4 ; counter++ , angle += M_PI/2 ) {
		xend = radius*cos(angle) + x ; 
		yend = -radius*sin(angle) + y ;
		gfx_line(x , y , xend, yend) ;
		draw_car(xend, yend, radius/5, radius/2) ;	
	}
	

}


void draw_spinner(int x, int y, double radius, double theta) {
	double xend, yend ;
	if (fabs(fmod(theta, 2*M_PI)) < (M_PI ) ) {
		xend = radius*cos(theta) + x ;
		yend = -radius*sin(theta) + y ;
	} else {
		xend = radius*cos(-theta) + x ;
		yend = -radius*sin(-theta) + y ; 
	}
	gfx_line(x, y, xend, yend) ;

	draw_little_spinner(xend, yend, radius/3, -3*theta) ;

}


void draw_horiz_slider(int x, int y , double radius, double length, double theta) {
	int xnew ;
	xnew = sin(5*theta)*length + x ;
	gfx_line( xnew + length*2/3, y-1, xnew-length*2/3, y-1) ;
	draw_spinner(xnew, y, radius, theta*3/2) ;
}



void draw_vert_slider(int x, int y, int ymax, double radius, double length, double theta) {
	int ynew ;
	ynew = cos(5*theta)*length + y ;
	draw_horiz_slider(x, ynew, radius, length/4, theta) ;
	//gfx_line(x+length/2, ynew, x+length/2, ymax) ;
	//gfx_line(x-length/2, ynew, x-length/2, ymax) ;
	gfx_line(x , ynew, x, ymax) ;
	gfx_line(x+length/2, ynew, x-length/2, ynew) ;
}









	
