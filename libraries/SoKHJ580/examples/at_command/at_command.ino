#include <hj580.h>

// User constants
#if defined(_VARIANT_SOK_ZERO_DAWN_)
const String DEVICE_NAME = "SoK Zero Dawn";
#elif defined(_VARIANT_SOK_M4_ADVANCE_)
const String DEVICE_NAME = "SoK M4 Advance";
#else
const String DEVICE_NAME = "HJ-580XP"; // Edit with your device name
#endif
const uint32_t BAUD_RATE = 115200;
const String   MANUFACTURER_NAME = "NeKuNeKo Inc.";

// Sketch variables
HJ580 ble; 
volatile bool ble_flag = false; // True:  Connected;  False: Disconnected
bool at_enabled = false;        // True:  Enabled;    False: Disabled
bool lastFlag   = true;



  
void ISR () {
  // Arduino Pin BLE_STATE (InputPullUp) <- ----- <--- BLE_FLAG (HJ-580XP) 
  // DigitalRead LOW  -> Connected
  // DigitalRead HIGH -> Disconnected
  
  ble_flag = !digitalRead(BLE_STATE);
}


void showAdditionalInfo()
{ 
  // BLE INFORMATION
  Serial.println("\nAdditional BLE Module information: ");
  Serial.println("BaudRate:   "+ble.getBaudRate()); 
  Serial.println("Stop bits:  "+ble.getStopBits());
  Serial.println("Parity:     "+ble.getParity());
  Serial.println("Advertising state: "+ble.getAdvState());
  Serial.println("Device Name:       "+ble.getDevName());
  Serial.println("Manufacturer Name: "+ble.getManName());
  Serial.println("Software version:  "+ble.getSoftVersion()); 
  Serial.println("Hardware version:  "+ble.getHardVersion()); 
  Serial.println("Manufacturer SN:   "+ble.getSerialNumber()); 
  Serial.println("State:    "+ble.getState());
  Serial.println("Role:     "+ble.getRole());
  Serial.println("MAC Addr: "+ble.getMAC());
  Serial.println("Peer MAC: "+ble.getPeerMAC());
  Serial.println("Bond MAC: "+ble.getBondMAC());
  Serial.println("RSSI:     "+ble.getRSSI());
  
  // Show error report
  Serial.println("\n\t_INFO_ERROR_REPORT_");
  Serial.print(ble.getErrors());
  Serial.println();
} // end showAdditionalInfo()


void setup() 
{
  Serial.begin(BAUD_RATE);
  while(!Serial);
  Serial.println("\tHJ-580XP bluetooth low energy module LIBRARY test");
  Serial.println("\tRemember to configure Serial Monitor to: No Line adjustment + 112500 baudrate");

  // Init BLE module
  if (ble.begin())
    Serial.println("BLE begin OK");
  else
    Serial.println("BLE begin FAIL");

  // Show startup error report
  Serial.println("\n\t_INIT_ERROR REPORT_");
  Serial.print(ble.getErrors());

  /*/ Test Master Mode
  ble.setMasterMode();
  ble.setBondMAC("66:55:44:33:22:11"); // */
  
  // BLE additional information
  showAdditionalInfo();
  
  /*/ Initial configuration batch commands
  Serial.println("Performing initial configuration commands");
  const int NUM_COMMANDS = 3;
  String commands[NUM_COMMANDS] = {  
              String("NAME")+DEVICE_NAME, 
              String("FAC") +MANUFACTURER_NAME), 
              String("DISCONNECT")
            };
  ble.writeCommands(commands, NUM_COMMANDS);

  // Show Manual Configuration error report
  Serial.println("\n\t_MANUAL_CONFIG_ERROR_REPORT_");
  Serial.print(ble.getErrors());
  
  // Check all configurations were done.
  Serial.println("\nCheck all configurations were done: ");
  Serial.println("DeviceName:       "+ble.writeCommand("MNAME"));
  Serial.println("ManufacturerName: "+ble.writeCommand("FNAME")); 
  Serial.println("Status:           "+ble.writeCommand("STATE"));
  // */
  
  Serial.println("Now you are in SPP Uart transparent mode");
  Serial.println("You can enable/disable AT mode by writing ENABLEAT");


  // Arduino Pin BLE_STATE (InputPullUp) <------ HJ-580XP Pin BLE_STATE 
  // DigitalRead LOW  -> Connected
  // DigitalRead HIGH -> Disconnected
  pinMode(BLE_STATE, INPUT_PULLUP);
  attachInterrupt(BLE_STATE, ISR, CHANGE);

  // Power on LED builtin
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, LOW);
} // end setup()


void loop() 
{
  /*/ Show connection info
   showAdditionalInfo();
   delay(1000); //*/ 
  
  /*/ Manual Interrupt
  ble_flag = !digitalRead(BLE_STATE); //*/

  // Check if connection status changed
  if (ble_flag != lastFlag) {
    lastFlag = ble_flag;
    if (lastFlag)
      Serial.println("BLE is connected");
    else
      Serial.println("BLE is disconnected");
  }
    
  // Wait for AT commands
  while (Serial.available()) {
    String s = Serial.readString();
    
    // Enable / Disable AT mode
    if (s.equalsIgnoreCase("ENABLEAT")){
      if (at_enabled) {// AT Enabled, Disable
        at_enabled = false;
        Serial.println("AT mode DISABLED");
      } else {           // AT Disabled, Enable
        at_enabled = true;
        Serial.println("AT mode ENABLED");
      }
    }
    else {// Print: Write command in AT / Sent BLE data in UART mode
      if (at_enabled){
        Serial.println(">AT:  " + s);
        s = ble.writeCommand(s);
        Serial.println("<ACK: " + s);
      } else { 
        Serial.println("Sending...  " + s);
        Serial2.print(s);
      }
    }
  } // end Wait for AT commands

  // Print received BLE data in UART mode
  while (Serial2.available()) {
    String s = Serial2.readString();
    Serial.print("Received... " + s);
  }
} // end loop()
