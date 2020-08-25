
#define ENABLE_SERIAL     1
#define ENABLE_SERIAL1    0
#define ENABLE_SERIAL2    0
#define ENABLE_SERIALSOK  0

#define ENABLE_WIRE   0
#define ENABLE_WIRE1  0

#define ENABLE_SPI    0
#define ENABLE_SPI1   0


#if ENABLE_WIRE || ENABLE_WIRE1
  #include <Wire.h>    // I2C
#endif

#if ENABLE_SPI || ENABLE_SP1
  #include <SPI.h>     // SPI
#endif

void setup() 
{
#if ENABLE_SERIAL
  Serial.begin(115200);
#endif
#if ENABLE_SERIAL1
  Serial1.begin(115200);
#endif
#if ENABLE_SERIAL2
  Serial2.begin(115200);
#endif
#if ENABLE_SERIALSOK
  SerialSOK.begin(115200);
#endif

#if ENABLE_WIRE
  Wire.begin();
#endif
#if ENABLE_WIRE1
  Wire1.begin();
#endif


#if ENABLE_SPI
  SPI.begin();
#endif
#if ENABLE_SPI1
  SPI1.begin();
#endif
}

void loop() {
  // put your main code here, to run repeatedly:

}
