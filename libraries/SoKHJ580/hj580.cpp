#include "hj580.h"


void HJ580::beginBaudRate (uint32_t baudrate)
{
	_uart->end();
	_uart->begin(baudrate); 		
	while(!_uart);
}

bool HJ580::guessBaudRate(void)
{
	bool success = true;

	_baudRateAtReset = 115200;
	beginBaudRate(_baudRateAtReset); // Aliexpress (New) HJ-580XP
	if (!checkCommand("STATE")) {
		_baudRateAtReset = 19200;	// Taobao (Old) HJ-580XP
		beginBaudRate(_baudRateAtReset);
		
		if (!checkCommand("STATE")) {
			_baudRateAtReset = 9600;	// Another baudrate ??
			beginBaudRate(_baudRateAtReset);

			if (!checkCommand("STATE")) {
				_baudRateAtReset = 0;
				success = false;
			}
		}
	}
	if (success)
		_errors += "\tbaudrate at reset is " + String(_baudRateAtReset) + "\n";
	else
		_errors += "\tbaudrate at reset is unknown\n";

	return success;
}



bool HJ580::begin (Uart* u, uint32_t finalBaudrate)
{
	_baudRate = finalBaudrate;
	_uart     = u;
	_errors   = String();
	bool success = true;
		
	// BLE: Pin initialization
	pinMode(BLE_RESET,  	OUTPUT);   		// HIGH: System Reset,        	LOW: System ON 
	pinMode(BLE_ENABLE,		OUTPUT);		// HIGH: Uart RX disabled, 		LOW: Uart RX enabled
	pinMode(BLE_CONFIG, 	OUTPUT);   		// HIGH: Transparent UART mode,	LOW: AT-Commands
	pinMode(BLE_MSTR_SLV, 	OUTPUT);		// HIGH: Slave mode, 			LOW: Master mode
	pinMode(BLE_STATE, 		INPUT_PULLUP);	// HIGH: BLE disconencted, 		LOW: BLE connected to host/peripheral

	digitalWrite(BLE_RESET, 	LOW);		// System NOT in Reset
	digitalWrite(BLE_ENABLE, 	LOW);		// Uart RX enabled
	digitalWrite(BLE_CONFIG, 	LOW);		// Config mode.
	digitalWrite(BLE_MSTR_SLV, 	HIGH);		// Slave mode

	// Reset configurations
	hardReset();

	// BLE Initial Configuration, initial baudrate selection
	success &= guessBaudRate();
	

	// Begin final baudrate
	//success &= checkCommand("FACTORY");
	//softReset();
	success &= disconnect();
	success &= setBaudRate(_baudRate);
	digitalWrite(BLE_CONFIG, 	HIGH);		// Config mode OFF. Transparent UART mode.

	beginBaudRate(_baudRate);
	
	return success;
}

void HJ580::hardReset (uint16_t timeReset)
{
	digitalWrite(BLE_RESET, HIGH);    delay(timeReset); // Perform Reset
    digitalWrite(BLE_RESET, LOW);     delay(150); 	 	// Release reset, System ON in AT COMMAND mode.
}

void HJ580::softReset (uint16_t timeReset)
{
	writeCommand("RESET"); delay(timeReset);
	beginBaudRate(_baudRateAtReset);
	setBaudRate(_baudRate);
	beginBaudRate(_baudRate);
}



String HJ580::readCommand (uint16_t timeout)
{
	_uart->setTimeout(timeout);
	return _uart->readString();
}

size_t HJ580::readCommandBytes (uint8_t* buffer, int32_t length, uint16_t timeout)
{
	_uart->setTimeout(timeout);
	return _uart->readBytes(buffer, length);
}


bool HJ580::writeCommands (String* commands, int32_t numCommands)
{
	String response = "";
	String command  = "";
	bool   success  = true;

	// Debug
	#if defined(DEBUG)
	Serial.print("writeCommands-> numCommands: ");
	Serial.println(numCommands);
	Serial.print("writeCommands-> commands: ");
	#endif

	atmodeON(); // Enter AT Command mode
	for (int i=0; i<=numCommands-1; ++i)
	{
		command = "<"+commands[i]+">";
		_uart->write(command.c_str());	// Send AT Command
		response = readCommand(); 			// Receive Acknowledgement

		success &= checkResponse(response);

		// Debug
		#if defined(DEBUG)
		Serial.print(response);	
		Serial.print("\t length: ");
		Serial.print(response.length());
		Serial.print("\t");
		#endif
	}

	atmodeOFF(); // Enter Transparent UART mode, turn off AT Command mode

	return success;
}

