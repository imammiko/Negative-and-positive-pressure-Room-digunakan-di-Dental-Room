class NrfKom: public RF24 {
  public:
    NrfKom(int pipe[2], int pin1, int pin2);
     void deklarasi();
    void mengirim(String data);
    void menerima();
    int lihat();
    int _pipes[2];
    byte counter = 1;
  private:

};



NrfKom::NrfKom(int pipe[2], int pin1, int pin2): RF24(pin1, pin2) {
  memcpy (this->_pipes, pipe,  sizeof(int) * 2);
  // Serial.println(_pipes[0] );
}
int NrfKom::lihat() {
  return _pipes[0];
}

void NrfKom::deklarasi() {

  this->begin();
  this->setAutoAck(1);                    // Ensure autoACK is enabled
  this->enableAckPayload();               // Allow optional ack payloads
  this->setRetries(0, 15);                // Smallest time between retries, max no. of retries
  //this->setPayloadSize(1);                // Here we are sending 1-byte payloads to test the call-response speed
  this->startListening();                 // Start listening
  this->printDetails();
}

void NrfKom::mengirim(String data) {
  this->openWritingPipe(this->_pipes[0]);
  this->openReadingPipe(1, this->_pipes[1]);
  this->stopListening();                                  // First, stop listening so we can talk.
  char text[] = "haloo";
  printf("Now sending %d as payload. ", this->counter);
  byte gotByte;
  unsigned long time = micros();                          // Take the time, and send it.  This will block until complete
  //Called when STANDBY-I mode is engaged (User is finished sending)
  if (!this->write(&text, sizeof(text))) {
    Serial.println(F("failed."));
  } else {
    if (!this->available()) {
      Serial.println(F("Blank Payload Received."));
    } else {
      while (this->available()) {
        unsigned long tim = micros();
        this->read(&gotByte, 1);
        printf("Got response %d, round-trip delay: %lu microseconds\n\r", gotByte, tim - time);
        this->counter++;
      }
    }
  }
  // Try again later
  delay(1000);
  // Try again later
  // delay();
}

void NrfKom::menerima() {

  this->openWritingPipe(this->_pipes[1]);
  this->openReadingPipe(1,  this->_pipes[0]);
  this->startListening();
  byte pipeNo;
  char gotByte[32] = "";
  byte text = 1; // Dump the payloads until we've gotten everything
  while (this->available(&pipeNo)) {
    this->read(&gotByte, sizeof(gotByte));
    this->writeAckPayload(pipeNo, &text, 1);
    Serial.print(gotByte);
    Serial.print(F("Received message and replied at "));
    Serial.println(millis());
  }
}
