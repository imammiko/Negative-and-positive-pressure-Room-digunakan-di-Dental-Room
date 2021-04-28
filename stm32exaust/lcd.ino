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

    case 5:
      remoteSetting();
      break;

    case 6:
      remoteLevelSet();
      break;

    case 7:
      remoteTombolSet();

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
      sprintf(buffdp, "beda tekan:%3d", data.dpSet);//kecepatan
      lcd.setCursor(0, 0);

      lcd.print(buffdp);

      //Serial.println(data.maxMotor);
      char buffDpSet[10];
      sprintf(buffDpSet, "negative :%3d", data.setPoint);//kecepatan
      lcd.setCursor(0, 1); lcd.print(buffDpSet);
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

      char buffset[10];//menyimpan karakter sebanyak 6 buah
      sprintf(buffset, "SET:%2d", data.setS);
      lcd.setCursor(0, 1); lcd.print(buffset);

      lcd.setCursor(9, 1); lcd.print(lcdStatusStartStop);
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
    lcdStatusStartStop = "START OTOMATIS";
  } else {
    lcdStatusStartStop = "STOP OTOMATIS";
  }
  if (statusHidupManual == 0) {
    lcdStatusStartStopManual = "START Manual";
  } else {
    lcdStatusStartStopManual = "STOP Manual";
  }


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
  //menu = constrain(menu, 1, 4);
  if (countLcd == 0) {
    lcd.clear();
    countLcd = 1;
  }
  switch (home.menu) { // switch menu

    case 1:
      lcd.setCursor(0, 0); lcd.write(byte(0));
      lcd.setCursor(1, 0); lcd.print(lcdStatusStartStop);
      lcd.setCursor(1, 1); lcd.print(lcdStatusStartStopManual);

      readB();
      if (countB == 1 || ((millis() - a0.last > 300) && irInput(0) == irIn.tengah))  {
        afterEnter(1);
        // turn the LED off by making the voltage LOW

        // w
        if (!statusHidupManual && !data.statusHidup) {
          start();
        } else if (!statusHidupManual && data.statusHidup) {
          stop();
        }
      }
      break;
    case 2:
      lcd.setCursor(0, 1); lcd.write(byte(0));
      lcd.setCursor(1, 0); lcd.print(lcdStatusStartStop);
      lcd.setCursor(1, 1); lcd.print(lcdStatusStartStopManual);
      //      lcd.setCursor(1, 1); lcd.print("SET  ");
      readB();
      if (countB == 1 || ((millis() - a0.last > 300) && irInput(0) == irIn.tengah))  {
        afterEnter(1);
        if (!statusHidupManual && !data.statusHidup) {
          startManual();
        } else if (statusHidupManual && !data.statusHidup) {
          stopManual();
        }
      }
      //      if (countB == 1 || ((millis() - a0.last > 300) && irInput(0) == irIn.tengah))  {
      //        afterEnter(1);
      //        setNilaiDp();
      //
      //        EEPROM.put(addressEE, save);
      //        exit();
      //      }



      break;
    case 3:
      lcd.setCursor(0, 0); lcd.write(byte(0));
      lcd.setCursor(1, 0); lcd.print("SET  ");
      lcd.setCursor(1, 1); lcd.print("SETTING");
      //      lcd.setCursor(0, 1); lcd.print(" EXIT       ");
      //      if (button == tekan && millis() - a5.last > 200) {
      //        tampilan.push(2);
      //        // exit();
      //        countLcd = 0;
      //        a5.last = millis();
      //        menuCounti.menu = 1;
      //      }
      readB();
      if (countB == 1 || ((millis() - a0.last > 300) && (irInput(0) == irIn.tengah || irInput(0) == irIn.kiri)))  {
        afterEnter(0);
        setNilaiDp();

        EEPROM.put(addressEE, save);
        exit();
      }

      //      if (countB == 1 || ((millis() - a0.last > 300) && irInput(0) == irIn.tengah))  {
      //        afterEnter();
      //        tampilan.push(2);
      //      }

      break;
    case 4:
      lcd.setCursor(0, 1); lcd.write(byte(0));
      lcd.setCursor(1, 0); lcd.print("SET  ");
      lcd.setCursor(1, 1); lcd.print("SETTING");
      //      lcd.setCursor(1, 1); lcd.print("EXIT         ");
      readB();

      if (countB == 1 || ((millis() - a0.last > 300) && irInput(0) == irIn.tengah))  {
        afterEnter();
        tampilan.push(2);
      }
      //      if (countB == 1 || ((millis() - a0.last > 300) && irInput(0) == irIn.tengah))  {
      //        afterEnter();
      //        exit();
      //      }

      break;
    case 5:
      lcd.setCursor(0, 0); lcd.write(byte(0));
      lcd.setCursor(1, 0); lcd.print("EXIT  ");
      readB();
      if (countB == 1 || ((millis() - a0.last > 300) && (irInput(0) == irIn.tengah || irInput(0) == irIn.kiri)))  {
        afterEnter();
        exit();
      }
      break;
  }
}


