#include "sokdetector.h"

int calculateAnalogValue (float VIN, float R1, float R2, int adcResolution)
{
  float vout = R2 / (R1+R2) * VIN;
  float aout = (vout * (pow(2, adcResolution)-1) / MAX_VOUT);
  
  return aout;
}

// returns 
//  0 - unknown
//  1 - Game SoK
//  2 - Drive SoK 
int determineBoard (int pin, int adcResolution)
{
  //analogReadResolution(adcResolution);
  //pinMode(pin, INPUT);
  //delay(1000);

  int ANALOG_GAMESOK  = calculateAnalogValue(3.3, RESISTANCE_MAIN, RESISTANCE_GAMESOK,  adcResolution);
  int ANALOG_DRIVESOK = calculateAnalogValue(5, RESISTANCE_MAIN, RESISTANCE_DRIVESOK, adcResolution);

  // Read detected analog value
  int analog=0;
  for (int i=1; i<=10; ++i)
    analog += analogRead(pin);
  analog /= 10;

/*
  SerialUSB.begin(115200);
  SerialUSB.println("A_GAME: " + String(ANALOG_GAMESOK));
  SerialUSB.println("A_DRIV: " + String(ANALOG_DRIVESOK));
  SerialUSB.println("ANALOG: " + String(analog)); 
*/
  if (ANALOG_GAMESOK-DEVIATION <= analog && analog <= ANALOG_GAMESOK+DEVIATION)
    return 1;
  else if (ANALOG_DRIVESOK-DEVIATION <= analog && analog <= ANALOG_DRIVESOK+DEVIATION)
    return 2;
  else 
    return 0;
}