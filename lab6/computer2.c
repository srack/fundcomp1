#include <stdio.h>
#include <stdlib.h>

#define BOARD_SIZE (8)	


//prototypes
void print_board(char board[BOARD_SIZE][BOARD_SIZE]) ;
void initialize_board(char board[BOARD_SIZE][BOARD_SIZE]) ;
void move(char board[BOARD_SIZE][BOARD_SIZE], char player, int x, int y) ;
void change_squares_diag(char board[BOARD_SIZE][BOARD_SIZE], char player, int x, int y) ;
void change_squares_vert(char board[BOARD_SIZE][BOARD_SIZE], char player, int x, int y) ;
void change_squares_horiz(char board[BOARD_SIZE][BOARD_SIZE], char player, int x, int y) ;
void get_move(char board[BOARD_SIZE][BOARD_SIZE], char player) ; 
void is_valid(char board[BOARD_SIZE][BOARD_SIZE], int x, int y) ;
int is_over(char board[BOARD_SIZE][BOARD_SIZE]) ;				//returns 0 if the game is still going and returns 1 if it is over
void determine_winner(char board[BOARD_SIZE][BOARD_SIZE], int frequency[2]) ; 
void computer_move(char board[BOARD_SIZE][BOARD_SIZE]) ;



//begin main
int main (void) {
	printf("\n") ;
	char board[BOARD_SIZE][BOARD_SIZE];
	initialize_board(board) ;

	int done = 0 ;
	char player = 'X' ;			

	while (done == 0) {			//continues until the board is full and the game is over
		if (player == 'X') get_move(board, player) ;
		else computer_move(board) ;	//computer is player 'O'

		if (player == 'X') {
			player = 'O' ;
		} else player = 'X' ;

		done = is_over(board) ;		//checks if the game is over
	}
	
	int wins[2] ;
	determine_winner(board, wins) ;

	return 0 ;
}   //end main





//function definitions
void print_board(char board[BOARD_SIZE][BOARD_SIZE]) {
	int i , j, k;
	printf("  ") ;
	for ( k = 0 ; k < BOARD_SIZE ; k++  ) {
		printf("%3d", k ) ;
	}
	printf("\n") ;
	for ( i = 0 ; i < BOARD_SIZE ; i++) {
		printf("%d ", i ) ;
		for ( j = 0 ; j < BOARD_SIZE ; j++ ) {
			printf("%3c", board[i][j]) ;		
		}
		printf("\n") ;
	}
	printf("\n") ;

}

void initialize_board(char board[BOARD_SIZE][BOARD_SIZE]) {
	int i, j ;
	for ( i = 0 ; i < BOARD_SIZE ; i++ ) {
		for ( j = 0 ; j < BOARD_SIZE ; j++ ) {
			board[i][j] = '.' ;
		}

	}

	int middle = BOARD_SIZE / 2 - 1 ;
	board[middle][middle] = 'X' ;
	board[middle][middle+1] = 'O' ;
	board[middle+1][middle] = 'O' ;
	board[middle+1][middle+1] = 'X' ;
	
	print_board(board) ;
}


void move(char board[BOARD_SIZE][BOARD_SIZE] , char player , int x, int y ) {	
	board[y][x] = player ;
	
	change_squares_diag(board, player, x, y) ;
	change_squares_vert(board, player, x, y) ;
	change_squares_horiz(board, player, x, y) ; 

	print_board(board) ;
}



void change_squares_diag(char board[BOARD_SIZE][BOARD_SIZE], char player, int x, int y) {	
	int i, j ;
	for (i = y+1, j = x+1 ; i < BOARD_SIZE && j < BOARD_SIZE ; i++, j++) {
		if (board[i][j] == player) {
			int k = i, l = j ;
			for ( ; k > y ; k--, l--) {
				board[k][l] = player ;
			}
			break ;
		}
		if (board[i][j] == '.') break ;
	}

	for (i = y-1 , j = x-1 ; i >= 0 && j >= 0 ; i--, j--) {
		if (board[i][j] == player) {
			int k = i, l = j ;
			for ( ; k < y ; k++, l++) {
				board[k][l] = player ;
			}
			break ;
		}
		if (board[i][j] == '.') break ;
	}

	for (i = y+1, j = x-1 ; i < BOARD_SIZE && j >= 0 ; i++, j-- ) {
		if (board[i][j] == player) {
			int k = i, l = j ; 
			for ( ; k > y ; k--, l++) {
				board[k][l] = player ;
			}
			break ;
		}
		if (board[i][j] == '.') break ;
	}

	for (i = y-1, j = x+1 ; i >= 0 && j < BOARD_SIZE ; i--, j++) {
		if (board[i][j] == player) {
			int k = i, l = j ;
			for ( ; k < y ; k++, l--) {
				board[k][l] = player ;
			}
			break ;
		}
		if (board[i][j] == '.') break ;
	}
}


