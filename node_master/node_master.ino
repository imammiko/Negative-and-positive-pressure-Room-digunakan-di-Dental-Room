#include <RF24Network.h>
#include <RF24.h>
#include <SPI.h>
//===========bmp==========
#include <Adafruit_BMP280.h>
Adafruit_BMP280 bmp; // use I2C interface
Adafruit_Sensor *bmp_temp = bmp.getTemperatureSensor();
Adafruit_Sensor *bmp_pressure = bmp.getPressureSensor();
//***************************bmp

RF24 radio(7, 8);

RF24Network network(radio);
const uint16_t nodeSensor = 00;
const uint16_t masterSensor = 01;
//=========variable
float valuePressure = 0;
float lastValuePressure = 0;
//*****************variable
struct payload_t {                 // Structure of our payload
  unsigned long msNodeSensor;
  unsigned long msNodeMaster;
  float sensorBmpSensor;
  float sensorBmpMaster;
};
payload_t payload;

void setup(void)
{
  Serial.begin(9600);
  Serial.println("RF24Network/examples/helloworld_rx/");
  deklarasiKom();
  bmpDeklarasi();
}

void loop(void) {
  rxKom(&payload);

}
