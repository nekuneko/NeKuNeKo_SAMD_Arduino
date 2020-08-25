#pragma once

#include <Arduino.h>

// Extern defined used global constants in variant.h file
extern uint8_t BLE_RESET;
extern uint8_t BLE_ENABLE;
extern uint8_t BLE_CONFIG;
extern uint8_t BLE_MSTR_SLV;
extern uint8_t BLE_STATE;
extern Uart Serial2;

// Integrated BLE 
class HJ580
{
public:

  bool begin     (Uart* u = &Serial2, uint32_t finalBaudrate = 115200);
  void hardReset (uint16_t timeReset = 50);   // Hardware Reset
  void softReset (uint16_t timeReset = 50);   // Software Reset
  bool setBondMAC(const String& mac = "11:22:33:44:55:66"); 
  void setMasterMode(void);
  void setSlaveMode (void);
  
  inline void atmodeON  () { digitalWrite(BLE_CONFIG, LOW);  delay(120); }
  inline void atmodeOFF () { digitalWrite(BLE_CONFIG, HIGH); delay(5);  } 
  
  String readCommand       (uint16_t timeout = 20);
  size_t readCommandBytes  (uint8_t* buffer, int32_t length, uint16_t timeout = 20);
  String writeCommand      (String command);
  size_t writeCommandBytes (String command, uint8_t* buffer, int32_t length);
  String writeBytes        (String command, uint8_t* buffer, int32_t bufferLength);
  bool   writeCommands (String* commands, int32_t numCommands);
  bool   checkCommand  (String  command);
  bool   checkResponse (String  response);


  inline String getBaudRate     () { return writeCommand("COMBAUD");  }
  inline String getStopBits     () { return writeCommand("STOPBIT");  }
  inline String getParity       () { return writeCommand("PARITY");   }
  inline String getAdvState     () { return writeCommand("ADVSTATE"); }
  inline String getDevName      () { return writeCommand("MNAME");    }
  inline String getManName      () { return writeCommand("FNAME");    }
  inline String getSoftVersion  () { return writeCommand("SVER");     }
  inline String getHardVersion  () { return writeCommand("HVER");     }
  inline String getSerialNumber () { return writeCommand("MSN");      }
  inline String getState        () { return writeCommand("STATE");    }
  inline String getRole         () { return writeCommand("ROLETYPE"); }

  String getRSSI();
  String getMAC();     // Device MAC: return "11:22:33:44:55:66"
  String getPeerMAC(); // Peer   MAC: return "11:22:33:44:55:66"
  String getBondMAC(); // Bonded MAC: return "11:22:33:44:55:66"
  String getErrors ();



  
  inline void setResetBaudRate (uint32_t baud) { _baudRateAtReset = baud; }
  inline bool setBaudRate      (uint32_t baud) { _baudRate = baud; return checkCommand("BAUD"+String(_baudRate)); }
  inline bool set1StopBit      (void)          { return checkCommand("1SB");   }
  inline bool set2StopBit      (void)          { return checkCommand("2SB");   }
  inline bool setParityEven    (void)          { return checkCommand("PEVEN"); }
  inline bool setParityOdd     (void)          { return checkCommand("PODD");  }
  inline bool setParityNo      (void)          { return checkCommand("PNO");   }
  inline bool setAdvData       (String advd)   { return checkCommand("ADVDATA"+advd); } // upto 22 bytes
  inline bool setiBacon        (String ibcn)   { return checkCommand("IBACON"+ibcn); } // Ibacon broadcast data: fixed 25 bytes
  inline bool setDevName       (String name)   { return checkCommand("NAME"+name); }  // Device name:       upto 18 bytes
  inline bool setManName       (String name)   { return checkCommand("FAC" +name); }  // Manufacturer name: upto 18 bytes
  inline bool setSoftVersion   (String vers)   { return checkCommand("SOFT"+vers); }  // Software version:  upto 18 bytes
  inline bool setHardVersion   (String vers)   { return checkCommand("HARD"+vers); }  // Hardware version:  upto 18 bytes
  inline bool setSerialNumber  (String snum)   { return checkCommand("SN"  +snum); }  // Serial Number:     upto 16 bytes
  inline bool disconnect       (void)          { return checkCommand("DISCONNECT"); } // Slave  Mode: Disconnect BLE connection
  inline bool disbond          (void)          { return checkCommand("DISBOND");    } // Master Mode: Disconnect BLE connection
  inline bool startBroadcast   (void)          { return checkCommand("STARTADV"); }
  inline bool stopBroadcast    (void)          { return checkCommand("STOPADV");  }


private:
  Uart* _uart;
  uint32_t _baudRateAtReset;
  uint32_t _baudRate;
  String _errors;
  static const uint8_t BUFF_SIZE = 20;
  uint8_t _buffer[BUFF_SIZE];

  void beginBaudRate(uint32_t baudrate);
  bool guessBaudRate(void);
}; // end class HJ580