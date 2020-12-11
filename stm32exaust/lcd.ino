void tampilanLcd(byte fungsiLcd) {

  switch (fungsiLcd) {
    case 0  :
      homeLcd();
      break; //optional
    case 1  :
      menuLcd();
      //lcd.print("tampil kosong");
      break; //optional
    case 2  :
      settingLcd();
      break; //optional

    case 3:
      settingMotorLcd();
      break;

    case 4:
      tampilanPid();
      break;

    default : //Optional
      lcd.print("tampil kosong");
  }
}
//irInput()irIn
//encoderInput()
//#define cw 1
//#define ccw 2
//#define tekan 3
//=========================================Master=====================
void homeLcd() {

  // //cursor
  //char buff6[16];
  if (data.statusHidup == 0) {
    lcdStatusStartStop = "OFF  ";
  } else {
    lcdStatusStartStop = "ON  ";
  }

  if ( (position < encoder.getPosition()) || ((millis() - a0.last > 300) && irInput(0) == irIn.bawah)) { // button down left
    position = encoder.getPosition();
    countLcd = 0;
    a0.last = millis();
    irmp_data.command = 0;
    if (++home.menu > 3) home.menu = 1;// menu akan naik jika lebih dari 4 counter akan kembali ke 1
    Serial.println("atas");
  }


  if (position > encoder.getPosition() || ((millis() - a0.last > 300) && irInput(0) == irIn.atas)) {
    position = encoder.getPosition();
    countLcd = 0;
    a0.last = millis();
    irmp_data.command = 0;
    if (--home.menu < 1) home.menu = 3;// menu akan naik jika lebih kurang dari 1 maka counter akan kembali ke 4
    Serial.println("BAWAH");
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
      sprintf(buffdp, "DP :%2d", data.dpSet);//kecepatan
      lcd.setCursor(0, 0);
      if (sensor.statusConnect) {
        lcd.print(buffdp);
      } else {
        lcd.print("discon");
      }

      char buffset[10];//menyimpan karakter sebanyak 6 buah
      sprintf(buffset, "SET:%2d", data.setS);
      lcd.setCursor(0, 1); lcd.print(buffset);

      lcd.setCursor(7, 0); lcd.print(lcdStatusStartStop);
      //Serial.println(data.maxMotor);
      char buffDpSet[10];
      sprintf(buffDpSet, "press:%3d", data.setPoint);//kecepatan
      lcd.setCursor(7, 1); lcd.print(buffDpSet);
      //Serial.println(data.maxMotor);
      readB();
      if (countB == 1 || ((millis() - a0.last > 300) && irInput(0) == irIn.tengah))  {
        afterEnter();
        tampilan.push(1);
      }


      break;
    case 2:
      if (countLcd == 0) {
        lcd.clear();
        countLcd = 1;
      }

      lcd.setCursor(0, 0); lcd.print("NSensor:");
      if (sensor.statusConnect) {
        lcd.setCursor(8, 0); lcd.print("con");
      } else {
        lcd.setCursor(8, 0); lcd.print("discon");
      }
      readB();
      if (countB == 1 || ((millis() - a0.last > 300) && irInput(0) == irIn.tengah))  {
        afterEnter();
        tampilan.push(1);
      }
      break;
    case 3:
      if (countLcd == 0) {
        lcd.clear();
        countLcd = 1;
      }

      lcd.setCursor(0, 0); lcd.print("SDalam:"); lcd.print(data.pressureDalam);
      lcd.setCursor(0, 1); lcd.print("SLuar :"); lcd.print(data.pressureLuar);
      readB();
      if (countB == 1 || ((millis() - a0.last > 300) && irInput(0) == irIn.tengah))  {
        afterEnter();
        tampilan.push(1);
      }
      break;

  }
}

