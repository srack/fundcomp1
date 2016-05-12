#include <stdio.h>
#include <math.h>
#include "gfx.h"

//prototypes
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
void draw_numeral( int x, int y, char n, int height, int width) ;

//begin main function
int main (void) 
{
	int xsize = 500, ysize = 500 ;
	gfx_open( xsize, ysize, "Numeric Typewriter" ) ;
	int stillgoing = 1 ;
	
	int h = 100 , w = h / 2 ;  //initial width and height of each number


	while (stillgoing) {
		char c = gfx_wait() ;
	
		int xpos = gfx_xpos() ;
		int ypos = gfx_ypos() ;
		draw_numeral(xpos, ypos, c, h, w) ;
		if (c == '=') {
			h*= 2;
			w*= 2;
		} else if( c == '-') {
			h/= 2;
			w/= 2;
		} else if(c == 'q') {
			stillgoing = 0;
		}
 		
	}

}




//function draw 1
void draw_one( int x, int y, int height, int width) {
	gfx_line( x, y+height, x+width, y+height) ;
	gfx_line( x+width/2, y+height, x+width/2, y) ;
	gfx_line( x+width/2, y, x, y+height/3) ;
}

//function draw 2
void draw_two( int x, int y, int height, int width) {
	gfx_line( x, y, x+width, y) ;
	gfx_line( x+width, y, x+width, y+height/2) ;
	gfx_line( x+width, y+height/2, x, y+height/2) ;
	gfx_line( x, y+height/2, x, y+height);
	gfx_line( x, y+height, x+width, y+height);
}

//function draw 3
void draw_three( int x, int y, int height, int width) {
	gfx_line( x, y, x+width, y) ;
	gfx_line( x+width, y, x+width, y+height) ;
	gfx_line( x+width, y+height/2, x+width/3, y+height/2) ;
	gfx_line( x+width, y+height, x, y+height) ;
}

//function draw 4
void draw_four( int x, int y, int height, int width) {
	gfx_line( x+width*4/5, y+height, x+width*4/5, y) ;
	gfx_line( x+width*4/5, y, x, y+height/2) ;
	gfx_line( x, y+height/2, x+width, y+height/2);
}

//function draw 5
void draw_five( int x, int y, int height, int width) {
	gfx_line( x , y, x+width, y) ;
	gfx_line( x, y, x, y+height/2) ;
	gfx_line(x, y+height/2, x+width, y+height/2) ;
	gfx_line(x+width, y+height/2, x+width, y+height) ;
	gfx_line(x, y+height, x+width, y+height) ;
}

//function draw 6
void draw_six( int x, int y, int height, int width) {
	gfx_line( x, y, x+width, y) ; 
	gfx_line( x, y, x, y+height) ;
	gfx_line( x, y+height/2, x+width, y+height/2) ;
	gfx_line( x, y+height, x+width, y+height) ;
	gfx_line( x+width, y+height/2, x+width, y+height) ;
}

//function draw 7
void draw_seven( int x, int y, int height, int width) {
	gfx_line( x, y, x+width, y) ;
	gfx_line( x+width, y, x+width/5, y+height) ;
}

//function draw 8
void draw_eight( int x, int y, int height, int width) {
	gfx_line( x, y, x+width, y) ;
	gfx_line( x, y, x, y+height) ;
	gfx_line( x+width, y, x+width, y+height) ;
	gfx_line( x, y+height/2, x+width, y+height/2) ;
	gfx_line(x, y+height, x+width, y+height) ;
}

//function draw 9
void draw_nine( int x, int y, int height, int width) {
	gfx_line( x, y, x+width, y) ;
	gfx_line( x, y, x, y+height/2) ;
	gfx_line( x, y+height/2, x+width, y+height/2) ;
	gfx_line( x+width, y, x+width, y+height) ; 
}

//function draw 0
void draw_zero( int x, int y, int height, int width) {
	gfx_line( x, y, x+width, y) ;
	gfx_line( x+width, y, x+width, y+height) ;
	gfx_line( x, y+height, x+width, y+height) ;
	gfx_line( x, y, x, y+height) ;
}


//function draw numeral
void draw_numeral( int x, int y, char n, int height, int width) {
	switch(n) {	
		case '1':
			draw_one(x, y, height, width) ;
			break ;
		case '2':
			draw_two(x, y, height, width) ;
			break ;
		case '3':
			draw_three(x, y, height, width) ;
			break ;
		case '4':
			draw_four(x, y, height, width) ;
			break ;
		case '5':
			draw_five(x, y, height, width) ;
			break ;
		case '6':
			draw_six(x, y, height, width) ;
			break ;
		case '7':
			draw_seven(x, y, height, width) ;
			break ;
		case '8':
			draw_eight(x, y, height, width) ;
			break ;
		case '9':
			draw_nine(x, y, height, width) ;
			break ;
		case '0':
			draw_zero(x, y, height, width) ;
			break ;
	}
}


