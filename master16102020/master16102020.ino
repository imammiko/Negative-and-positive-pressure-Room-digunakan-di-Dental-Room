#include <SPI.h>
#include "nRF24L01.h"
#include "RF24.h"
#include "printf.h"
#define transmitter "transmitter"
#define reciver "reciver"

//====================mengirim=============
RF24 radio(7, 8);
const uint64_t pipes[2] = { 0xABCDABCD71LL, 0x544d52687CLL };
byte counter = 1;
int statusPipe = 0;
byte randomData=0;
String channel="billy";

//===========merakit===================
String dataObjek[5] = {"/rd:", "/mode:", "/data:", "/asal:", "/channel:"};
//==============data=================== 
int sensor=0;
int ki=0;
int kp=0;
int kd=0;



void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);

  printf_begin();
  radio.begin();
  radio.setAutoAck(1);                    // Ensure autoACK is enabled
  radio.enableAckPayload();               // Allow optional ack payloads
  radio.setRetries(0, 15);                // Smallest time between retries, max no. of retries
  //radio.setPayloadSize(1);                // Here we are sending 1-byte payloads to test the call-response speed
  // radio.openWritingPipe(pipes[1]);        // Both radios listen on the same pipes by default, and switch when writing
  // radio.openReadingPipe(1, pipes[0]);
  radio.startListening();                 // Start listening
  radio.printDetails();
}

void loop() {
  // put your main code here, to run repeatedly:
kirim("test guys");
//terima();
}
