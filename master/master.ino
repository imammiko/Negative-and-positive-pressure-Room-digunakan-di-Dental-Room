//=====bmp==========
#include <Wire.h>
#include <SPI.h>
#include <Adafruit_BMP280.h>
//==================

//======nrf========
#include <RF24Network.h>
#include <RF24.h>
#include <SPI.h>
//=================

//=====bmp==========
Adafruit_BMP280 bmp; // use I2C interface
Adafruit_Sensor *bmp_temp = bmp.getTemperatureSensor();
Adafruit_Sensor *bmp_pressure = bmp.getPressureSensor();
//==================

//======nrf=======
RF24 radio(7, 8);               // nRF24L01(+) radio attached using Getting Started board

RF24Network network(radio);      // Network uses that radio
const uint16_t this_node = 00;    //** Address of our node in Octal format ( 04,031, etc)
const uint16_t nodeSensor = 01; // **Address of the other node in Octal format
const uint16_t nodeMotor = 02;//**


struct waktu {
  const unsigned long interval = 1000; //ms  // How often to send 'hello world to the other unit
  unsigned long last_sent;             // When did we last send?
  unsigned long packets_sent;
};

struct data {
  unsigned int asal;//master0 nodeSensor1 noedMotor2
  double pressureLuar;
  double pressureDalam;
  short int nilaiP;
  short int nilaiI;
  short int nilaiD;
  int speedMotorMax;
  bool nodeSensor;
  bool nodeMaster;
  bool nodeMotor;
};

//================
data dataNodeMaster;//**
waktu waktuNodeSensor;//**
waktu waktuNodeMotor;//**
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial.println(F("master"));
  nrfConfig();
  bmpConfig();
  dataNodeMaster.asal = this_node;
}

void loop() {
dataNodeMaster.pressureDalam=bmpPressure();

menerimaData();

//Serial.println(dataNodeMaster.pressureLuar);


}
