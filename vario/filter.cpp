#include "Arduino.h"
#include "filter.h"

#define FILTER_INTEGER_FACTOR	100
#define DERIVATED_PA_TO_MS_COEF	12


//// feed-forward coefficients
//#define B_0  	28
//#define B_1  	0
//#define B_2  	-28
//// feed-back coefficients,
//#define A_0 	1000
//#define A_1  	-1945
//#define A_2  	945


// feed-forward coefficients
#define B_0    251
#define B_1   0
#define B_2   -251
// feed-back coefficients,
#define A_0   2048
#define A_1   -3576
#define A_2   1547

//Low pass butterworth filter order=1 alpha1=0.004 
Filter::Filter()
{
      x_1=0; 
      x_2=0; 
      y_1=0; 
      y_2=0;
}

long Filter::filter(long x_0)
{
	int32_t y_0;
	long Vz;
	x_0 = x_0 * FILTER_INTEGER_FACTOR;
	y_0 = ((long)B_0*x_0) + ((long)B_1*x_1) + ((long)B_2*x_2)	- ((long)A_1*y_1) - ((long)A_2*y_2);
	x_2 = x_1;
	x_1 = x_0;

	y_2 = y_1;
	y_1 = (long)(y_0/(long)A_0);

	Vz = ((long)(-y_1/((long)FILTER_INTEGER_FACTOR/(long)DERIVATED_PA_TO_MS_COEF)));
	return Vz;

}
