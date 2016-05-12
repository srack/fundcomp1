//Emily Claps & Samantha Rack
//CSE 20211 Final Project
//Ssssssssnake

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include <errno.h>
#include "gfx.h"

#define HIGHSCORES (10) 



//FUNCTION PROTOTYPES

void get_name(char *name) ;
int get_level() ;

void initialize_snake(int *snake_x, int *snake_y, int length, int windowsize) ;
    //give initial location for snake, starts its movement to the right with head starting at center point of the window
void print_snake(int *snake_x, int *snake_y, int length) ;

void new_block(int *block_x, int *block_y, int low, int high) ;
void print_block(int block_x, int block_y, int bsize) ;
void eat_block(int **snake_x, int **snake_y, int length) ;

void print_border(int low, int high) ;

void set_barriers(int low, int high, int barriers[8][4]);
void draw_barriers(int barriers[8][4]);
int barrier_collision(int *snake_x, int *snake_y, int barriers[8][4]) ;

void set_maze(int low, int high, int maze[12][4]) ;
void draw_maze(int maze[12][4]) ;
int maze_collision(int *snake_x, int *snake_y, int maze[12][4]) ;

void next_tick(int *snake_x, int *snake_y, int length, int direction) ;
int user_action(int direction, int choice) ;

void update_score(int *score, int level) ;
void print_score(int score, int size, int high) ;
void draw_numeral( int x, int y, int n, int height, int width) ;
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

void draw_title(int low, int high);
void draw_score_letters(int low, int high);
void draw_S(int x, int y, int height, int width);
void draw_N(int x, int y, int height, int width);
void draw_A(int x, int y, int height, int width);
void draw_K(int x, int y, int height, int width);
void draw_E(int x, int y, int height, int width);
void draw_C(int x, int y, int height, int width);
void draw_O(int x, int y, int height, int width);
void draw_R(int x, int y, int height, int width);

int still_alive(int *snake_x, int *snake_y, int length, int low, int high, int level, int barriers[8][4], int maze[12][4]) ;
void game_over(int score, char *name, int *snake_x, int *snake_y, int length, int low, int high, int size, int level, int barriers[8][4], int maze[12][4], int block_x, int block_y, int bsize) ;
void update_highscores(int score, char *name) ;
void print_results() ;

////////////////////////////////////////////////////////////////

//begin main
int main (void) {
    int size = 600 ;
    int length = (size/8)*3/4 ;		//1/8th size of the playing window

    int lowerbound = size/8 ;
    int upperbound = size*7/8 ;

    int barriers[8][4];
    int maze[12][4] ;

    int *snake_x, *snake_y ;
    snake_x = malloc(length*sizeof(int)) ;
    snake_y = malloc(length*sizeof(int)) ;
 
    initialize_snake(snake_x, snake_y, length, size) ;
    set_barriers(lowerbound, upperbound, barriers);
    set_maze(lowerbound, upperbound, maze) ;
  
    printf("\nWelcome to Snake!\n\n") ;
    printf(" ---CONTROLS:---\n   up    - 'w'\n   down  - 's'\n   right - 'd'\n   left  - 'a'\n\n") ;
    printf(" Press 'p' to pause the game, and 'r' to resume play.\n\n") ;
    char name[20] ;
    get_name(name) ;
 
    int level ;
    level = get_level() ;    
 
    int block_x, block_y ;
    int block_size = 4 ;

    srand(time(0)) ;
    new_block(&block_x, &block_y, lowerbound, upperbound) ;

    //char color ;

    int score = 0 ;
    int direction = 2 ;    //1-up, 2-right (initial movement of snake), 3-down, 4-right

    int speed = 5 ;

    int counter = 1 ;
    int dt ;	//proportional to speed

    int add_length_count = 0 ;

    gfx_open(size, size, "Ssssssssssnake") ;
	char n = gfx_wait() ;
    while(1) {
        gfx_clear() ;
        print_border(lowerbound, upperbound) ;
    	if (level == 2) {
        	draw_barriers(barriers);
    	} else if (level == 3) {
      		draw_maze(maze) ;
  	}
	draw_title(lowerbound,upperbound);
	draw_score_letters(lowerbound, upperbound);
        gfx_color(255, 255, 255) ;
        print_snake(snake_x, snake_y, length) ;
        print_block(block_x, block_y, block_size) ;
        print_score(score, size, upperbound) ;    
        gfx_flush() ;
    
        int i, j ;
        for( i = 0 ; i <= block_size ; i++) {
            for( j = 0 ; j <= block_size ; j++) {
                if ( snake_x[0] == (block_x + i) && snake_y[0] == (block_y + j) ) {    //checks for entirety of block
                    length++ ;
                    eat_block(&snake_x, &snake_y, length) ;
		    add_length_count=5;	//snake length will eventually be incremented by 5
                    new_block(&block_x, &block_y, lowerbound, upperbound) ;
                    update_score(&score, level) ;
                }
            }
        }

	if(add_length_count>0){
		length++;
		eat_block(&snake_x, &snake_y, length);	//length is incremented until 5 blocks have been added to tail end of snake
		add_length_count--;		
   	}
    
        if ( !still_alive(snake_x, snake_y, length, lowerbound, upperbound, level, barriers, maze) ) {
            game_over(score, name, snake_x, snake_y, length, lowerbound, upperbound, size, level, barriers, maze, block_x, block_y, block_size) ;
            break ;
        }
    
        next_tick(snake_x, snake_y, length, direction) ;

        if (gfx_event_waiting()) {
            char c = gfx_wait() ;
            if (c == 'p') {
                char d = gfx_wait() ;
                while (d != 'r') {
                    d = gfx_wait();
                }
            }
            direction = user_action(direction, c) ;
        }
        counter++ ;
        speed = sqrt(counter)/10 + 5 ;    //speed increases as time goes on

        dt = 100000/speed ;
        usleep(dt) ;
    }

    free(snake_x) ;
    free(snake_y) ;
 
    return 0 ;
}  //end main


