#ifndef Filter_h
#define Filter_h

#include "Arduino.h"


//Low pass butterworth filter order=4 alpha1=0.004 
class Filter
{
	public:
		Filter();
	private:
     long  x_1;
     long  x_2;
     long  y_1;
     long  y_2;

	public:
		long filter(long x);
};

#endif
