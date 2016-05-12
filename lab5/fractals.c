#include <stdio.h>
#include "gfx.h"
#include <math.h>


//function prototypes
void fractal_sierpinsky_triangle(int x1, int y1, int x2, int y2, int x3, int y3) ;
void draw_triangle(int x1, int y1, int x2, int y2, int x3, int y3) ;

void fractal_shrinking_squares(int x, int y, int length) ;	//(x, y) are coordinates of upper left corner
void draw_square(int x, int y, int length) ;			//(x, y) are coordinates of upper left corner

void fractal_spiral_squares(int xc, int yc, int length, double theta) ;

void fractal_circular_lace(int x, int y, double radius) ;
void draw_circle(int x, int y, double radius) ;			//circle centered at (x, y)

void fractal_snowflake(int x, int y, double radius) ;
void draw_spokes(int x, int y, double radius, int n) ;

void fractal_tree(int x, int y, int length, double theta, double dt) ;	//theta refers to the inital angle (pi/2), dt is the radians moved away from this initial angle each time the function recurses
void draw_branch(int x, int y, int length, double theta, double dt) ;
	
void fractal_fern(int x, int y, int length, double theta, double dt) ;	//theta and dt are same as fractal_tree, (x, y) is base of first fern drawn 

void fractal_spiral_of_spirals(int xc, int yc, double theta, double maxradius) ;
void draw_spiral(int xc, int yc, double theta, double maxradius) ;


//begin main function
int main(void) {

	int xsize = 800, ysize = 800 ;
	int xc = xsize/2, yc = ysize/2 ;
	gfx_open(xsize, ysize, "Fractals") ;
	
	int stillgoing = 1;

	while (stillgoing) {
		if (gfx_event_waiting) {
			char c = gfx_wait() ;
			switch (c) {
				case '1':
					gfx_clear() ;
					gfx_color(100, 255, 200) ;
					fractal_sierpinsky_triangle(  xsize*15/16, ysize/16, xsize/16, ysize/16, xsize/2, ysize*15/16) ;
					break ;

				case '2':
					gfx_clear() ;
					gfx_color(255, 100, 255) ;
					fractal_shrinking_squares(xsize/2, ysize/2, xsize/2) ;
					break ;

				case '3':
					gfx_clear() ;
					gfx_color(255, 255, 0) ;
					fractal_spiral_squares(xc, yc, xsize/7, -M_PI/10) ;
					break ;

				case '4':
					gfx_clear() ;
					gfx_color(0, 50, 255) ;
					fractal_circular_lace(xc, yc, xsize/3) ;
					break ;

				case '5':
					gfx_clear() ;
					gfx_color(255, 255, 255) ;
					fractal_snowflake(xc, yc, xsize*5/16) ;
					break ;

				case '6':
					gfx_clear() ;
					gfx_color(0, 100, 0) ;
					gfx_line(xc, ysize*5/8, xc, ysize) ;
					fractal_tree(xc, ysize*5/8, xsize/8,  M_PI/ 2, M_PI/6) ;
					break ;

				case '7':
					gfx_clear() ;
					gfx_color(0, 200, 100) ;
					gfx_line(xsize/2, ysize, xsize/2, ysize/3) ;
					fractal_fern(xsize/2, ysize, xsize*2/3, M_PI/2, 0) ;
					break ;

				case '8':
					gfx_clear() ;
					gfx_color(255, 0, 255) ;
					fractal_spiral_of_spirals(xc, yc, -M_PI/3, xsize*2/3) ;
					break ;

				case 'q':
					stillgoing = 0 ;
					break ;
			}
		}
	}

	return 0;

}


void fractal_sierpinsky_triangle(int x1, int y1, int x2, int y2, int x3, int y3) {
	//base case
	if (abs(x2 - x1) < 2) {
		return ;
	}

	//drawing step
	draw_triangle(x1, y1, x2, y2, x3, y3) ;
	
	//recursive step
	fractal_sierpinsky_triangle(x1, y1, (x1+x2)/2, (y1+y2)/2, (x1+x3)/2, (y1+y3)/2) ;
	fractal_sierpinsky_triangle(x2, y2, (x1+x2)/2, (y1+y2)/2, (x2+x3)/2, (y2+y3)/2) ;
	fractal_sierpinsky_triangle(x3, y3, (x1+x3)/2, (y1+y3)/2, (x2+x3)/2, (y2+y3)/2) ;


}


void draw_triangle(int x1, int y1, int x2, int y2, int x3, int y3) {
	gfx_line(x1, y1, x2, y2) ;
	gfx_line(x2, y2, x3, y3) ;
	gfx_line(x3, y3, x1, y1) ;
}





void fractal_shrinking_squares(int x, int y, int length) {
	//base case
	if (length < 2) {
		return ;
	}

	//drawing step
	draw_square(x, y, length) ;

	//recursive step
	int newlength = length*4/9 ;
	fractal_shrinking_squares(x-length/2, y-length/2, newlength) ;
	fractal_shrinking_squares(x+length/2, y-length/2, newlength) ;
	fractal_shrinking_squares(x-length/2, y+length/2, newlength) ;
	fractal_shrinking_squares(x+length/2, y+length/2, newlength) ;
}


