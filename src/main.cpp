#include <cmath>
#include <iostream>
#include <time.h>

#define SAMPLE_RATE 8000

uint8_t tripleOscillator(int t, int f)
{
	// frequencies for each oscillator.
	// play around with them, it is fun.
	float f0 = f;
	float f1 = f*6/5;
	float f2 = f1*5/4;
	
	// oscillators
	float osc0 = (sin(t*2*M_PI/SAMPLE_RATE*f));
	float osc1 = (sin(t*2*M_PI/SAMPLE_RATE*f1));
	float osc2 = (sin(t*2*M_PI/SAMPLE_RATE*f2));

	// this does the following:
	//	adds the oscillators together
	//	divides them by three, to make the resulting wave as if it were the size of a single oscilator
	//	shitfs the wave up by one, because otherwise it would have negative portions.
	//	multiplies it, so that it takes up the entirety of the available space.
	return (uint8_t)(127*((osc0+osc1+osc2)/3+1));
}

int main()
{
   const double C=233.08; // f of middle-C (hertz)

   for (int t=0;;t++)
	{
		std::cout << tripleOscillator(t,C);
	}
}
