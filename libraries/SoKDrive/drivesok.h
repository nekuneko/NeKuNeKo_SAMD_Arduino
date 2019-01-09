/**

				FRONT
IZQ_A, IZQ_B 			DER_B, DER_A

				REAR
**/


#pragma once

#include <Arduino.h>
#include <hj580.h>
#include <SparkFun_TB6612.h> // This is the library for the TB6612 that contains the class Motor and all the functions

class DriveSoK;
extern DriveSoK car;

// Pins definitions for all inputs, keep in mind the PWM defines must be on PWM pins
// the default pins listed are the ones used on the Redbot (ROB-12097) with
// the exception of STBY which the Redbot controls with a physical switch
// NOTE! This pin definition is only valid for SoK Zero
static const int PWMA = D8;
static const int AIN2 = D7;
static const int AIN1 = D6;
static const int STBY = D5;
static const int BIN1 = D4;
static const int BIN2 = D3;
static const int PWMB = D2;

static const int FORE_LIGHTS[4] = {A1, A0, SCK, MOSI}; // IZQ_A, IZQ_B, DER_A, DER_B
static const int BACK_LIGHTS[4]  = {D9, D11, D13, D12}; // IZQ_A, IZQ_B, DER_A, DER_B

// these constants are used to allow you to make your motor configuration 
// line up with function names like forward.  Value can be 1 or -1
static const int offsetFront = 1;
static const int offsetRear  = -1;

static const bool FORWARD  = true;
static const bool BACKWARD = false;

static const bool ON  = true;
static const bool OFF = false;

class DriveSoK {

public:
	~DriveSoK ();

	void begin ();

	void turn (int power, int delayMillis = 0);
	void go   (int power, int delayMillis = 0);
	void stop ();
	void accelerate ();
	void decelerate ();

	void turnForeLights (bool onOff = ON);
	void turnBackLights (bool onOff = ON);
	void flashLights 	(int  delayMillis = 250, int numFlashes = 5);

	void powerOn  ();
	void shutdown ();

	inline bool foreLightState () { return _foreLightState; }
	inline bool backLightState () { return _backLightState;  }

private:
	Motor* foreMotor = nullptr;
	Motor* backMotor = nullptr;
	
	bool _foreLightState = OFF;
	bool _backLightState = OFF;
	
	int _powerOffset = 0;
};


void driveLoop ();