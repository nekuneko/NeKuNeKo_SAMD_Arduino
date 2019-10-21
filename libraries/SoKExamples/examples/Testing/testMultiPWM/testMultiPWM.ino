// Test PWM on SoK devices

#define ADC_RESOLUTION 8    // 8      10      16
#define PWM_RESOLUTION 255  // 255    1023    65535
#define FADE_VALUE     5    // 5      50      500

// PWM Pins
const int NUMPINS = 26;
const int testPins [NUMPINS] = {  0,  1,  2,  3,  4,  5,  6,  7,  8,  9, 10, 11, 12, 13, LED_BUILTIN,
                                 A0, A1, A2, A3, A4, A7, MISO, MOSI, SCK, SCL, SDA }; // */

// Note:
// SoK Zero Dawn:  
//    MISO uses the same timer as D2
//    MOSI uses the same timer as D3
//    A4 is DAC (10 bits).
// 
// SoK M4 Advance: 
//    Doesn't have PWM on A0, A1, A3. 
//    A4 & D1 are DAC0 & DAC1 (10 bits), SOK (AREF) need to be connected to 3.3V in order to make DAC work.

void setup() {
  analogWriteResolution(ADC_RESOLUTION);
}

void loop() {
  // fade in from min to max in increments of 5 points:
  for (int fadeValue = 0 ; fadeValue <= PWM_RESOLUTION; fadeValue += FADE_VALUE) {
    // sets the value (range from 0 to 255):
    for(int i=0; i<NUMPINS; ++i)
      analogWrite(testPins[i], fadeValue);
    // wait for 30 milliseconds to see the dimming effect
    delay(30);
  }

  // fade out from max to min in increments of 5 points:
  for (int fadeValue = PWM_RESOLUTION ; fadeValue >= 0; fadeValue -= FADE_VALUE) {
    // sets the value (range from 0 to 255):
    for(int i=0; i<NUMPINS; ++i)
      analogWrite(testPins[i], fadeValue);
    // wait for 30 milliseconds to see the dimming effect
    delay(30);
  }
}
