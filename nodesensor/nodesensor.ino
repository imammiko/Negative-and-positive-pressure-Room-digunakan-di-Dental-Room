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
RF24 radio(7,8);                // nRF24L01(+) radio attached using Getting Started board 

RF24Network network(radio);      // Network uses that radio
const uint16_t this_node = 01;    // Address of our node in Octal format ( 04,031, etc)
const uint16_t master = 00; // Address of the other node in Octal format
const uint16_t nodeMotor=02;

struct data{
  int pressureLuar;
  int pressureDalam;
  short int nilaiP;
  short int nilaiI;
  short int nilaiD;
  int speedMotorMax;
  bool nodeSensor;
  bool nodeMaster;
  bool nodeMotor;
};

//================

void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);
  Serial.println(F("nodesensort"));
 
 bmpConfig();
}

void loop() {
 //Serial.print( bmpPressure());
//Serial.println();
network.update();                  // Check the network regularly

//  // ======reciving
//  while ( network.available() ) {     // Is there anything ready for us?
//    
//    RF24NetworkHeader header;        // If so, grab it and print it out
//    data dataTerima;
//    network.read(header,&dataTerima,sizeof(dataTerima));
//    Serial.print("1");
//    Serial.print("Received packet #");
//    Serial.print(dataTerima.pressureLuar);
//    Serial.print(" at ");
//    Serial.println(dataTerima.pressureDalam);
//  }
////======

//=======ngirim 
int a=23;
    data dataKirim = {1 ,2,3,4,5,6,1,1,1};
    RF24NetworkHeader header1(/*to node*/ master);
    bool ok = network.write(header1,&a,sizeof(a));
     if (ok)
      Serial.println("ok.");
    else
      Serial.println("failed.");
//==========  
}
