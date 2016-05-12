#include <stdio.h>
#include <math.h>

int main(void) {
	printf("The following is a plot of y = 1.5*x*cos(1.5^x)+15 from x = 2.0 to x = 8.0)\n");
	
	float x , ycalculated, y, ymax, ymin, xmin, xmax;

	printf("    x     y \n") ;	//prints first line of table

	ymax = 1.5 * 2.0 * cos( pow (1.5, 2.0) ) + 9 ;
	ymin = ymax ;		//initial values for comparing max and min
	for ( x = 2.0; x < 8.05; x += 0.05 ) {
		printf("%5.2f ", x) ;
		
		ycalculated = 1.5 * x * cos( pow (1.5, x) ) + 15.0 ;
		printf("%5.2f ", ycalculated) ;
		
		if (ycalculated > ymax) {
			ymax = ycalculated ; 
			xmax = x ;	//x location of max
		}

		if (ycalculated < ymin) {
			ymin = ycalculated ;
			xmin = x;	//x location of min
		}	
		
		y = ycalculated ;
		for ( ; y >= 0 ; y-= 1 ) {
			printf("#");	//prints a # for the whole number portion of y
		}
		printf("\n");
	}
	
	printf("The minimum value is %.2f at x = %.2f.\n", ymin, xmin);
	printf("The maximum value is %.2f at x = %.2f.\n", ymax, xmax);
	

	return 0;
}