String HJ580::writeCommand (String command)
{
	String response = "";

	if (command.equalsIgnoreCase("MASTER"))
	{
		setMasterMode();
		return String("Enter in Master mode");
	}
	else if (command.equalsIgnoreCase("SLAVE"))
	{
		setSlaveMode();
		return String("Enter in Slave mode");
	}
	atmodeON(); // Enter AT Command mode

	command = "<"+command+">";
	_uart->write(command.c_str()); 	// Send AT Command
	response = readCommand(); 		// Receive Acknowledgement

	// Debug
	#if defined(DEBUG)
	Serial.print("writeCommand-> ");
	Serial.print(command + ": ");
	Serial.print(response);	
	Serial.print("\t length: ");
	Serial.println(response.length());
	#endif

	atmodeOFF(); // Enter Transparent UART mode, turn off AT Command mode

	return response;
}

size_t HJ580::writeCommandBytes (String command, uint8_t* buffer, int32_t length)
{
	size_t responseBytes = 0;

	atmodeON(); // Enter AT Command mode

	command = "<"+command+">";
	_uart->write(command.c_str());					 	// Send AT Command
	responseBytes = readCommandBytes(buffer, length); 	// Receive Acknowledgement

	// Debug
	#if defined(DEBUG)
	Serial.print("writeCommandBytes-> ");
	Serial.print(command + ": ");
	Serial.print(String((const char*)buffer));	
	Serial.print("\t length: ");
	Serial.println(responseBytes);
	#endif

	atmodeOFF(); // Enter Transparent UART mode, turn off AT Command mode

	return responseBytes;
}

void printBuffer (uint8_t* buffer, int32_t length)
{
	for (int i=0; i<=length-1; ++i)
		Serial.println("["+String(i)+"]: " + String((char)buffer[i]));
}

String HJ580::writeBytes (String command, uint8_t* buffer, int32_t bufferLength)
{
	String response;
	uint8_t myBytesLength = 2+command.length() + bufferLength; // '<' '>' + "COMMAND" + "BUFFER" 
	uint8_t* myBytes = (uint8_t *) malloc(((uint8_t)myBytesLength)*sizeof(uint8_t));

	myBytes[0] = '<';														// '<'
	memcpy(&myBytes[1], (uint8_t*) command.c_str(), command.length());		// "COMMAND"
	memcpy(&myBytes[1+command.length()], buffer, bufferLength);				// "BUFFER"
	myBytes[myBytesLength-1] = '>';											// '>'

	atmodeON(); // Enter AT Command mode
	_uart->write(myBytes, myBytesLength);	// Send command
	response = readCommand(); 				// Receive Acknowledgement
	atmodeOFF(); // Enter Transparent UART mode, turn off AT Command mode

	// Debug
	#if defined(DEBUG)
	Serial.println("Sent command: " + command);
	printBuffer(myBytes, myBytesLength);
	Serial.println("ACK: " + response);
	#endif

	free(myBytes);
	return response;
}

bool HJ580::checkResponse (String response)
{
	// Erase characters '<' & '>'
	//response.substring(1, response.length()-1);

	if (response.length() <= 1)
		return false;

	// Debug
	#if defined(DEBUG)
	Serial.print("checkResponse-> ");
	Serial.print(response);
	Serial.print("\t length: ");
	Serial.println(response.length());
	#endif

	if (response.equalsIgnoreCase("<OK>") || 
		response.equalsIgnoreCase("<CONNECTED>") ||
		response.equalsIgnoreCase("<DISCONNECTED>"))
	  return true;
	else 
	  return false; 
	// <INVALID_ERR> 	Instruction does not exist
	// <LEN_ERR>		The instruction exists, but the instruction length is out of range.
	// <HT_ERR>			The header and the end of the instruction are incorrect, and < or > is dropped at the beginning and the end.
	// <RANGE_ERR> 		The command is correct, but the parameter range exceeds the predetermined value.
}

bool HJ580::checkCommand (String command)
{
	return checkResponse(writeCommand(command));
}


String HJ580::getMAC ()
{
	String mac;
	// 8 bytes, 2 bytes are '<' & '>', 6 bytes are 48 bit mac address
	// '<' 0x"11:22:33:44:55::66" '>'
	size_t bytes = writeCommandBytes("MAC", _buffer, BUFF_SIZE);
	
	// Bytes are reversed, mac address are bytes[6-1], byte[7] is '<' and byte[0] is '>'
	// byte[6]:byte[5]:byte[4]:byte[3]:byte[2]:byte[1]

	if (bytes == 8)
	{
		for (int i=6; i>=2; --i)
			mac += String(_buffer[i], HEX)+ ":";
		mac += String(_buffer[1], HEX);
	}
	else
		mac = "<DISCONNECTED>";

	return mac;
}

