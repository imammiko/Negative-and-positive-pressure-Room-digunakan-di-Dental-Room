void nrfConfig() {
  SPI.begin();
  radio.begin();
  network.begin(90, this_node);  //(channel, node address)
  //radio.setDataRate(RF24_2MBPS);
}

void kirimDataNodeSensor(struct data *datas) {//**
  network.update();
  unsigned long now = millis();              // If it's time to send a message, send it!
  if ( now - waktuNodeSensor.last_sent >= waktuNodeSensor.interval  )
  {
    waktuNodeSensor.last_sent = now;
    RF24NetworkHeader header1(/*to node*/ nodeSensor);
    bool ok = network.write(header1, &datas, sizeof(datas));
    if (ok)
      Serial.println("ok.");
    else
      Serial.println("failed.");
  }
}

void kirimDataNodeMotor(struct data *datas) {//**
  network.update();
  unsigned long now = millis();              // If it's time to send a message, send it!
  if ( now - waktuNodeMotor.last_sent >= waktuNodeMotor.interval  )//**
  {
    waktuNodeMotor.last_sent = now;
    RF24NetworkHeader header2(/*to node*/ nodeMotor);
    bool ok = network.write(header2, &datas, sizeof(datas));
    if (ok)
      Serial.println("ok.");
    else
      Serial.println("failed.");
  }
}

void menerimaData() {
  network.update();
  while ( network.available() ) {     // Is there anything ready for us?

    RF24NetworkHeader header;        // If so, grab it and print it out
    data dataTerima;
    network.read(header, &dataTerima, sizeof(dataTerima));
    if(dataTerima.asal==1){//**
      dataNodeMaster.pressureLuar=dataTerima.pressureLuar;
    }else if(dataTerima.asal==2){//**
      dataNodeMaster.nilaiP=dataTerima.nilaiP;
    }else{
      Serial.println ("asal tidak di ketahui");
    }

    
//    Serial.print("1");
    Serial.print(dataTerima.asal);
    Serial.print("|");
    Serial.println(dataTerima.pressureLuar);
//    Serial.print(" at ");
//    Serial.println(dataTerima.pressureDalam);
  }
}
