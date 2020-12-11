


void nodeMasterF() {
  //motor.pressureDalam = bmpPressure();





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

  tampilanLcd(tampilan.peek());

  if (data.statusHidup && !statusHidupManual) {
    Serial.print("pid: ");
      Serial.println(pid());
    
    motorAcRun(pid());
  } else if (!data.statusHidup && statusHidupManual) {
   
    motorAcRun(data.speedMotorManualS);
  }
  //  lcd.setCursor(0, 0); lcd.print("luar:");// menampilkan trace
  //  lcd.setCursor(7, 0); lcd.print(data.pressureLuar);//
  //  lcd.setCursor(0, 1); lcd.print("Dalam:");// menampilkan trace
  //  lcd.setCursor(7, 1); lcd.print(data.pressureDalam);//

}


int pid() {
  int kesalahan = data.dpSet - data.setPoint;
  int derivatifKesalahan = kesalahan - kesalahanLalu;
  kesalahanLalu = kesalahan;

  return (data.kp * kesalahan) + (data.kd * derivatifKesalahan);
}

void motorAcRun(int persen) {
  persen = constrain(persen, data.minMotor, data.maxMotor);
  int pwm = (persen / 100.0) * 65535;
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
    } else {
      //
      if ((irmp_data.flags & IRMP_FLAG_REPETITION)) {
        return irmp_data.command;
      }
      return irmp_data.command = 0;


      // irmp_result_print(&irmp_data);
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

  countLcd = 0;
  if (status == 0) {
    home.menu = 1;
  } else if (status == 1) {

  }
  Serial.print("123");
}

void cekKoneksi() {
  if (millis() - a1.last > 5000 ) {
    sensor.statusConnect = 0;
  }
  if (millis() - a1.last > 25000 ) {
    data.statusHidup = 0;
  }
  if(data.dp>100||data.dp<-100){
    data.statusHidup = 0;
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
