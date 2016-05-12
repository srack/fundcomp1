//Mitchell Patin and Samantha Rack
//Nov 25 2013
//Lab 9
//This program creates a crossword puzzle that can be filled in by the user.



#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#define _GNU_SOURCE

#define BOARD_SIZE (15)

//FUNCTION PROTOTYPES
int get_words(char words[20][16]) ;
void string_upper(char *str);
int check_alpha(char *str) ;

int place_words(char words[20][16],char solved[BOARD_SIZE][BOARD_SIZE], int totalwords, int start[20][2], int orientation[20]) ;
void sort_words(char words[20][16], int totalwords) ;
int find_match(char words[16], int wordnumber, char solved[BOARD_SIZE][BOARD_SIZE], int start[20][2]) ;
int try_horizontal(char words[16], int wordnumber, char solved[BOARD_SIZE][BOARD_SIZE], int start[20][2]) ;
int try_vertical (char words[16], int wordnumber, char solved[BOARD_SIZE][BOARD_SIZE], int start[20][2]) ;
void place_horizontal(char words[16], char solved[BOARD_SIZE][BOARD_SIZE], int startx, int starty) ;
void place_vertical(char words[16], char solved[BOARD_SIZE][BOARD_SIZE], int startx, int starty) ;

void print_words(char words[20][16], int totalwords) ;
void blank_board(char solved[BOARD_SIZE][BOARD_SIZE], char unsolved[BOARD_SIZE][BOARD_SIZE]) ;
void print_board(char board[BOARD_SIZE][BOARD_SIZE]) ;
void initialize_board(char board[BOARD_SIZE][BOARD_SIZE], char c) ; 

void make_clues(char words[20][16], int totalwords, char clues[20][16]) ;
void print_clues(char clues[20][16], int totalwords, int start[20][2], int orientation[20]) ;

//begin main
int main()
{
	char solved[BOARD_SIZE][BOARD_SIZE] ;
	char unsolved[BOARD_SIZE][BOARD_SIZE] ;
	char words[20][16] = { ' ' } ;			
	char clues[20][16] ;
	int i = 0 ;
	int totalwords ;
	int start[20][2] ; 	//records starting locations of each word, first column is x coordinate, second column is y coordinate
	int orientation[20] ;	//records if word is placed vertically (1) or horizontally (2) 
	int wordsplaced ; 

	//fill words array with user input
        totalwords = get_words(words);
      
                     
       	// place words
	initialize_board(solved,'.');

	printf("\n") ;
	wordsplaced = place_words(words, solved, totalwords, start, orientation) ;
	//print_words(words, totalwords) ;

	// print solved board
        printf("Solution:\n\n");
	print_board(solved);

	// blank out solved board
	blank_board(solved,unsolved);    

	//print unsolved board
	printf("Crossword Puzzle:\n\n");    
	print_board(unsolved);

	// make clues
	make_clues(words, wordsplaced, clues);
	printf("Clues:\n\n");
	print_clues(clues, wordsplaced, start, orientation) ;
}  //end main




//FUNCTION DEFINITIONS

//getting words functions
int get_words(char words[20][16]) {		//returns number of words entered
	int i=0,j=0;
	char str[16];
	printf("Enter a list of words:\n");
	char checkword[200] ;
	int notvalid = 1 ;
                                                                            
	while(i<20)
	{	
		
		while (notvalid) {
			scanf("%s",checkword);
			if (checkword[0] == '.') return i ;
			if(strlen(checkword) <= 15 && check_alpha(checkword)) break ;
			printf("String not valid, try again. \n") ;		
		}
		strcpy(str, checkword) ;
		string_upper(str);
		j = 0 ;
		do {
			words[i][j] = str[j] ;
			j ++ ;
		} while(str[j]!='\0') ;
		i++ ;
	}
	return i ;	
}

