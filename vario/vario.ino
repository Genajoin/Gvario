#include "filter.h"
#include "Bmp180.h"
#include "Wire.h"                      //i2c library
#include <toneAC2.h>

#define DEBUG_PRINT 0
#define UART_SPEED 115200                //define serial transmision speed (9600,19200, etc...)
#define VARIO_LIFT 30
#define VARIO_SINK -150

Filter F;
Bmp180 B;

int Temperature;
long pressure;
long Altitude;
long average_pressure = 0;
unsigned long tempo, tempo0;



  //************************************************************************************************************

void setup()                // setup() function to setup all necessary parameters before we go to endless loop() function
{
#if DEBUG_PRINT
  Serial.begin(UART_SPEED);       // set up arduino serial port
#endif
  Wire.begin();             // lets init i2c protocol
  B.Calibration();
  B.Temperature();
}

  //********************************************** LOOP **************************************************************
void loop(void)
{
  pressure = B.Pressure();
  long Presure_ft = F.filter(pressure);
  average_pressure = average_pressure *.85 + Presure_ft*.15;

  if (average_pressure >1000) {
    average_pressure =1000;
  } else if (average_pressure <-1000) {
    average_pressure = -1000;
  } 

  if (average_pressure > VARIO_LIFT) {
    toneAC2(9,10,(1000 + (4 * average_pressure)),200,true);
  } else if (average_pressure < VARIO_SINK) {
    toneAC2(9,10,300 + (average_pressure>>2),200,true);
  } else {
    noToneAC2(); // Turn off toneAC2, can also use noToneAC2().
  }
  
  if (millis() - tempo > 1000) {
    Temperature = B.Temperature();
    tempo=millis();
  }

#if DEBUG_PRINT
  if (millis() - tempo0 > 100) {
    // altitude in cm
    long Altitude = get_altitude();
    Serial.print(pressure);
    Serial.print(";");
    Serial.print(average_pressure);
    Serial.print(";");
    Serial.print(Altitude);
    Serial.print(";");
    Serial.print(Temperature,DEC);      
    Serial.print(";");
    Serial.print(tempo);
    Serial.print(";");
    Serial.print(Presure_ft);
    Serial.println(";");
    
    tempo0 = millis();
  }
#endif

  
// ********************************************************  END LOOP  ****************************************************
}


long get_altitude()
{
  return 4433000 * (1 - pow(((float) pressure/101325), 0.190295));
}


