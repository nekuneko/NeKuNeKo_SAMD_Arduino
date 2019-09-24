#include <gamesok.h>


void setup() {
  Serial.begin(115200);
  //while(!Serial);
  gameBegin();
}

void loop() 
{
   gameLoop();
}