void settingLcd() {
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
      char buffSpeedManual[10];
      sprintf(buffSpeedManual, "KEC. MAN.  %3d", data.speedMotorManualS);
      lcd.setCursor(1, 0); lcd.print(buffSpeedManual);
      lcd.setCursor(1, 1); lcd.print("Remote  ");

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
          if (++data.speedMotorManualS > 100) data.speedMotorManualS = 0;
          Serial.println("bawah");
        }
        if ( (position > encoder.getPosition()) || ((millis() - a0.last > 300) && irInput(1) == irIn.atas)) { // button down left
          position = encoder.getPosition();
          countLcd = 0;
          a0.last = millis();
          irmp_data.command = 0;
          if (--data.speedMotorManualS < 1) data.speedMotorManualS = 100;
          Serial.println("atas");
        }
        readB();
        if (countB == 1 || ((millis() - a0.last > 500) && irInput(1) == irIn.tengah))  {
          afterEnter(1);
          sudahDiTekan = 0;
          save.speedMotorManualS = data.speedMotorManualS;
          EEPROM.put(addressEE, save);
          Serial.println("tengah");
        }


      }
      break;
    case 4:
      lcd.setCursor(0, 1); lcd.write(byte(0));
      sprintf(buffSpeedManual, "KEC. MAN.  %3d", data.speedMotorManualS);
      lcd.setCursor(1, 0); lcd.print(buffSpeedManual);
      lcd.setCursor(1, 1); lcd.print("Remote");
      readB();
      if (countB == 1 || ((millis() - a0.last > 300) && irInput(0) == irIn.tengah))  {
        afterEnter();
        tampilan.push(5);
      }
      break;

    case 5:
      lcd.setCursor(0, 0); lcd.write(byte(0));
      lcd.setCursor(1, 0); lcd.print("EXIT  ");
      readB();
      if (countB == 1 || ((millis() - a0.last > 300) && (irInput(0) == irIn.tengah || irInput(0) == irIn.kiri)))  {
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
          if (++data.maxMotor > 100) data.maxMotor = 0;
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
          if (++data.minMotor > 100) data.minMotor = 0;
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
      if (countB == 1 || ((millis() - a0.last > 300) && (irInput(0) == irIn.tengah || irInput(0) == irIn.kiri)))  {
        afterEnter(0);
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
      if (++home.menu > 6) home.menu = 1;// menu akan naik jika lebih dari 4 counter akan kembali ke 1
      Serial.println("atas");
    }


    if (position > encoder.getPosition() || ((millis() - a0.last > 300) && irInput(0) == irIn.atas)) {
      position = encoder.getPosition();
      countLcd = 0;
      a0.last = millis();
      irmp_data.command = 0;
      if (--home.menu < 1) home.menu = 6;// menu akan naik jika lebih kurang dari 1 maka counter akan kembali ke 4
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
      lcd.setCursor(1, 0); lcd.print("KP"); lcd.setCursor(12, 0); lcd.print(data.kp,1);
      lcd.setCursor(1, 1); lcd.print("KD"); lcd.setCursor(12, 1); lcd.print(data.kd,1);

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
          if ((data.kp += 0.1) > 100) data.kp = 0;
          Serial.println("bawah");
        }
        if ( (position > encoder.getPosition()) || ((millis() - a0.last > 300) && irInput(1) == irIn.atas)) { // button down left
          position = encoder.getPosition();
          countLcd = 0;
          a0.last = millis();
          irmp_data.command = 0;
          if ((data.kp -= 0.1) < 0) data.kp = 100;
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
//      sprintf(buffKp, "%.1f", data.kp);
      lcd.setCursor(1, 0); lcd.print("KP"); lcd.setCursor(12, 0); lcd.print(data.kp,1);
      //      char buffKd[10];//menyimpan karakter sebanyak 6 buah
  //    sprintf(buffKd, "%.1f", data.kd);
      lcd.setCursor(1, 1); lcd.print("KD"); lcd.setCursor(12, 1); lcd.print(data.kd,1);

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
          if ((data.kd += 0.1) > 100) data.kd = 0;
          Serial.println("bawah");
        }
        if ( (position > encoder.getPosition()) || ((millis() - a0.last > 300) && irInput(1) == irIn.atas)) { // button down left
          position = encoder.getPosition();
          countLcd = 0;
          a0.last = millis();
          irmp_data.command = 0;
          if ((data.kd -= 0.1) < 0) data.kd = 100;
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
          if (++data.setS > 100) data.setS = 0;
          Serial.println("bawah");
        }
        if ( (position > encoder.getPosition()) || ((millis() - a0.last > 300) && irInput(1) == irIn.atas)) { // button down left
          position = encoder.getPosition();
          countLcd = 0;
          a0.last = millis();
          irmp_data.command = 0;
          if (--data.setS < 0) data.setS = 100;
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
          if (++data.setPoint > 100) data.setPoint = -100;
          Serial.println("bawah");
        }
        if ( (position > encoder.getPosition()) || ((millis() - a0.last > 300) && irInput(1) == irIn.atas)) { // button down left
          position = encoder.getPosition();
          countLcd = 0;
          a0.last = millis();
          irmp_data.command = 0;
          if (--data.setPoint < -100) data.setPoint = 100;
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
      char buffKi[10];//menyimpan karakter sebanyak 6 buah
      sprintf(buffKi, "%.1f", data.ki);
      lcd.setCursor(1, 0); lcd.print("KI"); lcd.setCursor(12, 0); lcd.print(data.ki,1);
      //      char buffKd[10];//menyimpan karakter sebanyak 6 buah
      lcd.setCursor(1, 1); lcd.print("EXIT ");

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
          if ((data.ki += 0.1) > 50) data.ki = -50;
          Serial.println("bawah");
        }
        if ( (position > encoder.getPosition()) || ((millis() - a0.last > 300) && irInput(1) == irIn.atas)) { // button down left
          position = encoder.getPosition();
          countLcd = 0;
          a0.last = millis();
          irmp_data.command = 0;
          if ((data.ki -= 0.1) < -50) data.ki = 50;
          Serial.println("atas");
        }
        readB();
        if (countB == 1 || ((millis() - a0.last > 500) && irInput(1) == irIn.tengah))  {
          afterEnter(1);
          sudahDiTekan = 0;
          save.ki = data.ki;
          EEPROM.put(addressEE, save);
          Serial.println("tengah");
        }


      }
      break;

    case 6:
      lcd.setCursor(0, 1); lcd.write(byte(0));
      sprintf(buffKi, "%3d", data.ki);
      lcd.setCursor(1, 0); lcd.print("KI"); lcd.setCursor(12, 0); lcd.print(data.ki,1);
      lcd.setCursor(1, 1); lcd.print("EXIT ");
      readB();
      if (countB == 1 || ((millis() - a0.last > 300) && (irInput(0) == irIn.tengah || irInput(0) == irIn.kiri)))  {
        afterEnter();
        exit();
      }
      break;

  }
}

