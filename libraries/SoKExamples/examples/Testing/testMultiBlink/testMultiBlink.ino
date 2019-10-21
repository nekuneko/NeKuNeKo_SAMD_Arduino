// Test Blink on every GPIO on SoK boards

#define DELAY_MS 1000

// Testing pins
const int NUMPINS = 31;
const int testPins [NUMPINS] = {  0,  1,  2,  3,  4,  5,  6,  7,  8,  9, 10, 11, 12, 13, LED_BUILTIN,
                                 A0, A1, A2, A3, A4, A5, A6, A7, A8, A9, SOK, MISO, MOSI, SCK,
                                SCL, SDA }; // */

// Note: D14 (LED_BUILTIN) is active LOW.

void setup() 
{
  // Configure pins as OUTPUT
  for(int i=0; i<NUMPINS; ++i)
    pinMode(testPins[i], OUTPUT);
}

void loop() 
{
  for(int i=0; i<NUMPINS; ++i)
    digitalWrite(testPins[i], HIGH);
  delay(DELAY_MS);
  
  for(int i=0; i<NUMPINS; ++i)
    digitalWrite(testPins[i], LOW);
  delay(DELAY_MS);   
}