int check_alpha(char *str) {
	int i ;
	int alpha = 1 ;	
	for(i = 0 ; str[i] ; i++) {
		if (!isalpha(str[i])) return 0 ;
	}	
	return 1 ;
}


void string_upper(char *str) {
	int i;
	for(i = 0; str[i]; i++) {
		str[i] = toupper(str[i]);
	}
}



//placing words functions
int place_words(char words[20][16],char solved[BOARD_SIZE][BOARD_SIZE], int totalwords, int start[20][2], int orientation[20]) {
	int i ;	
	int wordsplaced = 1 ;
	sort_words(words, totalwords) ;	
	start[0][0] = 7 - strlen(words[0])/2 ;
	start[0][1] = 7 ;
	orientation[0] = 2 ;
	place_horizontal(words[0], solved, start[0][0], start[0][1]) ;		//places longest word
	for ( i = 1 ; i < totalwords ; i++) {
		orientation[i] = find_match(words[i], i, solved, start) ;	// =1 for vertical, =2 for horizontal, =0 for unplaceable
		switch(orientation[i]) {
			case 1:
				place_vertical(words[i], solved, start[i][0], start[i][1]) ;
				break ;
			case 2:
				place_horizontal(words[i], solved, start[i][0], start[i][1]) ;
				break ;
			case 0:
				printf("Error:  Not all words could be placed\n") ;
				return wordsplaced ;
		}
		wordsplaced++ ;
	}
	return wordsplaced ;	
}

void sort_words(char words[20][16], int totalwords) {
	int i , j ;
	char hold[16] ;
	//bubble sort
	for (i = 0 ; i < totalwords ; i++) {
		for (j = 0 ; j < totalwords-1 ; j++) {
			if ( strlen(words[j+1]) > strlen(words[j]) ) {
				strcpy(hold, words[j]) ;
				strcpy(words[j], words[j+1]) ;
				strcpy(words[j+1], hold) ;
			}
		}	
	}	
}

int find_match(char words[16], int wordnumber, char solved[BOARD_SIZE][BOARD_SIZE], int start[20][2]) {
	if(wordnumber % 2 == 1) {
		if ( try_vertical(words, wordnumber, solved, start) ) return 1 ;
		else if ( try_horizontal(words, wordnumber, solved, start) ) return 2 ;
		else return 0 ;	//word unable to be placed
	} else {
		if ( try_horizontal(words, wordnumber, solved, start) ) return 2 ;
		else if ( try_vertical(words, wordnumber, solved, start) ) return 1 ;
		else return 0 ;
	}
}


int try_horizontal(char words[16], int wordnumber, char solved[BOARD_SIZE][BOARD_SIZE], int start[20][2]) {
	int length = strlen(words) ;
	int i, j, k;
	int match = 0 ;
	for ( i = 0 ; i < BOARD_SIZE ; i++) {		//loop through y values
		for ( j = 0 ; j+length < BOARD_SIZE ; j++) {		//loop through x values
			if (solved[i][j] != words[0] && solved[i][j] != '.') continue ;
			if ( solved[i][j+length] != '.') continue ;
			if ( (j-1) >= 0 && solved[i][j-1] != '.') continue ;

			for ( k = 0 ; k < length ; k++) {
				if (solved[i][j+k] == words[k]) {
					start[wordnumber][0] = j ;
					start[wordnumber][1] = i ;
					match++ ;	//a horizontal match was found
					continue ;
				}
				if ((i+1) < BOARD_SIZE && solved[i+1][j+k] != '.') {	//checks for separation below
					match = 0 ;
					break ;
				}
				if((i-1) >= 0 && solved[i-1][j+k] != '.') {		//checks for separation above
					match = 0 ;
					break ;
				}
			}
			if (match == 1) return 1 ;
			match = 0 ;
		}
	}
	
	return 0 ;	//no match found
}

