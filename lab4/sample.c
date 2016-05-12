#include <stdio.h>
#include <math.h>


float compute_taylor(int n , float x) {
	int term = 0, bfact, b, c ;	
	float ans = 0;
	
	float ans1, ans2;
	
	for (term ; term <= n ; term++) {
		b = 1 + 2*term ;
		bfact = 1;
		//calculate b factorial
		c = b;		
		for (c ; c > 1 ; c--) {
			bfact *= c ;
		}		
		
		ans += pow(-1.0, term)*pow(x, b)/bfact;
	}
	return ans ;

}


int main(void) {
	float a = compute_taylor(0, 1);
	printf("a = %f\n", a) ;
}