void draw_square(int x, int y, int length) {
	gfx_line(x+length/2, y-length/2, x-length/2, y-length/2) ;
	gfx_line(x-length/2, y-length/2, x-length/2, y+length/2) ;
	gfx_line(x+length/2, y-length/2, x+length/2, y+length/2) ;
	gfx_line(x+length/2, y+length/2, x-length/2, y+length/2) ;
}




void fractal_spiral_squares(int xc, int yc, int length, double theta) {
	//base case
	if (length < 1) {
		return ;
	}

	//drawing step
	int radius = 3.25*length ;
	double x = (radius)*cos(theta) + xc ;
	double y = -(radius)*sin(theta) + yc ;
	draw_square(x, y, length) ;

	//recursize step
	double dt = -2*M_PI/10 ;
	int newlength = length*21/22 ;

	fractal_spiral_squares(xc, yc, newlength, theta + dt) ;


}




void fractal_circular_lace(int x, int y, double radius) {
	//base case
	if (radius < 1) {
		return ;
	}

	//drawing step
	draw_circle(x, y, radius) ;

	//recursive step
	int i ;
	double xnew, ynew, rnew ;
	double t = 2*M_PI/6 ;
	for ( i = 0 ; i < 6 ; i++ ) {
		xnew = radius*cos(i*t) + x ;
		ynew = -radius*sin(i*t) + y ;
		rnew = radius / 3 ;	
		fractal_circular_lace(xnew, ynew, rnew) ;
	} 
}


void draw_circle(int x, int y, double radius) {
	double t, dt = .1 ;
	double x1, y1, x2, y2 ;
	for ( t = 0 ; t<2*M_PI ; t+= dt) {
		x1 = radius*cos(t) + x ;
		x2 = radius*cos(t+dt) + x ;
		y1 = -radius*sin(t) + y ;
		y2 = -radius*sin(t+dt) + y ;
		gfx_line(x1, y1, x2, y2) ;
	}



}




void fractal_snowflake(int x, int y, double radius) {
	//base case
	if (radius < 1 ) {
		return ;
	}

	//drawing step
	draw_spokes(x, y, radius, 5) ;

	//recursive step
	int newradius = radius/3 ;
	double t ; 
	double dt = 2*M_PI/5 ;
	double xr, yr ;
	for (t = M_PI/5 ; t < 2*M_PI ; t+= dt) {
		xr = radius*cos(t) + x ;
		yr = -radius*sin(t) + y ;
		fractal_snowflake(xr, yr, newradius) ;
	}

}


void draw_spokes(int x, int y, double radius, int n) {
	double t;
	double dt = 2*M_PI/n ;
	double xr, yr ;	
	for ( t = M_PI/n ; t < 2*M_PI ; t+= dt) {
		xr = radius*cos(t) + x ;
		yr = -radius*sin(t) + y ;
		gfx_line(x, y, xr, yr) ;
	}
}




void fractal_tree(int x, int y, int length, double theta, double dt) {
	//base case
	if(length < 2) {		
		return ;
	}

	//drawing step
	draw_branch(x, y, length, theta, dt) ;
	
	//recursive step
	int newlength = length*13/16 ;
	fractal_tree(length*cos(theta-dt)+x, -length*sin(theta-dt)+y, newlength, theta - dt, dt ) ;
	fractal_tree(length*cos(theta+dt)+x, -length*sin(theta+dt)+y, newlength, theta + dt, dt) ;

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



void fractal_fern(int x, int y, int length, double theta, double dt) {
	//base case
	if (length < 5) {
		return ;
	}

	//drawing step
	draw_branch(x, y, length, theta, dt) ;	

	//recursive step
	int newlength = length/3 ;
	
	double newt1 = theta - dt ;
	double newt2 = theta + dt ;
	double newx1, newx2, newy1, newy2 ;
	
	double newdt ;
	if (dt < M_PI/5) {
		newdt = dt + M_PI/5 ;
	} else {
		newdt = dt ;
	}

	int n = 4, i ;
	for ( i = 1 ; i<=n ; i++) {
		newx1 = x + length*cos(newt1)*i/n ;
		newx2 = x + length*cos(newt2)*i/n ;
		newy1 = y - length*sin(newt1)*i/n ;	
		newy2 = y - length*sin(newt2)*i/n ;
		
		fractal_fern(newx1, newy1, newlength, newt1, newdt) ;
		fractal_fern(newx2, newy2, newlength, newt2, newdt) ;
	}	
	
}
	




void fractal_spiral_of_spirals(int xc, int yc, double theta, double maxradius) {
	//base case
	if (maxradius < 3) {
		return ;
	}

	//drawing step
	draw_spiral(xc, yc, theta, maxradius) ;

}


void draw_spiral(int xc, int yc, double theta, double maxradius) {
	int n = 10 ;	
	double radius ;	
	double dt = -2*M_PI/n ;
	int i ;
	for (radius = maxradius, i = 0 ; radius > 2 ; radius*=9.0/10, i++) {
		gfx_point(xc+radius*cos(theta+i*dt), yc-radius*sin(theta+i*dt)) ;
		fractal_spiral_of_spirals(xc+radius*cos(theta+i*dt), yc-radius*sin(theta+i*dt), theta+i*dt, radius*7/18) ;

	}
}




















