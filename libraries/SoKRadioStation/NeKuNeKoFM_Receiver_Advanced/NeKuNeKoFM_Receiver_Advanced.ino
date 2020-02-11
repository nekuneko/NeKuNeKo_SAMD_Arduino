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

#include <Adafruit_GFX.h>    // Core graphics library
#include <Adafruit_ST7735.h> // Hardware-specific library for ST7735
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_Si4705.h>

#define _BV(n) (1 << n)


  // For the breakout board, you can use any 2 or 3 pins.
  // These pins will also work for the 1.8" TFT shield.
  #define TFT_CS        D10
  #define TFT_RST       SOK // Or set to -1 and connect to Arduino RESET pin
  #define TFT_DC        A0

// For 1.44" and 1.8" TFT with ST7735 use:
Adafruit_ST7735 tft = Adafruit_ST7735(&SPI1, TFT_CS, TFT_DC, TFT_RST);
  
//#define SI470X_CMD_DEBUG
//#define RESETPIN D13 // SoK
//#define RESETPIN D10 // Kitten Syringe
#define RESETPIN D4  // Kitten Display

//#define BTTN_SEEK D1 // Kitten Syringe
#define BTTN_SEEK_DOWN D0// Kitten Display
#define BTTN_SEEK_UP D5 // Kitten Display
#define BTTN_B D12 // Kitten Display
#define BTTN_A D13 // Kitten Display
#define FMSTATION  9990 //10410 //8940 //10230  // 10230 == 102.30 MHz // Range is: 8750-10790
uint16_t currFreq;
Adafruit_Si4705 radio = Adafruit_Si4705(RESETPIN);

#include <Adafruit_NeoPixel.h>
Adafruit_NeoPixel neopixel(1, D8, NEO_GRB + NEO_KHZ800);



void testdrawtext(char *text, uint8_t x, uint8_t y) {
  tft.setCursor(x, y);
  tft.setTextSize(2);
  tft.setTextColor(ST77XX_WHITE);
  tft.print(text);
}

int x, minX;
void setup() 
{
  neopixel.begin();           // INITIALIZE NeoPixel strip object (REQUIRED)
  neopixel.setBrightness(0); // Set BRIGHTNESS to about 1/5 (max = 255)
  neopixel.setPixelColor(0, 0, 0, 0); // red, green, blue
  neopixel.show();            // Turn OFF all pixels ASAP
  pinMode(DAC0, OUTPUT);
  digitalWrite(DAC0, LOW);
  tft.initR(INITR_MINI160x80);  // Init ST7735S mini display
  tft.fillScreen(ST77XX_BLACK);
  tft.invertDisplay(true);
  tft.setRotation(1);
  tft.enableTearing(true);
  tft.setTextWrap(false);
  testdrawtext("hola mundo!", 5, 5);
  
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
  radio.tuneFM(FMSTATION);
  //radio.startSeek();
  radio.readTuneStatus();
  currFreq = radio.currFreq;
  Serial.print("Freq: "); Serial.print(radio.currFreq); Serial.println(" kHz");
  tft.fillScreen(ST77XX_BLACK);
  String freq = String(radio.currFreq/100.0) + " kHz";
  testdrawtext((char*) freq.c_str(), 5, 5);
  
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

  pinMode(BTTN_SEEK_UP, INPUT_PULLUP);
  pinMode(BTTN_SEEK_DOWN, INPUT_PULLUP);
  pinMode(BTTN_A, INPUT_PULLUP);
  pinMode(BTTN_B, INPUT_PULLUP);

}

char message[] = "Hijo de puta, hay que decirlo mas";

void loop() 
{    

  if(digitalRead(BTTN_SEEK_UP) == LOW) {
    radio.startSeek(true);
    delay(500);
  }
  else if (digitalRead(BTTN_SEEK_DOWN) == LOW) {   
    radio.startSeek(false);
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
  radio.readRDSstatus();
  radio.updateRDS();
    
    String freq = String(radio.currFreq/100.0) + " kHz"; 
    String progServ  = String((const char*) radio.PS) + '\0';
    //String progServ  = String((const char*) radio.psDisplay);
    //String radioText = String((const char*) radio.RT);
    String radioText = String((const char*) radio.rtSimple);
    tft.fillScreen(ST77XX_BLACK);
    testdrawtext((char*) freq.c_str(),      0,  5);
    testdrawtext((char*) progServ.c_str(),  0, 25);
  //  testdrawtext((char*) radioText.c_str(), 0, 45);
  Serial.print("Emisora: 0x");
  for(int i=0; i<8; ++i) 
    Serial.print(radio.PS[i], HEX);
    //Serial.print(radio.psDisplay[i], HEX);
    //Serial.print((uint8_t) progServ.c_str()[i], HEX);
  Serial.println();

  Serial.print("RT: ");
  Serial.println(radioText);

 
  //
    minX = -12 * strlen((const char*) radio.rtSimple);
    tft.setCursor(x, 45);
    tft.setTextSize(2);
    tft.print(String((const char*) radio.rtSimple));
    x = x-4;
    if (x < minX)
      x  = tft.width(); //*/
    testdrawtext((char*) radio.decodePTYeurope(radio.RDSPTYcode).c_str(), 0, 65);
  if (currFreq != radio.currFreq) 
  {
    currFreq = radio.currFreq;
    /*
    String freq = String(radio.currFreq/100.0) + " kHz"; 
    String progServ  = String((const char*) radio.PS);
    String radioText = String((const char*) radio.RT); */
    Serial.print("Freq: "); Serial.print(radio.currFreq); Serial.println(" kHz");
    //Serial.println(radioText);

    tft.fillScreen(ST77XX_BLACK);
    testdrawtext((char*) freq.c_str(),      0,  5);
    testdrawtext((char*) progServ.c_str(),  0, 25);
    testdrawtext((char*) radioText.c_str(), 0, 45);
    testdrawtext((char*) radio.decodePTYeurope(radio.RDSPTYcode).c_str(), 0, 65);
    //loopText(message);
  }

  progServ = "";
  /*
  tft.setCursor(radio.RTindex*12, 65);
  //tft.fillScreen(ST77XX_BLACK);
  //tft.setCursor(0, 65);
  //tft.print((const char* ) radio.PS);
  tft.print(String((const char*) radio.PS[radio.PSindex]));
  */
 

  
  
  
  
  
  /*/ toggle GPO1 and GPO2
  radio.setGPIO(_BV(1));
  delay(500);
  radio.setGPIO(_BV(2));
  delay(500); //*/
}