void remoteSetting() {
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
      lcd.setCursor(1, 0); lcd.print("Level Kp Setting");
      lcd.setCursor(1, 1); lcd.print("Tombol");

      readB();
      if (countB == 1 || ((millis() - a0.last > 300) && irInput(0) == irIn.tengah))  {
        afterEnter(1);
        // turn the LED off by making the voltage LOW
        tampilan.push(6);
      }
      break;
    case 2:
      lcd.setCursor(0, 1); lcd.write(byte(0));
      lcd.setCursor(1, 0); lcd.print("Level Kp Setting");
      lcd.setCursor(1, 1); lcd.print("Tombol");
      //      lcd.setCursor(1, 1); lcd.print("SET  ");
      readB();
      if (countB == 1 || ((millis() - a0.last > 300) && irInput(0) == irIn.tengah))  {
        afterEnter(1);
        // turn the LED off by making the voltage LOW
        tampilan.push(7);
      }


      break;
    case 3:
      lcd.setCursor(0, 0); lcd.write(byte(0));
      lcd.setCursor(1, 0); lcd.print("EXIT  ");
      readB();
      if (countB == 1 || ((millis() - a0.last > 300) && (irInput(0) == irIn.tengah || irInput(0) == irIn.kiri)))  {
        afterEnter();
        exit();
      }
      break;
  }
}


