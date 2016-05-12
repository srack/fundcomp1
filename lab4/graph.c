#include <stdio.h>
#include <math.h>
#include "gfx.h"

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
double compute_taylor(int n, double x) ;			//computes the taylor series of sin(x) for expansion of n terms
void plot_taylor(int xsize, int ysize, float xl, float xu, float dx, int n) ;	//plots taylor expansion of n terms with domain [x1, x2]; m is the amount by which x is incremented




//begin main function
int main (void) 
{		
	int xsize = 800, ysize = 800 ;
	gfx_open( xsize, ysize, "Taylor-Series Expansion of sin(x)" ) ;

	int stillgoing = 1;
	int terms = 0 ;		//intially use only a0 (ie. first term) of the Taylor Series
	int onesdigit, tensdigit ; 


	while (stillgoing) {
		gfx_clear() ;
		gfx_color(255, 255, 255) ;	//axis is white		
		draw_axes( xsize, ysize) ;
		gfx_color(150, 0, 255) ;		
		plot_taylor(xsize, ysize, -10, 10, .1, terms) ;
		
		gfx_color(0, 150, 150) ;
		if ((terms+1)/10 != 0) {
			onesdigit = (terms+1) % 10 ;
			tensdigit = (terms+1)/10 ;
			draw_numeral(xsize*7/8 + xsize/150, ysize*7/8, onesdigit, xsize/100, ysize/100) ;
			draw_numeral(xsize*7/8 - xsize/150 , ysize*7/8, tensdigit, xsize/100, ysize/100) ;	
		} else {
			draw_numeral(xsize*7/8, ysize*7/8, terms+1, xsize/100, ysize/100);
		}

		gfx_flush() ;

		char c = gfx_wait() ;
		switch (c) {
			case '-':
				terms-- ;
				break ;
			case '=':
				terms++ ;
				break ;
			case 'q':
				stillgoing = 0 ;
				break ;
		}
	}
	return 0 ;
}		






//function definitions

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


double compute_taylor(int n , double x) {
	double term = 0, b, bfact, c;	
	double ans = 0 ;	
	for (term ; term <= n ; term++) {
		b = 1 + 2*term ;
		bfact = 1;
		//calculate b factorial
		c = b;		
		for (c ; c > 1 ; c--) {
			bfact *= c ;
		}		
		ans = ans + pow(-1.0, term)*pow(x, b)/bfact;

	}
	return ans ;

}




void plot_taylor(int xsize, int ysize, float xl, float xu, float dx, int n) {
	double x = xl, y1, y2 ;

	int xpos = 0 ;	//original position in terms of coordinates of pixels
	int ypos1, ypos2; 	//positions of y in terms of coordinates of pixels


	while (x < xu ) {
		y1 = compute_taylor(n, x) ;
		x+= dx ;
		y2 = compute_taylor(n, x) ;

		xpos = xpos + dx*xsize/(xu-xl) ;
		
		ypos1 = ysize/2 - (y1*ysize/(xu-xl)) ;
		ypos2 = ysize/2 - (y2*ysize/(xu-xl)) ;

		if ((ypos1 <= ysize && ypos1 >= 0) || (ypos2 <= ysize && ypos2 >= 0) ) { 
			gfx_line(xpos - dx*xsize/(xu-xl) , ypos1, xpos, ypos2) ;		
		}
	}

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


	










