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
#include <Adafruit_Si4713.h>
#define _BV(n) (1 << n)

#define RESETPIN SOK

#define FMSTATION 10230      // 10230 == 102.30 MHz

Adafruit_Si4713 radio = Adafruit_Si4713(RESETPIN);

bool isAlive ()
{
  Wire.beginTransmission(0x11);
  byte error = Wire.endTransmission();

  if (error)
    return false;
  else 
    return true;
}


void setup() {
  Serial.begin(9600);
  while(!Serial); // wait until Arduino Serial Monitor is open
  Serial.println("NeKuNeKo's SoK Radio Station - Si4713 Test");

  while (! radio.begin(0x11)) {  // begin with address 0x11 (CS low)
    Serial.println("Couldn't find radio?");
    delay (1000);
  }

  /*/ Uncomment to scan power of entire range from 87.5 to 108.0 MHz
  
  for (uint16_t f  = 8750; f<10800; f+=10) {
   radio.readTuneMeasure(f);
   Serial.print("Measuring "); Serial.print(f); Serial.print("...");
   radio.readTuneStatus();
   Serial.println(radio.currNoiseLevel);
   }
   */

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

  Serial.println("RDS on!");  

  radio.setGPIOctrl(_BV(1) | _BV(2));  // set GP1 and GP2 to output
}



void loop() {
  if (!isAlive())
    Serial.println("CONNECTION LOST WITH FM TRANSMITTER");
    
  radio.readASQ();
  Serial.print("\tCurr ASQ: 0x"); 
  Serial.println(radio.currASQ, HEX);
  Serial.print("\tCurr InLevel:"); 
  Serial.println(radio.currInLevel);
  // toggle GPO1 and GPO2
  radio.setGPIO(_BV(1));
  delay(500);
  radio.setGPIO(_BV(2));
  delay(500);
}
