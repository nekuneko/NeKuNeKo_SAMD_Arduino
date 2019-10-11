#include <Arduino.h>
#include <Adafruit_ZeroI2S.h>
#include <Adafruit_ZeroDMA.h>

/* create a buffer for both the left and right channel data */
#define BUFSIZE 128
int32_t left[BUFSIZE];
int32_t right[BUFSIZE];


// Uncoment the desired option
// Adafruit_ZeroI2S i2s(FS_PIN, SCK_PIN, TX_PIN, RX_PIN); 

  // SOK M4 I2S0 (EXTERNAL)
  Adafruit_ZeroI2S i2s; // */
  
  /*/ SOK ZERO I2S0 (INTERNAL) (INPUT) **DOESN'T WORK**
  Adafruit_ZeroI2S i2s(PIN_I2S_FS, PIN_I2S_SCK, PIN_I2S_SD, PIN_I2S_SD);  //*/
  
  /*/ SOK ZERO I2S0 (EXTERNAL) (INPUT/OUTPUT) **DOESN'T WORK**
  Adafruit_ZeroI2S i2s(PIN_I2S1_FS, PIN_I2S1_SCK, PIN_I2S1_SD, PIN_I2S1_SD); //*/
  
  /*/ SOK ZERO I2S1 (EXTERNAL) (INPUT/OUTPUT) **DOESN'T WORK**
  Adafruit_ZeroI2S i2s(D9, D8, D6, D6); //*/

  /*/ SOK DARK I2S0 (INTERNAL) (INPUT only)
  Adafruit_ZeroI2S i2s(PIN_I2S_FS, PIN_I2S_SCK, PIN_I2S_SDI, PIN_I2S_SDO); //*/

  /*/ SOK DARK I2S0 (EXTERNAL) 
  Adafruit_ZeroI2S i2s(PIN_I2S1_FS, PIN_I2S1_SCK, PIN_I2S1_SDO, PIN_I2S1_SDI);  //*/
  
  /*/ SOK DARK I2S1 (EXTERNAL) **DOESN'T WORK**
  Adafruit_ZeroI2S i2s(D9, D8, PIN_I2S1_SDO, PIN_I2S1_SDI); //*/


void setup()
{
  Serial.begin(115200);
  while(!Serial);
  Serial.println("amplitudeZeroI2S");
  i2s.begin(I2S_24_BIT, 44100);
  i2s.enableRx();
}

void loop()
{
  /* write the output buffers
   * note that i2s.write() will block until both channels are written.
   */
  // if (i2s.rxReady())
   {
    i2s.read(&left[0], &right[0]);
    if (left[0] != -1)
      if (left[0] != 0)
        if (left[0] < 60000)
          Serial.println(String(left[0]));
    if (right[0] != -1)
      if (right[0] != 0)
        if (right[0] < 60000)
          Serial.println(String(right[0]));
   }
}