void remoteLevelSet() {

  if (sudahDiTekan == 0) {
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
  }
  //menu = constrain(menu, 1, 4);
  if (countLcd == 0) {
    lcd.clear();
    countLcd = 1;
  }
  switch (home.menu) { // switch menu

    case 1:
      lcd.setCursor(0, 0); lcd.write(byte(0));
      char buffLKp[10];//menyimpan karakter sebanyak 6 buah
      sprintf(buffLKp, "Low KP:%.1f", save.lKp);
      lcd.setCursor(1, 0); lcd.print(buffLKp);
      char buffMKp[10];//menyimpan karakter sebanyak 6 buah
      sprintf(buffMKp, "Medium KP :%.1f", save.mKp);
      lcd.setCursor(1, 1); lcd.print(buffMKp);

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
          if ((save.lKp+0.1) > 100) save.lKp = 0;
          Serial.println("bawah");
        }
        if ( (position > encoder.getPosition()) || ((millis() - a0.last > 300) && irInput(1) == irIn.atas)) { // button down left
          position = encoder.getPosition();
          countLcd = 0;
          a0.last = millis();
          irmp_data.command = 0;
          if ((save.lKp-0.1) < 0) save.lKp = 100;
          Serial.println("atas");
        }
        readB();
        if (countB == 1 || ((millis() - a0.last > 500) && irInput(1) == irIn.tengah))  {
          afterEnter(1);
          sudahDiTekan = 0;
          EEPROM.put(addressEE, save);
          Serial.println("tengah");
        }


      }

      break;
    case 2:
      lcd.setCursor(0, 1); lcd.write(byte(0));

      sprintf(buffLKp, "Low KP:%.1f", save.lKp);
      lcd.setCursor(1, 0); lcd.print(buffLKp);

      sprintf(buffMKp, "Medium KP :%.1f", save.mKp);
      lcd.setCursor(1, 1); lcd.print(buffMKp);

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
          if ((save.mKp+0.1) > 100) save.mKp = 0;
          Serial.println("bawah");
        }
        if ( (position > encoder.getPosition()) || ((millis() - a0.last > 300) && irInput(1) == irIn.atas)) { // button down left
          position = encoder.getPosition();
          countLcd = 0;
          a0.last = millis();
          irmp_data.command = 0;
          if ((save.mKp-0.1) < 1) save.mKp = 100;
          Serial.println("atas");
        }
        readB();
        if (countB == 1 || ((millis() - a0.last > 500) && irInput(1) == irIn.tengah))  {
          afterEnter(1);
          sudahDiTekan = 0;
          EEPROM.put(addressEE, save);
          Serial.println("tengah");
        }


      }
      break;
    case 3:
      lcd.setCursor(0, 0); lcd.write(byte(0));
      char buffHKp[10];//menyimpan karakter sebanyak 6 buah
      sprintf(buffHKp, "High KP:%.1f", save.hKp);
      lcd.setCursor(1, 0); lcd.print(buffHKp);
      lcd.setCursor(1, 1); lcd.print("EXIT ");
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
          if ((save.hKp+0.1) > 100) save.hKp = 0;
          Serial.println("bawah");
        }
        if ( (position > encoder.getPosition()) || ((millis() - a0.last > 300) && irInput(1) == irIn.atas)) { // button down left
          position = encoder.getPosition();
          countLcd = 0;
          a0.last = millis();
          irmp_data.command = 0;
          if ((save.hKp-0.1) < 1) save.hKp = 100;
          Serial.println("atas");
        }
        readB();
        if (countB == 1 || ((millis() - a0.last > 500) && irInput(1) == irIn.tengah))  {
          afterEnter(1);
          sudahDiTekan = 0;
          EEPROM.put(addressEE, save);
          Serial.println("tengah");
        }


      }
      break;

    case 4:
      lcd.setCursor(0, 1); lcd.write(byte(0));
      sprintf(buffHKp, "High KP:%3d", save.hKp);
      lcd.setCursor(1, 0); lcd.print(buffHKp);
      lcd.setCursor(1, 1); lcd.print("EXIT ");

      readB();
      if (countB == 1 || ((millis() - a0.last > 300) && (irInput(0) == irIn.tengah || irInput(0) == irIn.kiri)))  {
        afterEnter();
        exit();
      }
      break;



  }

}

