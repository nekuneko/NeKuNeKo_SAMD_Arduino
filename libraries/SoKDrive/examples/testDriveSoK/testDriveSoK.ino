#include <drivesok.h>
DriveSoK car;

void setup() {
  Serial.begin(115200);
  while(!Serial);
  Serial.println("Drive SoK motors test");
  
  digitalWrite(LED_BUILTIN, LOW);
  car.begin();
}

void loop() {

  turnForeLights(ON);
  turnBackLights(ON);
  turn(0);
  car.go(50);
  delay(5000);

  car.decelerate();
  delay(5000);

  car.accelerate();
  delay(5000);

  car.decelerate();
  car.go(-50);
  delay(5000);

  car.stop();
  turnForeLights(OFF);
  turnBackLights(OFF);
  delay(5000);

  flashLights();
  delay(5000);

  turn(100);
  delay(5000);

  turn(-100);
  delay(5000);
}
