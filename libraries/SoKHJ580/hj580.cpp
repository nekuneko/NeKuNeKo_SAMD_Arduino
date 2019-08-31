#include "hj580.h"


bool HJ580::begin (String softVersion, unsigned long baud, Uart* u)
{
	String name = "HJ-580";
	bool success   = true;
	this->baudRate = baud;
	this->uart     = u;

	#if defined(_VARIANT_SOK_ZER_DAWN_)
		name = "SoK Zero Dawn";

	#elif defined(_VARIANT_SOK_M4_ADVANCE_)
		name = "SoK M4 Advance";
	#endif
		
	// BLE: Pin initialization
	pinMode(BLE_RESET,  	OUTPUT);   		// HIGH: System Reset,        	LOW: System ON 
	pinMode(BLE_ENABLE,		OUTPUT);		// HIGH: Uart RX disabled, 		LOW: Uart RX enabled
	pinMode(BLE_CONFIG, 	OUTPUT);   		// HIGH: Transparent UART mode,	LOW: AT-Commands
	pinMode(BLE_MSTR_SLV, 	OUTPUT);		// HIGH: Slave mode, 			LOW: Master mode
	pinMode(BLE_STATE, 		INPUT_PULLUP);	// HIGH: BLE disconencted, 		LOW: BLE connected to host/peripheral

	digitalWrite(BLE_RESET, 	HIGH);		// System Reset
	digitalWrite(BLE_ENABLE, 	LOW);		// Uart RX enabled
	digitalWrite(BLE_CONFIG, 	LOW);		// Transparent UART mode
	digitalWrite(BLE_MSTR_SLV, 	HIGH);		// Slave mode

	// Reset configurations
	reset();

	// BLE Initial Configuration
	//this->uart->begin(19200); // Taobao (Old) HJ-580XP
	this->uart->begin(115200); 	// Aliexpress HJ-580XP

	String commands[5] = { 	"NAME"+name, 
							"SOFT"+softVersion, 
							"FAC" +String("NeKuNeKo Inc."), 
							"BAUD"+String(baudRate), 
							"DISCONNECT"};
	success = writeCommands(commands, 5);

	this->uart->begin(baudRate);
	
	return success;
}

void HJ580::reset (unsigned long timeReset)
{
	digitalWrite(BLE_RESET, HIGH);    delay(timeReset); // Perform Reset
    digitalWrite(BLE_RESET, LOW);     //delay(150); 	// Release reset, System ON in AT COMMAND mode.
}




String HJ580::readCommand (unsigned long timeout)
{
	this->uart->setTimeout(timeout);
	return this->uart->readString();
}



bool HJ580::writeCommands (String* commands, int size)
{
	String response = "";
	String command  = "";
	bool   success  = true;

	atmodeON(); // Enter AT Command mode
	for (int i=0; i<=size-1; ++i)
	{
		command = "<"+commands[i]+">";
		this->uart->write(command.c_str());	// Send AT Command
		response = readCommand(); 			// Receive Acknowledgement

		success &= checkResponse(response);

		// Debug
		Serial.print(command + ": ");
		Serial.println(response);	
	}

	atmodeOFF(); // Enter Transparent UART mode, turn off AT Command mode

	return success;
}

String HJ580::writeCommand (String command)
{
	String response = "";

	atmodeON(); // Enter AT Command mode
	
	command = "<"+command+">";
	this->uart->write(command.c_str()); // Send AT Command
	response = readCommand(); 			// Receive Acknowledgement

	// Debug
	//Serial.print(command + ": ");
	//Serial.println(response);	

	atmodeOFF(); // Enter Transparent UART mode, turn off AT Command mode

	return response;
}


bool HJ580::checkResponse (String response)
{
	// Erase characters '<' & '>'
	//response.substring(1, response.length()-1);

	if (response.equalsIgnoreCase("<OK>") || 
		response.equalsIgnoreCase("<CONNECTED>") ||
		response.equalsIgnoreCase("<DISCONNECTED>"))
	  return true;
	else 
	  return false; 
}

bool HJ580::checkCommand (String command)
{
	checkResponse(writeCommand(command));
}