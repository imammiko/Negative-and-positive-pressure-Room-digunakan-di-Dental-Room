
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <EEPROM.h>
int addressEE = 0;
int addressEER = 0;
#include <Adafruit_BMP280.h>
//===============nrf=======
#include <RF24Network.h>
#include <RF24.h>
#include <SPI.h>
#include <DWEasyFlipFlop.h>
DWEasyFlipFlop myFlipFlop;
#include "Stack.h"

//===============remote=====

#include <Arduino.h>

/*
   Set input pin and output pin definitions etc.
*/
#include "PinDefinitionsAndMore.h"

#define IRMP_PROTOCOL_NAMES 1 // Enable protocol number mapping to protocol strings - requires some FLASH. Must before #include <irmp*>

#include <irmpSelectMain15Protocols.h>  // This enables 15 main protocols
//#define IRMP_SUPPORT_NEC_PROTOCOL        1 // this enables only one protocol

#ifdef ALTERNATIVE_IRMP_FEEDBACK_LED_PIN
#define IRMP_FEEDBACK_LED_PIN   ALTERNATIVE_IRMP_FEEDBACK_LED_PIN
#endif
/*
   After setting the definitions we can include the code and compile it.
*/
#include <irmp.c.h>

IRMP_DATA irmp_data;

//=============================

//=============encoder====
#include <RotaryEncoder.h>

#define PIN_A   PB4 //ky-040 clk pin, add 100nF/0.1uF capacitors between pin & ground!!!
#define PIN_B  PB3 //ky-040 dt  pin, add 100nF/0.1uF capacitors between pin & ground!!!
#define BUTTON  PB5 //ky-040 sw  pin, add 100nF/0.1uF capacitors between pin & ground!!!
#define cw 1
#define ccw 2
#define tekan 3
bool readBt = 0;
bool lastB;
bool countB;


int16_t position = 0;

RotaryEncoder encoder(PIN_A, PIN_B, 0);
//=================================
//===============nrf=================

RF24 radio(PA4, PA3);
RF24Network network(radio);
const uint16_t nodeKendali = 00;    //** Address of our node in Octal format ( 04,031, etc)
const uint16_t nodeSensor = 01;
//====================================




//=====bmp==========//

Adafruit_BMP280 bmp; // use I2C interface
Adafruit_Sensor *bmp_temp = bmp.getTemperatureSensor();
Adafruit_Sensor *bmp_pressure = bmp.getPressureSensor();
//============================

//====================kursor=============
uint8_t kursor[8] = {// kursor ke kanan
  0b01000,
  0b01100,
  0b01110,
  0b01111,
  0b01110,
  0b01100,
  0b01000,
  0b00000
}, kursor1[8] = {// kursor ke kiri
  0b00010,
  0b00110,
  0b01110,
  0b11110,
  0b01110,
  0b00110,
  0b00010,
  0b00000
};

struct menuCount {
  byte menu = 1;
} home, menuCounti;
byte countLcd = 0;
LiquidCrystal_I2C lcd(0x27, 16, 2); // set the LCD address to 0x27 for a 16 chars and 2 line display

//================================================
struct motorAc {
  int minMotor, maxMotor;
  int setPoint, dp, dpSet, setS;
  float kp, kd, ki;
  double pressureLuar;
  double pressureDalam;
  bool statusHidup = 0;
  byte modeKirim;
  int speedMotorManualS;
};
struct komSensor {
  float pressureLuar;
};
struct motorAcEepfrom {
  int minMotor, maxMotor;
  int setS, setPoint;
  float kp, kd, ki;
  int speedMotorManualS;
  float lKp;
  float mKp;
  float hKp;
};

komSensor senLuar;
motorAc data;
motorAcEepfrom save;//EEprom
// EEprom
//================b;uzzer==========
#define buzzer PA10
bool buzzerS = 0;
long intervalDiscon = 1500;
long interval = 50;
struct waktu {
  unsigned long last;
} a0, a1, a2;
int countBa = 0;


struct statusNode {
  boolean statusConnect = 0;
  boolean statusGagal = 0;
  byte countPing = 0;
} sensor;

