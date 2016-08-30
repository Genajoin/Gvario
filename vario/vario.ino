#include "filter.h"
#include "Bmp180.h"
#include "Wire.h"                      //i2c library

#define DEBUG_PRINT 1
#define UART_SPEED 115200                //define serial transmision speed (9600,19200, etc...)

Filter F;
Bmp180 B;

int Temperature;
long pressure;
long Altitude;
long average_pressure;
int ap_count = 0;
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
  average_pressure =  B.Pressure();
}

  //********************************************** LOOP **************************************************************
void loop(void)
{
  pressure = B.Pressure();
  // altitude in cm
  Altitude = get_altitude();

  average_pressure = average_pressure *.9 + F.filter(pressure)*.1;
  
  if (millis() - tempo > 1000) {
    Temperature = B.Temperature();
    tempo=millis();
  }

#if DEBUG_PRINT
  if (millis() - tempo0 > 100) {
    Serial.print(pressure);
    Serial.print(";");
    Serial.print(Altitude);
    Serial.print(";");
    Serial.print(average_pressure);
    Serial.print(";");
//Serial.print(Temperature,DEC);      
  //  Serial.print(";");
    Serial.print(tempo);
//    Serial.print(";");
//    Serial.print(";");
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


