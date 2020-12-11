void deklarasiJoy() {
  //deklarasi xPin dan yPin sebagai input
  pinMode(x_Pin, INPUT); pinMode(y_Pin, INPUT);
  //deklarasi buttonPin sebagai input dengan kondisi pull-up
  pinMode(button_Pin, INPUT_PULLUP);

}


void joystick() {


  //Pembacaan kondisi
  joy.x_Position = analogRead(x_Pin);
  joy.y_Position = analogRead(y_Pin);
  joy.buttonState = digitalRead(button_Pin);
  if (joy.x_Position > joy.dibagiDua) {
    joy.xHasilMap = map(joy.x_Position, (joy.dibagiDua + 1), 1022, 0, 255);
  } else if (joy.x_Position <= joy.dibagiDua) {
    joy.xHasilMap = map(joy.x_Position, 0, (joy.dibagiDua), -255, 0);
  }

  if (joy.y_Position > joy.dibagiDua) {
    joy.yHasilMap = map(joy.y_Position, (joy.dibagiDua + 1), 1022, 0, 255);
  } else if (joy.y_Position <= joy.dibagiDua) {
    joy.yHasilMap = map(joy.y_Position, 0, (joy.dibagiDua), -255, 0);
  }
  if (joy.xHasilMap >= 0 && joy.yHasilMap >= 0) {// kuadran 1
    joy.derajat = atan2(joy.yHasilMap, joy.xHasilMap) * 180 / PI ;
  }  else if (joy.xHasilMap <= 0 && joy.yHasilMap >= 0) { //kuadran 2
    joy.derajat = atan2(joy.yHasilMap, joy.xHasilMap) * 180 / PI ;
    //joy.derajat=180+joy.derajat;
  } else if (joy.xHasilMap <= 0 && joy.yHasilMap <= 0) {
    joy.derajat = atan2(joy.yHasilMap, joy.xHasilMap) * 180 / PI ;
    joy.derajat = 360 + joy.derajat;
  } else if (joy.xHasilMap >= 0 && joy.yHasilMap <= 0) {
    joy.derajat = atan2(joy.yHasilMap, joy.xHasilMap) * 180 / PI ;
    joy.derajat = 360 + joy.derajat;
  }
  //joy.derajat = atan2(joy.yHasilMap, joy.xHasilMap)* 180 / PI ;

  //  if (joy.derajat < 0) {
  //    joy.derajat = 360 + joy.derajat;
  //  }

  joy.polar = sqrt(pow(joy.xHasilMap, 2) + pow(joy.yHasilMap, 2));


  //menampilkan hasil pada serial monitor
  //  Serial.print(" |variable x: "); Serial.print(joy.xHasilMap);
  //  Serial.print(" variable y: "); Serial.print(joy.yHasilMap);
  //  Serial.print(" X: "); Serial.print(joy.x_Position);
  //  Serial.print(" | Y: "); Serial.print(joy.y_Position);
  //  Serial.print(" | Button: "); Serial.println(joy.buttonState);
  //  Serial.print(" hasil  "); Serial.print(joy.derajat);
  //  Serial.println(" polar"); Serial.print(joy.polar);

  //delay(100); //waktu tunda sebesar 100ms
}

byte read_button() {
  joystick();
  if (!(joy.buttonState) ) {
    return tekan;
  }
  if (joy.polar >= 145) {

    if ((joy.derajat <= 45 || joy.derajat >= 315) || joy.derajat == 0) {
      return kiri;
    } else if ( joy.derajat > 45 && joy.derajat <= 135) {
      return atas;
    } else if (joy.derajat > 135 && joy.derajat <= 225) {
      return kanan;
    } else if (joy.derajat > 225 && joy.derajat <= 315) {
      return bawah;
    }
  } else {
    return unpressed;
  }


}
