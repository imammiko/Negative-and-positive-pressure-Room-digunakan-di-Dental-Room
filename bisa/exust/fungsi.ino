
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
  data.dp = data.pressureLuar - data.pressureDalam;
  cekKoneksi();
  tampilanLcd(tampilan.peek());
  //    lcd.setCursor(0, 0); lcd.print("luar:");// menampilkan trace
  //    lcd.setCursor(7, 0); lcd.print(data.pressureLuar);//
  //    lcd.setCursor(0, 1); lcd.print("Dalam:");// menampilkan trace
  //    lcd.setCursor(7, 1); lcd.print(data.pressureDalam);//
}

void cekKoneksi() {
  if (millis() - a2.last > 5000  && exaust != nodeSensorE) {
    kirimData(&dataKom, nodeSensor, ping);
  }
  if (millis() - a3.last > 5000  && exaust != nodeMasterE) {
    kirimData(&dataKom, nodeMaster, ping);
  }

  if (millis() - a4.last > 5000  && exaust != nodeMotorE) {
    kirimData(&dataKom, nodeMotor, ping);
  }
  if (sensor.statusGagal == 1) {Serial.println("ping sensor");
    if (kirimData(&dataKom, nodeSensor, ping)) {
      Serial.println("ping ssensor");
      sensor.pingGagal=1;
      }
      delay(30);
      kirimData(&dataKom, nodeSensor, publish);
     
    }
  }
  if (master.statusGagal == 1) {
    Serial.println("ping master2");
    if (kirimData(&dataKom, nodeMaster, ping)) {
      Serial.println("ping master3");
      delay(30);
      kirimData(&dataKom, nodeMaster, publish);
    
    }
  }
  if (motor.statusGagal == 1) {
    Serial.println("ping motor");
    if (kirimData(&dataKom, nodeMotor, ping)) {
      
      Serial.println("ping motor");
      delay(30);
      kirimData(&dataKom, nodeMotor, publish);
    
    }
  }
}
