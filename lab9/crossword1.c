#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>

#define BOARD_SIZE (15)

void string_upper(char *str);
int get_words(char words[20][16]);
void place_words(char words[20][16],char solved[BOARD_SIZE][BOARD_SIZE], int totalwords);
void blank_board(char solved[BOARD_SIZE][BOARD_SIZE], char unsolved[BOARD_SIZE][BOARD_SIZE]);
void print_board(char board[BOARD_SIZE][BOARD_SIZE]);
void make_clues(char words[20][16],char clues[20][16]);
void initialize_board(char board[BOARD_SIZE][BOARD_SIZE], char c); 
void sort_words(char words[20][16], int totalwords) ;
void print_words(char words[20][16], int totalwords) ;
void place_horizontal(char words[16], char solved[BOARD_SIZE][BOARD_SIZE], int startx, int starty)  ;
void place_vertical(char words[16], char solved[BOARD_SIZE][BOARD_SIZE], int startx, int starty) ;
void find_match(char words[16], char solved[BOARD_SIZE][BOARD_SIZE]) ;
int try_horizontal(char words[16], char solved[BOARD_SIZE][BOARD_SIZE], int startx, int starty) ;
int try_vertical(char words[16], char solved[BOARD_SIZE][BOARD_SIZE], int startx, int starty)

int main()
{
	char solved[BOARD_SIZE][BOARD_SIZE];
	char unsolved[BOARD_SIZE][BOARD_SIZE];
	char words[20][16] = { ' ' };			
	char clues[20][16];
	int i=0;
	int totalwords ;

	//fill words array with user input
        totalwords = get_words(words);
                                
       	// place words
	initialize_board(solved,'.');
	place_words(words, solved, totalwords);
	printf("\n") ;
	print_words(words, totalwords) ;
	printt("\n") ;

	// print solved board
        printf("Solution:\n\n");
	print_board(solved);

	// blank out solved board
	blank_board(solved,unsolved);    

	//print unsolved board
	printf("Crossword Puzzle:\n\n");    
	print_board(unsolved);

	// make clues
	//make_clues(words,clues);
	printf("Clues:\n\n");
}




//function definitions
int get_words(char words[20][16])		//returns number of words entered
{
	int i=0,j=0;
	char str[16];
	printf("Enter a list of words: ");
                                                                            
	while(i<20)
	{
		scanf("%15s",str);	

		if(str[0]=='.') return i ;

		string_upper(str);
		j = 0 ;
		do 
		{
			words[i][j] = str[j] ;
			j ++ ;
		} while(str[j]!='\0') ;
		i++ ;
	}
}

void string_upper(char *str)
{
	int i;
	for(i = 0; str[i]; i++)
	{
		str[i] = toupper(str[i]);
	}
}














void place_words(char words[20][16],char solved[BOARD_SIZE][BOARD_SIZE], int totalwords)
{
	int i ;	
	sort_words(words, totalwords) ;	
	int word1 = strlen(words[0]) ;
	int startx = 7 - word1/2 ;
	int starty = 7 ;
	place_horizontal(words[0], solved, startx, starty) ;		

	for ( i = 1 ; i < totalwords ; i++) {
		find_match(words[i], solved) ;
	}	

}

void find_match(char words[16], char solved[BOARD_SIZE][BOARD_SIZE]) 
{
	int i ;
	for (i = 0 ; words[i] ; i++)




}


int try_horizontal(char words[16], char solved[BOARD_SIZE][BOARD_SIZE], int startx, int starty)
{



}

int try_vertical (char words[16], char solved[BOARD_SIZE][BOARD_SIZE], int startx, int starty)
{



}

void place_horizontal(char words[16], char solved[BOARD_SIZE][BOARD_SIZE], int startx, int starty) 
{
	int i ;
	for (i = 0 ; words[i] ; i++)
	{
		solved[starty][startx+i] = words[i] ;
	}

}


void place_vertical(char words[16], char solved[BOARD_SIZE][BOARD_SIZE], int startx, int starty) 
{
	int i ;
	for (i = 0 ; words[i] ; i++)
	{
		solved[starty+i][startx] = words[i] ;
	}

}









void print_words(char words[20][16], int totalwords) {
	int i;
	for(i = 0 ; i < totalwords ; i++) {
		printf("%s\n" , words[i]) ;
	}
}



void sort_words(char words[20][16], int totalwords) 
{
	int i , j ;
	char hold[16] ;
	//bubble sort method
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



void initialize_board(char board[BOARD_SIZE][BOARD_SIZE], char c) 
{
	int i, j; 
	for (i = 0 ; i < BOARD_SIZE ; i++) {
		for (j = 0 ; j < BOARD_SIZE ; j++) {
			board[i][j] = c ;
		}
	}
}

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



/*void make_clues(char words[20][15], char clues[20][15])
{
	int i ;
	for (i = 0 ; i < 20 ; i++) {
		clues[i] = strfry(words[i]) ;
		//strcpy(clues[i], words[i] ;
		//strfry(clues[i] ;
		printf("%s\n", clues[i]) ;
	}
}*/