//////////////////////////////////////////////////////////////////////

//FUNCTION DEFINITIONS

void get_name(char *name) {
	printf(" Please enter your name:  ") ;
	char checkname[100] ;
	int notvalid = 1 ;
	while(1) {
		scanf("%s", checkname) ;
		if(strlen(checkname) <=19) break ;
		printf("  Invalid name.  Please enter your name:  ") ;
	}
	strcpy(name, checkname) ;
	printf("\n") ;
}

int get_level() {
    int level ;
    char levelchar ;   
    printf(" Please enter a level number (1-3):  ") ;
    scanf(" %c", &levelchar) ;
    while (levelchar != '1' && levelchar != '2' && levelchar != '3') {
        printf(" Invalid level number.  Please enter a level number (1-3):  ") ;
        scanf(" %c", &levelchar) ;
    }
    printf("\n") ; 
    if (levelchar == '1') level = 1 ;
    else if (levelchar == '2') level = 2 ;
    else level = 3 ;
    return level ;
}


void initialize_snake(int *snake_x, int *snake_y, int length, int windowsize) {
    int i ;
    for (i = 0 ; i < length ; i++) {
        snake_x[i] = windowsize/2 - i ;
        snake_y[i] = windowsize/2 ;
    }
}

void print_snake(int *snake_x, int *snake_y, int length) {
    int i ;
    for (i = 0 ; i < length ; i++) {
        gfx_point(snake_x[i], snake_y[i]) ;
    }
}


void new_block(int *block_x, int *block_y, int low, int high){
    int size = high - low ;    
    *block_x = rand() % (size-10) + low + 5 ;
        *block_y = rand() % (size-10) + low + 5 ;
}

void print_block(int block_x, int block_y, int bsize) {
    int i, j ;
    gfx_color(0, 200, 50) ;
    for( i = 0 ; i <= bsize ; i++) {
        for( j = 0 ; j <= bsize ; j++) {
            gfx_point(block_x+i, block_y+j) ;
        }
    }
}

void eat_block(int **snake_x, int **snake_y, int length) {
    *snake_x = realloc(*snake_x, length*sizeof(int)) ;
    *snake_y = realloc(*snake_y, length*sizeof(int)) ;
}


void print_border(int low, int high) {
    gfx_color(100, 200, 200) ;
    gfx_line(low, low, low, high) ;
    gfx_line(low, low, high, low) ;
    gfx_line(low, high, high, high) ;
    gfx_line(high, low, high, high) ;
}


