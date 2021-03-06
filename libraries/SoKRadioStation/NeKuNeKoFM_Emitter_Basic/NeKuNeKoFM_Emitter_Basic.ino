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
#include <ArduinoLowPower.h>
uint64_t previousMillis = 0;
uint64_t currentMillis  = 0;   
#define SLEEP_AFTER_MS  2000 // 10000, 10s

#include <Wire.h>
#include <Adafruit_Si4713.h>
#define _BV(n) (1 << n)

//#define SI471X_CMD_DEBUG
//#define RESETPIN D13 // SoK

 
#define RESETPIN FSC_IRQ // Kitten Syringe/Display 
//#define SI4713_I2CADDR 0x63
// */
//
#define SI4713_I2CADDR 0x11 // old
// */
 
#define BTTN_SEEK BTTN_INJECT // Kitten Syringe 2.0

#define ENABLE_SLEEP

#define FMSTATION 9800      // 10230 == 102.30 MHz

Adafruit_Si4713 radio = Adafruit_Si4713(RESETPIN);

void setup() 
{
  digitalWrite(RESETPIN, LOW);
  delay(500);
  digitalWrite(RESETPIN, HIGH);
  
  Serial.begin(115200); // 
  //while(!Serial); // wait until Arduino Serial Monitor is open */
  Serial.println("NeKuNeKo's SoK Radio Station - Si4713 Test");
  
  while (! radio.begin(SI4713_I2CADDR, &Wire)) {  // begin with address 0x63 (CS high)
    Serial.println("Couldn't find radio?");
    delay (1000);
  }

  // Show IC information
  radio.getRev();
  radio.setGPIOctrl(_BV(1) | _BV(2));  // set GP1 and GP2 to output
  radio.setGPIO(_BV(1) | _BV(2));      // turn ON Both leds
  uint8_t stat = radio.getStatus();
  Serial.print("status: 0x");
  Serial.println(stat, HEX); 
  
  /*/ Uncomment to scan power of entire range from 87.5 to 108.0 MHz
  for (uint16_t f  = 8750; f<10800; f+=10) {
   radio.readTuneMeasure(f);
   Serial.print("Measuring "); Serial.print(f); Serial.print("...");
   radio.readTuneStatus();
   Serial.println(radio.currNoiseLevel);
  } //*/
  
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
}



void loop() 
{    
  radio.readASQ();
  Serial.print("\tCurr ASQ: 0x"); 
  Serial.println(radio.currASQ, HEX);
  Serial.print("\tCurr InLevel:"); 
  Serial.println(radio.currInLevel);
  Serial.println();
  
  /*/ toggle GPO1 and GPO2
  radio.setGPIO(_BV(1));
  delay(500);
  radio.setGPIO(_BV(2));
  delay(500); //*/

  #ifdef ENABLE_SLEEP
  // Standby Mode
  currentMillis = millis(); 
  //Serial.print("Current: "); Serial.println((long) currentMillis);
  //Serial.print("Previous: "); Serial.println((long) previousMillis);
  if(currentMillis - previousMillis > SLEEP_AFTER_MS)
  {
    Serial.println("gotosleep");
    USBDevice.detach();
    
    LowPower.attachInterruptWakeup(BTTN_SEEK, [] (void) {}, CHANGE);
    LowPower.attachInterruptWakeup(FSP_IRQ,   [] (void) {}, CHANGE);
    // Triggers an infinite sleep (the device will be woken up only by the registered wakeup sources)
    // The power consumption of the chip will drop consistently
    //LowPower.idle(); // Ok, no apaga USB
    LowPower.sleep(); // Ok, apaga USB
    detachInterrupt(BTTN_SEEK);
    detachInterrupt(FSP_IRQ);
    
    USBDevice.attach();

    //myReceiver = IRrecvPCI(FSP_IRQ);
    //myReceiver.enableIRIn(); 
    
    previousMillis = millis();
  } //*/
#endif // ENABLE_SLEEP

}