void remoteTombolSet() {
  if (sudahDiTekan == 0) {
    if (sudahDiTekan == 0) {
      if ( (position < encoder.getPosition()) || ((millis() - a0.last > 300) && irInput(0) == irIn.bawah) ) { // button down left
        position = encoder.getPosition();
        countLcd = 0;
        a0.last = millis();
        irmp_data.command = 0;
        if (++home.menu > 11) home.menu = 1;// menu akan naik jika lebih dari 4 counter akan kembali ke 1
        Serial.println("atas");
      }


      if (position > encoder.getPosition() || ((millis() - a0.last > 300) && irInput(0) == irIn.atas)) {
        position = encoder.getPosition();
        countLcd = 0;
        a0.last = millis();
        irmp_data.command = 0;
        if (--home.menu < 1) home.menu = 11;// menu akan naik jika lebih kurang dari 1 maka counter akan kembali ke 4
        Serial.println("BAWAH");
      }
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
      char bufflowKp[10];//menyimpan karakter sebanyak 6 buah
      sprintf(bufflowKp, "%3d", irIn.lowKp);
      lcd.setCursor(1, 0); lcd.print("Low Kp"); lcd.setCursor(12, 0); lcd.print(bufflowKp);
      char buffmediumKp[10];//menyimpan karakter sebanyak 6 buah
      sprintf(buffmediumKp, "%3d", irIn.mediumKp);
      lcd.setCursor(1, 1); lcd.print("Medium Kp"); lcd.setCursor(12, 1); lcd.print(buffmediumKp);

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
        if (irInput(0) > 0) {

          irIn.lowKp = irmp_data.command;
        }
        readB();
        if (countB == 1 || ((millis() - a0.last > 500) && irInput(1) == irIn.tengah))  {
          afterEnter(1);
          sudahDiTekan = 0;

          EEPROM.put(addressEER, irIn);
          Serial.println("tengah");
        }


      }

      break;
    case 2:
      lcd.setCursor(0, 1); lcd.write(byte(0));
      sprintf(bufflowKp, "%3d", irIn.lowKp);
      lcd.setCursor(1, 0); lcd.print("Low Kp"); lcd.setCursor(12, 0); lcd.print(bufflowKp);
      sprintf(buffmediumKp, "%3d", irIn.mediumKp);
      lcd.setCursor(1, 1); lcd.print("Medium Kp"); lcd.setCursor(12, 1); lcd.print(buffmediumKp);

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
        if (irInput(0) > 0) {

          irIn.mediumKp = irmp_data.command;
        }
        readB();
        if (countB == 1 || ((millis() - a0.last > 500) && irInput(1) == irIn.tengah))  {
          afterEnter(1);
          sudahDiTekan = 0;

          EEPROM.put(addressEER, irIn);
          Serial.println("tengah");
        }


      }
      break;


    case 3:
      lcd.setCursor(0, 0); lcd.write(byte(0));
      char buffhighKp[10];//menyimpan karakter sebanyak 6 buah
      sprintf(buffhighKp, "%3d", irIn.highKp);
      lcd.setCursor(1, 0); lcd.print("High Kp"); lcd.setCursor(12, 0); lcd.print(buffhighKp);
      char buffstartR[10];//menyimpan karakter sebanyak 6 buah
      sprintf(buffstartR, "%3d", irIn.startR);
      lcd.setCursor(1, 1); lcd.print("Start"); lcd.setCursor(12, 1); lcd.print(buffstartR);

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
        if (irInput(0) > 0) {

          irIn.highKp = irmp_data.command;
        }
        readB();
        if (countB == 1 || ((millis() - a0.last > 500) && irInput(1) == irIn.tengah))  {
          afterEnter(1);
          sudahDiTekan = 0;

          EEPROM.put(addressEER, irIn);
          Serial.println("tengah");
        }


      }

      break;

    case 4:
      lcd.setCursor(0, 1); lcd.write(byte(0));
      sprintf(buffhighKp, "%3d", irIn.highKp);
      lcd.setCursor(1, 0); lcd.print("High Kp"); lcd.setCursor(12, 0); lcd.print(buffhighKp);
      sprintf(buffstartR, "%3d", irIn.startR);
      lcd.setCursor(1, 1); lcd.print("Start"); lcd.setCursor(12, 1); lcd.print(buffstartR);

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
        if (irInput(0) > 0) {

          irIn.startR = irmp_data.command;
        }
        readB();
        if (countB == 1 || ((millis() - a0.last > 500) && irInput(1) == irIn.tengah))  {
          afterEnter(1);
          sudahDiTekan = 0;

          EEPROM.put(addressEER, irIn);
          Serial.println("tengah");
        }


      }

      break;

    case 5:
      lcd.setCursor(0, 0); lcd.write(byte(0));
      char buffsetR[10];//menyimpan karakter sebanyak 6 buah
      sprintf(buffsetR, "%3d", irIn.setR);
      lcd.setCursor(1, 0); lcd.print("Set"); lcd.setCursor(12, 0); lcd.print(buffsetR);
      char buffatas[10];//menyimpan karakter sebanyak 6 buah
      sprintf(buffatas, "%3d", irIn.atas);
      lcd.setCursor(1, 1); lcd.print("Atas"); lcd.setCursor(12, 1); lcd.print(buffatas);

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
        if (irInput(0) > 0) {

          irIn.setR = irmp_data.command;
        }
        readB();
        if (countB == 1 || ((millis() - a0.last > 500) && irInput(1) == irIn.tengah))  {
          afterEnter(1);
          sudahDiTekan = 0;

          EEPROM.put(addressEER, irIn);
          Serial.println("tengah");
        }


      }

      break;

    case 6:
      lcd.setCursor(0, 1); lcd.write(byte(0));
      sprintf(buffsetR, "%3d", irIn.setR);
      lcd.setCursor(1, 0); lcd.print("Set"); lcd.setCursor(12, 0); lcd.print(buffsetR);
      sprintf(buffatas, "%3d", irIn.atas);
      lcd.setCursor(1, 1); lcd.print("Atas"); lcd.setCursor(12, 1); lcd.print(buffatas);

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
        if (irInput(0) > 0) {

          irIn.atas = irmp_data.command;
        }
        readB();
        if (countB == 1 || ((millis() - a0.last > 500) && irInput(1) == irIn.tengah))  {
          afterEnter(1);
          sudahDiTekan = 0;

          EEPROM.put(addressEER, irIn);
          Serial.println("tengah");
        }


      }

      break;

    case 7:
      lcd.setCursor(0, 0); lcd.write(byte(0));
      char buffbawah[10];//menyimpan karakter sebanyak 6 buah
      sprintf(buffbawah, "%3d", irIn.bawah);
      lcd.setCursor(1, 0); lcd.print("Bawah"); lcd.setCursor(12, 0); lcd.print(buffbawah);
      char buffkiri[10];//menyimpan karakter sebanyak 6 buah
      sprintf(buffkiri, "%3d", irIn.kiri);
      lcd.setCursor(1, 1); lcd.print("Kiri"); lcd.setCursor(12, 1); lcd.print(buffkiri);

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
        if (irInput(0) > 0) {

          irIn.bawah = irmp_data.command;
        }
        readB();
        if (countB == 1 || ((millis() - a0.last > 500) && irInput(1) == irIn.tengah))  {
          afterEnter(1);
          sudahDiTekan = 0;

          EEPROM.put(addressEER, irIn);
          Serial.println("tengah");
        }


      }

      break;


    case 8:
      lcd.setCursor(0, 1); lcd.write(byte(0));
      sprintf(buffbawah, "%3d", irIn.bawah);
      lcd.setCursor(1, 0); lcd.print("Bawah"); lcd.setCursor(12, 0); lcd.print(buffbawah);
      sprintf(buffkiri, "%3d", irIn.kiri);
      lcd.setCursor(1, 1); lcd.print("Kiri"); lcd.setCursor(12, 1); lcd.print(buffkiri);

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
        if (irInput(0) > 0) {

          irIn.kiri = irmp_data.command;
        }
        readB();
        if (countB == 1 || ((millis() - a0.last > 500) && irInput(1) == irIn.tengah))  {
          afterEnter(1);
          sudahDiTekan = 0;

          EEPROM.put(addressEER, irIn);
          Serial.println("tengah");
        }


      }

      break;


    case 9:
      lcd.setCursor(0, 0); lcd.write(byte(0));
      char buffkanan[10];//menyimpan karakter sebanyak 6 buah
      sprintf(buffkanan, "%3d", irIn.kanan);
      lcd.setCursor(1, 0); lcd.print("Kanan"); lcd.setCursor(12, 0); lcd.print(buffkanan);
      char bufftengah[10];//menyimpan karakter sebanyak 6 buah
      sprintf(bufftengah, "%3d", irIn.tengah);
      lcd.setCursor(1, 1); lcd.print("Tengah/Ok"); lcd.setCursor(12, 1); lcd.print(bufftengah);

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
        if (irInput(0) > 0) {

          irIn.kanan = irmp_data.command;
        }
        readB();
        if (countB == 1 || ((millis() - a0.last > 500) && irInput(1) == irIn.tengah))  {
          afterEnter(1);
          sudahDiTekan = 0;

          EEPROM.put(addressEER, irIn);
          Serial.println("tengah");
        }


      }

      break;

    case 10:
      lcd.setCursor(0, 1); lcd.write(byte(0));
      sprintf(buffkanan, "%3d", irIn.kanan);
      lcd.setCursor(1, 0); lcd.print("Kanan"); lcd.setCursor(12, 0); lcd.print(buffkanan);
      sprintf(bufftengah, "%3d", irIn.tengah);
      lcd.setCursor(1, 1); lcd.print("Tengah/Ok"); lcd.setCursor(12, 1); lcd.print(bufftengah);

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
        if (irInput(0) > 0) {

          irIn.tengah = irmp_data.command;
        }
        readB();
        if (countB == 1)  {
          afterEnter(1);
          sudahDiTekan = 0;

          EEPROM.put(addressEER, irIn);
          Serial.println("tengah");
        }


      }

      break;
    case 11:
      lcd.setCursor(0, 0); lcd.write(byte(0));
      lcd.setCursor(0, 0); lcd.write(byte(0));
      lcd.setCursor(1, 0); lcd.print("EXIT ");
      readB();
      if (countB == 1 || ((millis() - a0.last > 300) && (irInput(0) == irIn.tengah || irInput(0) == irIn.kiri)))  {
        afterEnter();
        exit();
      }
      break;

  }
}