void set_barriers(int low, int high, int barriers[8][4]){
        int i;
        srand(time(0));
        for(i=0;i<=7;i++){
                if(i<=3){       //horizontal barriers (4)
                        barriers[i][0]=0;       //0 = indicator of horizontal
                        //starting points no further than 1/4 of respective quadrant
                        if(i==0 || i==1){       //top quadrants
                                barriers[i][2]=low + 5 + rand()%((high-low-15)/2);
                                if(i==0)        //top left
                                        barriers[i][1]=low+5+rand()%((high-low-15)/8);//initial x of barrier
                                else if(i==1)   //top right
                                        barriers[i][1]=low + (high-low)/2 + 2.5 + rand()%((high-low-15)/8);//initial x
                        }
                        else if(i==2 || i==3){  //lower quadrants
                                barriers[i][2]=low + (high-low)/2 + 2.5 + rand()%((high-low-15)/2); //same y
                                if(i==2)        //bottom left
                                        barriers[i][1]=low+5+rand()%((high-low-15)/8);  //initial x
                                else if(i==3)   //bottom right
                                        barriers[i][1]=low + (high-low)/2 + 2.5 + rand()%((high-low-15)/8);  //initial x
                        }
                        barriers[i][3]=(high-low-15)/4 + rand()%((high-low-15)/8);      //length of barrier; min=1/2 quadrant; max=whole quadrant


                }
                else{           //vertical barriers (4)
                        barriers[i][0]=1;       //1=indicator of vertical
                        if(i==4 || i==5){       //left quadrants - same expression for x
                                barriers[i][1]=low + 5 + rand()%((high-low)/2);
                                if(i==4)        //upper left vertical barrier
                                        barriers[i][2]=low+5+rand()%((high-low-15)/8);  //initial y of barrier
                                else if(i==5)   //lower left vertical barrier
                                        barriers[i][2]=low + (high-low)/2 + 2.5 + rand()%((high-low-15)/8);  //initial y of barrier
                        }
                        else if(i==6 || i==7){  //right quadrants - same expression for x
                                barriers[i][1]=low + (high-low)/2 + 2.5 + rand()%((high-low-15)/2);  //initial y of barrier
                                if(i==6)        //upper right vertical barrier
                                        barriers[i][2]=low+5+rand()%((high-low-15)/8);  //initial y of barrier
                                else if(i==7)   //lower right vertical barrier
                                        barriers[i][2]=low + (high-low)/2 + 2.5 + rand()%((high-low-15)/8); //initial y
                        }
                        barriers[i][3]=(high-low-15)/4 + rand()%((high-low-15)/8);      //length of barrier; min=1/2 quadrant; max=whole quadrant
                }
        }
}

void draw_barriers(int barriers[8][4]){
    gfx_color(100, 200, 200) ;
    int i;
    for(i=0;i<=7;i++){
        switch(barriers[i][0]){
            case 0:
                gfx_line(barriers[i][1],barriers[i][2],barriers[i][1]+barriers[i][3],barriers[i][2]);
                break;
            case 1:
                gfx_line(barriers[i][1],barriers[i][2],barriers[i][1],barriers[i][2]+barriers[i][3]);
                break;
        }
    }
}

int barrier_collision(int *snake_x, int *snake_y, int barriers[8][4]){
        int collide=0;
        int i,j;
        for(i=0;i<8;i++){                       //for every barrier (all eight of them)
                for(j=0;j<=barriers[i][3];j++)          //checks to see if head has collided with any element of barrier through entirety of length
                        if(i<=3){                               //horizontal barrier cases - x is incremented to length
                                if(snake_x[0]==(barriers[i][1]+j) && snake_y[0]==barriers[i][2])
                                        collide=1;
                        }
                        else if(i>3 && i<8){                    //vertical barrier cases - y is incremented to length
                                if (snake_x[0]==barriers[i][1] && (snake_y[0]==barriers[i][2]+j))
                                        collide=1;
                        }
        }
        return collide;
}


