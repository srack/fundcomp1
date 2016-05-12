#include <stdio.h>
#define BOARD_SIZE (40) 


//function prototypes

void initialize_board(char board[BOARD_SIZE][BOARD_SIZE], char c) ;				//intializes all elements to c
void print_board(char board[BOARD_SIZE][BOARD_SIZE]) ;
void copy_board(char board1[BOARD_SIZE][BOARD_SIZE], char board2[BOARD_SIZE][BOARD_SIZE]) ;	//copies board 2 into board 1
int user_action(char board1[BOARD_SIZE][BOARD_SIZE], char board2[BOARD_SIZE][BOARD_SIZE], char user) ;
void add_cell(char board[BOARD_SIZE][BOARD_SIZE]) ;
void remove_cell(char board[BOARD_SIZE][BOARD_SIZE]) ;
void apply_rules(char board1[BOARD_SIZE][BOARD_SIZE], char board2[BOARD_SIZE][BOARD_SIZE]) ;	
int count_neighbors(char board[BOARD_SIZE][BOARD_SIZE], int row, int column) ;




//begin main
int main (void) {

	char current[BOARD_SIZE][BOARD_SIZE] ;
	char future[BOARD_SIZE][BOARD_SIZE] ;

	initialize_board(current, ' ') ;
	initialize_board(future, ' ') ;

	char choice ;	
	int stillgoing = 1;

	while (stillgoing) {
		
		printf("\033[2J\033[H") ;

		copy_board(current, future) ;
		print_board(current) ;	

		printf("Please enter one of the following:\n a: to add a new cell\n r: to remove a cell\n n: to advance the simulation\n q: to quit\n p: to play the game forever\n") ;
		scanf("%c", &choice) ;
		
		stillgoing = user_action(current, future, choice) ;		
	}
	return 0 ;

}	//end main







//function definitions

void initialize_board(char board[BOARD_SIZE][BOARD_SIZE], char c) {
	int i, j ;
	for ( i = 0 ; i < BOARD_SIZE ; i++) {
		for ( j = 0 ; j < BOARD_SIZE ; j++ ) {
			board[i][j] = c ;
		}
	}
}




void print_board(char board[BOARD_SIZE][BOARD_SIZE]) {
	int i, j ;
	for ( i = 0 ; i < BOARD_SIZE ; i++) {
		for ( j = 0 ; j < BOARD_SIZE ; j++ ) {
			printf("%2c", board[i][j]) ;
		}
		printf("\n") ;
	}
}



//copies board 2 into board 1
void copy_board(char board1[BOARD_SIZE][BOARD_SIZE], char board2[BOARD_SIZE][BOARD_SIZE] ) {
	int i, j ;
	for ( i = 0 ; i < BOARD_SIZE ; i++) {
		for ( j = 0 ; j < BOARD_SIZE ; j++) {
			board1[i][j] = board2[i][j] ;
		}
	}
}




int user_action(char board1[BOARD_SIZE][BOARD_SIZE], char board2[BOARD_SIZE][BOARD_SIZE], char user) {
	switch (user) {
		case 'a': 
			add_cell(board2) ;
			break ;

		case 'r':
			remove_cell(board2) ;
			break ;

		case 'n':
			apply_rules(board1, board2) ;
			break ;

		case 'q':
			return 0 ;

		case 'p':		
			while (1) {
				apply_rules(board1, board2) ;	
				copy_board(board1, board2) ;
				printf("\033[2J\033[H") ;
				usleep(500000) ;
				print_board(board1) ;			
			}
	}
	return 1 ;
}



void add_cell(char board[BOARD_SIZE][BOARD_SIZE]) {
	int x , y ;
	printf("Enter location of new live cell:  " ) ;
	scanf("%d %d", &x, &y) ;
	board[y][x] = 'X' ;
}



void remove_cell(char board[BOARD_SIZE][BOARD_SIZE]) {
	int x , y ;
	printf("Enter location of cell to remove:  ") ;
	scanf("%d %d", &x, &y) ;
	board[y][x] = ' ' ;
}
	


void apply_rules(char board1[BOARD_SIZE][BOARD_SIZE], char board2[BOARD_SIZE][BOARD_SIZE]) {
	int i, j, neighbors ;
	for ( i = 0 ; i < BOARD_SIZE ; i++ ) {
		for ( j = 0 ; j < BOARD_SIZE ; j++ ) {
			neighbors = count_neighbors( board1, i, j) ;	
	
			if (board1[i][j] == 'X') {		//for live cells
				if (neighbors < 2) board2[i][j] = ' ' ;
				else if (neighbors > 3) board2[i][j] = ' ' ;			
			}else {					//for dead cells
				if (neighbors == 3) board2[i][j] = 'X' ;

			}
		}


	} 
}

int count_neighbors(char board[BOARD_SIZE][BOARD_SIZE], int row, int column) {
	int neighbors = 0 ;
	int k, l ;

	for ( k = -1 ; k <= 1 ; k++ ) {
		for ( l = -1 ; l <= 1 ; l++ ) {
			if ((board[row+k][column+l]=='X') && (k!=0 || l!=0) && (row+k<BOARD_SIZE) && (row+k>=0) && (column+l<BOARD_SIZE) && (column+l>=0) ) {
				 neighbors++ ;
			}
		}
	}

	return neighbors ;
}

