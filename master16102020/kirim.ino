void kirim(String data) {
  pipeChange("transmitter");

  printf("Now sending %d as payload. ", counter);
  byte gotByte;
  char text[100] = "";
  data.toCharArray(text, 100);
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
}

void terima() {
  pipeChange("reciver");
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

void pipeChange(String change) {
  if (statusPipe != 1 && change == "transmitter" ) { //transmitter
    statusPipe = 1;
    radio.openWritingPipe(pipes[0]);
    radio.openReadingPipe(1, pipes[1]);
    radio.stopListening();
  } else if (statusPipe != 2 && change == "reciver") { //reciver
    statusPipe = 2;
    radio.openWritingPipe(pipes[1]);
    radio.openReadingPipe(1, pipes[0]);
    radio.startListening();
  } else {
    // Serial.print("perubahan pipe gagal  ");
  }
}
//"/rd:1234/mode:publish/data:(sensor:2345,ki:23,kp=123,kd:12412)/asal:nodeSensor/channel:billy/";
void merakit(String _modeData, int sensor, int ki, int kp, int kd) {
  randomData = random(255);
  String data = "";
  if (_modeData = "publish") {
    data.concat(dataObjek[0]);
    data.concat(randomData);
    data.concat(dataObjek[1]);
    data.concat(_modeData);
    data.concat(dataObjek[2]);
    data.concat("(");

  };
  Serial.println(data);
}