void set_maze(int low, int high, int maze[12][4]) {
	int i ;
	int playsize = high-low ;
	for( i = 0 ; i < 12 ; i++) {
		if(i%2 == 0) maze[i][0]=1 ;
		else maze[i][0]=0 ;
	}
	
	maze[0][1] = low+playsize*7/8 ;
	maze[1][1] = low+playsize/8 ;
	maze[2][1] = low+playsize/8 ;
	maze[3][1] = low+playsize/8 ;
	maze[4][1] = low+playsize*3/4 ;
	maze[5][1] = low+playsize/4 ;
	maze[6][1] = low+playsize/4 ;
	maze[7][1] = low+playsize/4 ;
	maze[8][1] = low+playsize*5/8 ;
	maze[9][1] = low+playsize*3/8 ;
	maze[10][1] = low+playsize*3/8 ;
	maze[11][1] = low+playsize*3/8 ;

	maze[0][2] = low+playsize/8 ;
	maze[1][2] = low+playsize*7/8 ;
	maze[2][2] = low+playsize/8 ;
	maze[3][2] = low+playsize/8 ;
	maze[4][2] = low+playsize/8 ;
	maze[5][2] = low+playsize*3/4 ;
	maze[6][2] = low+playsize/4 ;
	maze[7][2] = low+playsize/4 ;
	maze[8][2] = low+playsize/4 ;
	maze[9][2] = low+playsize*5/8 ;
	maze[10][2] = low+playsize*3/8 ;
	maze[11][2] = low+playsize*3/8 ;

	maze[0][3] = playsize*3/4 ;
	maze[1][3] = playsize*3/4 ;
	maze[2][3] = playsize*3/4 ;
	maze[3][3] = playsize*5/8 ;
	maze[4][3] = playsize*5/8 ;
	maze[5][3] = playsize/2 ;
	maze[6][3] = playsize/2 ;
	maze[7][3] = playsize*3/8 ;
	maze[8][3] = playsize*3/8 ;
	maze[9][3] = playsize/4 ;
	maze[10][3] = playsize/4 ;
	maze[11][3] = playsize/8 ;

}

void draw_maze(int maze[12][4]){
    int i;
    gfx_color(100, 200, 200) ;
    for(i = 0; i < 12; i++) {
        switch(maze[i][0]) {
            case 0:
                gfx_line(maze[i][1], maze[i][2], maze[i][1]+maze[i][3], maze[i][2]);
                break;
            case 1:
                gfx_line(maze[i][1], maze[i][2], maze[i][1], maze[i][2]+maze[i][3]);
                break;
        }
    }
}


int maze_collision(int *snake_x, int *snake_y, int maze[12][4]){
        int i;
        for(i=0; i<12 ;i++){
                if(maze[i][0] == 1) { //vertical check
			if( (snake_x[0] == maze[i][1]) && (snake_y[0] >= maze[i][2]) && (snake_y[0]<= (maze[i][2]+maze[i][3])) ) {
	                        return 1;
			}
		}
		else {
			if( (snake_y[0] == maze[i][2]) && (snake_x[0] >= maze[i][1]) && (snake_x[0] <= (maze[i][1]+maze[i][3])) ) {
				return 1;	
			}
		}
        }
        return 0;
}


void next_tick(int *snake_x, int *snake_y, int length, int direction) {
    int i ;
    for (i = 0 ; i < length-1 ; i++) {
        snake_x[length-1-i] = snake_x[length-2-i] ;
        snake_y[length-1-i] = snake_y[length-2-i] ;
    }
    switch(direction) {
        case 1:        //up--snake_x[0] unchanged
            snake_y[0] -= 1 ;
            break ;
        case 2:        //right--snake_y[0] unchanged
            snake_x[0] += 1 ;
            break ;
        case 3:        //down
            snake_y[0] += 1 ;
            break ;
        case 4:        //left
            snake_x[0] -= 1 ;
            break ;
    }
}

int user_action(int direction, int choice) {
    int newdirection = direction ;
    switch (choice) {
        case 'w':    //corresponds to up
            if (direction == 2 || direction == 4 ) {
                newdirection = 1 ;
            }
            break ;
        case 'd':    //corresponds to right
            if (direction == 1 || direction == 3) {
                newdirection = 2 ;
            }
            break ;
        case 's':    //down
            if (direction == 2 || direction == 4) {
                newdirection = 3 ;
            }
            break ;
        case 'a':    //left
            if (direction == 1 || direction == 3) {
                newdirection = 4 ;
            }
            break ;
        default:
            break ;
    }
    return newdirection ;
}


void update_score(int *score, int level) {
        if(level==1)
                *score+=1;
        else if(level==2)
                *score+=2;
        else if(level==3)
                *score+=3;
}