void change_squares_vert(char board[BOARD_SIZE][BOARD_SIZE], char player, int x, int y) {
	int i ;
	for (i = y-1 ; i >= 0 ; i--) {
		if (board[i][x] == player) {
			int k = i ;
			for ( ; k < y ; k++ ) {
				board[k][x] = player ;
			}
			break ;
		}
		if (board[i][x] == '.') break ;
	} 

	for (i = y+1 ; i < BOARD_SIZE ; i++) {
		if (board[i][x] == player) {
			int k = i ;
			for ( ; k > y ; k-- ) {
				board[k][x] = player ;
			}
			break ;
		}
		if (board[i][x] == '.') break ;
	}
}

void change_squares_horiz(char board[BOARD_SIZE][BOARD_SIZE], char player, int x, int y) {
	int j ;
	for ( j = x-1 ; j >= 0 ; j--) {
		if (board[y][j] == player) {
			int l = j ;
			for ( ; l < x ; l++ ) {
				board[y][l] = player ;
			}
			break ;
		}
		if (board[y][j] == '.') break ;
	}	

	for ( j = x+1 ; j < BOARD_SIZE ; j++) {
		if(board[y][j] == player) {
			int l = j ;
			for ( ; l > x ; l-- ) {
				board[y][l] = player ;
			}
			break ;
		}
		if (board[y][j] == '.') break ;
	}
}



void get_move(char board[BOARD_SIZE][BOARD_SIZE], char player ) {
	int x, y ;
	int ask = 1;
	while (ask) {
		printf("Player %c , enter your move :  " , player) ;
		scanf("%d %d" , &x, &y) ;
		printf("\n") ;
		if ( is_legal(board, x, y) ) {
			ask = 0 ;
		} else printf("Invalid move. \n\n") ;
	}
	printf("\n") ;
	move(board, player, x, y) ;
}



int is_legal( char board[BOARD_SIZE][BOARD_SIZE] , int x, int y ) {
		
	if (board[y][x] != '.')	return 0 ;
	if ( y >= BOARD_SIZE || y < 0 || x >= BOARD_SIZE || x < 0 ) return 0 ;	
	
	if (y+1 < BOARD_SIZE) {
		if (x+1 < BOARD_SIZE) {
			if(board[y+1][x+1] == 'X' || board[y+1][x+1] == 'O') return 1 ;
			if(board[y+1][x] == 'X' || board[y+1][x] == 'O') return 1 ;
		}
		if (x-1 >= 0) {
			if(board[y+1][x-1] == 'X' || board[y+1][x-1] == 'O') return 1 ;
		}
	}
	if (y-1 >= 0 ) {
		if (x+1 < BOARD_SIZE) {
			if(board[y-1][x+1] == 'X' || board[y-1][x+1] == 'O') return 1 ;
			if(board[y-1][x] == 'X' || board[y-1][x] == 'O') return 1 ;
		}
		if (x-1 >= 0) {
			if(board[y-1][x-1] == 'X' || board[y-1][x-1] == 'O') return 1 ;
		}
	}

	if ( x+1 < BOARD_SIZE && ( board[y][x+1] == 'X' || board[y][x+1] == 'O' ) ) return 1 ;
	if ( x-1 >= 0 && ( board[y][x-1] == 'X' || board[y][x-1] == 'O' ) ) return 1 ;

	return 0 ;
}



int is_over(char board[BOARD_SIZE][BOARD_SIZE]) {
	int ans = 1 ;

	int i, j ;
	for (i = 0 ; i< BOARD_SIZE ; i++ ) {
		for ( j = 0 ; j < BOARD_SIZE ; j++) {
			if (board[i][j] == '.' ) {
				ans = 0 ;
			} 

		}
	}
	if (ans == 1) {
		printf("Game over.\n") ;
	}
	return ans ;
	
}


void determine_winner(char board[BOARD_SIZE][BOARD_SIZE], int frequency[2]) {
	int i, j ;
	frequency[0] = 0 ;
	frequency[1] = 0 ;
	for (i = 0 ; i < BOARD_SIZE ; i++) {
		for (j = 0 ; j < BOARD_SIZE ; j++) {
			if (board[i][j] == 'X') {
				frequency[0]++ ;
			} else frequency[1]++ ;
		}
	}

	printf("You (Player X) have %d squares.  I (Player O) have %d squares. \n", frequency[0], frequency[1]) ;

	if (frequency[0] > frequency[1]) {
		printf("You win.\n") ;
	} else if (frequency[1] > frequency[0]) {
		printf("I win!\n") ;
	} else printf("Tie.\n") ;


}

void computer_move(char board[BOARD_SIZE][BOARD_SIZE]) {
	int x, y ;
	int retry = 1 ;
	srand( time(0) ) ;
	printf("...\n") ;
	while (retry) {
		x = rand()%BOARD_SIZE ;		//produces a random number within the range of the board
		y = rand()%BOARD_SIZE ;
		if (is_legal(board, x, y)) {
			retry = 0 ;
		}
	}
	sleep(1) ;
	printf("\nI choose:  %d %d\n\n", x, y) ;
	move(board, 'O', x, y) ;
}
