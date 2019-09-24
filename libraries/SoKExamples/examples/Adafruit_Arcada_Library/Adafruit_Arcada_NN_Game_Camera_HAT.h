#if defined(_VARIANT_SOK_M4_ADVANCE_)

  #include <Adafruit_LIS3DH.h>
  #include <Adafruit_ST7735.h>

  #define ARCADA_TFT_SPI         SPI
  #define ARCADA_TFT_CS          A8       // Display CS Arduino pin number
  #define ARCADA_TFT_DC          A9       // Display D/C Arduino pin number
  #define ARCADA_TFT_RST         PIN_NOT_CONNECTED       // Display reset Arduino pin number
  #define ARCADA_TFT_LITE        PIN_NOT_CONNECTED
  #define ARCADA_TFT_ROTATION     1
  #define ARCADA_TFT_DEFAULTFILL  0xFFFF
  #define ARCADA_TFT_WIDTH        160
  #define ARCADA_TFT_HEIGHT       128

  #define ARCADA_AUDIO_OUT       A0/*
  #define ARCADA_BUTTON_CLOCK    PIN_NOT_CONNECTED
  #define ARCADA_BUTTON_DATA     PIN_NOT_CONNECTED
  #define ARCADA_BUTTON_LATCH    PIN_NOT_CONNECTED
  #define ARCADA_BUTTON_SHIFTMASK_B           0x80
  #define ARCADA_BUTTON_SHIFTMASK_A           0x40
  #define ARCADA_BUTTON_SHIFTMASK_START       0x20
  #define ARCADA_BUTTON_SHIFTMASK_SELECT      0x10 */

  #define ARCADA_BUTTONPIN_L      12
  #define ARCADA_BUTTONPIN_R      A4
  #define ARCADA_BUTTONPIN_A      A6
  #define ARCADA_BUTTONPIN_B      A5
  #define ARCADA_BUTTONPIN_C      PIN_NOT_CONNECTED
  #define ARCADA_BUTTONPIN_START  11
  #define ARCADA_BUTTONPIN_SELECT 13

  #define ARCADA_BUTTONPIN_UP     A2
  #define ARCADA_BUTTONPIN_DOWN    2
  #define ARCADA_BUTTONPIN_LEFT   10
  #define ARCADA_BUTTONPIN_RIGHT   7
  #define ARCADA_BUTTONPIN_PRESS  A3

  #define ARCADA_LIGHT_SENSOR             PIN_NOT_CONNECTED

  #define ARCADA_RIGHT_AUDIO_PIN          A0
  #define ARCADA_LEFT_AUDIO_PIN           A1

  #define ARCADA_SD_CS                    PIN_NOT_CONNECTED

  #define ARCADA_USE_JSON

  #define ARCADA_CALLBACKTIMER               4
  #define ARCADA_CALLBACKTIMER_HANDLER       TC4_Handler
  #include "arcadatype.h"

class Adafruit_Arcada : public Adafruit_Arcada_SPITFT {
 public:
  Adafruit_LIS3DH accel = Adafruit_LIS3DH();
  
  Adafruit_Arcada(void) {
    _has_accel = true;
  };

  bool variantBegin(void) {
    if (! accel.begin(0x18) && ! accel.begin(0x19)) {
      return false;  // couldn't find accelerometer
    }
    accel.setRange(LIS3DH_RANGE_4_G);   // 2, 4, 8 or 16 G!
    return true;
  }

  uint32_t variantReadButtons(void) { return 0; }
  
  void displayBegin(void) {
    Adafruit_ST7735 *tft = new Adafruit_ST7735(&ARCADA_TFT_SPI, ARCADA_TFT_CS, ARCADA_TFT_DC, ARCADA_TFT_RST); 
    tft->initR(INITR_BLACKTAB);
    tft->setRotation(ARCADA_TFT_ROTATION);
    tft->fillScreen(ARCADA_TFT_DEFAULTFILL);
    display = tft;
  }
};

#endif