void menuLcd() {
  if (data.statusHidup == 0) {
    lcdStatusStartStop = "START";
  } else {
    lcdStatusStartStop = "STOP";
  }

  if ( (position < encoder.getPosition()) || ((millis() - a0.last > 300) && irInput(0) == irIn.bawah) ) { // button down left
    position = encoder.getPosition();
    countLcd = 0;
    a0.last = millis();
    irmp_data.command = 0;
    if (++home.menu > 4) home.menu = 1;// menu akan naik jika lebih dari 4 counter akan kembali ke 1
    Serial.println("atas");
  }


  if (position > encoder.getPosition() || ((millis() - a0.last > 300) && irInput(0) == irIn.atas)) {
    position = encoder.getPosition();
    countLcd = 0;
    a0.last = millis();
    irmp_data.command = 0;
    if (--home.menu < 1) home.menu = 4;// menu akan naik jika lebih kurang dari 1 maka counter akan kembali ke 4
    Serial.println("BAWAH");
  }
  //menu = constrain(menu, 1, 4);
  if (countLcd == 0) {
    lcd.clear();
    countLcd = 1;
  }
  switch (home.menu) { // switch menu

    case 1:
      lcd.setCursor(0, 0); lcd.write(byte(0));
      lcd.setCursor(1, 0); lcd.print(lcdStatusStartStop);
      lcd.setCursor(1, 0); lcd.print(lcdStatusStartStop);
      lcd.setCursor(0, 1); lcd.print(" SET  ");
      readB();
      if (countB == 1 || ((millis() - a0.last > 300) && irInput(0) == irIn.tengah))  {
        afterEnter(1);
        if (data.statusHidup == 0) {
          start();
        } else {
          stop(); 
        }
      }
      break;
    case 2:
      lcd.setCursor(0, 1); lcd.write(byte(0));
      lcd.setCursor(1, 0); lcd.print(lcdStatusStartStop);
      lcd.setCursor(1, 1); lcd.print("SET  ");
      readB();
      if (countB == 1 || ((millis() - a0.last > 300) && irInput(0) == irIn.tengah))  {
        afterEnter(1);
        setNilaiDp();
        EEPROM.put(addressEE, save);
        exit();
      }



      break;
    case 3:
      lcd.setCursor(0, 0); lcd.write(byte(0));
      lcd.setCursor(1, 0); lcd.print("SETTING");
      lcd.setCursor(0, 1); lcd.print(" EXIT       ");
      //      if (button == tekan && millis() - a5.last > 200) {
      //        tampilan.push(2);
      //        // exit();
      //        countLcd = 0;
      //        a5.last = millis();
      //        menuCounti.menu = 1;
      //      }
      readB();
      if (countB == 1 || ((millis() - a0.last > 300) && irInput(0) == irIn.tengah))  {
        afterEnter();
        tampilan.push(2);
      }

      break;
    case 4:
      lcd.setCursor(0, 1); lcd.write(byte(0));
      lcd.setCursor(0, 0); lcd.print(" SETTING");
      lcd.setCursor(1, 1); lcd.print("EXIT         ");
      readB();
      if (countB == 1 || ((millis() - a0.last > 300) && irInput(0) == irIn.tengah))  {
        afterEnter();
        exit();
      }

      break;

  }
}


void settingLcd() {


  if ( (position < encoder.getPosition()) || ((millis() - a0.last > 300) && irInput(0) == irIn.bawah) ) { // button down left
    position = encoder.getPosition();
    countLcd = 0;
    a0.last = millis();
    irmp_data.command = 0;
    if (++home.menu > 3) home.menu = 1;// menu akan naik jika lebih dari 4 counter akan kembali ke 1
    Serial.println("atas");
  }


  if (position > encoder.getPosition() || ((millis() - a0.last > 300) && irInput(0) == irIn.atas)) {
    position = encoder.getPosition();
    countLcd = 0;
    a0.last = millis();
    irmp_data.command = 0;
    if (--home.menu < 1) home.menu = 3;// menu akan naik jika lebih kurang dari 1 maka counter akan kembali ke 4
    Serial.println("BAWAH");
  }

  //menu = constrain(menu, 1, 4);
  if (countLcd == 0) {
    lcd.clear();
    countLcd = 1;
  }
  switch (home.menu) { // switch menu

    case 1:
      lcd.setCursor(0, 0); lcd.write(byte(0));
      lcd.setCursor(1, 0); lcd.print("Motor");
      lcd.setCursor(0, 1); lcd.print(" PID  ");

      readB();
      if (countB == 1 || ((millis() - a0.last > 300) && irInput(0) == irIn.tengah))  {
        afterEnter();
        tampilan.push(3);
      }
      //      if (button == tekan && millis() - a5.last > 200) {
      //        tampilan.push(3);
      //
      //        countLcd = 0;
      //        menuCounti.menu = 1;
      //        a5.last = millis();
      //      }
      break;
    case 2:
      lcd.setCursor(0, 1); lcd.write(byte(0));
      lcd.setCursor(1, 0); lcd.print("Motor");
      lcd.setCursor(1, 1); lcd.print("PID  ");
      //      if (button == tekan && millis() - a5.last > 200) {
      //        tampilan.push(4);
      //        countLcd = 0;
      //        a5.last = millis();
      //        menuCounti.menu = 1;
      //      }
      readB();
      if (countB == 1 || ((millis() - a0.last > 300) && irInput(0) == irIn.tengah))  {
        afterEnter();
        tampilan.push(4);
      }
      break;

    case 3:
      lcd.setCursor(0, 0); lcd.write(byte(0));
      lcd.setCursor(1, 0); lcd.print("EXIT ");
      readB();
      if (countB == 1 || ((millis() - a0.last > 300) && irInput(0) == irIn.tengah))  {
        afterEnter();
        exit();
      }
      break;

  }
}


