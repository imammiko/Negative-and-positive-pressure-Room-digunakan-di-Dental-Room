void deklarasiKom() {
  SPI.begin();
  radio.begin();
  network.begin(/*channel*/ 90, /*node address*/ masterSensor);
  radio.setPALevel(RF24_PA_MAX);

}

void txKom(struct payload_t payload) {
  network.update();                          // Check the network regularly
  Serial.print("Sending...");
  RF24NetworkHeader header(/*to node*/ nodeSensor);
  bool ok = network.write(header, &payload, sizeof(payload));
  if (ok)
    Serial.println("ok.");
  else{
    Serial.println("failed");
    }

}

void rxKom(struct payload_t *payloads){
  network.update();                  // Check the network regularly

  
  while ( network.available() ) {     // Is there anything ready for us?
    
    RF24NetworkHeader header;        // If so, grab it and print it out
    network.read(header,payloads,sizeof(payload));
    Serial.print("Received packet #");
    Serial.print(payload.sensorBmpSensor);
    Serial.print(" at ");
    Serial.println(payload.msNodeSensor);
  }
  }
