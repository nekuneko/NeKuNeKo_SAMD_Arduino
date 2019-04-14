#pragma once

#include <Arduino.h>

class HJ580;
extern HJ580 ble;

// Extern defined used global constants in variant.h file
// BLE_RESET    -> PIN*
// BLE_ENABLE   -> PIN
// BLE_CONFIG   -> PIN*
// BLE_MSTR_SLV -> PIN
// BLE_STATE    -> PIN
// SerialBLE

#ifdef _VARIANT_GONTAK_SOK_ZERO_
  #define BLE_ENABLE    PIN_NOT_CONNECTED
  #define BLE_CONFIG    PIN_NOT_CONNECTED
  #define BLE_MSTR_SLV  PIN_NOT_CONNECTED
  #define BLE_STATE     PIN_NOT_CONNECTED
#endif


// BLE Integrated
class HJ580
{
public:

  bool begin (String softVersion = " ", unsigned long baud = 115200, Uart* u = &SerialBLE);


  void reset (unsigned long timeReset = 50);
  inline String getBaudRate () { baudRate = strtoul(writeCommand("COMBAUD").c_str(), NULL, 10); return String(baudRate); }
  inline String getName     () { return writeCommand("MNAME"); }
  inline String getFactory  () { return writeCommand("FNAME"); }
  inline String getVersion  () { return writeCommand("SVER");  }
  inline bool   getState    () { return checkCommand("STATE"); }

  inline bool setBaudRate (unsigned long baud) { baudRate = baud; return checkCommand("BAUD"+String(baudRate)); }
  inline bool setName     (String name) { return checkCommand("NAME"+name);  }
  inline bool setFactory  (String name) { return checkCommand("FAC"+name);   }
  inline bool setVersion  (String vers) { return checkCommand("SOFT"+vers);  }
  inline bool disconnect  ()            { return checkCommand("DISCONNECT"); }
  

  

  String readCommand   (unsigned long timeout = 20);
  String writeCommand  (String  command);
  bool   writeCommands (String* commands, int size);
  bool   checkCommand  (String  command);
  bool   checkResponse (String  response);

  inline void atmodeON  () { digitalWrite(BLE_CONFIG, LOW);  delay(120); }
  inline void atmodeOFF () { digitalWrite(BLE_CONFIG, HIGH); delay(5);  }
  

private:
  Uart* uart;
  unsigned long baudRate;
};