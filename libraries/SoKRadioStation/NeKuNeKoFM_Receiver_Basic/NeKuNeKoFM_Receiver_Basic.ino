/*************************************************** 
  This is an example for the Si4713 FM Radio Transmitter with RDS

  Designed specifically to work with the NeKuNeKo's SoK Radio Station 
  based on Si4713 breakout in the adafruit shop
  ----> https://www.adafruit.com/products/1958

  These transmitters use I2C to communicate, plus reset pin. 
  3 pins are required to interface
  Adafruit invests time and resources providing this open source code, 
  please support Adafruit and open-source hardware by purchasing 
  products from Adafruit!

  Written by Limor Fried/Ladyada for Adafruit Industries. 
  Modified by NeKuNeKo. 
  BSD license, all text above must be included in any redistribution

  Many thx to https://github.com/phrm/fmtx/blob/master/firmware/firmware.ino !

 ****************************************************/

#include <Wire.h>
#include <Adafruit_Si4705.h>

#define _BV(n) (1 << n)

//#define SI470X_CMD_DEBUG
//#define RESETPIN D13 // SoK
//#define RESETPIN D10 // Kitten Syringe
#define RESETPIN D4  // Kitten Display

//#define BTTN_SEEK D1 // Kitten Syringe
#define BTTN_SEEK D5 // Kitten Display
#define FMSTATION  8770//8940 //10230  // 10230 == 102.30 MHz // Range is: 8750-10790
uint16_t currFreq;
Adafruit_Si4705 radio = Adafruit_Si4705(RESETPIN);

#include <Adafruit_NeoPixel.h>
Adafruit_NeoPixel neopixel(1, D8, NEO_GRB + NEO_KHZ800);
void setup() 
{
    neopixel.begin();           // INITIALIZE NeoPixel strip object (REQUIRED)
  neopixel.setBrightness(0); // Set BRIGHTNESS to about 1/5 (max = 255)
  neopixel.setPixelColor(0, 0, 0, 0); // red, green, blue
  neopixel.show();            // Turn OFF all pixels ASAP
  
  Serial.begin(115200); /*/ 
  while(!Serial); // wait until Arduino Serial Monitor is open */
  Serial.println("NeKuNeKo's SoK Radio Station - Si4705 Test");
  while (! radio.begin(0x11, &Wire)) {  // begin with address 0x11
    Serial.println("Couldn't find radio?");
    delay (1000);
  }

  
  // Show IC information
  //radio.getRev();
  radio.setGPIOctrl(_BV(1) | _BV(2));  // set GP1 and GP2 to output
  //radio.setGPIO(_BV(1) | _BV(2));      // turn ON Both leds
  //radio.readTuneStatus();
  radio.getProperty(SI4705_PROP_GPO_IEN);
  radio.getProperty(SI4705_PROP_REFCLK_FREQ);
  radio.getProperty(SI4705_PROP_REFCLK_PRESCALE);
  radio.getProperty(SI4705_PROP_FM_ANTENNA_INPUT);
  //radio.tuneFM(FMSTATION);
  radio.startSeek();
  radio.readTuneStatus();
  currFreq = radio.currFreq;
  Serial.print("Freq: "); Serial.print(radio.currFreq); Serial.println(" kHz");
  /*/ Uncomment to scan power of entire range from 87.5 to 108.0 MHz
  for (uint16_t f  = 8750; f<10800; f+=10) {
   radio.readTuneMeasure(f);
   Serial.print("Measuring "); Serial.print(f); Serial.print("...");
   radio.readTuneStatus();
   Serial.println(radio.currNoiseLevel);
  } //*/
  /*
  Serial.print("\nSet TX power");
  radio.setTXpower(115);  // dBuV, 88-115 max

  Serial.print("\nTuning into "); 
  Serial.print(FMSTATION/100); 
  Serial.print('.'); 
  Serial.println(FMSTATION % 100);
  radio.tuneFM(FMSTATION); // 102.3 mhz

  // This will tell you the status in case you want to read it from the chip
  radio.readTuneStatus();
  Serial.print("\tCurr freq: "); 
  Serial.println(radio.currFreq);
  Serial.print("\tCurr freqdBuV:"); 
  Serial.println(radio.currdBuV);
  Serial.print("\tCurr ANTcap:"); 
  Serial.println(radio.currAntCap);

  // begin the RDS/RDBS transmission
  radio.beginRDS();
  radio.setRDSstation("NeKu FM");
  radio.setRDSbuffer( "NeKuNeKo's SoK Radio Station");
*/

  pinMode(BTTN_SEEK, INPUT_PULLUP);
}



void loop() 
{    

  if(digitalRead(BTTN_SEEK) == LOW)
  {
    radio.startSeek();
    delay(500);
  }
  /*
  radio.readRSQ();
  Serial.print("\tCurr ASQ: 0x"); 
  Serial.println(radio.currRSQ, HEX);
  Serial.print("\tCurr RSSI:"); 
  Serial.println(radio.currRSSI);
  Serial.println();
  */
  radio.readTuneStatus();
  if (currFreq != radio.currFreq) {
    currFreq = radio.currFreq;
    Serial.print("Freq: "); Serial.print(radio.currFreq); Serial.println(" kHz");
  }
  /*/ toggle GPO1 and GPO2
  radio.setGPIO(_BV(1));
  delay(500);
  radio.setGPIO(_BV(2));
  delay(500); //*/
}
