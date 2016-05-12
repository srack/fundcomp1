#include <stdio.h>
#include <math.h>
#include "gfx.h"

//graphs triangle_waveform with no added harmonics

//prototypes
void draw_axes(int x, int y) ;					//draws xy axis for [-10, 10] for a window of size x and y
void draw_ten(int xpos, int ypos, int height, int width) ;
void draw_one( int x, int y, int height, int width) ;
void draw_two( int x, int y, int height, int width) ;
void draw_three( int x, int y, int height, int width) ;
void draw_four( int x, int y, int height, int width) ;
void draw_five( int x, int y, int height, int width) ;
void draw_six( int x, int y, int height, int width) ;
void draw_seven( int x, int y, int height, int width) ;
void draw_eight( int x, int y, int height, int width) ;
void draw_nine( int x, int y, int height, int width) ;
void draw_zero( int x, int y, int height, int width) ;
void draw_numeral( int x, int y, int n, int height, int width) ;
void draw_vtick(int xpos, int ypos, int length) ;
void draw_htick(int xpos, int ypos, int length) ;
void draw_ellipse(int cx, int cy, int rx, int ry) ;		//draws ellipse centered at (cx, cy) with radii rx (in x dir) and ry (in y dir)
void draw_arc(int cx, int cy, int r, double t1, double t2) ;	//draws arc centered at (cx, cy) with radius r from angle t1 to t2

double triangle_waveform (double freq, double amp, double t) ;
void plot_triangle(int xsize, int ysize, float xl, float xu, float dx) ;




//begin main function
int main (void) 
{		
	int xsize = 800, ysize = 800 ;
	gfx_open( xsize, ysize, "Test Graph of Function triangle_waveform" ) ;

	int stillgoing = 1;

	while (stillgoing) {
		gfx_clear() ;
		gfx_color(255, 255, 255) ;	//axis is white		
		draw_axes( xsize, ysize) ;
		gfx_color(150, 0, 255) ;
		plot_triangle(xsize, ysize, -10., 10, .1) ;
		gfx_flush() ;

		char c = gfx_wait() ;
		if (c == 'q') stillgoing = 0 ;
	}
	return 0 ;
}	//end main		






//functions for axes

void draw_axes(int x, int y) {
	gfx_line(0, y/2, x, y/2) ;	//draws x axis
	gfx_line(x/2, 0, x/2, y) ;	//draws y axis
	
	int xcounter = 0, ycounter = 0 ;
	//draw tick marks on x axis
	for (xcounter ; xcounter <= x ; xcounter+= x/20) {
		draw_vtick(xcounter, y/2, 10) ;
	} 

	//draw tick marks on y axis
	for (ycounter; ycounter <= y ; ycounter+= y/20) {
		draw_htick(x/2, ycounter, 10) ;
	}

	//draw numeric labels
	int h = x/100 , w = x/100 ;			//height and width of numbers	
	int n ;
	//numbers on +x axis
	for (n = 1; n< 10; n++) {
		draw_numeral(x*(10+n)/20 - w/2 , y/2 + 10, n, h, w) ;
	}
	draw_ten(x - 2*w, y/2+10, h, w) ;
	//numbers on +y axis
	for (n = 1; n < 10;  n++) {
		draw_numeral(x/2+10, y*n/20 - h/2, 10-n , h, w) ;
	}	
	draw_ten(x/2+10, 0, h, w) ;
	//numbers on -x axis
	for ( n = 1; n < 10 ; n++) {
		draw_numeral(x*n/20, y/2+10, 10-n, h, w) ;
	}
	draw_ten(w, y/2+10, h, w) ;
	for (n = 1 ; n<10 ; n++) {
		draw_htick(x*n/20 - 5, y/2+15, w/2) ;
	}
	draw_htick(w-2, y/2+15, w/2) ;	
	//numbers on -y axis
	for (n = 1; n < 10 ; n++) {
		draw_numeral(x/2+10, y*(10+n)/20 - h/2, n, h, w) ;
	}
	draw_ten(x/2+20, y - 1.5*h, h, w) ;
	for (n = 1 ; n<10 ; n++) {
		draw_htick(x/2+15, y*(10+n)/20, w/2) ;
	}
	draw_htick(x/2+15, y-h, w/2) ;

}



void draw_vtick(int xpos, int ypos, int length) {
	gfx_line(xpos, ypos+length/2, xpos, ypos-length/2) ;
}



void draw_htick(int xpos, int ypos, int length) {
	gfx_line(xpos+length/2, ypos, xpos-length/2, ypos) ;
}



void draw_ten(int x, int y, int height, int width) {
	//draw 1
	draw_one(x, y, height, width/2) ;
	//draw 0
	draw_zero(x+width, y, height, width/2) ;	
	
}


void draw_one( int x, int y, int height, int width) {
	gfx_line( x, y+height, x+width, y+height) ;
	gfx_line( x+width/2, y+height, x+width/2, y) ;
	gfx_line( x+width/2, y, x, y+height/3) ;
}


