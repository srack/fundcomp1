#include <stdio.h>
#include <math.h>

int main ( void )
{
	printf("This program computes distance away a ball lands when thrown. \n");
	
	float armheight;
	float v;
	float angle;
	float omega;		// angle in radians
	float xv;		// x component of velocity
	float yv;		// y component of velocity
	float h;		// max height of the projectile with respect to the armheight 	
	float maxh;		// max height of the projectile with respect to the ground
	float t1;		// time taken to reach top of projectile
	float t2;		// time to reach the ground from top of projectile
	float a = 9.8;		// acceleration due to gravity (m/s/s)
	float ttotal;
	float d;		// horizontal distance traveled
	float pi = 3.14159;

	printf("Enter the height of the arm (m): ") ;
	scanf("%f", &armheight) ;
	if ( armheight < 0) {
		printf("Sorry, the arm height cannot be negative.\n") ;
		return 0 ;
	}

	printf("Enter the speed at which the ball was thrown (m/s): ") ;
	scanf("%f", &v) ;
	if ( v < 0) {
		printf("Sorry, the speed cannot be negative.\n") ;
		return 0 ;
	}
	
	printf("Enter the angle of elevation at which the ball was thrown (degrees): ") ;
	scanf("%f", &angle) ;
	if ( angle < 0) {
		printf("Sorry, the angle cannot be less than 0.") ;
		return 0 ;
	}
	if ( angle > 90) {
		printf("Sorry, the angle cannot be greater than 90.") ;
		return 0 ;
	}

	omega = angle * pi / 180 ;
	xv = v * cos(omega) ;
	yv = v * sin(omega) ;

	h = pow ( yv, 2) / (2 * a) ;
	maxh = h + armheight ;
	t1 = yv / a ; 
	t2 = sqrt ( 2 * maxh / a ) ;
	
	ttotal = t1 + t2 ;
	d = xv * ttotal ;

	printf( "The ball lands %f meters away from where it was thrown. \n" , d) ;
}