String HJ580::getPeerMAC ()
{
	String mac;
	// 9 bytes, 2 bytes are '<' & '>', 1 byte is 'P', 6 bytes are 48 bit mac address
	// '<' 'P' 0x"11:22:33:44:55::66" '>'
	size_t bytes = writeCommandBytes("PEERMAC", _buffer, BUFF_SIZE);
	// Bytes are ordered, mac address are bytes[7-2], byte[0] is '<', byte[1] is 'P' and byte[8] is '>'
 	// mac_addr is byte[2]:byte[3]::byte[4]:byte[5]:byte[6]:byte[7]
	if (bytes == 9)
	{
		for (int i=2; i<=6; ++i)
			mac += String(_buffer[i], HEX)+ ":";
		mac += String(_buffer[7], HEX);
	}
	else
		mac = String("<DISCONNECTED>");
	return mac;
}

String HJ580::getBondMAC()
{
	String mac;
	// 9 bytes, 2 bytes are '<' & '>', 1 byte is 'B', 6 bytes are 48 bit mac address
	// '<' 'B' 0x"11:22:33:44:55::66" '>'
	size_t bytes = writeCommandBytes("RBMAC", _buffer, BUFF_SIZE);
	// Bytes are ordered, mac address are bytes[7-2], byte[0] is '<', byte[1] is 'B' and byte[8] is '>'
 	// mac_addr is byte[2]:byte[3]::byte[4]:byte[5]:byte[6]:byte[7]
	if (bytes == 9)
	{
		for (int i=2; i<=6; ++i)
			mac += String(_buffer[i], HEX)+ ":";
		mac += String(_buffer[7], HEX);
	}
	else
		mac = String("<DISCONNECTED>");
	return mac;
}


bool HJ580::setBondMAC(const String& mac)
{
	//MAC has to be converted to char format, "0x11" in String would be converted to character in Ascii 
	//hex 0x -> 61:62:63:64:65:66
	//string -> a:b:c:d:e:f

	uint8_t macBytes[6];
	char* cmac =new char[mac.length()+1];
	char* pc;

	strcpy(cmac, mac.c_str());

	// Extract string bytes by delimiter ':'
	pc = strtok(cmac, ":");
	uint8_t i = 0;
	while(pc!=0) {
		if (i>=6)
			break;
		macBytes[i] = (char) strtoul(pc, NULL, 16) & 0xff;
		pc = strtok(NULL, ":");
		++i;
	}

	delete[] cmac;

	if (i == 6)
		return checkCommand(writeBytes("BONDMAC", macBytes, sizeof(macBytes))); // Question: mac address must be send in order or with bytes reversed?
	else
	{
		_errors += String("BONDMAC MAC address invalid length\n");
		return false; // Invalid length
	}
}

String HJ580::getRSSI () 
{
	// Note: rssi has 1 byte, 8 bits, MSBit is signed. so 7 bits represents data. 
	// <disconnected> message has 14 bytes
	int rssi;
	// 4 bytes, 2 bytes are '<' & '>', 1 bytes is 'R' and 1 byte is the rssi value
	// '<' 'R' 'rssi' '>'
	size_t bytes = writeCommandBytes("RSSI", _buffer, BUFF_SIZE);

	// Bytes are: byte[0] = '<', byte[1] = 'R', byte[2] = 'RSSIvalue',  byte[3] = '>' 
	if (bytes == 4)
		rssi = (int)_buffer[2];
	else
		rssi = 0;

	return String(-rssi);
}


void HJ580::setMasterMode()
{
	digitalWrite(BLE_RESET, 	LOW);		// System NOT in Reset
	digitalWrite(BLE_ENABLE, 	LOW);		// Uart RX enabled
	digitalWrite(BLE_CONFIG, 	LOW);		// Config mode ON.
	digitalWrite(BLE_MSTR_SLV, 	LOW);		// Master mode
	softReset();	
}

void HJ580::setSlaveMode()
{
	digitalWrite(BLE_RESET, 	LOW);		// System NOT in Reset
	digitalWrite(BLE_ENABLE, 	LOW);		// Uart RX enabled
	digitalWrite(BLE_CONFIG, 	LOW);		// Config mode ON.
	digitalWrite(BLE_MSTR_SLV, 	HIGH);		// Slave mode
	softReset();	
}


String HJ580::getErrors()
{
	String errors;
	if (_errors.length() <= 2)
		_errors = String("\tNONE\n");
	
	errors = _errors;
	_errors = String();
	return errors;
}