int try_vertical (char words[16], int wordnumber, char solved[BOARD_SIZE][BOARD_SIZE], int start[20][2]) {
	int length = strlen(words) ;
	int i, j, k ;
	int match = 0 ;
	for ( j = 0 ; j < BOARD_SIZE ; j++) {		//loop through x values
		for ( i = 0 ; i+length < BOARD_SIZE ; i++) {	//loop through y values
			if (solved[i][j] != words[0] && solved[i][j] != '.') continue ;
			if ( solved[i+length][j] != '.') continue ;
			if ( (i-1) >= 0 && solved[i-1][j] != '.') continue ;

			for ( k = 0 ; k < length ; k++) {
				if (solved[i+k][j] == words[k]) {
					start[wordnumber][0] = j ;
					start[wordnumber][1] = i ;
					match++ ;	//a vertical match was found
					continue ;
				}
				if((j+1) < BOARD_SIZE && solved[i+k][j+1] != '.') {	//checks for separation to right
					match = 0 ;
					break ;
				}
				if((j-1) >= 0 && solved[i+k][j-1] != '.') {
					match = 0 ;
					break ;
				}
			}
			if (match == 1) return 1 ;
			match = 0 ;
		}
	}
	return 0 ;	//no match found
}

void place_horizontal(char words[16], char solved[BOARD_SIZE][BOARD_SIZE], int startx, int starty) {
	int i ;
	for (i = 0 ; words[i] ; i++) {
		solved[starty][startx+i] = words[i] ;
	}

}

void place_vertical(char words[16], char solved[BOARD_SIZE][BOARD_SIZE], int startx, int starty) {
	int i ;
	for (i = 0 ; words[i] ; i++) {
		solved[starty+i][startx] = words[i] ;
	}
}


//print function
void print_words(char words[20][16], int totalwords) {		//for debugging sort_words
	int i;
	for(i = 0 ; i < totalwords ; i++) {
		printf("%s\n" , words[i]) ;
	}
}




//board functions
void print_board(char board[BOARD_SIZE][BOARD_SIZE]) 
{
	int i , j , k ;
	printf("   ") ;
	for (k = 0 ; k < BOARD_SIZE ; k++) {
		printf("%3d", k) ;
	}
	printf("\n") ;

	for (i = 0 ; i < BOARD_SIZE ; i++) {
		printf("%2d ", i ) ;
		for ( j = 0 ; j < BOARD_SIZE ; j++) {
			printf("%3c", board[i][j]) ;
		}
		printf("\n") ;
	}
	printf("\n") ;
} 

void initialize_board(char board[BOARD_SIZE][BOARD_SIZE], char c) 
{
	int i, j; 
	for (i = 0 ; i < BOARD_SIZE ; i++) {
		for (j = 0 ; j < BOARD_SIZE ; j++) {
			board[i][j] = c ;
		}
	}
}

void blank_board(char solved[BOARD_SIZE][BOARD_SIZE], char unsolved[BOARD_SIZE][BOARD_SIZE]) 
{
	int i , j ;
	for (i = 0 ; i < BOARD_SIZE ; i++) {
		for (j = 0 ; j < BOARD_SIZE ; j++) {
			if (solved[i][j] == '.') unsolved[i][j] = '#' ;
			else unsolved[i][j] = ' ' ;
		}
	}
}


//clues functions
void make_clues(char words[20][16], int totalwords, char clues[20][16]) {
	int i ;
	for (i = 0 ; i < totalwords ; i++) {
		strcpy(clues[i], words[i]) ;
		strfry(clues[i]) ;
	}
}

void print_clues(char clues[20][16], int totalwords, int start[20][2], int orientation[20]) {
	int i;
	for(i = 0 ; i < totalwords ; i++) {
		printf("%2d, %2d   ", start[i][0], start[i][1]) ;
		if (orientation[i] == 1) {
			printf("Vertical     ") ;
		} else {
			printf("Horizontal   ") ;
		}
		printf("%s\n", clues[i]) ;
	}
	printf("\n") ;
}