void settingMotorLcd() {
  if (sudahDiTekan == 0) {
    if ( (position < encoder.getPosition()) || ((millis() - a0.last > 300) && irInput(0) == irIn.bawah) ) { // button down left
      position = encoder.getPosition();
      countLcd = 0;
      a0.last = millis();
      irmp_data.command = 0;
      if (++home.menu > 3) home.menu = 1;// menu akan naik jika lebih dari 4 counter akan kembali ke 1
      Serial.println("atas");
    }


    if (position > encoder.getPosition() || ((millis() - a0.last > 300) && irInput(0) == irIn.atas)) {
      position = encoder.getPosition();
      countLcd = 0;
      a0.last = millis();
      irmp_data.command = 0;
      if (--home.menu < 1) home.menu = 3;// menu akan naik jika lebih kurang dari 1 maka counter akan kembali ke 4
      Serial.println("BAWAH");
    }
  }
  //menu = constrain(menu, 1, 4);
  if (countLcd == 0) {
    lcd.clear();
    countLcd = 1;
  }
  switch (home.menu) { // switch menu

    case 1:
      lcd.setCursor(0, 0); lcd.write(byte(0));
      char buffMax[10];//menyimpan karakter sebanyak 6 buah
      sprintf(buffMax, "%3d", data.maxMotor);
      lcd.setCursor(1, 0); lcd.print("MaxMotor"); lcd.setCursor(12, 0); lcd.print(buffMax); lcd.print("%");
      char buffMin[10];//menyimpan karakter sebanyak 6 buah
      sprintf(buffMin, "%3d", data.minMotor);
      lcd.setCursor(1, 1); lcd.print("MinMotor"); lcd.setCursor(12, 1); lcd.print(buffMin); lcd.print("%");

      readB();
      if (sudahDiTekan == 0) {
        if (countB == 1 || ((millis() - a0.last > 500) && irInput(0) == irIn.tengah))  {
          afterEnter(1);
          sudahDiTekan = 1;
          irmp_data.command = 0;
          Serial.println("tengah1");
        }
      }
      if (sudahDiTekan == 1) {

        if ( (position < encoder.getPosition()) || ((millis() - a0.last > 300) && irInput(1) == irIn.bawah)) { // button down left
          position = encoder.getPosition();
          countLcd = 0;
          a0.last = millis();
          irmp_data.command = 0;
          if (++data.maxMotor > 100) data.maxMotor = 1;
          Serial.println("bawah");
        }
        if ( (position > encoder.getPosition()) || ((millis() - a0.last > 300) && irInput(1) == irIn.atas)) { // button down left
          position = encoder.getPosition();
          countLcd = 0;
          a0.last = millis();
          irmp_data.command = 0;
          if (--data.maxMotor < 1) data.maxMotor = 100;
          Serial.println("atas");
        }
        readB();
        if (countB == 1 || ((millis() - a0.last > 500) && irInput(1) == irIn.tengah))  {
          afterEnter(1);
          sudahDiTekan = 0;
          save.maxMotor = data.maxMotor;
          EEPROM.put(addressEE, save);
          Serial.println("tengah");
        }


      }

      break;
    case 2:
      lcd.setCursor(0, 1); lcd.write(byte(0));
      //char buffMax[10];//menyimpan karakter sebanyak 6 buah
      sprintf(buffMax, "%3d", data.maxMotor);
      lcd.setCursor(1, 0); lcd.print("MaxMotor"); lcd.setCursor(12, 0); lcd.print(buffMax); lcd.print("%");
      //char buffMin[10];//menyimpan karakter sebanyak 6 buah
      sprintf(buffMin, "%3d", data.minMotor);
      lcd.setCursor(1, 1); lcd.print("MinMotor"); lcd.setCursor(12, 1); lcd.print(buffMin); lcd.print("%");


      readB();
      if (sudahDiTekan == 0) {
        if (countB == 1 || ((millis() - a0.last > 500) && irInput(0) == irIn.tengah))  {
          afterEnter(1);
          sudahDiTekan = 1;
          irmp_data.command = 0;
          Serial.println("tengah1");
        }
      }
      if (sudahDiTekan == 1) {

        if ( (position < encoder.getPosition()) || ((millis() - a0.last > 300) && irInput(1) == irIn.bawah)) { // button down left
          position = encoder.getPosition();
          countLcd = 0;
          a0.last = millis();
          irmp_data.command = 0;
          if (++data.minMotor > 100) data.minMotor = 1;
          Serial.println("bawah");
        }
        if ( (position > encoder.getPosition()) || ((millis() - a0.last > 300) && irInput(1) == irIn.atas)) { // button down left
          position = encoder.getPosition();
          countLcd = 0;
          a0.last = millis();
          irmp_data.command = 0;
          if (--data.minMotor < 1) data.minMotor = 100;
          Serial.println("atas");
        }
        readB();
        if (countB == 1 || ((millis() - a0.last > 500) && irInput(1) == irIn.tengah))  {
          afterEnter(1);
          sudahDiTekan = 0;
          save.minMotor = data.minMotor;
          EEPROM.put(addressEE, save);
          Serial.println("tengah");
        }

      }

      break;

    case 3:
      lcd.setCursor(0, 0); lcd.write(byte(0));
      lcd.setCursor(1, 0); lcd.print("EXIT ");
      readB();
      if (countB == 1 || ((millis() - a0.last > 300) && irInput(0) == irIn.tengah))  {
        afterEnter();
        exit();
      }
      break;

  }
}


