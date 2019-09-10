#include <hj580.h>

HJ580 ble; 

// True:  Connected
// False: Disconnected
volatile bool ble_flag = false;
bool lastFlag   = true;
bool at_enabled = false;

void ISR () {
  // Arduino Pin BLE_STATE (InputPullUp) <- ----- <--- BLE_FLAG (HJ-580XP) 
  // DigitalRead LOW  -> Connected
  // DigitalRead HIGH -> Disconnected
  
  ble_flag = !digitalRead(BLE_STATE);
}

void setup() 
{
  Serial.begin(115200);
  while(!Serial);
  Serial.println("\tHJ-580XP bluetooth low energy module LIBRARY test");
  Serial.println("\tRemember to configure Serial Monitor to: No Line adjustment + 112500 baudrate");
  
  if (ble.begin())
    Serial.println("BLE begin OK");
  else
    Serial.println("BLE begin FAIL");
    
  // Arduino Pin BLE_STATE (InputPullUp) <- ----- <--- BLE_FLAG (HJ-580XP) 
  // DigitalRead LOW  -> Connected
  // DigitalRead HIGH -> Disconnected
  pinMode(BLE_STATE, INPUT_PULLUP);
  attachInterrupt(BLE_STATE, ISR, CHANGE);
  
  // Check all configurations were done.
  Serial.println("\nCheck all configurations were done: ");
  Serial.println("BaudRate:         "+ble.writeCommand("COMBAUD")); 
  Serial.println("DeviceName:       "+ble.writeCommand("MNAME"));
  Serial.println("SoftwareVersion:  "+ble.writeCommand("SVER"));
  Serial.println("ManufacturerName: "+ble.writeCommand("FNAME"));

  // Done
  Serial.println("\nConfiguration done. Multiserial initiated:");
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, LOW);
}

void loop() {

  /*/ Manual Interrupt
  ble_flag = !digitalRead(BLE_STATE); //*/
  if (ble_flag != lastFlag)
  {
    lastFlag = ble_flag;
    
    if (lastFlag)
      Serial.println("BLE is connected");
    else
      Serial.println("BLE is disconnected");
  }
    
  // Wait for AT commands
  while (Serial.available())
  {
    String s = Serial.readString();

    // Enable / Disable AT mode
    if (s.equalsIgnoreCase("ENABLEAT"))
      if (at_enabled) // AT Enabled, Disable
      {
        at_enabled = false;
        Serial.println("AT mode DISABLED");
      }
      else            // AT Disabled, Enable
      {
        at_enabled = true;
        Serial.println("AT mode ENABLED");
      }
    else // Print / Write command in AT / UART mode
    {
      if (at_enabled)
      {
        Serial.println("AT:  " + s);
        s = ble.writeCommand(s);
        Serial.println("ACK: " + s);
      }
      else
      { 
        Serial.println("Sending...  " + s);
        Serial2.print(s);
      }
    }
  }

  while (Serial2.available())
  {
    String s = Serial2.readString();
    Serial.print("Received... " + s);
  }
  
}
