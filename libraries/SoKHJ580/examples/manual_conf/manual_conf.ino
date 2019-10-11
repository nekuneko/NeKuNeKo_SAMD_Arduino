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
const uint32_t BAUD_RATE  = 115200;         
const String DEVICE_NAME  = "SoK Device"; 
const String MANUFAC_NAME = "NeKuNeKo Inc.";

// Choose your serial port
Uart& SerialBLE = Serial2;


bool checkResponse (String response)
{
  if (response.length() <= 1)
    return false;
    
  if (response.equalsIgnoreCase("<OK>") || 
    response.equalsIgnoreCase("<CONNECTED>") ||
    response.equalsIgnoreCase("<DISCONNECTED>"))
    return true;
  else 
    return false; 
}


String ble_writeCommand (String command)
{
  SerialBLE.write(command.c_str());          // Send AT command
  SerialBLE.setTimeout(20);                  // Wait for Acknowledgement
  return SerialBLE.readString();            // Receive Acknowledgement
}

void showAdditionalInfo()
{ 
  // BLE INFORMATION
  Serial.println("\nAdditional BLE Module information: ");
  Serial.println("BaudRate:   "+ble_writeCommand("<COMBAUD>")); 
  Serial.println("Stop bits:  "+ble_writeCommand("<STOPBIT>"));
  Serial.println("Parity:     "+ble_writeCommand("<PARITY>"));
  Serial.println("Advertising state: "+ble_writeCommand("<ADVSTATE>"));
  Serial.println("Device Name:       "+ble_writeCommand("<MNAME>"));
  Serial.println("Manufacturer Name: "+ble_writeCommand("<FNAME>"));
  Serial.println("Software version:  "+ble_writeCommand("<SVER>")); 
  Serial.println("Hardware version:  "+ble_writeCommand("<HVER>")); 
  Serial.println("Manufacturer SN:   "+ble_writeCommand("<MSN>")); 
  Serial.println("State:    "+ble_writeCommand("<STATE>"));
  Serial.println("Role:     "+ble_writeCommand("<ROLETYPE>"));
  Serial.println("MAC Addr: "+ble_writeCommand("<MAC>"));
  Serial.println("Peer MAC: "+ble_writeCommand("<PEERMAC>"));
  Serial.println("Bond MAC: "+ble_writeCommand("<RBMAC>"));
  Serial.println("RSSI:     "+ble_writeCommand("<RSSI>"));
} // end showAdditionalInfo()


void beginBaudrateSequence (uint32_t baudrate)
{ 
  SerialBLE.end();
  SerialBLE.begin(baudrate);     
  while(!SerialBLE);
}

uint32_t guessBLEbaudrate(void)
{
  uint32_t actualBaudRate = 115200;
  beginBaudrateSequence(actualBaudRate); // Aliexpress (New) HJ-580XP
  if (!checkResponse(ble_writeCommand("STATE"))) {
    actualBaudRate = 19200; // Taobao (Old) HJ-580XP
    beginBaudrateSequence(actualBaudRate);
    
    if (!checkResponse(ble_writeCommand("STATE"))) {
      actualBaudRate = 9600;  // Another baudrate ??
      beginBaudrateSequence(actualBaudRate);
      
      if (!checkResponse(ble_writeCommand("STATE")))
        actualBaudRate = 0;
    }
  }
  
  return actualBaudRate;
}

void setup() 
{
  // Serial open
  Serial.begin(BAUD_RATE);
  while(!Serial);
  Serial.println("\tHJ-580XP bluetooth low energy module MANUAL test");
  Serial.println("\tRemember to configure Serial Monitor to: No Line adjustment + 112500 baudrate\n");
  
  // BLE: Pin initialization
  pinMode(BLE_RESET,    OUTPUT);        // HIGH: System Reset,          LOW: System ON 
  pinMode(BLE_ENABLE,   OUTPUT);        // HIGH: Uart RX disabled,      LOW: Uart RX enabled
  pinMode(BLE_CONFIG,   OUTPUT);        // HIGH: Transparent UART mode, LOW: AT-Commands
  pinMode(BLE_MSTR_SLV, OUTPUT);        // HIGH: Slave mode,            LOW: Master mode
  pinMode(BLE_STATE,    INPUT_PULLUP);  // HIGH: BLE disconencted,      LOW: BLE connected to host/peripheral

  // BLE: Setting initial State
  digitalWrite(BLE_RESET,     LOW);     // System ON
  digitalWrite(BLE_ENABLE,    LOW);     // Uart RX enabled, needed for AT-COMMAND & Transparent UART modes.
  digitalWrite(BLE_CONFIG,    HIGH);    // Transparent UART mode
  digitalWrite(BLE_MSTR_SLV,  HIGH);    // Slave mode

  // BLE: Perform reset
  Serial.print("Performing hardware reset... ");
  digitalWrite(BLE_RESET, HIGH);    delay(50); // Perform Reset
  digitalWrite(BLE_RESET, LOW);                // Release reset, System ON in AT COMMAND mode.
  Serial.println("<OK>");
  
  // BLE: Enter AT Command mode
  digitalWrite(BLE_CONFIG, LOW);    delay(120); // Enter AT Command mode
  Serial.println("Enter AT Command mode... <OK>");

  // BLE: Init Uart
  uint32_t BLEbaudrate = guessBLEbaudrate();
  beginBaudrateSequence(BLEbaudrate);
  if (BLEbaudrate != BAUD_RATE) {
    Serial.print("Setting Baudrate... "); ble_writeCommand("<BAUD"+String(BAUD_RATE)+">");    // Set Baudrate to BAUD_RATE
    beginBaudrateSequence(BAUD_RATE);
  }
  
  // BLE: Show status
  showAdditionalInfo();
  
  /*/ BLE: Configure BLE
  Serial.print("Setting Device name...       "); ble_writeCommand("<NAME"+DEVICE_NAME+">");  // Set Device Name to DEVICE_NAME
  Serial.print("Setting Manufacturer name... "); ble_writeCommand("<FAC"+MANUFAC_NAME+">");  // Set Manufacturer Name to NeKuNeKo Inc.
  Serial.print("Connection status is...      "); ble_writeCommand("<DISCONNECT>");           // Disconnect any device attached to refresh changes

  // Check all configurations were done.
  Serial.println("\nCheck all configurations were done: ");
  Serial.print("BaudRate:         "); ble_writeCommand("<COMBAUD>");
  Serial.print("DeviceName:       "); ble_writeCommand("<MNAME>");
  Serial.print("ManufacturerName: "); ble_writeCommand("<FNAME>"); //*/
  
  // BLE: Exit AT Command mode; Enter Transparent UART mode
  digitalWrite(BLE_CONFIG, HIGH);    // Enter Transparent UART mode
  Serial.println("Enter Transparent UART mode... <OK>");
  
  // BLE: Send & Receive Data by UART
  beginBaudrateSequence(BAUD_RATE);

  // Done
  Serial.println();
  Serial.println("Now you are in SPP Uart transparent mode.");
  Serial.println("Configuration done. Multiserial initiated:");
  digitalWrite(LED_BUILTIN, LOW); // Power on
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

  // Send data
  while (Serial.available()) {
    String s = Serial.readString();
    Serial.print("Sending...  " + s);
    SerialBLE.print(s);
  }

  // Receive data
  while(SerialBLE.available())
    Serial.print("Received... " + SerialBLE.readString());

  delay(1000);
}
