/*
* Arduino Wireless Communication Tutorial
*     Example 1 - Transmitter Code
*                
* by Dejan Nedelkovski, www.HowToMechatronics.com
* 
* Library: TMRh20/RF24, https://github.com/tmrh20/RF24/
*/

#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
int count=0;
RF24 radio(7, 8); // CE, CSN

const byte address[6] = "00001";

void setup() {
    Serial.begin(9600); 
  radio.begin();
  radio.openWritingPipe(address);
  radio.setPALevel(RF24_PA_MIN);
  radio.stopListening();
}

void loop() {
  const String text = "Hello World saya mau mencoba nilai dengan tipe data string semoga bisa di aplikasikan ke tempat lanin";
  count+=1;
  radio.write(&text, sizeof(text));
  Serial.print(text);
  delay(1000);
}
