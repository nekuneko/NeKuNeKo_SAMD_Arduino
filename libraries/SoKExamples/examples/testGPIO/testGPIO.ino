
#define TESTING_PIN A5    // Analog: A0, A1, ... An; Digital; 0, 1, ... n; See variant.cpp.
#define ADC_RESOLUTION 10 // 12, 10, 8
#define DAC_RESOLUTION 12 // 12, 10, 8

// Input Mode: Please select only one:
#define INPUT_SETTING INPUT
//#define INPUT_SETTING INPUT_PULLUP

// PinMode Test: Please select only one:
#define TEST_ANALOG_INPUT
//#define TEST_DIGITAL_INPUT
//#define TEST_ANALOG_OUTPUT
//#define TEST_DIGITAL_OUTPUT

// Uncomment for Serial as USB
//#define SerialUSB Serial

void setup()
{
  /* Arduino SAMD Boards (Zero, etc.):
      - AR_DEFAULT: the default analog reference of 3.3V
      - AR_INTERNAL: a built-in 2.23V reference
      - AR_INTERNAL1V0: a built-in 1.0V reference
      - AR_INTERNAL1V65: a built-in 1.65V reference
      - AR_INTERNAL2V23: a built-in 2.23V reference
      - AR_EXTERNAL: the voltage applied to the AREF pin is used as the reference
   */
  // Analog Reference. Please select only one:
  analogReference(AR_DEFAULT);
  // analogReference(AR_INTERNAL);
  // analogReference(AR_INTERNAL1V0);
  // analogReference(AR_INTERNAL1V65);
  // analogReference(AR_INTERNAL2V23);
  // analogReference(AR_EXTERNAL);
  
  SerialUSB.begin(115200);
  while (!SerialUSB);
  SerialUSB.println("TEST GPIO BEGINS!");

  #ifdef __SAMD21J18A__
  SerialUSB.println("DEFINED __SAMD21J18A__");
  #else
  SerialUSB.println("NOT DEFINED __SAMD21J18A__");
  #endif

  SerialUSB.println("digitalPinHasPWM(" + String(TESTING_PIN) + ") = " + String(digitalPinHasPWM(TESTING_PIN)));
  
  // Setting ADC/DAC RESOLUTION
  analogReadResolution(ADC_RESOLUTION);   // defined on Arduino-SAMDCore/wiring_analog.h, default resolution is 10 bits
  analogWriteResolution(DAC_RESOLUTION);  // defined on Arduino-SAMDCore/wiring_analog.h, default resolution is 8 bits

  SerialUSB.println("analogReadResolution ( " + String(ADC_RESOLUTION) + " );" );
  SerialUSB.println("analogWriteResolution( " + String(DAC_RESOLUTION) + " );" );
  
  // set TESTING_PING as INPUT
  #if defined(TEST_ANALOG_INPUT) || defined(TEST_DIGITAL_INPUT)
    SerialUSB.println("Setting test pin as INPUT...");
    pinMode(TESTING_PIN, INPUT_SETTING);
  #endif

  // set TESTING_PING as OUTPUT
  #if defined(TEST_ANALOG_OUTPUT) || defined(TEST_DIGITAL_OUTPUT)
    SerialUSB.println("Setting test pin as OUTPUT...");
    pinMode(TESTING_PIN, OUTPUT);
  #endif
}

void loop()
{
// test Analog Input
  #ifdef TEST_ANALOG_INPUT
    SerialUSB.println("analogRead(" + String(TESTING_PIN) + "); = " + String(analogRead(TESTING_PIN)));
    delay(1000);
  #endif

// test Digital Input
  #ifdef TEST_DIGITAL_INPUT
    SerialUSB.println("digitalRead(" + String(TESTING_PIN) + "); = " + String(digitalRead(TESTING_PIN)));
    delay(1000);
  #endif

// test Analog Output (PWM)
  #ifdef TEST_ANALOG_OUTPUT
    int maxResolution = pow(2, DAC_RESOLUTION) - 1;
    int increment = (maxResolution+1) / 16;
    
    for (int i = 0; i <= maxResolution; i += increment)
    {
      SerialUSB.println("analogWrite(" + String(TESTING_PIN) + " , " + String(i) + ");");
      analogWrite(TESTING_PIN, i);
      delay(1000);
    }
  
    for (int i = maxResolution; i >= 0; i -= increment)
    {
      SerialUSB.println("analogWrite(" + String(TESTING_PIN) + " , " + String(i) + ");");
      analogWrite(TESTING_PIN, i);
      delay(1000);
    }
  #endif

// test Digital Output (Blink)
  #ifdef TEST_DIGITAL_OUTPUT
    SerialUSB.println("digitalWrite(" + String(TESTING_PIN) + " , HIGH); ");
    digitalWrite(TESTING_PIN, HIGH);
    delay(1000);
  
    SerialUSB.println("digitalWrite(" + String(TESTING_PIN) + " , LOW); ");
    digitalWrite(TESTING_PIN, LOW);
    delay(1000);
  #endif
}