void tampilanPid() {
  if (sudahDiTekan == 0) {
    if ( (position < encoder.getPosition()) || ((millis() - a0.last > 300) && irInput(0) == irIn.bawah) ) { // button down left
      position = encoder.getPosition();
      countLcd = 0;
      a0.last = millis();
      irmp_data.command = 0;
      if (++home.menu > 5) home.menu = 1;// menu akan naik jika lebih dari 4 counter akan kembali ke 1
      Serial.println("atas");
    }


    if (position > encoder.getPosition() || ((millis() - a0.last > 300) && irInput(0) == irIn.atas)) {
      position = encoder.getPosition();
      countLcd = 0;
      a0.last = millis();
      irmp_data.command = 0;
      if (--home.menu < 1) home.menu = 5;// menu akan naik jika lebih kurang dari 1 maka counter akan kembali ke 4
      Serial.println("BAWAH");
    }
  }
  //menu = constrain(menu, 1, 4);
  if (countLcd == 0) {
    lcd.clear();
    countLcd = 1;
  }
  switch (home.menu) { // switch menu

    case 1:
      lcd.setCursor(0, 0); lcd.write(byte(0));
      char buffKp[10];//menyimpan karakter sebanyak 6 buah
      sprintf(buffKp, "%3d", data.kp);
      lcd.setCursor(1, 0); lcd.print("KP"); lcd.setCursor(12, 0); lcd.print(buffKp);
      char buffKd[10];//menyimpan karakter sebanyak 6 buah
      sprintf(buffKd, "%3d", data.kd);
      lcd.setCursor(1, 1); lcd.print("KD"); lcd.setCursor(12, 1); lcd.print(buffKd);

      readB();
      if (sudahDiTekan == 0) {
        if (countB == 1 || ((millis() - a0.last > 500) && irInput(0) == irIn.tengah))  {
          afterEnter(1);
          sudahDiTekan = 1;
          irmp_data.command = 0;
          Serial.println("tengah1");
        }
      }
      if (sudahDiTekan == 1) {

        if ( (position < encoder.getPosition()) || ((millis() - a0.last > 300) && irInput(1) == irIn.bawah)) { // button down left
          position = encoder.getPosition();
          countLcd = 0;
          a0.last = millis();
          irmp_data.command = 0;
          if (++data.kp > 100) data.kp = 1;
          Serial.println("bawah");
        }
        if ( (position > encoder.getPosition()) || ((millis() - a0.last > 300) && irInput(1) == irIn.atas)) { // button down left
          position = encoder.getPosition();
          countLcd = 0;
          a0.last = millis();
          irmp_data.command = 0;
          if (--data.kp < 1) data.kp = 100;
          Serial.println("atas");
        }
        readB();
        if (countB == 1 || ((millis() - a0.last > 500) && irInput(1) == irIn.tengah))  {
          afterEnter(1);
          sudahDiTekan = 0;
          save.kp = data.kp;
          EEPROM.put(addressEE, save);
          Serial.println("tengah");
        }


      }

      break;
    case 2:
      lcd.setCursor(0, 1); lcd.write(byte(0));
      //      char buffKp[10];//menyimpan karakter sebanyak 6 buah
      sprintf(buffKp, "%3d", data.kp);
      lcd.setCursor(1, 0); lcd.print("KP"); lcd.setCursor(12, 0); lcd.print(buffKp);
      //      char buffKd[10];//menyimpan karakter sebanyak 6 buah
      sprintf(buffKd, "%3d", data.kd);
      lcd.setCursor(1, 1); lcd.print("KD"); lcd.setCursor(12, 1); lcd.print(buffKd);

      readB();
      if (sudahDiTekan == 0) {
        if (countB == 1 || ((millis() - a0.last > 500) && irInput(0) == irIn.tengah))  {
          afterEnter(1);
          sudahDiTekan = 1;
          irmp_data.command = 0;
          Serial.println("tengah1");
        }
      }
      if (sudahDiTekan == 1) {

        if ( (position < encoder.getPosition()) || ((millis() - a0.last > 300) && irInput(1) == irIn.bawah)) { // button down left
          position = encoder.getPosition();
          countLcd = 0;
          a0.last = millis();
          irmp_data.command = 0;
          if (++data.kd > 100) data.kd = 1;
          Serial.println("bawah");
        }
        if ( (position > encoder.getPosition()) || ((millis() - a0.last > 300) && irInput(1) == irIn.atas)) { // button down left
          position = encoder.getPosition();
          countLcd = 0;
          a0.last = millis();
          irmp_data.command = 0;
          if (--data.kd < 1) data.kd = 100;
          Serial.println("atas");
        }
        readB();
        if (countB == 1 || ((millis() - a0.last > 500) && irInput(1) == irIn.tengah))  {
          afterEnter(1);
          sudahDiTekan = 0;
          save.kd = data.kd;
          EEPROM.put(addressEE, save);
          Serial.println("tengah");
        }


      }
      break;
    case 3:
      lcd.setCursor(0, 0); lcd.write(byte(0));
      char buffSet[10];//menyimpan karakter sebanyak 6 buah
      sprintf(buffSet, "%3d", data.setS);
      lcd.setCursor(1, 0); lcd.print("SET"); lcd.setCursor(12, 0); lcd.print(buffSet);
      char buffSetPoint[10];//menyimpan karakter sebanyak 6 buah
      sprintf(buffSetPoint, "%3d", data.setPoint);
      lcd.setCursor(1, 1);  lcd.print("SETPOINT "); lcd.setCursor(12, 1); lcd.print(buffSetPoint);
      readB();
      if (sudahDiTekan == 0) {
        if (countB == 1 || ((millis() - a0.last > 500) && irInput(0) == irIn.tengah))  {
          afterEnter(1);
          sudahDiTekan = 1;
          irmp_data.command = 0;
          Serial.println("tengah1");
        }
      }
      if (sudahDiTekan == 1) {

        if ( (position < encoder.getPosition()) || ((millis() - a0.last > 300) && irInput(1) == irIn.bawah)) { // button down left
          position = encoder.getPosition();
          countLcd = 0;
          a0.last = millis();
          irmp_data.command = 0;
          if (++data.setS > 100) data.setS = 1;
          Serial.println("bawah");
        }
        if ( (position > encoder.getPosition()) || ((millis() - a0.last > 300) && irInput(1) == irIn.atas)) { // button down left
          position = encoder.getPosition();
          countLcd = 0;
          a0.last = millis();
          irmp_data.command = 0;
          if (--data.setS < 1) data.setS = 100;
          Serial.println("atas");
        }
        readB();
        if (countB == 1 || ((millis() - a0.last > 500) && irInput(1) == irIn.tengah))  {
          afterEnter(1);
          sudahDiTekan = 0;
          save.setS = data.setS;
          EEPROM.put(addressEE, save);
          Serial.println("tengah");
        }


      }
      break;

    case 4:
      lcd.setCursor(0, 1); lcd.write(byte(0));
      //char buffSet[10];//menyimpan karakter sebanyak 6 buah
      sprintf(buffSet, "%3d", data.setS);
      lcd.setCursor(1, 0); lcd.print("SET"); lcd.setCursor(12, 0); lcd.print(buffSet);
      sprintf(buffSetPoint, "%3d", data.setPoint);
      lcd.setCursor(1, 1); lcd.print("SETPOINT "); lcd.setCursor(12, 1); lcd.print(buffSetPoint);
      readB();
      if (sudahDiTekan == 0) {
        if (countB == 1 || ((millis() - a0.last > 500) && irInput(0) == irIn.tengah))  {
          afterEnter(1);
          sudahDiTekan = 1;
          irmp_data.command = 0;
          Serial.println("tengah1");
        }
      }
      if (sudahDiTekan == 1) {

        if ( (position < encoder.getPosition()) || ((millis() - a0.last > 300) && irInput(1) == irIn.bawah)) { // button down left
          position = encoder.getPosition();
          countLcd = 0;
          a0.last = millis();
          irmp_data.command = 0;
          if (++data.setPoint > 100) data.setPoint = 1;
          Serial.println("bawah");
        }
        if ( (position > encoder.getPosition()) || ((millis() - a0.last > 300) && irInput(1) == irIn.atas)) { // button down left
          position = encoder.getPosition();
          countLcd = 0;
          a0.last = millis();
          irmp_data.command = 0;
          if (--data.setPoint < 1) data.setPoint = 100;
          Serial.println("atas");
        }
        readB();
        if (countB == 1 || ((millis() - a0.last > 500) && irInput(1) == irIn.tengah))  {
          afterEnter(1);
          sudahDiTekan = 0;
          save.setPoint = data.setPoint;
          EEPROM.put(addressEE, save);
          Serial.println("tengah");
        }


      }

      //      if (button == tekan && millis() - a5.last > 200 && sudahDiTekan == 0) {
      //        sudahDiTekan = 1;
      //        countLcd = 0;
      //
      //        a5.last = millis();
      //      }
      //      if (sudahDiTekan == 1) {
      //        if (button == bawah && millis() - a5.last > 200) {
      //          if (++data.setPoint > 100) data.setPoint = -100;
      //          a5.last = millis();
      //        }
      //        if (button == atas && millis() - a5.last > 200) {
      //          if (--data.setPoint < -100) data.setPoint = 100;
      //          a5.last = millis();
      //        }
      //        if (button == tekan && millis() - a5.last > 200 && sudahDiTekan == 1) {
      //          sudahDiTekan = 0;
      //          save.setPoint = data.setPoint;
      //          kirimSet();
      //          countLcd = 0;
      //          //menuCounti.menu = 1;
      //          a5.last = millis();
      //        }
      //
      //      }
      break;

    case 5:
      lcd.setCursor(0, 0); lcd.write(byte(0));
      lcd.setCursor(1, 0); lcd.print("EXIT ");
      readB();
      if (countB == 1 || ((millis() - a0.last > 300) && irInput(0) == irIn.tengah))  {
        afterEnter();
        exit();
      }
      break;

  }
}
