


void tampilanLcd(byte fungsiLcd) {

  if (exaust == nodeMasterE) {
    switch (fungsiLcd) {
      case 0  :
        homeLcd();
        break; //optional
      case 1  :
        menuLcd();
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

    // you can have any number of case statements.

  } else if (exaust == nodeMotorE) {
    switch (fungsiLcd) {
      case 0  :
        homeLcdMotor();
        break; //optional
      case 1  :
        menuLcdMotor();
        break; //optional
      //      case 2  :
      //        settingLcd();
      //        break; //optional
      //
      //      case 3:
      //        settingMotorLcd();
      //        break;
      //
      //      case 4:
      //        tampilanPid();
      //        break;



      // you can have any number of case statements.
      default : //Optional
        lcd.print("tampil kosong");
    }
  }
}

//=========================================Master=====================
void homeLcd() {

  // //cursor
  //char buff6[16];
  if (data.statusHidup == 0) {
    lcdStatusStartStop = "OFF  ";
  } else {
    lcdStatusStartStop = "ON  ";
  }

  if (millis() - a0.last > 300)
  {
    if (button == atas) {// button down left
      if (++home.menu > 3) home.menu = 1;// menu akan naik jika lebih dari 4 counter akan kembali ke 1
      countLcd = 0;
    }
    a0.last = millis();
  }
  if (millis() - a1.last > 300)
  {
    if (button == bawah) {
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
      sprintf(buffdp, "DP :%2d", data.dpSet);//kecepatan
      lcd.setCursor(0, 0);
      if (sensor.statusConnect) {
        lcd.print(buffdp);
      } else {
        lcd.print("discon");
      }

      char buffset[10];//menyimpan karakter sebanyak 6 buah
      sprintf(buffset, "SET:%2d", data.set);
      lcd.setCursor(0, 1); lcd.print(buffset);

      lcd.setCursor(7, 0); lcd.print(lcdStatusStartStop);
      //Serial.println(data.maxMotor);
      char buffDpSet[10];
      sprintf(buffDpSet, "press:%3d", data.setPoint);//kecepatan
      lcd.setCursor(7, 1); lcd.print(buffDpSet);
      //Serial.println(data.maxMotor);
      if (button == tekan && millis() - a5.last > 500) {
        if (exaust == nodeMasterE) {
          tampilan.push(1);
          countLcd = 0;
        }
        a5.last = millis();

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
      if (exaust == nodeMasterE) {
        lcd.setCursor(0, 1); lcd.print("NMotor :");
        if (motor.statusConnect) {
          lcd.setCursor(8, 1); lcd.print("con");
        } else {
          lcd.setCursor(8, 1); lcd.print("discon");
        }
      }
      if (exaust == nodeMotorE) {
        lcd.setCursor(0, 1); lcd.print("NMaster :");
        if (master.statusConnect) {
          lcd.setCursor(8, 1); lcd.print("con");
        } else {
          lcd.setCursor(8, 1); lcd.print("discon");
        }
      }
      if (button == tekan && millis() - a5.last > 200) {
        if (exaust == nodeMasterE) {
          tampilan.push(1);
          countLcd = 0;
        }
        a5.last = millis();
      }
      break;
    case 3:
      if (countLcd == 0) {
        lcd.clear();
        countLcd = 1;
      }

      lcd.setCursor(0, 0); lcd.print("SDalam:"); lcd.print(data.pressureDalam);
      lcd.setCursor(0, 1); lcd.print("SLuar :"); lcd.print(data.pressureLuar);
      if (button == tekan && millis() - a5.last > 200) {
        if (exaust == nodeMasterE) {
          tampilan.push(1);
          countLcd = 0;
        }
        a5.last = millis();
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



  if (millis() - a0.last > 300)
  {
    if (button == atas) {// button down left
      if (++menuCounti.menu > 4) menuCounti.menu = 1;// menu akan naik jika lebih dari 4 counter akan kembali ke 1
      countLcd = 0;
    }
    a0.last = millis();
  }
  if (millis() - a1.last > 300)
  {
    if (button == bawah) {
      if (--menuCounti.menu < 1) menuCounti.menu = 3;// menu akan naik jika lebih kurang dari 1 maka counter akan kembali ke 4
      countLcd = 0;
    }
    a1.last = millis();
  }
  //menu = constrain(menu, 1, 4);
  if (countLcd == 0) {
    lcd.clear();
    countLcd = 1;
  }
  switch (menuCounti.menu) { // switch menu

    case 1:
      lcd.setCursor(0, 0); lcd.write(byte(0));
      lcd.setCursor(1, 0); lcd.print(lcdStatusStartStop);
      lcd.setCursor(0, 1); lcd.print(" SET  ");
      if (button == tekan && millis() - a5.last > 500) {
        if (data.statusHidup == 0) {
          start();
        } else {
          stop();
        }

        countLcd = 0;
        menuCounti.menu = 1;
        a5.last = millis();
      }
      break;
    case 2:
      lcd.setCursor(0, 1); lcd.write(byte(0));
      lcd.setCursor(1, 0); lcd.print(lcdStatusStartStop);
      lcd.setCursor(1, 1); lcd.print("SET  ");
      if (button == tekan && millis() - a5.last > 200) {
        setNilaiDp();
        exit();
        countLcd = 0;
        a5.last = millis();
        menuCounti.menu = 1;
      }

      break;
    case 3:
      lcd.setCursor(0, 0); lcd.write(byte(0));
      lcd.setCursor(1, 0); lcd.print("SETTING");
      lcd.setCursor(0, 1); lcd.print(" EXIT       ");
      if (button == tekan && millis() - a5.last > 200) {
        tampilan.push(2);
        // exit();
        countLcd = 0;
        a5.last = millis();
        menuCounti.menu = 1;
      }
      break;
    case 4:
      lcd.setCursor(0, 1); lcd.write(byte(0));
      lcd.setCursor(0, 0); lcd.print(" SETTING");
      lcd.setCursor(1, 1); lcd.print("EXIT         ");
      if (button == tekan && millis() - a5.last > 200) {
        exit();
        countLcd = 0;
        a5.last = millis();
        menuCounti.menu = 1;
      }
      break;

  }
}

void settingLcd() {
  if (millis() - a0.last > 300)
  {
    if (button == atas) {// button down left
      if (++menuCounti.menu > 3) menuCounti.menu = 1;// menu akan naik jika lebih dari 4 counter akan kembali ke 1
      countLcd = 0;
    }
    a0.last = millis();
  }
  if (millis() - a1.last > 300)
  {
    if (button == bawah) {
      if (--menuCounti.menu < 1) menuCounti.menu = 3;// menu akan naik jika lebih kurang dari 1 maka counter akan kembali ke 4
      countLcd = 0;
    }
    a1.last = millis();
  }
  //menu = constrain(menu, 1, 4);
  if (countLcd == 0) {
    lcd.clear();
    countLcd = 1;
  }
  switch (menuCounti.menu) { // switch menu

    case 1:
      lcd.setCursor(0, 0); lcd.write(byte(0));
      lcd.setCursor(1, 0); lcd.print("Motor");
      lcd.setCursor(0, 1); lcd.print(" PID  ");
      if (button == tekan && millis() - a5.last > 200) {
        tampilan.push(3);

        countLcd = 0;
        menuCounti.menu = 1;
        a5.last = millis();
      }
      break;
    case 2:
      lcd.setCursor(0, 1); lcd.write(byte(0));
      lcd.setCursor(1, 0); lcd.print("Motor");
      lcd.setCursor(1, 1); lcd.print("PID  ");
      if (button == tekan && millis() - a5.last > 200) {
        tampilan.push(4);
        countLcd = 0;
        a5.last = millis();
        menuCounti.menu = 1;
      }

      break;

    case 3:
      lcd.setCursor(0, 0); lcd.write(byte(0));
      lcd.setCursor(1, 0); lcd.print("EXIT ");
      if (button == tekan && millis() - a5.last > 200) {
        exit();
        countLcd = 0;
        a5.last = millis();
        menuCounti.menu = 1;
      }
      break;

  }
}

void settingMotorLcd() {
  if (!sudahDiTekan) {
    if (millis() - a0.last > 300)
    {
      if (button == atas) {// button down left
        if (++menuCounti.menu > 3) menuCounti.menu = 1;// menu akan naik jika lebih dari 4 counter akan kembali ke 1
        countLcd = 0;
      }
      a0.last = millis();
    }
    if (millis() - a1.last > 300)
    {
      if (button == bawah) {
        if (--menuCounti.menu < 1) menuCounti.menu = 3;// menu akan naik jika lebih kurang dari 1 maka counter akan kembali ke 4
        countLcd = 0;
      }
      a1.last = millis();
    }
  }
  //menu = constrain(menu, 1, 4);
  if (countLcd == 0) {
    lcd.clear();
    countLcd = 1;
  }
  switch (menuCounti.menu) { // switch menu

    case 1:
      lcd.setCursor(0, 0); lcd.write(byte(0));
      char buffMax[10];//menyimpan karakter sebanyak 6 buah
      sprintf(buffMax, "%3d", data.maxMotor);
      lcd.setCursor(1, 0); lcd.print("MaxMotor"); lcd.setCursor(12, 0); lcd.print(buffMax); lcd.print("%");
      char buffMin[10];//menyimpan karakter sebanyak 6 buah
      sprintf(buffMin, "%3d", data.minMotor);
      lcd.setCursor(1, 1); lcd.print("MinMotor"); lcd.setCursor(12, 1); lcd.print(buffMin); lcd.print("%");
      if (button == tekan && millis() - a5.last > 200 && sudahDiTekan == 0) {
        sudahDiTekan = 1;
        countLcd = 0;

        a5.last = millis();
      }
      if (sudahDiTekan == 1) {
        if (button == bawah && millis() - a5.last > 200) {
          if (++data.maxMotor > 100) data.maxMotor = 1;
          a5.last = millis();
        }
        if (button == atas && millis() - a5.last > 200) {
          if (--data.maxMotor < 1) data.maxMotor = 100;
          a5.last = millis();
        }
        if (button == tekan && millis() - a5.last > 200 && sudahDiTekan == 1) {
          sudahDiTekan = 0;
          save.maxMotor = data.maxMotor;
          kirimSet();
          countLcd = 0;
          //menuCounti.menu = 1;
          a5.last = millis();
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
      if (button == tekan && millis() - a5.last > 200 && sudahDiTekan == 0) {
        sudahDiTekan = 1;
        countLcd = 0;

        a5.last = millis();
      }
      if (sudahDiTekan == 1) {
        if (button == bawah && millis() - a5.last > 200) {
          if (++data.minMotor > 100) data.minMotor = 1;
          a5.last = millis();
        }
        if (button == atas && millis() - a5.last > 200) {
          if (--data.minMotor < 1) data.minMotor = 100;
          a5.last = millis();
        }
        if (button == tekan && millis() - a5.last > 200 && sudahDiTekan == 1) {
          sudahDiTekan = 0;
          save.minMotor = data.minMotor;
          kirimSet();
          countLcd = 0;
          //menuCounti.menu = 1;
          a5.last = millis();
        }

      }
      break;

    case 3:
      lcd.setCursor(0, 0); lcd.write(byte(0));
      lcd.setCursor(1, 0); lcd.print("EXIT ");
      if (button == tekan && millis() - a5.last > 200) {
        exit();
        countLcd = 0;
        a5.last = millis();
        menuCounti.menu = 1;
      }
      break;

  }
}

void tampilanPid() {
  if (!sudahDiTekan) {
    if (millis() - a0.last > 300)
    {
      if (button == atas) {// button down left
        if (++menuCounti.menu > 5) menuCounti.menu = 1;// menu akan naik jika lebih dari 4 counter akan kembali ke 1
        countLcd = 0;
      }
      a0.last = millis();
    }
    if (millis() - a1.last > 300)
    {
      if (button == bawah) {
        if (--menuCounti.menu < 1) menuCounti.menu = 5;// menu akan naik jika lebih kurang dari 1 maka counter akan kembali ke 4
        countLcd = 0;
      }
      a1.last = millis();
    }
  }
  //menu = constrain(menu, 1, 4);
  if (countLcd == 0) {
    lcd.clear();
    countLcd = 1;
  }
  switch (menuCounti.menu) { // switch menu

    case 1:
      lcd.setCursor(0, 0); lcd.write(byte(0));
      char buffKp[10];//menyimpan karakter sebanyak 6 buah
      sprintf(buffKp, "%3d", data.kp);
      lcd.setCursor(1, 0); lcd.print("KP"); lcd.setCursor(12, 0); lcd.print(buffKp);
      char buffKd[10];//menyimpan karakter sebanyak 6 buah
      sprintf(buffKd, "%3d", data.kd);
      lcd.setCursor(1, 1); lcd.print("KD"); lcd.setCursor(12, 1); lcd.print(buffKd);
      if (button == tekan && millis() - a5.last > 200 && sudahDiTekan == 0) {
        sudahDiTekan = 1;
        countLcd = 0;

        a5.last = millis();
      }
      if (sudahDiTekan == 1) {
        if (button == bawah && millis() - a5.last > 200) {
          if (++data.kp > 100) data.kp = 1;
          a5.last = millis();
        }
        if (button == atas && millis() - a5.last > 200) {
          if (--data.kp < 1) data.kp = 100;
          a5.last = millis();
        }
        if (button == tekan && millis() - a5.last > 200 && sudahDiTekan == 1) {
          sudahDiTekan = 0;
          save.kp = data.kp;
          kirimSet();
          countLcd = 0;
          //menuCounti.menu = 1;
          a5.last = millis();
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
      if (button == tekan && millis() - a5.last > 200 && sudahDiTekan == 0) {
        sudahDiTekan = 1;
        countLcd = 0;

        a5.last = millis();
      }
      if (sudahDiTekan == 1) {
        if (button == bawah && millis() - a5.last > 200) {
          if (++data.kd > 100) data.kd = 1;
          a5.last = millis();
        }
        if (button == atas && millis() - a5.last > 200) {
          if (--data.kd < 1) data.kd = 100;
          a5.last = millis();
        }
        if (button == tekan && millis() - a5.last > 200 && sudahDiTekan == 1) {
          sudahDiTekan = 0;
          save.kd = data.kd;
          kirimSet();
          countLcd = 0;
          //menuCounti.menu = 1;
          a5.last = millis();
        }

      }
      break;
    case 3:
      lcd.setCursor(0, 0); lcd.write(byte(0));
      char buffSet[10];//menyimpan karakter sebanyak 6 buah
      sprintf(buffSet, "%3d", data.set);
      lcd.setCursor(1, 0); lcd.print("SET"); lcd.setCursor(12, 0); lcd.print(buffSet);
      char buffSetPoint[10];//menyimpan karakter sebanyak 6 buah
      sprintf(buffSetPoint, "%3d", data.setPoint);
      lcd.setCursor(1, 1);  lcd.print("SETPOINT "); lcd.setCursor(12, 1); lcd.print(buffSetPoint);
      if (button == tekan && millis() - a5.last > 200 && sudahDiTekan == 0) {
        sudahDiTekan = 1;
        countLcd = 0;

        a5.last = millis();
      }
      if (sudahDiTekan == 1) {
        if (button == bawah && millis() - a5.last > 200) {
          if (++data.set > 100) data.set = -100;
          a5.last = millis();
        }
        if (button == atas && millis() - a5.last > 200) {
          if (--data.set < -100) data.set = 100;
          a5.last = millis();
        }
        if (button == tekan && millis() - a5.last > 200 && sudahDiTekan == 1) {
          sudahDiTekan = 0;
          save.set = data.set;
          kirimSet();
          countLcd = 0;
          //menuCounti.menu = 1;
          a5.last = millis();
        }

      }
      break;

    case 4:
      lcd.setCursor(0, 1); lcd.write(byte(0));
      //char buffSet[10];//menyimpan karakter sebanyak 6 buah
      sprintf(buffSet, "%3d", data.set);
      lcd.setCursor(1, 0); lcd.print("SET"); lcd.setCursor(12, 0); lcd.print(buffSet);
      sprintf(buffSetPoint, "%3d", data.setPoint);
      lcd.setCursor(1, 1); lcd.print("SETPOINT "); lcd.setCursor(12, 1); lcd.print(buffSetPoint);
      if (button == tekan && millis() - a5.last > 200 && sudahDiTekan == 0) {
        sudahDiTekan = 1;
        countLcd = 0;

        a5.last = millis();
      }
      if (sudahDiTekan == 1) {
        if (button == bawah && millis() - a5.last > 200) {
          if (++data.setPoint > 100) data.setPoint = -100;
          a5.last = millis();
        }
        if (button == atas && millis() - a5.last > 200) {
          if (--data.setPoint < -100) data.setPoint = 100;
          a5.last = millis();
        }
        if (button == tekan && millis() - a5.last > 200 && sudahDiTekan == 1) {
          sudahDiTekan = 0;
          save.setPoint = data.setPoint;
          kirimSet();
          countLcd = 0;
          //menuCounti.menu = 1;
          a5.last = millis();
        }

      }
      break;

    case 5:
      lcd.setCursor(0, 0); lcd.write(byte(0));
      lcd.setCursor(1, 0); lcd.print("EXIT ");
      if (button == tekan && millis() - a5.last > 200) {
        exit();
        countLcd = 0;
        a5.last = millis();
        menuCounti.menu = 1;
      }
      break;

  }
}
//====================Master======================
//=====================Motor=====================

void homeLcdMotor() {

  // //cursor
  //char buff6[16];
  if (data.statusHidup == 0) {
    lcdStatusStartStop = "OFF  ";
  } else {
    lcdStatusStartStop = "ON  ";
  }

  if (millis() - a0.last > 300)
  {
    if (button == atas) {// button down left
      if (++home.menu > 4) home.menu = 1;// menu akan naik jika lebih dari 4 counter akan kembali ke 1
      countLcd = 0;
    }
    a0.last = millis();
  }
  if (millis() - a1.last > 300)
  {
    if (button == bawah) {
      if (--home.menu < 1) home.menu = 4;// menu akan naik jika lebih kurang dari 1 maka counter akan kembali ke 4
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
      lcd.setCursor(0, 0); lcd.print(buffdp);
      //      if (sensor.statusConnect) {
      //        lcd.print(buffdp);
      //      } else {
      //        lcd.print("discon");
      //      }

      char buffset[10];//menyimpan karakter sebanyak 6 buah
      sprintf(buffset, "SET:%2d", data.set);
      lcd.setCursor(0, 1); lcd.print(buffset);

      lcd.setCursor(7, 0); lcd.print(lcdStatusStartStop);
      //Serial.println(data.maxMotor);
      char buffDpSet[10];
      sprintf(buffDpSet, "press:%3d", data.setPoint);//kecepatan
      lcd.setCursor(7, 1); lcd.print(buffDpSet);

      //Serial.println(data.maxMotor);
      if (button == tekan && millis() - a5.last > 500) {
        if (exaust == nodeMotorE) {
          tampilan.push(1);
          countLcd = 0;
        }
        a5.last = millis();

      }
      break;
    case 2:
      if (countLcd == 0) {
        lcd.clear();
        countLcd = 1;
      }
      //lcd.setCursor(0, 1); lcd.write(byte(0));
      //      lcd.setCursor(0, 0); lcd.print("NSensor:");
      //      if (sensor.statusConnect) {
      //        lcd.setCursor(8, 0); lcd.print("con");
      //      } else {
      //        lcd.setCursor(8, 0); lcd.print("discon");
      //      }
      if (exaust == nodeMasterE) {
        lcd.setCursor(0, 1); lcd.print("NMotor :");
        if (motor.statusConnect) {
          lcd.setCursor(8, 1); lcd.print("con");
        } else {
          lcd.setCursor(8, 1); lcd.print("discon");
        }
      }
      if (exaust == nodeMotorE) {
        lcd.setCursor(0, 0); lcd.print("NMaster:");
        if (master.statusConnect) {
          lcd.setCursor(8, 0); lcd.print("con     ");
        } else {
          lcd.setCursor(8, 0); lcd.print("discon");
        }
      }
      if (button == tekan && millis() - a5.last > 200) {
        if (exaust == nodeMotorE) {
          tampilan.push(1);
          countLcd = 0;
        }
        a5.last = millis();
      }
      break;
    case 3:
      if (countLcd == 0) {
        lcd.clear();
        countLcd = 1;
      }

      lcd.setCursor(0, 0); lcd.print("SDalam:"); lcd.print(data.pressureDalam);
      lcd.setCursor(0, 1); lcd.print("SLuar :"); lcd.print(data.pressureLuar);
      if (button == tekan && millis() - a5.last > 200) {
        if (exaust == nodeMotorE) {
          tampilan.push(1);
          countLcd = 0;
        }
        a5.last = millis();
      }
      break;
    case 4:
      if (countLcd == 0) {
        lcd.clear();
        countLcd = 1;
      }
      char buffKp[10];//menyimpan karakter sebanyak 6 buah
      sprintf(buffKp, "KP :%2d", data.kp);//kecepatan
      lcd.setCursor(0, 0);  lcd.print(buffKp);
      char buffDp[10];//menyimpan karakter sebanyak 6 buah
      sprintf(buffDp, "KD :%2d", data.kd);//kecepatan
      lcd.setCursor(0, 1); lcd.print(buffDp);
      char buffMax[10];
      sprintf(buffMax, "MAX:%3d", data.maxMotor);//kecepatan
      lcd.setCursor(9, 0); lcd.print(buffMax); lcd.print("%");
      char buffMin[10];
      sprintf(buffMin, "MIN:%3d", data.minMotor);//kecepatan
      lcd.setCursor(9, 1); lcd.print(buffMin); lcd.print("%");
      if (button == tekan && millis() - a5.last > 200) {
        if (exaust == nodeMotorE) {
          tampilan.push(1);
          countLcd = 0;
        }
        a5.last = millis();
      }
      break;
  }
}


void menuLcdMotor() {
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

  if (!sudahDiTekan) {
    if (millis() - a0.last > 300)
    {
      if (button == atas) {// button down left
        if (++menuCounti.menu > 4) menuCounti.menu = 1;// menu akan naik jika lebih dari 4 counter akan kembali ke 1
        countLcd = 0;
      }
      a0.last = millis();
    }
    if (millis() - a1.last > 300)
    {
      if (button == bawah) {
        if (--menuCounti.menu < 1) menuCounti.menu = 4;// menu akan naik jika lebih kurang dari 1 maka counter akan kembali ke 4
        countLcd = 0;
      }
      a1.last = millis();
    }
  }
  //menu = constrain(menu, 1, 4);
  if (countLcd == 0) {
    lcd.clear();
    countLcd = 1;
  }
  switch (menuCounti.menu) { // switch menu

    case 1:
      lcd.setCursor(0, 0); lcd.write(byte(0));
      lcd.setCursor(1, 0); lcd.print(lcdStatusStartStop);
      lcd.setCursor(1, 1); lcd.print(lcdStatusStartStopManual);
      if (button == tekan && millis() - a5.last > 500) {
        if (data.statusHidup == 0 ) {
          start();
        } else {
          stop();
        }

        countLcd = 0;
        menuCounti.menu = 1;
        a5.last = millis();
      }
      break;


    case 2:
      lcd.setCursor(0, 1); lcd.write(byte(0));
      lcd.setCursor(1, 0); lcd.print(lcdStatusStartStop);
      lcd.setCursor(1, 1); lcd.print(lcdStatusStartStopManual);
      if (button == tekan && millis() - a5.last > 500) {
        if (statusHidupManual == 0) {
          startManual();
        } else {
          stopManual();
        }

        countLcd = 0;
       // menuCounti.menu = 1;
        a5.last = millis();
      }

      break;

    case 3:
      lcd.setCursor(0, 0); lcd.write(byte(0));
      char buffSpeedManual[10];
      sprintf(buffSpeedManual, "KEC. MAN.  %3d", speedMotorManual);
      lcd.setCursor(1, 0); lcd.print(buffSpeedManual);
      lcd.setCursor(1, 1); lcd.print("EXIT  ");
      if (button == tekan && millis() - a5.last > 200 && sudahDiTekan == 0) {
        sudahDiTekan = 1;
        countLcd = 0;

        a5.last = millis();
      }
      if (sudahDiTekan == 1) {
        if (button == bawah && millis() - a5.last > 200) {
          if (++speedMotorManual > 100) speedMotorManual = 1;
          a5.last = millis();
        }
        if (button == atas && millis() - a5.last > 200) {
          if (--speedMotorManual < 1) speedMotorManual = 100;
          a5.last = millis();
        }
        if (button == tekan && millis() - a5.last > 200 && sudahDiTekan == 1) {
          sudahDiTekan = 0;
          speedMotorManualS = speedMotorManual;
          countLcd = 0;
          //menuCounti.menu = 1;
          a5.last = millis();
        }

      }

      break;

    case 4:
      lcd.setCursor(0, 1); lcd.write(byte(0));
      sprintf(buffSpeedManual, "KEC. MAN.  %3d", speedMotorManual);
      lcd.setCursor(1, 0); lcd.print(buffSpeedManual);
      lcd.setCursor(1, 1); lcd.print("EXIT ");
      if (button == tekan && millis() - a5.last > 200) {
        exit();
        countLcd = 0;
        a5.last = millis();
        menuCounti.menu = 1;
      }
      break;

  }
}
