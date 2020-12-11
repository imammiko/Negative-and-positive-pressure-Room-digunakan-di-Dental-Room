void encoderISR()
{
  encoder.readAB();
}

void encoderButtonISR()
{
  encoder.readPushButton();
}

void encoderConfig() {
  encoder.begin();                                                           //set encoders pins as input & enable built-in pullup resistors

  attachInterrupt(digitalPinToInterrupt(PIN_A),  encoderISR,       CHANGE);  //call encoderISR()    every high->low or low->high changes

}

void readB() {
  readBt = digitalRead(BUTTON);
  if ((lastB != readBt)) {
    lastB = readBt;
    if (readBt == 0) {
      countB = 1;
    }
  }

}

//
//void lihatPutar() {
//  if (position != encoder.getPosition())
//  {
//    position = encoder.getPosition();
//    //Serial.println(position);
//
//  }
//}