void draw_two( int x, int y, int height, int width) {
	gfx_line( x, y, x+width, y) ;
	gfx_line( x+width, y, x+width, y+height/2) ;
	gfx_line( x+width, y+height/2, x, y+height/2) ;
	gfx_line( x, y+height/2, x, y+height);
	gfx_line( x, y+height, x+width, y+height);
}


void draw_three( int x, int y, int height, int width) {
	gfx_line( x, y, x+width, y) ;
	gfx_line( x+width, y, x+width, y+height) ;
	gfx_line( x+width, y+height/2, x+width/3, y+height/2) ;
	gfx_line( x+width, y+height, x, y+height) ;
}


void draw_four( int x, int y, int height, int width) {
	gfx_line( x+width*4/5, y+height, x+width*4/5, y) ;
	gfx_line( x+width*4/5, y, x, y+height/2) ;
	gfx_line( x, y+height/2, x+width, y+height/2);
}

void draw_five( int x, int y, int height, int width) {
	gfx_line( x , y, x+width, y) ;
	gfx_line( x, y, x, y+height/2) ;
	gfx_line(x, y+height/2, x+width, y+height/2) ;
	gfx_line(x+width, y+height/2, x+width, y+height) ;
	gfx_line(x, y+height, x+width, y+height) ;
}


void draw_six( int x, int y, int height, int width) {
	gfx_line( x, y, x+width, y) ; 
	gfx_line( x, y, x, y+height) ;
	gfx_line( x, y+height/2, x+width, y+height/2) ;
	gfx_line( x, y+height, x+width, y+height) ;
	gfx_line( x+width, y+height/2, x+width, y+height) ;
}


void draw_seven( int x, int y, int height, int width) {
	gfx_line( x, y, x+width, y) ;
	gfx_line( x+width, y, x+width/5, y+height) ;
}


void draw_eight( int x, int y, int height, int width) {
	gfx_line( x, y, x+width, y) ;
	gfx_line( x, y, x, y+height) ;
	gfx_line( x+width, y, x+width, y+height) ;
	gfx_line( x, y+height/2, x+width, y+height/2) ;
	gfx_line(x, y+height, x+width, y+height) ;
}


void draw_nine( int x, int y, int height, int width) {
	gfx_line( x, y, x+width, y) ;
	gfx_line( x, y, x, y+height/2) ;
	gfx_line( x, y+height/2, x+width, y+height/2) ;
	gfx_line( x+width, y, x+width, y+height) ; 
}


void draw_zero( int x, int y, int height, int width) {
	gfx_line( x, y, x+width, y) ;
	gfx_line( x+width, y, x+width, y+height) ;
	gfx_line( x, y+height, x+width, y+height) ;
	gfx_line( x, y, x, y+height) ;
}
		
		

void draw_numeral( int x, int y, int n, int height, int width) {
	switch(n) {	
		case 1:
			draw_one(x, y, height, width) ;
			break ;
		case 2:
			draw_two(x, y, height, width) ;
			break ;
		case 3:
			draw_three(x, y, height, width) ;
			break ;
		case 4:
			draw_four(x, y, height, width) ;
			break ;
		case 5:
			draw_five(x, y, height, width) ;
			break ;
		case 6:
			draw_six(x, y, height, width) ;
			break ;
		case 7:
			draw_seven(x, y, height, width) ;
			break ;
		case 8:
			draw_eight(x, y, height, width) ;
			break ;
		case 9:
			draw_nine(x, y, height, width) ;
			break ;
		case 0:
			draw_zero(x, y, height, width) ;
			break ;
	}
}


	

//functions for triangle waveform

double triangle_waveform (double freq, double amp, double t) {
	double period = 1/freq ;
	double m1 = 4*amp / period ;	//slope of first quarter of the wave
	double yint1 = 0 ; 
	double m2 = -m1 ; 
	double yint2 = 2*amp ;
	double m3 = m1 ;
	double yint3 = -4*amp ;
	if (t >= 0){
		while (t >= 0) {
			t -= period ;
		}
		t += period ;		//gives t within the first wavelength
	} else {
		while (t < 0) {
			t += period ;
		}
	}
	
	if (t <= period/4) {
		return (m1*t+yint1) ;
	} else if (t <= period*3/4) {
		return (m2*t+yint2) ;
	} else return (m3*t+yint3) ;

}



void plot_triangle(int xsize, int ysize, float xl, float xu, float dx) {
	double x = xl, y1, y2 ;

	int xpos = 0 ;	//original position in terms of coordinates of pixels
	int ypos1, ypos2; 	//positions of y in terms of coordinates of pixels


	while (x < xu ) {
		y1 = triangle_waveform(1.0/5, 3 , x) ;
		x+= dx ;
		y2 = triangle_waveform(1.0/5, 3, x) ;

		xpos = xpos + dx*xsize/(xu-xl) ;
		
		ypos1 = ysize/2 - (y1*ysize/(xu-xl)) ;
		ypos2 = ysize/2 - (y2*ysize/(xu-xl)) ;

		if ((ypos1 <= ysize && ypos1 >= 0) || (ypos2 <= ysize && ypos2 >= 0) ) { 
			gfx_line(xpos - dx*xsize/(xu-xl) , ypos1, xpos, ypos2) ;		
		}
	}

}




