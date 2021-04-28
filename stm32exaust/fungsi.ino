


void buzzerF() {

  unsigned long currentMillis = millis();
  if (countBa == 0) {
    if (currentMillis - a2.last >= interval) {
      // save the last time you blinked the LED
      a2.last = currentMillis;

      // if the LED is off turn it on and vice-versa:
      if (buzzerS == LOW) {
        buzzerS = HIGH;
      } else {
        buzzerS = LOW;
        countBa = 1;
      }


      // set the LED with the ledState of the variable:
      digitalWrite(buzzer, buzzerS);
    }
  }
}


void nodeMasterF() {
  //motor.pressureDalam = bmpPressure();

  //buzzerF();


  //Serial.println(data.pressureDalam);
  menerimaDataNode();
  data.pressureDalam = bmpPressure();
  data.dp = data.pressureDalam - data.pressureLuar;
  data.dpSet = data.dp - data.setS;
  if (data.dpSet != lastDpSet) {
    lastDpSet = data.dpSet;
  }
  //Serial.println(encoderInput());
  cekKoneksi();
  langsungIr();


  if (data.statusHidup && !statusHidupManual) {
    Serial.print("pid: ");
    Serial.println(pid());

    motorAcRun(pid());
  } else if (!data.statusHidup && statusHidupManual) {

    motorAcRun(data.speedMotorManualS);
  } else if (!data.statusHidup && !statusHidupManual) {
    analogWrite(PA2, 0);

  }

  tampilanLcd(tampilan.peek());


  //  lcd.setCursor(0, 0); lcd.print("luar:");// menampilkan trace
  //  lcd.setCursor(7, 0); lcd.print(data.pressureLuar);//
  //  lcd.setCursor(0, 1); lcd.print("Dalam:");// menampilkan trace
  //  lcd.setCursor(7, 1); lcd.print(data.pressureDalam);//

}


int pid() {
  kesalahan = data.dpSet - data.setPoint;
  derivatifKesalahan = kesalahan - kesalahanLalu;
  integralKesalahan +=  kesalahan;
  kesalahanLalu = kesalahan;
//  if(data.dpSet<(data.setPoint-1)){
//    integralKesalahan=0;
//    }


  return (data.kp * kesalahan) + (data.kd * derivatifKesalahan) + (data.ki * integralKesalahan);
}

void motorAcRun(int persen) {
  persen = constrain(persen, data.minMotor, data.maxMotor);
  float pwm = 0;
  if (persen != 0) {
    pwm = (persen / 100.0) * 255;
  } else {
    pwm = 0;
  }

  analogWrite(PA2, pwm);
  Serial.print(pwm);
  Serial.print("persen: ");
  Serial.println(persen);
}



void irConfig() {
#if defined(__AVR_ATmega32U4__) || defined(SERIAL_USB) || defined(SERIAL_PORT_USBVIRTUAL)
  delay(2000); // To be able to connect Serial monitor after reset and before first printout
#endif
#if defined(ESP8266)
  Serial.println(); // to separate it from the internal boot output
#endif

  // Just to know which program is running on my Arduino
  Serial.println(F("START " __FILE__ " from " __DATE__ "\r\nUsing library version " VERSION_IRMP));

  irmp_init();

  Serial.print(F("Ready to receive IR signals of protocols: "));
  irmp_print_active_protocols(&Serial);
#if defined(ARDUINO_ARCH_STM32)
  Serial.println(F("at pin " IRMP_INPUT_PIN_STRING));
#else
  Serial.println(F("at pin " STR(IRMP_INPUT_PIN)));
#endif

#ifdef ALTERNATIVE_IRMP_FEEDBACK_LED_PIN
  irmp_irsnd_LEDFeedback(true); // Enable receive signal feedback at ALTERNATIVE_IRMP_FEEDBACK_LED_PIN
  Serial.print(F("IR feedback pin is " STR(ALTERNATIVE_IRMP_FEEDBACK_LED_PIN)));
#endif

}



