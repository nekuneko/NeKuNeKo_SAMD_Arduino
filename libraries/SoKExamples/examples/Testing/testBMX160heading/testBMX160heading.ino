 /*!
  * file readAllData.ino
  *
  * Through the example, you can get the sensor data by using getSensorData:
  * get all data of magnetometer, gyroscope, accelerometer.
  * 
  * With the rotation of the sensor, data changes are visible.
  *
  * Copyright   [DFRobot](http://www.dfrobot.com), 2016
  * Copyright   GNU Lesser General Public License
  *
  * version  V0.1
  * date  2019-6-25
  */

#include <DFRobot_BMX160.h>

DFRobot_BMX160 bmx160;
void setup(){
  Serial.begin(115200);
  delay(100);
  
  //init the hardware bmx160  
  if (bmx160.begin() != true){
    Serial.println("init false");
    while(1);
  }
  //bmx160.setLowPower();   //disable the gyroscope and accelerometer sensor
  //bmx160.wakeUp();        //enable the gyroscope and accelerometer sensor
  //bmx160.softReset();     //reset the sensor
  
  /** @typedef enum{eGyroRange_2000DPS,
   *                eGyroRange_1000DPS,
   *                eGyroRange_500DPS,
   *                eGyroRange_250DPS,
   *                eGyroRange_125DPS
   *                }eGyroRange_t;
   **/
  //bmx160.setGyroRange(eGyroRange_500DPS);
  
  /** @typedef enum{eAccelRange_2G,
   *                eAccelRange_4G,
   *                eAccelRange_8G,
   *                eAccelRange_16G
   *                }eAccelRange_t;
   */
  //bmx160.setAccelRange(eAccelRange_4G);
  delay(100);
}

void loop(){
  bmx160SensorData Omagn, Ogyro, Oaccel;

  /* Get a new sensor event */
  bmx160.getAllData(&Omagn, &Ogyro, &Oaccel);

  float Pi = 3.14159;

  // Calculate the angle of the vector y,x
  float heading = (atan2(Omagn.y, Omagn.x) * 180) / Pi;

  // Normalize to 0-360
  if (heading < 0) {
    heading = 360 + heading;
  }
  Serial.print("Compass Heading: ");
  Serial.println(heading);
  delay(500);
}
