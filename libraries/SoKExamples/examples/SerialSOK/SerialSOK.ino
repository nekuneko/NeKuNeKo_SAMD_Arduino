// Please Enable SerialSOK on Tools > SerialSOK with having selected a SoK board
// Replace Serial1 with SerialSOK
#define Serial1 SerialSOK //*/ // Comment this line to test Serial1 instead of SerialSOK

// Configuration:
// Baudrate: 115200
// Parity: none
// Data bits: 8
// Stop bits: 1
// Line Adjust: NL & CR

void setup() {
  // initialize both serial ports:
  Serial.begin(115200);
  Serial1.begin(115200);
  
  while(!Serial);
  while(!Serial1);
  Serial.println("SerialSOK multiserial communication test");
  
}

uint8_t i=0;
void loop() {
  /*/ MultiSerial: read from port SOK, send to port 0:
  if (Serial1.available()) {
    int inByte = Serial1.read();
    Serial.write(inByte);
  }

  // MultiSerial: read from port 0, send to port SOK:
  if (Serial.available()) {
    int inByte = Serial.read();
    Serial1.write(inByte);
  } //*/

  
  // Serial Life Proof
  Serial.println(i);
  Serial1.write(i++);
  delay(10); //*/

  
  /*/ Serial Print message
  String mes = "Strager Things";
  Serial.println(mes);
  SerialSOK.println(mes);
  delay(1000); //*/
}
