#ifndef Filter_h
#define Filter_h

#include "Arduino.h"


//Low pass butterworth filter order=4 alpha1=0.004 
class Filter
{
	public:
		Filter();
	private:
		short v[5];
	public:
		short step(short x);
};

#endif
