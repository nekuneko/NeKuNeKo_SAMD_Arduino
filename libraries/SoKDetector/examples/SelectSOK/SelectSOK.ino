#include <sokdetector.h>

#define PIN_SOK_SELECTOR SOK
#define ADC_RESOLUTION 10
// #define ADC_RESOLUTION 12 

void setup() {
  Serial.begin(115200);
  while(!Serial);
  Serial.println("Test SoK Selector");
}

void loop() {
  // put your main code here, to run repeatedly:
  int board = determineBoard(PIN_SOK_SELECTOR, ADC_RESOLUTION);
  Serial.println("Board: " + String(board));
}
