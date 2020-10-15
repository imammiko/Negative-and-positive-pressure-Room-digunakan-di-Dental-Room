

#include <SPI.h>
#include "nRF24L01.h"
#include "RF24.h"
#include "printf.h"
#include "NrfKom.h"
//#include "Data.h"
// Hardware configuration: Set up nRF24L01 radio on SPI bus plus pins 7 & 8

int nodeSensor[2]={1, 2};
int nodeMotor[2]={3, 4};
String nodeAsal[3]={"nodeSensor","nodeMaster","nodeMotor"};
String kataPublish="/rd:1234/mode:publish/data:(pres:2345,ki:23,kp=123,kd:12412)/asal:nodeSensor/channel:billy/";
String channel="billy";
//String kataSubcribe="/rd:1234/mode:subcribe/data:(pres,ki,kp,kd,dp)/asal:nodeMaster/channel:1234/";
NrfKom nrfSensor(nodeSensor,7,8,channel);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600); 
  printf_begin();
//Serial.println(nrfSensor.lihat());
 nrfSensor.deklarasi();
 
              // Dump the configuration of the rf unit for debugging
//  
}

void loop() {
  // put your main code here, to run repeatedly:
 
 //nrfSensor.mengirim("test");
//nrfSensor.menerima();
nrfSensor.pemisah(kataPublish);
}
