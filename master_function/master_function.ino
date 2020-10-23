#include <SPI.h>
#include "nRF24L01.h"
#include "RF24.h"
#include "printf.h"

RF24 radio(7, 8);


const unsigned short int _pipes[2] = {1, 2};


byte counter = 1;

void setup() {
  Serial.begin(115200);
  printf_begin();

  //=======================radio ==========================
  //  radio.begin();
  //  radio.printDetails();
  //  radio.setPALevel(RF24_PA_LOW);

  radio.begin();
  radio.setAutoAck(1);                    // Ensure autoACK is enabled
  radio.enableAckPayload();               // Allow optional ack payloads
  radio.setRetries(0, 15);                // Smallest time between retries, max no. of retries
  //radio.setPayloadSize(1);                // Here we are sending 1-byte payloads to test the call-response speed
//  radio.openWritingPipe(pipes[1]);        // Both radios listen on the same pipes by default, and switch when writing
//  radio.openReadingPipe(1, pipes[0]);
  radio.startListening();                 // Start listening
  radio.printDetails();

}

void loop() {
  //mengirim("");
  menerima();
}

void mengirim(String data) {
  radio.openWritingPipe(_pipes[0]);
  radio.openReadingPipe(0, _pipes[1]);
  radio.stopListening();                                    // First, stop listening so we can talk.

  // First, stop listening so we can talk.
  char text[] = "haloo";
  printf("Now sending %d as payload. ", counter);
  byte gotByte;
  unsigned long time = micros();                          // Take the time, and send it.  This will block until complete
  //Called when STANDBY-I mode is engaged (User is finished sending)
  if (!radio.write(&text, sizeof(text))) {
    Serial.println(F("failed."));
  } else {
    if (!radio.available()) {
      Serial.println(F("Blank Payload Received."));
    } else {
      while (radio.available()) {
        unsigned long tim = micros();
        radio.read(&gotByte, 1);
        printf("Got response %d, round-trip delay: %lu microseconds\n\r", gotByte, tim - time);
        counter++;
      }
    }
  }
  // Try again later
  //delay();
}


void menerima() {

  radio.openWritingPipe(_pipes[1]);
  radio.openReadingPipe(0, _pipes[0]);
  radio.startListening();
  byte pipeNo;
  char gotByte[32] = "";
  byte text = 1; // Dump the payloads until we've gotten everything
  while (radio.available(&pipeNo)) {
    radio.read(&gotByte, sizeof(gotByte));
    radio.writeAckPayload(pipeNo, &text, 1);
    Serial.print(gotByte);
    Serial.print(F("Received message and replied at "));
    Serial.println(millis());
  }
}