struct irRemote {
  byte lowKp = 69;
  byte mediumKp = 70;
  byte highKp = 71;
  byte startR = 22;
  byte setR = 13;
  byte atas = 24;
  byte bawah = 82;
  byte kiri = 8;
  byte kanan = 90;
  byte tengah = 28;
} irIn;

//struct irRemote {
//  byte lowKp ;
//  byte mediumKp ;
//  byte highKp ;
//  byte startR ;
//  byte setR ;
//  byte atas ;
//  byte bawah ;
//  byte kiri ;
//  byte kanan ;
//  byte tengah ;
//} irIn;

bool sudahDiTekan = 0;
float kesalahanLalu = 0;
int lastDpSet = 0;
bool statusHidupManual = 0;

String lcdStatusStartStop = "";
String lcdStatusStartStopManual = "";
float kesalahan = 0;
float derivatifKesalahan = 0;
float integralKesalahan = 0;
//menuCounti.menu=4;
//=============mengubah node==========

//**************************************

class Stack tampilan;



void setup() {
  Serial.begin(9600);
  irConfig();
  lcd.begin();
  lcd.backlight();
  lcd.clear();
  bmpConfig();
  pinMode(PB5, INPUT_PULLUP);
  pinMode(PA2, OUTPUT);
  lcd.createChar(0, kursor);//membuat karakter bayte
  lcd.createChar(1, kursor1);// memb
  addressEER += addressEE + (20 + sizeof(irIn));
  SPI.begin();
  radio.begin();
  network.begin(/*channel*/ 90, /*node address*/ nodeKendali);
  encoderConfig();
  analogWrite(PA2, 0);
  // motorAcRun(0);

  //readB();
  //
  if (digitalRead(BUTTON) == 0) {
    lcd.setCursor(0, 0); lcd.print("FACTORY SET.....");// di lcd set cursor 0,0
    delay(800);// jeada waktu 800ms
    lcd.clear();// lcd bersih
    lcd.setCursor(0, 0); lcd.print("Initialization  ");// lcd initialization 0,0
    for (byte x = 0; x <= 15; ++x) {//buat efek garis
      lcd.setCursor(x, 1); lcd.write(0xff);
      delay(25);
    }
    //
    //  int minMotor, maxMotor;
    //  int setS, setPoint;
    //  int kp, kd;
    //  int speedMotorManualS;
    save.minMotor = 0;
    save.maxMotor = 100;
    save.setS = 0;
    save.setPoint = -10;
    save.kp = 3;
    save.kd = 0;
    save.ki = 1;
    save.speedMotorManualS = 50;

    EEPROM.put(addressEE, save);
    //    save.minMotor = 0;
    //    save.maxMotor = 0;// memasukan setingan ke awal
    //    save.kp = 0;
    //    save.kd = 0;
    //    save.setPoint = 0;
    //    save.set = 0;
    //    speedMotorManualS = 100;

    lcd.setCursor(0, 1); lcd.print("    Complete    ");
    delay(800);
    lcd.clear();

  }
  lcd.setCursor(0, 0); lcd.print("    exaust    ");
  delay(1000);
  lcd.clear();
  EEPROM.get( addressEE, save );
  addressEER += addressEE + (20 + sizeof(save));
  EEPROM.get( addressEER, irIn );
  data.minMotor = save.minMotor;
  data.maxMotor = save.maxMotor;
  data.setS = save.setS;
  data.setPoint = save.setPoint;
  data.kp = save.kp;
  data.kd = save.kd;
  data.ki = save.ki;
  data.speedMotorManualS = save.speedMotorManualS;

  tampilan.push(0);
  radio.setPALevel(RF24_PA_MAX);
  Serial.println("setup");
  pinMode(buzzer, OUTPUT);
  buzzerFlipFlopConf();
}

void loop() {
  buzzerF();
  // put your main code here, to run repeatedly:
  nodeMasterF();

  // Serial.println(sizeof(irIn));
  //motorAcRun(50 );

  // Serial.println(readB());
}
