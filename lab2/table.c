#include <stdio.h>

int main(void) {
	
	int x ;
	int y ;
	printf ("Type number of columns desired: ") ;
	scanf ("%d", &x) ;
	printf ("Type number of rows desired: ") ;
	scanf ("%d", &y) ;

	int xi = 1 ;
	int yi = 1 ;
	int value ;
	printf( "   *" );
	
	while (xi <= x) {
		printf("%4d", xi);
		xi++;
	}			//prints first line of table
	printf("\n");
		
	while (yi <= y) {
		xi = 1;		//resets value of xi for next row
		printf("\n%4d", yi);
		while (xi <= x) {
			value = yi*xi ; 	//current row*current column
			printf("%4d", value) ;
			xi++ ;
		}
		printf("\n") ;
		yi++ ;
	}
	

	return 0;
}
