#include "drivesok.h"



void DriveSoK::begin ()
{
	// Initializing Lights
	for (int i=0; i<4; ++i)
	{
		pinMode(LIGHTS_REAR[i], OUTPUT);
		digitalWrite(LIGHTS_REAR[i], LOW);

		pinMode(LIGHTS_FRONT[i], OUTPUT);
		digitalWrite(LIGHTS_FRONT[i], LOW);
	}

	lightState = false;


	// Initializing motors.  The library will allow you to initialize as many motors as you have memory for.  
	// If you are using functions like forward that take 2 motors as arguements you can either write new functions 
	// or call the function more than once.
	motorFront =new Motor(AIN1, AIN2, PWMA, offsetFront, STBY); // FRONT, -255 LEFT, +255 RIGHT
	motorRear  =new Motor(BIN1, BIN2, PWMB, offsetRear, STBY);  // REAR, +255 FORWARD, -255 BACKWARD

	turn(50);
	motorRear->brake();
}



// Power 1 - 100 (1 LEFT; 50 - STRAIGHT; 100 - RIGHT)
void DriveSoK::turn (uint8_t power, int duration)
{
	constrain(power, 1, 100);
	motorFront->drive(map(power, 1, 100, -255, 255), duration);
//	if (power == 50)
//		motorFront->brake();
}

// direction 0 - Backward; 1 - Forward
// Power 0 - 100
void DriveSoK::go (bool forward, uint8_t power, int duration)
{
	power = map (power, 1, 100, 0, 255);
	motorRear->drive(forward?power:-power, duration);
}

void DriveSoK::stop ()
{
	motorRear->brake();
	motorFront->brake();
}


void DriveSoK::lights ()
{
	lightState = !lightState;

	for (int i=0; i<4; ++i)
	{
		digitalWrite(LIGHTS_REAR[i], lightState);
		digitalWrite(LIGHTS_FRONT[i], lightState);
	}
}


DriveSoK::~DriveSoK ()
{
	if (motorFront != nullptr)
		delete(motorFront);

	if (motorRear != nullptr)
		delete(motorRear);
}

void DriveSoK::lightsGame ()
{
	for (int j=1; j<=5; ++j)
	{
		// Lights ON
		for (int i=0; i<4; ++i)
		{
			digitalWrite(LIGHTS_FRONT[i], HIGH);
			digitalWrite(LIGHTS_REAR[i], HIGH);
		}

		delay(250);

		// Lights OFF
		for (int i=0; i<4; ++i)
		{
			digitalWrite(LIGHTS_FRONT[i], LOW);
			digitalWrite(LIGHTS_REAR[i], LOW);
		}

		delay(250);
	}

	if (lightState)
	{
		// Lights ON
		for (int i=0; i<4; ++i)
		{
			digitalWrite(LIGHTS_FRONT[i], HIGH);
			digitalWrite(LIGHTS_REAR[i], HIGH);
		}
	}
}

void DriveSoK::powerOn()
{
	// Power on Lights
	if (!lightState)
		lights();
}

void DriveSoK::shutdown ()
{
	// Shutdown Motors
	motorRear->brake();
	motorFront->brake();

	// Shutdown Lights
	if (lightState)
		lights();

	ble.writeCommand("DISCONNECT");
}

void driveLoop ()
{
	String command = ble.readCommand();

	SerialUSB.println(command);
	int a;

	if (command.equalsIgnoreCase("arrancar"))
		car.powerOn();
	else if (command.equalsIgnoreCase("apagar"))
		car.shutdown();
	else if (command.equalsIgnoreCase("luces"))
		car.lights();
	else if (command.equalsIgnoreCase("parar"))
		car.stop();
	else if (command.equalsIgnoreCase("adelante"))
		car.go(FORWARD, 45);
	else if (command.equalsIgnoreCase("atrás"))
		car.go(BACKWARD, 40);
	else if (command.equalsIgnoreCase("izquierda"))
		car.turn(1);
	else if (command.equalsIgnoreCase("recto"))
		car.turn(50);
	else if (command.equalsIgnoreCase("derecha"))
		car.turn(100);
	else if (command.equalsIgnoreCase("especial"))
		car.lightsGame();
	else if (command.equalsIgnoreCase("Código secreto"))
		car.lightsGame();


}