/*
  ESP-01F WiFi module uses Expressif ESP8285 chipset based on ESP8266 chipset.

  Useful links:
    - Manufacturer's ESP-01F official Wiki: https://wiki.ai-thinker.com/esp8266/docs?s[]=esp&s[]=01f
    - ESP266 AT command specification: https://www.espressif.com/sites/default/files/documentation/4a-esp8266_at_instruction_set_en.pdf
    - ESP266 AT command examples: https://www.espressif.com/sites/default/files/documentation/4b-esp8266_at_command_examples_en.pdf

  This example code is in the public domain.
*/


const String ROUTER_SSID = "";  // Write router's SSID you want to connect
const String ROUTER_PSSW = "";  // Write router's password you want to connect

void setup() {
  // initialize both serial ports:
  Serial1.begin(115200);
  Serial.begin(115200);
  while(!Serial); // wait until Arduino Serial Monitor is open
  while(Serial1.available()) // Flush Serial1 ESP01-F buffer
    Serial1.readString();

  
  Serial.println("NeKuNeKo's SoK Radio Station ESP-01F WiFi B/G/N 2.4Ghz");
  Serial.println("\tDefault badurate: 115200");
  Serial.println("\tPlease \"set New Line Mode\": NL & CR");
  Serial.println("\tAT commands have to be capitalized");
  Serial.println();


  Serial.println("Checking connection to ESP-01F by sending \"AT+OK\" command");
  Serial1.println("AT\r"); delay(1000);
  while(Serial1.available())
    Serial.print(Serial1.readString());

  Serial.println("Getting device version with \"AT+GMR\" command");
  Serial1.println("AT+GMR\r"); delay(1000);
  while(Serial1.available())
    Serial.print(Serial1.readString());
      
  Serial.println("Sending \"AT+CIFSR\" to get device IP address");
  Serial1.println("AT+CIFSR\r"); delay(1000); // Query the ESP8266 device's IP address
  while(Serial1.available())
    Serial.print(Serial1.readString());
  Serial.println();

  Serial.println("Checking APs around with \"AT+CWMODE_CUR=1\" and \"AT+CWLAP\" commands");
  Serial1.println("AT+CWMODE_CUR=1\r"); delay(1000);
  while(Serial1.available())
    Serial.print(Serial1.readString());
  Serial1.println("AT+CWLAP\r"); delay(5000);
  while(Serial1.available())
    Serial.print(Serial1.readString());

  Serial.println("Multiserial ENABLED");
  Serial.println("Write your own commands!");
}

void loop() {
  
  // read from port 1, send to port 0:
  if (Serial1.available()) {
    int inByte = Serial1.read();
    Serial.write(inByte);
  }

  // read from port 0, send to port 1:
  if (Serial.available()) {
    int inByte = Serial.read();
    Serial1.write(inByte);
  }
}
