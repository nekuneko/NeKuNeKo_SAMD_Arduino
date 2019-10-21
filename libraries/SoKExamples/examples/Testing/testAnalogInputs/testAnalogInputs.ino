// Test Analog Inputs on SoK devices

#define ADC_RESOLUTION 10 // 12, 10, 8
#define DELAY_MS 1000

void setup() 
{
   Serial.begin(115200);
   while(!Serial);
   Serial.println("analogTest");
   Serial.println();
 
  // Configure as INPUT: 
  // A0, A1, A2, A3, A4, A5, A6, A7, A8, A9, 
  // A10 (D0), A11 (D1), A12 (D2), A13 (D3), 
  // A14 (D4), A15 (D5), A17 (SDA) A18 (SCL) A19 (SOK)
  // SoK Zero Dawn:  A16 (D6)
  // SoK M4 Advance: A16 (D10)
  for (int i=A0; i<=SOK; ++i)
    pinMode(i, INPUT);

  analogReadResolution(ADC_RESOLUTION); 
}

void loop() 
{
  for (int i=A0; i<=SOK; ++i)
    Serial.println("A" + String(i-A0) + ": " + String(analogRead(i)));
  Serial.println();
  delay(DELAY_MS);
}