void print_score(int score, int size, int high){    //for scores up to 999
    int ones, tens, hundreds;
    gfx_color(150, 0, 255) ;
    if (score/100 != 0) {
        hundreds = score / 100 ;
        tens = (score % 100) / 10 ;
        ones = (score % 100) % 10 ;
        draw_numeral(size*3/4, high + size/25, ones, size/75, size/75) ;
        draw_numeral(size*3/4 - size/50, high + size/25, tens, size/75, size/75) ;
        draw_numeral(size*3/4 - size/25, high + size/25, hundreds, size/75, size/75) ;
    }else if (score/10 != 0) {
        tens = score / 10 ;
        ones = score % 10 ;
        draw_numeral(size*3/4, high + size/25, ones, size/75, size/75) ;
        draw_numeral(size*3/4 - size/50, high + size/25, tens, size/75, size/75) ;
    } else {
        draw_numeral(size*3/4, high + size/25, score, size/75, size/75);
    }
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


void draw_title(int low, int high){
    //write out 'snake' at top
    gfx_color(100, 200, 200) ;
    int i;
    i*(high-low)/7 - 3*low/16;
    draw_S(low + 1.5*(high-low)/7 - 3*low/16, low/8, 3*low/4, 3*low/8);
    draw_N(low + 2.5*(high-low)/7 - 3*low/16, low/8, 3*low/4, 3*low/8);
    draw_A(low + 3.5*(high-low)/7 - 3*low/16, low/8, 3*low/4, 3*low/8);
    draw_K(low + 4.5*(high-low)/7 - 3*low/16, low/8, 3*low/4, 3*low/8);
    draw_E(low + 5.5*(high-low)/7 - 3*low/16, low/8, 3*low/4, 3*low/8);
}

void draw_score_letters(int low, int high){
    //writes out 'score' at bottom
    gfx_color(150, 0, 255) ;
    int i;
    draw_S(low + 1*(high-low)/7 - 3*low/16, high+low/8, 3*low/8, 3*low/16);
    draw_C(low + 2*(high-low)/7 - 3*low/16, high+low/8, 3*low/8, 3*low/16);
    draw_O(low + 3*(high-low)/7 - 3*low/16, high+low/8, 3*low/8, 3*low/16);
    draw_R(low + 4*(high-low)/7 - 3*low/16, high+low/8, 3*low/8, 3*low/16);
    draw_E(low + 5*(high-low)/7 - 3*low/16, high+low/8, 3*low/8, 3*low/16);
}

void draw_S(int x, int y, int height, int width){
        gfx_line(x,y,x+width,y);
        gfx_line(x,y,x,y+height/2);
        gfx_line(x,y+height/2, x+width,y+height/2);
        gfx_line(x+width,y+height/2,x+width,y+height);
        gfx_line(x,y+height,x+width,y+height);
}
void draw_N(int x, int y, int height, int width){
        gfx_line(x,y,x,y+height);
        gfx_line(x+width,y,x+width,y+height);
        gfx_line(x,y,x+width,y+height);
}
void draw_A(int x, int y, int height, int width){
        gfx_line(x,y,x,y+height);
        gfx_line(x,y,x+width,y);
        gfx_line(x+width,y,x+width,y+height);
        gfx_line(x,y+height/2,x+width,y+height/2);
}
void draw_K(int x, int y, int height, int width){
        gfx_line(x,y,x,y+height);
        gfx_line(x,y+2*height/5,x+width,y);
        gfx_line(x,y+2*height/5,x+width,y+height);
}
void draw_E(int x, int y, int height, int width){
        gfx_line(x,y,x+width,y);
        gfx_line(x,y,x,y+height);
        gfx_line(x,y+height,x+width,y+height);
        gfx_line(x,y+height/2,x+width,y+height/2);
}

void draw_C(int x, int y, int height, int width){
        gfx_line(x,y,x,y+height);
        gfx_line(x,y,x+width,y);
        gfx_line(x,y+height,x+width,y+height);
        gfx_line(x+width,y,x+width,y+height/4);
        gfx_line(x+width,y+height,x+width,y+3*height/4);
}
void draw_O(int x, int y, int height, int width){
        gfx_line( x, y, x+width, y) ;
        gfx_line( x+width, y, x+width, y+height) ;
        gfx_line( x, y+height, x+width, y+height) ;
        gfx_line( x, y, x, y+height) ;
}
void draw_R(int x, int y, int height, int width){
        gfx_line(x,y,x,y+height);
        gfx_line(x,y,x+width,y);
        gfx_line(x+width,y,x+width,y+height/2);
        gfx_line(x+width,y+height/2,x,y+height/2);
        gfx_line(x+width/2,y+height/2,x+width,y+height);
}


int still_alive(int *snake_x, int *snake_y, int length, int low, int high, int level, int barriers[8][4], int maze[12][4]){
        int alive = 1 ;
        int i ;
        int collide=0;

        for(i=1;i<length;i++){
                if(snake_x[0]==snake_x[i]){
                        if(snake_y[0]==snake_y[i]){
                                collide=1;
                        }
                }
        }

	if(level == 2 && barrier_collision(snake_x, snake_y, barriers)) collide=1;
	else if(level == 3 && maze_collision(snake_x, snake_y, maze)) collide=1;

        if (snake_x[0]>=high || snake_x[0]<=low || snake_y[0]>=high || snake_y[0]<=low)
                alive=0;
        else if(collide==1)
                alive=0;
        else
                alive=1;

        return alive;
}

void game_over(int score, char *name, int *snake_x, int *snake_y, int length, int low, int high, int size, int level, int barriers[8][4], int maze[12][4], int block_x, int block_y, int bsize) {
    int i ;
    for ( i = 0 ; i < 15 ; i++) {
        if(i%2 == 0){
            gfx_color(255, 25, 25) ;
            print_snake(snake_x, snake_y, length) ;          
        }else {
            gfx_clear() ;
        }
	if (level==2) draw_barriers(barriers) ;
	else if (level==3) draw_maze(maze) ;
        print_border(low, high) ;
	print_block(block_x, block_y, bsize) ;
	draw_title(low, high) ;
	draw_score_letters(low, high) ;
	print_score(score, size, high) ;
        gfx_flush() ;
        usleep(200000) ;
    }
    printf("  Your score:  %d\n\n", score) ;
    update_highscores(score, name) ;
    print_results() ;

}

void print_results() {
	FILE *f ;
	f = fopen(".highscores", "r") ;
	if (!f) {
		printf("Failed to open %s: %s\n", ".highscores", strerror(errno)) ;
		return ;	
	}
	printf("        ----HIGHSCORES----\n") ;
	printf("    %-20s %-6s\n", "Name", "Score") ;
	int counter = 1;
	while(1) {
		char name[20] ; 
		int score ;
		int n ;
		n = fscanf(f, "%s %d", name, &score) ;
		if(n != 2) break ;
		printf("%2d. %-19s %6d\n", counter, name, score) ;
		counter++ ;
	}
	printf("\n") ;
	fclose(f) ;
}

void update_highscores(int score, char *name) {
	FILE *f ;	
	f = fopen(".highscore", "r") ;
	if (!f) {
		if (errno == 2) {	//failed to open because does not exist, ie. first highscore recorded
			f = fopen(".highscores", "w") ;
			if(!f) {
				printf("Failed to open %s: %s\n", ".highscores", strerror(errno)) ;
				return ;
			}
			fprintf(f, "%s %d\n", name, score) ;
			fclose(f) ;
			return ;
		}
		printf("Failed to open %s: %s\n", ".highscores", strerror(errno)) ;
		return ;
	}

	char names[HIGHSCORES][20] ;
	int scores[HIGHSCORES] ;
	int i, n ;
	for(i = 0 ; i<HIGHSCORES ; i++) {	//saves one space for the new score
		n = fscanf(f, "%s %d", names[i], &scores[i]) ;
		if(n != 2) break ;
	}	//at end of loop: i = number of names/highscores after the new score is added

	int elements_read = i ;

	//insert new name and score, if the new score is greater than or equal to any of 10 in the list or if there are less than 10 highscores in the list
	int j ;
	for (j = 0 ; j < elements_read  ; j++) {
		if( score >= scores[j]) {
			int k ;
			for (k = elements_read - 1 ; k > j ; k--) {
				scores[k] = scores[k-1] ;
				strcpy(names[k], names[k-1]) ;
			}
			scores[k] = score ;
			strcpy(names[k], name) ;
			break ;
		}
	}
	if (j==elements_read && elements_read!= HIGHSCORES) {
		scores[elements_read] = score ;	
		strcpy(names[elements_read], name) ;
	}
	fclose(f) ;
	f = fopen(".highscores", "w") ;	//opens same file for writing and discards previous contents
	int m ;	
	for(m = 0 ; m < elements_read ; m++) {
		fprintf(f, "%s %d\n", names[m], scores[m]) ;
	}
	fclose(f) ;
}
