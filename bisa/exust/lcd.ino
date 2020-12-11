


void tampilanLcd(byte fungsiLcd) {
  switch (fungsiLcd) {
    case 0  :
      homeLcd();
      break; //optional
    case 1  :
      menuLcd();
      break; //optional

    // you can have any number of case statements.
    default : //Optional
      lcd.print("tampil kosong");
  }
}


void homeLcd() {

  // //cursor
  //char buff6[16];

  if (millis() - a0.last > 300)
  {
    if (button == bawah) {// button down left
      if (++home.menu > 3) home.menu = 1;// menu akan naik jika lebih dari 4 counter akan kembali ke 1
      countLcd = 0;
    }
    a0.last = millis();
  }
  if (millis() - a1.last > 300)
  {
    if (button == atas) {
      if (--home.menu < 1) home.menu = 3;// menu akan naik jika lebih kurang dari 1 maka counter akan kembali ke 4
      countLcd = 0;
    }
    a1.last = millis();
  }
  //menu = constrain(menu, 1, 4);
  if (countLcd == 0) {
    lcd.clear();
    countLcd = 1;
  }
  switch (home.menu) { // switch menu
    case 1:
      if (countLcd == 0) {
        lcd.clear();
        countLcd = 1;
      }
      char buffdp[10];//menyimpan karakter sebanyak 6 buah
      sprintf(buffdp, "DP :%2d", data.dp);//kecepatan
      lcd.setCursor(0, 0);
      if (sensor.statusConnect) {
        lcd.print(buffdp);
      } else {
        lcd.print("discon");
      }

      char buffset[10];//menyimpan karakter sebanyak 6 buah
      sprintf(buffset, "SET:%2d", data.set);
      lcd.setCursor(0, 1); lcd.print(buffset);
      char buffmax1[10];//menyimpan karakter sebanyak 6 buah
      sprintf(buffmax1, "MAX :%3d", data.maxMotor);//kecepatan
      lcd.setCursor(7, 0); lcd.print(buffmax1); lcd.print("%");
      Serial.println(data.maxMotor);
      if (button == tekan) {
        tampilan.push(1);
      }
      break;
    case 2:
      if (countLcd == 0) {
        lcd.clear();
        countLcd = 1;
      }
      //lcd.setCursor(0, 1); lcd.write(byte(0));
      lcd.setCursor(0, 0); lcd.print("NSensor:");
      if (sensor.statusConnect) {
        lcd.print("con");
      } else {
        lcd.print("discon");
      }
      lcd.setCursor(0, 1); lcd.print("NMotor :");
      if (motor.statusConnect) {
        lcd.print("con");
      } else {
        lcd.print("discon");
      }

      if (button == tekan) {
        //   autoset();
      }
      break;
    case 3:
      if (countLcd == 0) {
        lcd.clear();
        countLcd = 1;
      }

      lcd.setCursor(0, 0); lcd.print("SDalam:"); lcd.print(data.pressureDalam);
      lcd.setCursor(0, 1); lcd.print("SLuar :"); lcd.print(data.pressureLuar);
      if (button == tekan) {
        // manualset();
      }
      break;

  }
}

void menuLcd() {

  if (millis() - a0.last > 300)
  {
    if (button == bawah) {// button down left
      if (++home.menu > 3) home.menu = 1;// menu akan naik jika lebih dari 4 counter akan kembali ke 1
      countLcd = 0;
    }
    a0.last = millis();
  }
  if (millis() - a1.last > 300)
  {
    if (button == atas) {
      if (--home.menu < 1) home.menu = 3;// menu akan naik jika lebih kurang dari 1 maka counter akan kembali ke 4
      countLcd = 0;
    }
    a1.last = millis();
  }
  //menu = constrain(menu, 1, 4);
  if (countLcd == 0) {
    lcd.clear();
    countLcd = 1;
  }
  switch (home.menu) { // switch menu

    case 1:
      lcd.setCursor(0, 0); lcd.write(byte(0));
      lcd.setCursor(1, 0); lcd.print("Check Sensor   ");
      lcd.setCursor(0, 1); lcd.print(" Auto SETPOINT  ");
      if (button == tekan) {
      
      }
      break;
    case 2:
      lcd.setCursor(0, 1); lcd.write(byte(0));
      lcd.setCursor(0, 0); lcd.print(" Check Sensor   ");
      lcd.setCursor(1, 1); lcd.print("Auto SETPOINT  ");
      if (button == tekan) {
       
      }
      break;
    case 3:
      lcd.setCursor(0, 0); lcd.write(byte(0));
      lcd.setCursor(1, 0); lcd.print("Manual SETPOINT");
      lcd.setCursor(0, 1); lcd.print(" Set PID       ");
      if (button == tekan) {

      }
      break;
    case 4:
      lcd.setCursor(0, 1); lcd.write(byte(0));
      lcd.setCursor(0, 0); lcd.print(" Manual SETPOINT");
      lcd.setCursor(1, 1); lcd.print("Set PID         ");
      if (button == tekan) {

      }
      break;

  }
}
