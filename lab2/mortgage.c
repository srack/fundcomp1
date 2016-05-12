#include <stdio.h>

int main (void) {
	
	float balance, payment, totalpayment = 0 ; 
	float interestr, interestrd, mir, interest; 
	int month = 0 , years , remmonth ;
	
	printf("Enter the principal ($): ") ;
	scanf("%f", &balance) ;

	printf("Enter the interest rate (%): ") ;
	scanf("%f", &interestr) ;
	while (interestr < 0) {
		printf("You cannot have a negative interest rate.\nEnter the interest rate (%): ");
		scanf("%f", &interestr) ;
	}
	interestrd = interestr/100 ; 	//puts interest in decimal form
	mir = interestrd/12 ; 		//calculates monthly interest rate

	printf("Enter desired monthly payment ($): ") ;
	scanf("%f", &payment) ;

	interest = mir * balance ;	//calculates first month's mortgage
	if (payment < interest) {
		printf("The desired payment is too small.  Your balance would increase each month.\n");
		return 0 ;
	}

	printf("Month    Payment    Interest      Balance\n") ;
	while (balance > 0) {
		month ++ ;
		printf("%3d     ", month);
		
		interest = mir * balance ;	//dollars of interest each month
	
		balance = balance + interest ;
		if (balance < payment) {
			payment = balance ;
		}
		balance = balance - payment ;
		
		printf("$%.2f     $%6.2f     $%9.2f \n", payment, interest, balance);     
		
		totalpayment = payment + totalpayment ;
	}
	
	years = month / 12 ;
	remmonth = month % 12 ;		//number of months after the years are determined 
	printf("You paid a total of $%.2f over %d years and %d months.\n", totalpayment, years, remmonth); 

	return 0;
}
