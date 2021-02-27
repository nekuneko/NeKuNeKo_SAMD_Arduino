/*
  Keyboard logout

  This sketch demonstrates the Keyboard library.

  When you connect pin 2 to ground, it performs a logout.
  It uses keyboard combinations to do this, as follows:

  On Windows, CTRL-ALT-DEL followed by ALT-l
  On Ubuntu, CTRL-ALT-DEL, and ENTER
  On OSX, CMD-SHIFT-q

  To wake: Spacebar.

  Circuit:
  - Arduino Leonardo or Micro
  - wire to connect D2 to ground

  created 6 Mar 2012
  modified 27 Mar 2012
  by Tom Igoe

  This example is in the public domain.

  http://www.arduino.cc/en/Tutorial/KeyboardLogout
*/

#include "Keyboard.h"
#include <Adafruit_NeoPixel.h>

#define OSX 0
#define WINDOWS 1
#define UBUNTU 2

// change this to match your platform:
int platform = WINDOWS;

// Inject Button
// uint8_t BTTN_INJECT = A1; // Defined on Variant.h

// Neopixel
Adafruit_NeoPixel neopixel(1, D8, NEO_GRB + NEO_KHZ800);



void setup() {
  // make pin D1 an input and turn on the pull-up resistor so it goes high unless
  // connected to ground:
  pinMode(BTTN_INJECT, INPUT_PULLUP);
  Keyboard.begin();
  
  neopixel.begin();           // INITIALIZE NeoPixel strip object (REQUIRED)
  neopixel.setBrightness(10); // Set BRIGHTNESS to about 1/5 (max = 255)
  neopixel.show();            // Turn OFF all pixels ASAP
}

void loop() {
  while (digitalRead(BTTN_INJECT)) {
    // do nothing until pin 2 goes low
    neopixel.setPixelColor(0, 0, 0, 0); // red, green, blue
    neopixel.show();
    delay(5);
  }
  
  switch (platform) {
    case OSX:
      Keyboard.press(KEY_LEFT_GUI);
      // Shift-Q logs out:
      Keyboard.press(KEY_LEFT_SHIFT);
      Keyboard.press('Q'); // */
      delay(100);
      Keyboard.releaseAll();
      // enter:
      Keyboard.write(KEY_RETURN);
      brightNeopixel(255, 0, 0, 2000); // red, green, blue, waitMS
      break;
    case WINDOWS:
      /*/ CTRL-ALT-DEL:
      Keyboard.press(KEY_LEFT_CTRL);
      Keyboard.press(KEY_LEFT_ALT);
      Keyboard.press(KEY_DELETE);
      delay(100);
      Keyboard.releaseAll(); // */
      // CTRL-SHIFT-ESC:
      Keyboard.press(KEY_LEFT_CTRL);
      Keyboard.press(KEY_LEFT_SHIFT);
      Keyboard.press(KEY_ESC);
      delay(100);
      Keyboard.releaseAll(); // */
      /*/ ALT-F4:
      delay(2000);
      Keyboard.press(KEY_LEFT_ALT);
      Keyboard.press(KEY_F4);
      Keyboard.releaseAll(); // */
      brightNeopixel(0, 0, 255, 2000); // red, green, blue, waitMS
      break;
    case UBUNTU:
      // CTRL-ALT-DEL:
      Keyboard.press(KEY_LEFT_CTRL);
      Keyboard.press(KEY_LEFT_ALT);
      Keyboard.press(KEY_DELETE); // */
      delay(1000);
      Keyboard.releaseAll();
      // Enter to confirm logout:
      Keyboard.write(KEY_RETURN);
      brightNeopixel(0, 255, 0, 2000); // red, green, blue, waitMS
      break;
  }

  // do nothing:
  //while (true);
}

void brightNeopixel (uint8_t red, uint8_t green, uint8_t blue, uint32_t waitMS)
{
  neopixel.setPixelColor(0, red, green, blue); // red, green, blue
  neopixel.show();                         //  Update strip to match
  delay(waitMS);                           //  Pause for a moment
}
