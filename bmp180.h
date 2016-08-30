#ifndef Bmp180_h
#define Bmp180_h

#include "Arduino.h"
#include "Wire.h"

// BMP180
class Bmp180
{
	public:
		Bmp180();
	private:
    // Calibration values
    int ac1;
    int ac2; 
    int ac3; 
    unsigned int ac4;
    unsigned int ac5;
    unsigned int ac6;
    int b1; 
    int b2;
    int mb;
    int mc;
    int md;
    // b5 is calculated in bmp085GetTemperature(...), this variable is also used in bmp085GetPressure(...)
    // so ...Temperature(...) must be called before ...Pressure(...).
    long b5; 
    unsigned char OSS;  // Oversampling Setting https://www.sparkfun.com/tutorial/Barometric/OSS-values.PNG

    int GetTemperature(unsigned int ut);
    long GetPressure(unsigned long up);
    unsigned int ReadUT();
    unsigned long ReadUP();
    int ReadInt(unsigned char address);
	public:
    int Temperature();
    long Pressure();
    void Calibration();
};

#endif
