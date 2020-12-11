void deklarasiKom() {
  SPI.begin();
  radio.begin();
  network.begin(/*channel*/ 90, /*node address*/ nodeSensor);
  radio.setPALevel(RF24_PA_MAX);

}

void txKom(struct payload_t payload) {
  network.update();                          // Check the network regularly
  Serial.print("Sending...");
  RF24NetworkHeader header(/*to node*/ masterSensor);
  bool ok = network.write(header, &payload, sizeof(payload));
  if (ok)
    Serial.println("ok.");
  else{
    Serial.println("failed");
    }

}