byte irInput(bool status = 0) {



  if (irmp_get_data(&irmp_data)) {
    /*
       Skip repetitions of command
    */

    /*
       Here data is available and is no repetition -> evaluate IR command
    */
    if (status == 0) {
      if (!(irmp_data.flags & IRMP_FLAG_REPETITION)) {

        return irmp_data.command;
      }
      return irmp_data.command = 0;


      // irmp_result_print(&irmp_data);
    } else if (status == 1) {
      //
      if ((irmp_data.flags & IRMP_FLAG_REPETITION)) {
        return irmp_data.command;
      }
      return irmp_data.command = 0;


      // irmp_result_print(&irmp_data);
    } else if (status == 2) {
      if ((irmp_data.flags & IRMP_FLAG_REPETITION)) {
        return irmp_data.command;
      }

    }
  }

}



void exit() {
  tampilan.pop();
}

void afterEnter(byte status = 0) {
  irmp_data.command = 0;
  countB = 0;
  a0.last = millis();
  countBa = 0;
  countLcd = 0;
  if (status == 0) {
    home.menu = 1;
  } else if (status == 1) {

  }
  Serial.print("123");
}

void langsungIr() {
  //  Serial.println("masuk");
  if (((millis() - a0.last > 300)))  {
    //Serial.println("satu");
    if (irInput(0) == irIn.lowKp) {
      save.kp = save.lKp;
      data.kp = save.kp;
      EEPROM.put(addressEE, save);
    } else if (irInput(0) == irIn.mediumKp) {
      save.kp = save.mKp;
      data.kp = save.kp;
      EEPROM.put(addressEE, save);
    } else if (irInput(0) == irIn.highKp) {
      save.kp = save.hKp;
      data.kp = save.kp;
      EEPROM.put(addressEE, save);
    } else if (irInput(0) == irIn.startR) {
      if (!statusHidupManual && !data.statusHidup) {
        start();
      } else if (!statusHidupManual && data.statusHidup) {
        stop();
      }

    } else if (irInput(0) == irIn.setR) {
      setNilaiDp();
    }
  }
}
void buzzerFlipFlopConf() {



  // Set Flip cycle time in millisecondes
  myFlipFlop.setFlipDelay(2000);
  // Set Flip call back function (the function will be called after desigred ms delay)
  myFlipFlop.setFlipHandler(flip);

  // Set Flop cycle time in millisecondes
  myFlipFlop.setFlopDelay(1000 * 60);
  // Set Flop call back function (the function will be called after desigred ms delay)
  myFlipFlop.setFlopHandler(flop);
  // Start flip flop
  myFlipFlop.start();
}
void flip()
{
  // Any action desigred should be put in this function
  // In this examle led green turn on and red turn off
  digitalWrite(PA10, HIGH);

}
void flop()
{
  // Any action desigred should be put in this function
  // In this examle led green turn off and red turn on
  digitalWrite(PA10, LOW);

}

void cekKoneksi() {
  if (millis() - a1.last > 5000 ) {
    sensor.statusConnect = 0;
  }
  if (millis() - a1.last > 25000 ) {
    data.statusHidup = 0;
  }
  if (data.dp > 100 || data.dp < -100) {
    data.statusHidup = 0;
  }
  if (sensor.statusConnect == 0 && statusHidupManual == 0) {
    myFlipFlop.loop();
  }


}

void start() {

  if (sensor.statusConnect == 1)
  {
    data.statusHidup = 1;
  } else {

    data.statusHidup = 0;
  }



}

void stop() {

  data.statusHidup = 0;


}

void startManual() {


  statusHidupManual = 1;


}

void stopManual() {

  statusHidupManual = 0;


}

void setNilaiDp() {
  data.setS = data.dp;
  save.setS = data.setS;
}
//
//int encoderInput() {
//  readBt = digitalRead(BUTTON);
//
//  if (position != encoder.getPosition() || lastB != readBt) {
//    if (position < encoder.getPosition()) {
//      position = encoder.getPosition();
//      return 1;
//    } else if (position > encoder.getPosition()) {
//      position = encoder.getPosition();
//      return 2;
//    } else if ((lastB != readBt)) {
//      lastB = readBt;
//      if(readBt==0){
//      return 3;}
//    }
//    return 0;
//  }
//}
