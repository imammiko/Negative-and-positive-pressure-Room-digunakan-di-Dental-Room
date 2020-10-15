class NrfKom: public RF24 {
  public:
    NrfKom(int pipe[2], int pin1, int pin2,String channel);
    void deklarasi();
    void mengirim(String data);
    void menerima();
    int lihat();
    void pemisah(String data);
    String segment(String objek, String data);
    void merakit();
    //=========================
    int _pipes[2];
    byte counter = 1;
    String channel="";
    

  private:
    String dataObjek[5] = {"/rd", "/mode", "/data", "/asal", "/channel"};
};



NrfKom::NrfKom(int pipe[2], int pin1, int pin2,String channel): RF24(pin1, pin2) {
  memcpy (this->_pipes, pipe,  sizeof(int) * 2);
  this->channel=channel;
  // Serial.println(_pipes[0] );
}
int NrfKom::lihat() {
  return _pipes[0];
}

void NrfKom::deklarasi() {

  this->begin();
  // this->setAutoAck(1);                    // Ensure autoACK is enabled
  // this->enableAckPayload();               // Allow optional ack payloads
  //this->setRetries(0, 15);                // Smallest time between retries, max no. of retries
  //this->setPayloadSize(1);                // Here we are sending 1-byte payloads to test the call-response speed
  // this->startListening();                 // Start listening
  this->printDetails();
  this->setPALevel(RF24_PA_MAX);
}

void NrfKom::mengirim(String data) {
  this->openWritingPipe(this->_pipes[0]);
  this->openReadingPipe(0, this->_pipes[1]);
  this->stopListening();                                  // First, stop listening so we can talk.
  char text[100] = "";
  data.toCharArray(text, 100);
  this->write(&text, sizeof(text));
  //unsigned long time = micros();                          // Take the time, and send it.  This will block until complete
  //Called when STANDBY-I mode is engaged (User is finished sending)
  delay(1000);
  // Try again later
  // delay();
  Serial.println(text);
}

void NrfKom::menerima() {

  this->openWritingPipe(this->_pipes[1]);
  this->openReadingPipe(0, this->_pipes[0]);
  this->startListening();
  if (this->available()) {
    char text[100] = "";
    this->read(&text, sizeof(text));
    Serial.println(text);
  }
}

void NrfKom::pemisah(String data) {
  String penampungData = data;
  if (this->segment(dataObjek[4],data)==this->channel){
     Serial.println(this->segment(dataObjek[4], data));
  }
 

}

String NrfKom::segment(String objek, String data) {
  String penampungData = data;
  String hasil =
    penampungData.substring(
      penampungData.indexOf(":", penampungData.indexOf(objek) + 1) + 1,
      penampungData.indexOf("/", penampungData.indexOf(objek) + 1)

    );
  return hasil;
}
