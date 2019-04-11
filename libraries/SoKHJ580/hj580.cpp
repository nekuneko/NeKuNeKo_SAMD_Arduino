#include "hj580.h"


bool HJ580::begin (String softVersion, unsigned long baud, Uart* u)
{
	bool success   = true;
	this->baudRate = baud;
	this->uart     = u;


	this->uart->begin(19200);
	while(!uart);

	// BLE: Pin initialization
	pinMode(BLE_RESET,     OUTPUT);   // HIGH - Reset,        LOW  - System ON 
	pinMode(BLE_CONFIG,    OUTPUT);   // LOW  - AT-Commands,  HIGH - Transparent UART mode
	
	reset();

	// BLE Initial Configuration
	String commands[5] = { "NAME"+String("SoK Zero"), "SOFT"+softVersion, "FAC"+String("NeKuNeKo Inc."),  "BAUD"+String(baudRate), "DISCONNECT"};
	writeCommands(commands, 5);

	this->uart->begin(baudRate);
	while(!uart);
	
	return success;
}

void HJ580::reset (unsigned long timeReset)
{
	digitalWrite(BLE_RESET, HIGH);    delay(timeReset); // Perform Reset
    digitalWrite(BLE_RESET, LOW);     //delay(150); // Release reset, System ON in AT COMMAND mode.
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
		this->uart->write(command.c_str());		// Send AT Command
		response = readCommand(); 				// Receive Acknowledgement

		// Erase characters '<' & '>'
		response.substring(1, response.length()-1);
		
		// Debug
		Serial.print(command + ": ");
		Serial.println(response);	

		success &= checkResponse(response);
	}

	atmodeOFF(); // Enter Transparent UART mode, turn off AT Command mode

	return success;
}

String HJ580::writeCommand (String command)
{
	String response = "";

	atmodeON(); // Enter AT Command mode
	
	command = "<"+command+">";
	this->uart->write(command.c_str());  	// Send AT Command
	response = readCommand(); 				// Receive Acknowledgement

	// Erase characters '<' & '>'
	response.substring(1, response.length()-1);

	// Debug
	Serial.print(command + ": ");
	Serial.println(response);	

	atmodeOFF(); // Enter Transparent UART mode, turn off AT Command mode

	return response;
}


bool HJ580::checkResponse (String response)
{
	if (response.equalsIgnoreCase("OK") || 
		response.equalsIgnoreCase("CONNECTED"))
	  return true;
	else 
	  return false; 
}

bool HJ580::checkCommand (String command)
{
	checkResponse(writeCommand(command));
}