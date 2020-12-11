#include <SPI.h>
#include "nRF24L01.h"
#include "RF24.h"
#include "printf.h"
#include "NrfKom.h"

//======define carakter string///


const uint64_t nodeSensor[2] = {0xABCDABCD71LL, 0x544d52687CLL};
int nodeMotor[2] = {3, 4};
String kataPublish = "/rd:1234/mode:publish/data:(sensor:2345,ki:23,kp=123,kd:12412)/asal:nodeSensor/channel:billy/";
int sensor = 0;
int ki = 0;
int kp = 0;
int kd = 0;
//String kataSubcribe="/rd:1234/mode:subcribe/data:(pres,ki,kp,kd,dp)/asal:nodeMaster/channel:1234/";

//=========================data dikirim============



int randomData = 0;
String nodeAsal[3] = {"nodeSensor", "nodeMaster", "nodeMotor"};
String channel = "billy";
String serialString = "";
//==================================================
NrfKom nrfSensor(nodeSensor, 7, 8, channel, nodeAsal);
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
  //nrfSensor.menerima();
  int a = 0;
  int r = 0;
  String stringData = "";
  String data = "/md:publish/dt:(sensor:2345,ki:23,kp=123,kd:12412)/sl:nodeSensor/chnl:billy/>";
  if (Serial.available() > 0) {
    // read the incoming byte:
    serialString = Serial.readString();
    //  /a:1/r:87/b:sdaf/
    if (serialString.indexOf("/b:") > -1) {

      stringData = (serialString.substring(serialString.indexOf("/b:") + 3, serialString.indexOf("/", serialString.indexOf("/b:") + 3)));
      nrfSensor.mengirim(stringData);
      Serial.print(serialString);
      Serial.println(stringData);
    } else {

      a = (serialString.substring(serialString.indexOf("/a:") + 3, serialString.indexOf("/", serialString.indexOf("/a:") + 3))).toInt();
      r = (serialString.substring(serialString.indexOf("/r:") + 3, serialString.indexOf("/", serialString.indexOf("/r:") + 3))).toInt();
      nrfSensor.mengirim(nrfSensor.dataGabungHeader(data, a, r ));
      Serial.print(serialString);
      Serial.println(a);
      Serial.println(r);
    }
    // say what you got:

  }





  //String objek[]={"kp","ki","kd"} ;int nilaikObjek[]={1,2,3};nrfSensor.merakit("publish",objek, nilaikObjek,3);


  //int x=sizeof(nilaikObjek) / sizeof(nilaikObjek[0]);
  //Serial.println(x);
}
