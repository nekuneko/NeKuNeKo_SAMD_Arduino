#include <drivesok.h>
DriveSoK car;

void setup() {
  Serial.begin(115200);
 // while(!Serial);
  Serial.println("Drive SoK motors test");
  
  digitalWrite(LED_BUILTIN, LOW);
  car.begin();
}

void loop() {

  Serial.println("Lights On");
  car.turnForeLights(ON);
  car.turnBackLights(ON);
  
  Serial.println("Ready...? GO");
  car.turn(0);
  car.go(50);
  delay(5000);
  
  Serial.println("Turn Right");
  car.turn(100);
  delay(2500);

  Serial.println("Turn Left");
  car.turn(-100);
  delay(2500);

  Serial.println("Turn Straight");
  car.turn(0);

  Serial.println("Accelerate");
  car.accelerate();
  car.accelerate();
  car.go(50);
  delay(5000);

  Serial.println("Decelerate");
  car.decelerate();
  car.decelerate();
  car.go(50);
  delay(5000);

  Serial.println("Backwards");
  car.decelerate();
  car.go(-50);
  delay(5000);

  Serial.println("Turn off all");
  car.stop();
  car.turnForeLights(OFF);
  car.turnBackLights(OFF);
  delay(5000);

  Serial.println("Flash lights");
  car.flashLights();
  delay(2500);

}
