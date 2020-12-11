void nrfConfig(int channel, const uint16_t nodeAddres) {
  SPI.begin();
  radio.begin();
  network.begin(channel, nodeAddres);  //(channel, node address)
  //radio.setDataRate(RF24_2MBPS);
}


void kirimData(struct motorAc *datas, const uint16_t node) { //**
  network.update();
  unsigned long now = millis();              // If it's time to send a message, send it!
  if ( now - last_sent >= interval  )
  {
    last_sent = now;

    RF24NetworkHeader header2(/*to node*/ node);
    bool ok = network.write(header2, datas, sizeof(*datas));
    if (ok)
      Serial.println("ok.");
    else
      Serial.println("failed.");
  }
}

void menerimaDataNode(struct motorAc *datas) {
  network.update();                  // Check the network regularly


  while ( network.available() ) {     // Is there anything ready for us?

    RF24NetworkHeader header;        // If so, grab it and print it out
  
    network.read(header, datas, sizeof(*datas));
  }

}
