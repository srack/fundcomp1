#include <stdio.h>

int main(void)
{
	int td; //initializes variables
	int ep;
	int fg;
	int s;
	int total;

	printf("Enter number of touchdowns: ");
	scanf("%d", &td);

	printf("Enter number of extra points: ");
	scanf("%d", &ep);

	printf("Enter number of field goals: ");
	scanf("%d", &fg);

	printf("Enter number of safeties: ");
	scanf("%d", &s);

	total = 6*td + 1*ep + 3*fg + 2*s;

	printf("The total score is %d \n", total);

}
