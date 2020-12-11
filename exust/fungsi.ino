
void nodeSensorF() {
  data.pressureLuar = bmpPressure();
  menerimaDataNode(&dataKom);
  kirimData(&dataKom, nodeMaster, publish);
  cekKoneksi();

  // Serial.println(data.pressureLuar);


  lcd.setCursor(0, 0); lcd.print("luar:");// menampilkan trace
  lcd.setCursor(7, 0); lcd.print(data.pressureLuar);// menam

}

void nodeMasterF() {
  //motor.pressureDalam = bmpPressure();

  //Serial.println(data.pressureDalam);
  menerimaDataNode(&dataKom);
  data.pressureDalam = bmpPressure();
  data.dp =    data.pressureDalam - data.pressureLuar;
  data.dpSet = data.dp - data.set;
  if (data.dpSet != lastDpSet) {
    lastDpSet = data.dpSet;
    kirimSet();
  }
  cekKoneksi();
  tampilanLcd(tampilan.peek());
  //    lcd.setCursor(0, 0); lcd.print("luar:");// menampilkan trace
  //    lcd.setCursor(7, 0); lcd.print(data.pressureLuar);//
  //    lcd.setCursor(0, 1); lcd.print("Dalam:");// menampilkan trace
  //    lcd.setCursor(7, 1); lcd.print(data.pressureDalam);//
}
void nodeMotorF() {
  menerimaDataNode(&dataKom);
  cekKoneksi();
  tampilanLcd(tampilan.peek());
  if (data.statusHidup && statusHidupManual == 0) {
    //  Serial.println(pid());
    motorAcRun(pid());
  } else if (!data.statusHidup && statusHidupManual == 1) {
    motorAcRun(100);
  }
}

void motorAcRun(int persen) {
  persen=constrain(persen, data.minMotor, data.maxMotor); 
  int pwm = (persen / 100.0) * 255;
  analogWrite(10, pwm);
  Serial.println(persen);
}
void kirimSet() {
  if (exaust == nodeMasterE) {
    // data.statusHidup = 1;
    kirimData(&dataKom, nodeMotor, publish);
  } else if (exaust == nodeMotor) {
    //data.statusHidup = 1;
    kirimData(&dataKom, nodeMaster, publish);
  }
}

void start() {

  if (exaust == nodeMasterE) {
    data.statusHidup = 1;
    kirimData(&dataKom, nodeMotor, publish);
  } else if (exaust == nodeMotor) {
    data.statusHidup = 1;
    kirimData(&dataKom, nodeMaster, publish);
  }
}

void stop() {
  if (exaust == nodeMasterE) {
    data.statusHidup = 0;
    kirimData(&dataKom, nodeMotor, publish);
  } else if (exaust == nodeMotor) {
    data.statusHidup = 0;
    kirimData(&dataKom, nodeMaster, publish);
  }
}

void startManual() {

  if (exaust == nodeMasterE) {
    statusHidupManual = 1;

  } else if (exaust == nodeMotor) {
    statusHidupManual = 1;

  }
}

void stopManual() {
  if (exaust == nodeMasterE) {
    statusHidupManual = 0;

  } else if (exaust == nodeMotor) {
    statusHidupManual = 0;

  }
}

void exit() {
  tampilan.pop();
}

void setNilaiDp() {
  data.set = data.dp;
  save.set = data.set;
}

void cekKoneksi() {
  if (millis() - a2.last > 5000  && exaust != nodeSensorE && exaust != nodeMotorE) {
    kirimData(&dataKom, nodeSensor, ping);
  }
  if (millis() - a3.last > 5000  && exaust != nodeMasterE) {
    kirimData(&dataKom, nodeMaster, ping);
  }

  if (millis() - a4.last > 5000  && exaust != nodeMotorE && exaust != nodeSensorE ) {
    kirimData(&dataKom, nodeMotor, ping);

  }
  if (sensor.statusGagal == 1) {

    if (kirimData(&dataKom, nodeSensor, publish)) {
      sensor.countPing = 0;
    } else {
      sensor.countPing += 1;
      if (sensor.countPing > 5 ) {
        sensor.countPing = 0;

        data.statusHidup = 0;
        kirimData(&dataKom, nodeMotor, publish);
      }
    }
  }
  if (motor.statusGagal == 1) {

    if (kirimData(&dataKom, nodeMotor, publish)) {
      sensor.countPing = 0;
    } else {
      sensor.countPing += 1;
      if (sensor.countPing > 5 ) {
        sensor.countPing = 0;
        data.statusHidup = 0;
      }
    }
  }
  if (master.statusGagal == 1) {

    if (kirimData(&dataKom, nodeMaster, publish)) {
      sensor.countPing = 0;
    } else {
      sensor.countPing += 1;
      if (sensor.countPing > 5 ) {
        sensor.countPing = 0;
        data.statusHidup = 0;
      }
    }
  }
}

int pid() {
  int kesalahan = data.dpSet - data.setPoint;
  int derivatifKesalahan = kesalahan - kesalahanLalu;
  kesalahanLalu = kesalahan;

  return (data.kp * kesalahan) + (data.kd * derivatifKesalahan);
}
