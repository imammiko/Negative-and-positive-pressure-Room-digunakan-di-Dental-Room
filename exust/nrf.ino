void nrfConfig(int channel, const uint16_t nodeAddres) {
  SPI.begin();
  radio.begin();
  network.begin(channel, nodeAddres);  //(channel, node address)
  radio.setPALevel(RF24_PA_MIN);
  //radio.setDataRate(R  F24_2MBPS);
}

bool kirimData(struct motorAc *datas, const uint16_t node, byte modeKirim) { //**
  //  int MAX,V;
  //  unsigned int SPEED, SETPOINT, KP, KD;
  //  double pressureLuar;
  //  double pressureDalam;
  //==================transfer
  if (exaust == nodeSensorE && node == nodeMaster) {
    if (modeKirim == publish) {
      data.modeKirim = publish;
      dataKom.modeKirim = data.modeKirim;
      dataKom.pressureLuar = data.pressureLuar;
    } else if (modeKirim == ping) {
      data.modeKirim = ping;
      dataKom.modeKirim = data.modeKirim;
    }

  } else if (exaust == nodeMasterE && node == nodeMotor) {
    if (modeKirim == publish) {
      data.modeKirim = publish;
      dataKom.modeKirim = publish;
      dataKom.pressureLuar = data.pressureLuar;
      dataKom.pressureDalam = data.pressureDalam;


      dataKom.kp = data.kp;
      dataKom.kd = data.kd;
      dataKom.maxMotor = data.maxMotor;
      dataKom.setPoint = data.setPoint;
      dataKom.statusHidup = data.statusHidup;
      dataKom.dp = data.dp;
      dataKom.set = data.set;
      dataKom.dpSet = data.dpSet;
      dataKom.minMotor = data.minMotor;
    } else if (modeKirim == ping) {
      data.modeKirim = ping;
      dataKom.modeKirim = data.modeKirim;

    }


  } else if (exaust == nodeMotorE && node == nodeMaster) {
    if (modeKirim == publish) {
      data.modeKirim = publish;
      dataKom.modeKirim = data.modeKirim;


      dataKom.kp = data.kp;
      dataKom.kd = data.kd;
      dataKom.setPoint = data.setPoint;
      dataKom.maxMotor = data.maxMotor;

      dataKom.statusHidup = data.statusHidup;
      dataKom.dp = data.dp;
      dataKom.set = data.set;
      dataKom.dpSet = data.dpSet;
      dataKom.minMotor = data.minMotor;
    } else if (modeKirim == ping) {
      data.modeKirim = ping;
      dataKom.modeKirim = data.modeKirim;

    }
  }
  //****************transfer

  network.update();
  //  unsigned long now = millis();              // If it's time to send a message, send it!
  //  if ( now - last_sent >= interval  )
  //  {
  //  last_sent = now;

  RF24NetworkHeader header2(/*to node*/ node);
  bool ok = network.write(header2, datas, sizeof(*datas));
  if (ok) {
    Serial.print(node);
    Serial.println("ok.");
    if (node == nodeSensor && exaust != nodeSensorE  && exaust != nodeMotorE) {
      sensor.statusConnect = 1;
      if (modeKirim == publish || modeKirim == ping) {
        sensor.statusGagal = 0;
      }
      a2.last = millis();
    } else if (node == nodeMaster && exaust != nodeMasterE) {
      master.statusConnect = 1;
      if (modeKirim == publish || modeKirim == ping) {
        Serial.println("ping master1");
        master.statusGagal = 0;
      }
      a3.last = millis();
    } else if (node == nodeMotor && exaust != nodeMotorE) {
      motor.statusConnect = 1;
      if (modeKirim == publish || modeKirim == ping) {
        motor.statusGagal = 0;
      }
      a4.last = millis();
    }
    return true;
  }
  else {
    Serial.print(node);
    Serial.println("failed.");
    if (node == nodeSensor && exaust != nodeSensorE  && exaust != nodeMotorE) {
      sensor.statusConnect = 0;
      if (modeKirim == publish || modeKirim == ping) {
        sensor.statusGagal = 1;
      }
      a2.last = millis();
    } else if (node == nodeMaster && exaust != nodeMasterE) {
      Serial.println("ping master0");
      master.statusConnect = 0;
      if (modeKirim == publish || modeKirim == ping) {
        Serial.println("ping master1");
        master.statusGagal = 1;
      }
      a3.last = millis();
    } else if (node == nodeMotor && exaust != nodeMotorE) {
      motor.statusConnect = 0;
      if (modeKirim == publish || modeKirim == ping) {
        motor.statusGagal = 1;
      }
      a4.last = millis();
    }

    // }
    return false;
  }
}
void menerimaDataNode(struct motorAc * datas) {
  network.update();                  // Check the network regularly


  while ( network.available() ) {     // Is there anything ready for us?

    RF24NetworkHeader header;        // If so, grab it and print it out

    network.read(header, datas, sizeof(*datas));
    if (header.from_node == nodeSensor && exaust != nodeSensorE  && exaust != nodeMotorE) {
      sensor.statusConnect = 1;
      a2.last = millis();
    } else if (header.from_node == nodeMaster && exaust != nodeMasterE) {
      master.statusConnect = 1;
      a3.last = millis();
    } else if (header.from_node == nodeMotor && (exaust == nodeMotorE)) {
      motor.statusConnect = 1;
      a4.last = millis();
    }


    if (header.from_node == nodeSensor && exaust == nodeMasterE) {
      //if(
      data.modeKirim = dataKom.modeKirim;
      if (data.modeKirim == publish) {
        data.pressureLuar = dataKom.pressureLuar;
      } else if (data.modeKirim == ping) {
      }


    } else if (header.from_node == nodeMaster && exaust == nodeMotorE) {
      data.modeKirim = dataKom.modeKirim;
      if (data.modeKirim == publish) {
        data.pressureLuar = dataKom.pressureLuar;
        data.pressureDalam = dataKom.pressureDalam;


        data.kp = dataKom.kp;
        data.kd = dataKom.kd;
        data.maxMotor = dataKom.maxMotor;
        data.setPoint = dataKom.setPoint;
        data.statusHidup = dataKom.statusHidup;
        data.dp = dataKom.dp;
        data.set = dataKom.set;
        data.dpSet = dataKom.dpSet;
      } else if (data.modeKirim == ping) {
      }

    } else if (header.from_node == nodeMotor && exaust == nodeMasterE) {
      data.modeKirim = dataKom.modeKirim;
      if (data.modeKirim == publish) {
        data.pressureLuar = dataKom.pressureLuar;
        data.pressureDalam = dataKom.pressureDalam;


        data.kp = dataKom.kp;
        data.kd = dataKom.kd;
        data.setPoint = dataKom.setPoint;
        data.maxMotor = dataKom.maxMotor;

        data.statusHidup = dataKom.statusHidup;
        data.dp = dataKom.dp;
        data.set = dataKom.set;
        data.dpSet = dataKom.dpSet;
        data.minMotor = dataKom.minMotor;

      } else if (data.modeKirim == ping) {
      }


    }
  }

}
