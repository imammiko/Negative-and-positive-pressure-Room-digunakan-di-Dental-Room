

#include <SPI.h>
#include "nRF24L01.h"
#include "RF24.h"
#include "printf.h"
#include "NrfKom.h"

//======define carakter string///


const uint64_t nodeSensor[2]={0xABCDABCD71LL, 0x544d52687CLL};
int nodeMotor[2]={3, 4};
String kataPublish="/rd:1234/mode:publish/data:(sensor:2345,ki:23,kp=123,kd:12412)/asal:nodeSensor/channel:billy/";
int sensor=0;
int ki=0;
int kp=0;
int kd=0;
//String kataSubcribe="/rd:1234/mode:subcribe/data:(pres,ki,kp,kd,dp)/asal:nodeMaster/channel:1234/";

//=========================data dikirim============



int randomData=0;
String nodeAsal[3]={"nodeSensor","nodeMaster","nodeMotor"};
String channel="billy";
//==================================================
NrfKom nrfSensor(nodeSensor,7,8,channel,nodeAsal);
void setup() {

  Serial.begin(9600); 
  printf_begin();

 nrfSensor.deklarasi();
 
              
//  
}

void loop() {
//nodeAsal[3];
 //Serial.println(nrfSensor.lihat());
 //nrfSensor.mengirim("test");

//nrfSensor.pemisah(kataPublish);
nrfSensor.menerima();


//String objek[]={"kp","ki","kd"} ;int nilaikObjek[]={1,2,3};nrfSensor.merakit("publish",objek, nilaikObjek,3);


//int x=sizeof(nilaikObjek) / sizeof(nilaikObjek[0]);
  //Serial.println(x);
}
