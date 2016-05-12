#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <errno.h>
#include "wavfile.h"

const int TOTAL_SAMPLES = (WAVFILE_SAMPLES_PER_SECOND*2) ;	//length of longest possible note

//function prototypes
double letters_to_frequency (char c) ;
void update_waveform(short waveform[], int maxvolume, double frequency, int notelength, FILE *f) ;
float change_octave(char c) ;
int determine_change_type(char c) ;
float new_notelength(char c) ;
void insert_rest(short waveform[], int notelength, FILE *f) ;
double triangle_waveform (double freq, double amp, double t) ;
int adjust_volume(int maxv, double t, int nl) ;


//begin main
int main (void) {

	short waveform [TOTAL_SAMPLES] ;
	FILE *f ;
	f = wavfile_open("music.wav") ;
	if(!f) {
		printf("couldn't open music.wav for writing: %s",strerror(errno)) ;
		return 1 ;
	}

	char input ;
	float octavefactor = 1 ;
	float notelength = .5 * WAVFILE_SAMPLES_PER_SECOND ;		//quarter note is default note length
	double frequency ;
	printf("Please enter valid instructions for octaves, notes, rests, and their lengths.  Enter X for end of song.\n") ; 

	do {
		scanf(" %c", &input) ;
		if (input == 'X') break ;

		int change = determine_change_type(input) ;
		int volume = 30000 ;
		switch (change) {
			case 0:
				printf("Error. Invalid character entered. File was written ignoring this invalid data.\n") ;
				break ;

			case 1:	
				frequency = letters_to_frequency(input) * octavefactor ;
				update_waveform(waveform, volume, frequency, notelength, f) ;	//only updated when a note is read
				break ;		

			case 2: 
				octavefactor *= change_octave(input) ;
				break ;
	
			case 3:
				notelength = new_notelength(input)*WAVFILE_SAMPLES_PER_SECOND ;
				break ;

			case 4:
				insert_rest(waveform, notelength, f) ;
		}
		
	} while (input != 'X' ) ;

	wavfile_close(f) ;

	return 0 ;
}



double letters_to_frequency (char c) {
	switch (c) {
		case 'a': return 415.30 ;
		case 'A': return 440.00 ;
		case 'b': return 466.16 ;
		case 'B': return 493.88 ;
		case 'C': return 523.25 ;
		case 'd': return 554.37 ;
		case 'D': return 587.33 ;
		case 'e': return 622.25 ;
		case 'E': return 659.26 ;
		case 'F': return 698.46 ;
		case 'g': return 739.99 ;
		case 'G': return 783.99 ;
	}
	return 0 ;

}


void update_waveform(short waveform[], int maxvolume, double frequency, int notelength, FILE *f) {
	int i ;
	int volume ;
	float t ;
	for ( i = 0 ; i < notelength ; i++) {
		t = (float) i / WAVFILE_SAMPLES_PER_SECOND ;
		volume = maxvolume ;
		//volume = adjust_volume(maxvolume, t, notelength) ;  //not used in the final program because it will not produce sound
		waveform[i] = triangle_waveform(frequency, .4*volume, t) + triangle_waveform(2*frequency, .2*volume, t) + triangle_waveform(4*frequency, .6*volume, t) ;
	}
	wavfile_write(f, waveform, notelength) ;
}


//piecewise function to vary the volume during notes
int adjust_volume(int maxv, double t, int nl) {
		
	if (t < nl/6) {				//attack
		double yint = 0 ;
		double m = 6*maxv / nl ;
		return m*t + yint ;
	}else if (t < nl/3) {			//decay
		double m = -(3*maxv)/(nl) ;
		double yint = maxv - m*nl/6 ;
		return m*t + yint ;
	}else if (t < 5*nl/6) {			//sustain
		return maxv/2 ;
	}else {					//release
		double m = -(2*maxv)/(nl) ;
		double yint = 2*maxv/3 - m*(5*nl/6) ;
		return m*t + yint ;
	}
}


float change_octave(char c) {
	if (c == '-') return .5 ;
	else return 2 ;
}


int determine_change_type(char c) {
	switch (c) {
		case 'a':
		case 'A':
		case 'b':
		case 'B':
		case 'C':
		case 'd':
		case 'D':
		case 'e':
		case 'E':
		case 'F':
		case 'g':
		case 'G':
			return 1 ;	//corresponds to calling letters_to_frequency in main
		case '+':
		case '-':
			return 2 ;	//corresponds to calling change_octave in main
		case '1':
		case '2':
		case '4':
		case '8':
		case '6':
			return 3 ;	//corresponds to calling change_notelength in main
		case '.':  return 4 ;	//corresponds to a rest		
		default :
			return 0 ;	//prints error message in main
	}

}


float new_notelength(char c) {
	switch(c) {
		case '1':  return 2 ;
		case '2':  return 1 ;
		case '4':  return .5 ;
		case '8':  return .25 ;
		case '6':  return .125 ;
	}

}


void insert_rest(short waveform[], int notelength, FILE *f) {
	int i ;
	for ( i = 0 ; i < notelength ; i++) {
		waveform[i] = 0 ;
	}
	wavfile_write(f, waveform, notelength) ;
}



double triangle_waveform (double freq, double amp, double t) {
	double period = 1/freq ;
	double m1 = 4*amp / period ;	//slope of first quarter of the wave
	double yint1 = 0 ; 
	double m2 = -m1 ; 
	double yint2 = 2*amp ;
	double m3 = m1 ;
	double yint3 = -4*amp ;
	if (t >= 0){
		while (t >= 0) {
			t -= period ;
		}
		t += period ;		//gives t within the first wavelength
	} else {
		while (t < 0) {
			t += period ;
		}
	}
	
	if (t <= period/4) {
		return (m1*t+yint1) ;
	} else if (t <= period*3/4) {
		return (m2*t+yint2) ;
	} else return (m3*t+yint3) ;

}
