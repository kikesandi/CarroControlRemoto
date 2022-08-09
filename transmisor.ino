#include "SPI.h"
#include "NRFLite.h"
#include <Arduino_LSM6DS3.h>
float x, y, z;



struct ComboDatos // Any packet up to 32 bytes can be sent.
{
  float acelX;
  float acelY;
  float acelZ;
};

NRFLite _radio;
ComboDatos _comboDatos;



void setup()
{
    if (!IMU.begin()) {
    Serial.println("Failed to initialize IMU!");
    while (1);
  }
  _radio.init(1, 9, 10); // Set radio to Id = 1, along with the CE and CSN pins
}

void loop()
{


  if (IMU.accelerationAvailable()) {
    IMU.readAcceleration(x, y, z);
  }

_comboDatos.acelX = x;
_comboDatos.acelY = y;
_comboDatos.acelZ = z;

  Serial.println(_comboDatos.acelX);
  Serial.println(_comboDatos.acelY);
  Serial.println(_comboDatos.acelZ);


  _radio.send(0, &_comboDatos, sizeof(_comboDatos)); // Send data to the radio with Id = 0
  delay(10);
}
