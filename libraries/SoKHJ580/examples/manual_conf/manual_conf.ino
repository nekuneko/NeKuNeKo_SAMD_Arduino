/*/ BLE HJ-580XP: Pin definitions
// Extern defined by using global constants in variant.h file
// Uncoment to use another pins
  #define BLE_TX         0
  #define BLE_RX         1
  #define BLE_RESET      2
  #define BLE_ENABLE     3
  #define BLE_CONFIG     4
  #define BLE_MSTR_SLV   5
  #define BLE_STATE      6 //*/

// Set some options
String BAUD_RATE    = "115200";
String DEVICE_NAME  = "SoK Device"; 
String MANUFAC_NAME = "NeKuNeKo Inc.";

// Choose your serial port
Uart& SerialBLE = Serial2;

void ble_writeCommand (String command)
{
  SerialBLE.write(command.c_str());          // Send AT command
  SerialBLE.setTimeout(20);                  // Wait for Acknowledgement
  Serial.println(SerialBLE.readString());    // Receive Acknowledgement
}

void setup() 
{
  Serial.begin(115200);
  while(!Serial);
  Serial.println("\tHJ-580XP bluetooth low energy module MANUAL test");
  
  // BLE: Pin initialization
  pinMode(BLE_RESET,    OUTPUT);        // HIGH: System Reset,          LOW: System ON 
  pinMode(BLE_ENABLE,   OUTPUT);        // HIGH: Uart RX disabled,      LOW: Uart RX enabled
  pinMode(BLE_CONFIG,   OUTPUT);        // HIGH: Transparent UART mode, LOW: AT-Commands
  pinMode(BLE_MSTR_SLV, OUTPUT);        // HIGH: Slave mode,            LOW: Master mode
  pinMode(BLE_STATE,    INPUT_PULLUP);  // HIGH: BLE disconencted,      LOW: BLE connected to host/peripheral

  // BLE Initial Configuration
  digitalWrite(BLE_RESET,     HIGH);    // System Reset
  digitalWrite(BLE_ENABLE,    LOW);     // Uart RX enabled, needed for AT-COMMAND & Transparent UART modes.
  digitalWrite(BLE_CONFIG,    LOW);     // Transparent UART mode
  digitalWrite(BLE_MSTR_SLV,  HIGH);    // Slave mode

  // Perform reset
  Serial.print("Performing reset... ");
  digitalWrite(BLE_RESET, HIGH);    delay(50); // Perform Reset
  digitalWrite(BLE_RESET, LOW);                // Release reset, System ON in AT COMMAND mode.
  Serial.println("<OK>");
  
  // BLE: Enter AT Command mode
  digitalWrite(BLE_CONFIG, LOW);    delay(120); // Enter AT Command mode
  Serial.println("Enter AT Command mode... <OK>");
  
  // BLE: Configure BLE
  SerialBLE.begin(19200);
  while(!SerialBLE);
  Serial.print("Setting Baudrate... ");              ble_writeCommand("<BAUD"+BAUD_RATE+">");    // Set Baudrate to 115200
  Serial.print("Setting Device name... ");           ble_writeCommand("<NAME"+DEVICE_NAME+">");  // Set Device Name to DEVICE_NAME
  Serial.print("Setting Manufacturer name... ");     ble_writeCommand("<FAC"+MANUFAC_NAME+">");  // Set Manufacturer Name to NeKuNeKo Inc.
  Serial.print("All connected devices nor are... "); ble_writeCommand("<DISCONNECT>");           // Disconnect any device attached to refresh changes

  // Check all configurations were done.
  Serial.println("\nCheck all configurations were done: ");
  Serial.print("BaudRate:         "); ble_writeCommand("<COMBAUD>");
  Serial.print("DeviceName:       "); ble_writeCommand("<MNAME>");
  Serial.print("ManufacturerName: "); ble_writeCommand("<FNAME>");
  
  // BLE: Enter Transparent UART mode
  digitalWrite(BLE_CONFIG, HIGH);    // Enter Transparent UART mode
  Serial.println("Enter Transparent UART mode... <OK>");
  
  // BLE: Send & Receive Data by UART
  SerialBLE.begin(115200);
  //while(!SerialBLE);
  //SerialBLE.println("Hello World!");

  // Done
  Serial.println("\nConfiguration done. Multiserial initiated:");
  digitalWrite(LED_BUILTIN, LOW);
}

void printReceived ()
{
  while (SerialBLE.available()) {
    int inByte = SerialBLE.read();
    Serial.write(inByte);
  }
}

void loop() {
  // BLE: Send & Receive Data by UART
  //Serial.println("Sending... Hello World!");
  //SerialBLE.println("Hello World!");

  while (Serial.available())
  {
    String s = Serial.readString();
    Serial.print("Sending...  " + s);
    SerialBLE.print(s);
  }
  
  while(SerialBLE.available())
    Serial.print("Received... " + SerialBLE.readString());

  delay(1000);
}
