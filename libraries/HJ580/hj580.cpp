#include "hj580.h"


bool HJ580::begin (String softVersion, String baud, Uart* u)
{
	bool success = false;

	this->baudRate = baud;
	this->uart = u;

	// BLE: Pin initialization
	pinMode(BLE_RESET,     OUTPUT);   // HIGH - Reset,        LOW  - System ON 
	pinMode(BLE_CONFIG,    OUTPUT);   // LOW  - AT-Commands,  HIGH - Transparent UART mode

	
	digitalWrite(BLE_CONFIG, HIGH);
	reset();
	

	uart->begin(19200); delay(100);



	// BLE Initial Configuration
	success = setBaudRate (baudRate);
	//SerialUSB.println("Baudrate: " + String(success));
	success &= setFactory("NeKuNeKo Inc.");
	//SerialUSB.println("factoryName: " + String(success));
	if (!softVersion.equals(""))
		success &= setVersion(softVersion);
	//SerialUSB.println("softVersion: " + String(success));
	disconnect();

	this->uart->begin(baudRate.toInt()); 	//delay(150); 
	
	//SerialUSB.println("success: " + String(success));
	return success;
}

void HJ580::reset ()
{
	digitalWrite(BLE_RESET, HIGH);    delay(100); // Perform Reset
    digitalWrite(BLE_RESET, LOW);     //delay(150); // Release reset, System ON in AT COMMAND mode.
}


String HJ580::readCommandTimeout (unsigned long timeout) 
{
	unsigned long currentTime, startTime = millis();

	while(!uart->available() && (currentTime - startTime <= timeout))
		currentTime = millis();
	return uart->readString();
}

String HJ580::readCommand ()
{
	while(!uart->available());
	return uart->readString();
}


String HJ580::writeCommand (String command)
{
	digitalWrite(BLE_CONFIG, LOW);    		delay(150); // Enter AT Command mode
	
	command = "<"+command+">";
	this->uart->write(command.c_str());     delay(150); // Send AT Command
	String response = readCommand(); // Receive Acknowledgement

	digitalWrite(BLE_CONFIG, HIGH);       		// Enter Transparent UART mode

	return response;
}


bool HJ580::checkCommand (String command)
{
	String response = writeCommand(command);
	//SerialUSB.println(response);

	if (response.equalsIgnoreCase("<OK>") || 
		response.equalsIgnoreCase("<CONNECTED>"))
	  return true;
	else 
	  return false; 
}