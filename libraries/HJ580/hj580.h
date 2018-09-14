#pragma once

#include <Arduino.h>

class HJ580;
extern HJ580 ble;

// EXTERN GLOBAL VARIABLES
// BLE_RESET -> PIN
// BLE_CONFIG  -> PIN


// BLE Integrated
class HJ580
{
public:

  bool begin (String softVersion = "", String baud = "115200", Uart* u = &Serial);


  void reset ();

  inline String getBaudRate () { baudRate = writeCommand("COMBAUD"); return baudRate; }
  inline String getName     () { return writeCommand("MNAME"); }
  inline String getFactory  () { return writeCommand("FNAME"); }
  inline String getVersion  () { return writeCommand("SVER");  }
  inline bool   getState    () { return checkCommand("STATE"); }

  inline bool setBaudRate (String baud) { baudRate = baud; return checkCommand("BAUD"+baudRate); }
  inline bool setName     (String name) { return checkCommand("NAME"+name);  }
  inline bool setFactory  (String name) { return checkCommand("FAC"+name);   }
  inline bool setVersion  (String vers) { return checkCommand("SOFT"+vers);  }
  inline bool disconnect  ()            { return checkCommand("DISCONNECT"); }
  


  String readCommand ();
  String readCommandTimeout (unsigned long timeout = 0);
  String writeCommand (String command);
  bool   checkCommand (String command);

private:
  Uart* uart;
  String baudRate;
};