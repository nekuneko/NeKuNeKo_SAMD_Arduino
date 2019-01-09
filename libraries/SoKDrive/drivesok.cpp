#include "drivesok.h"


void DriveSoK::begin ()
{
	// Initializing Lights
	turnForeLights(OFF);
	turnBackLights(OFF);

	// Initializing motors.  The library will allow you to initialize as many motors as you have memory for.  
	// If you are using functions like forward that take 2 motors as arguements you can either write new functions 
	// or call the function more than once.
	foreMotor =new Motor(AIN1, AIN2, PWMA, offsetFront, STBY); // FRONT: -255 LEFT, 	+255 RIGHT
	backMotor =new Motor(BIN1, BIN2, PWMB, offsetRear,  STBY); // REAR:  +255 FORWARD, -255 BACKWARD

	foreMotor->brake();
	backMotor->brake();
}


DriveSoK::~DriveSoK ()
{
	if (foreMotor != nullptr)
		delete(foreMotor);

	if (backMotor != nullptr)
		delete(backMotor);
}


// power: 	-100 to 100, left, Straight, Right
// delay:	seconds to delay
void DriveSoK::turn (int power, int delayMillis)
{
	analogWriteResolution(8);

	power = constrain(power, -100, 100);
	power = map(power, -100, 100, -255, 255); // 255 is for 8 bit analog write resolution
	foreMotor->drive(power, delayMillis);

//	if (power == 0)
//		foreMotor->brake();
}



// power: 	-100 to +100, Backward, Stop, Forward
// delay: 	seconds to delay
void DriveSoK::go (int power, int delayMillis)
{
	analogWriteResolution(8);

	if (power > 0)
		power += _powerOffset;
	else if (power < 0)
		power -= _powerOffset;
	
	power = constrain(power, -100, 100);
	power = map (power, -100, 100, -255, 255); // 255 is for 8 bit analog write resolution
	backMotor->drive(power, delayMillis);

	// If backwards or stopped, turn on back lights
	if (power <= 0)
		turnBackLights(ON);
	else // forward, turn off back lights
		turnBackLights(OFF);

//	if (power == 0)
//		foreMotor->brake();
}


void DriveSoK::stop ()
{
	backMotor->brake();
	
	// We are pulling the brake, so turn on back lights
	turnBackLights(ON);
}


void DriveSoK::turnForeLights (bool onOff)
{
	for (int i=0; i<4; ++i)
		digitalWrite(FORE_LIGHTS[i], onOff);

	_foreLightState = onOff;
}


void DriveSoK::turnBackLights (bool onOff)
{
	for (int i=0; i<4; ++i)
		digitalWrite(BACK_LIGHTS[i], onOff);

	_backLightState = onOff;
}


void DriveSoK::flashLights (int delayMillis, int numFlashes)
{
	for (int i=1; i<=numFlashes; ++i)
	{
		turnForeLights(ON);
		turnBackLights(ON);

		delay(delayMillis);

		turnForeLights(OFF);
		turnBackLights(OFF);

		delay(delayMillis);
	}

	// restore previous light state
	if (_foreLightState)
		turnForeLights(ON);

	if (_backLightState)
		turnBackLights(ON);
}


void DriveSoK::powerOn()
{
	// Power on Lights
	if (!_foreLightState)
		turnForeLights(ON);
}


void DriveSoK::shutdown ()
{
	// Shutdown Motors
	backMotor->brake();
	foreMotor->brake();

	// flash lights for last time & turn them off
	_foreLightState = OFF;
	_backLightState = OFF;
	flashLights();

	ble.writeCommand("DISCONNECT");
}


void DriveSoK::accelerate ()
{

	_powerOffset += 10;
}


void DriveSoK::decelerate ()
{
	_powerOffset -= 10;
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
		car.turnForeLights(!car.foreLightState());
	else if (command.equalsIgnoreCase("parar"))
		car.stop();
	else if (command.equalsIgnoreCase("adelante"))
		car.go(50);
	else if (command.equalsIgnoreCase("atrás"))
		car.go(-50);
	else if (command.equalsIgnoreCase("izquierda"))
		car.turn(-100);
	else if (command.equalsIgnoreCase("recto"))
		car.turn(0);
	else if (command.equalsIgnoreCase("derecha"))
		car.turn(100);
	else if (command.equalsIgnoreCase("acelerar"))
		car.accelerate();
	else if (command.equalsIgnoreCase("decelerar"))
		car.decelerate();
	else if (command.equalsIgnoreCase("especial"))
		car.flashLights();
	else if (command.equalsIgnoreCase("Código secreto"))
		car.flashLights();


}