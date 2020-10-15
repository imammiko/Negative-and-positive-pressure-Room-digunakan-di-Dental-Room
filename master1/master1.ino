

#include <SPI.h>
#include "nRF24L01.h"
#include "RF24.h"
#include "printf.h"
#include "NrfKom.h"
// Hardware configuration: Set up nRF24L01 radio on SPI bus plus pins 7 & 8

int nodeSensor[2]={1, 2};
int nodeMotor[2]={3, 4};

NrfKom nrfSensor(nodeSensor,7,8);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600); 
  printf_begin();
//Serial.println(nrfSensor.lihat());
 nrfSensor.deklarasi();
 nrfSensor.begin();
nrfSensor.setAutoAck(1);                    // Ensure autoACK is enabled
nrfSensor.enableAckPayload();               // Allow optional ack payloads
nrfSensor.setRetries(0, 15);                // Smallest time between retries, max no. of retries
//nrfSensor.setPayloadSize(1);                // Here we are sending 1-byte payloads to test the call-response speed
//  //thisopenWritingPipe(pipes[1]);        // Both radios listen on the same pipes by default, and switch when writing
//  //radio.openReadingPipe(1, pipes[0]);
nrfSensor.startListening();                 // Start listening
nrfSensor.printDetails();                   // Dump the configuration of the rf unit for debugging
//  
}

void loop() {
  // put your main code here, to run repeatedly:
 
 nrfSensor.mengirim("test");
//nrfSensor.menerima();
}
