#include "Arduino.h"
#include "filter.h"

//Low pass butterworth filter order=4 alpha1=0.004 
Filter::Filter()
    {
      for(int i=0; i <= 4; i++)
        v[i]=0;
    }
    
short Filter::step(short x)
{
      v[0] = v[1];
      v[1] = v[2];
      v[2] = v[3];
      v[3] = v[4];
      long tmp = ((((x *  13269L) >> 28)  //= (   2.4136223201e-8 * x)
        + ((v[0] * -15343L) >> 3) //+( -0.9364332432*v[0])
        + ((v[1] * 15594L) >> 1)  //+(  3.8072324572*v[1])
        + (v[2] * -11889L)  //+( -5.8051254211*v[2])
        + ((v[3] * 16115L) >> 1)  //+(  3.9343258208*v[3])
        )+1024) >> 11; // round and downshift fixed point /2048

      v[4]= (short)tmp;
      return (short)((/* xpart */
         (((v[0] + v[4]))<<9) /* 8192L (^2)*/
         + (((v[1] + v[3]))<<11) /* 8192L (^2)*/
         + (12288L * v[2])
        )+1024) >> 11; // round and downshift fixed point
}
