#include <cmath>
#include <iostream>
#include <time.h>

#define PI 3.14159
#define SAMPLE_RATE 8000

uint8_t tripleOscillator(int t, int f)
{
	int f0 = f;
	int f1 = f/2;
	int f2 = f;
	float osc0 = (sin(t*2*M_PI/SAMPLE_RATE*f));
	float osc1 = (sin(2*t*2*M_PI/SAMPLE_RATE*f));
	float osc2 = (sin(6*t*2*M_PI/SAMPLE_RATE*f));
	return (uint8_t)(127*((osc0+osc1+osc2)/6+0.5f));
}

int main()
{
   const double C=261.625565; // f of middle-C (hertz)

   for (int t=0;;t++)
	{
		std::cout << tripleOscillator(t,C);
	}
	

}
