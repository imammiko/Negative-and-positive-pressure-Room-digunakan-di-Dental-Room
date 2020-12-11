


void menerimaDataNode() {
  network.update();                  // Check the network regularly

  while ( network.available() ) {     // Is there anything ready for us?
    sensor.statusConnect = 1;
    a1.last = millis();
    RF24NetworkHeader header;        // If so, grab it and print it out

    network.read(header, &senLuar, sizeof(senLuar));


    data.pressureLuar = senLuar.pressureLuar;
    //Serial.println(senLuar.pressureLuar);

  }


}
