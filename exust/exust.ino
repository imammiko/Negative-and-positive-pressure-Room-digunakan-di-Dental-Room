#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <EEPROM.h>
#include <EEWrap.h>
//===============nrf=======
#include <RF24Network.h>
#include <RF24.h>
#include <SPI.h>
//******************nrf*******
#include "Stack.h"

#define button read_button()
#define publish 0
#define subribe 1
#define ping 2

RF24 radio(7, 8);
RF24Network network(radio);
const uint16_t nodeMaster = 00;    //** Address of our node in Octal format ( 04,031, etc)
const uint16_t nodeSensor = 01; // **Address of the other node in Octal format
const uint16_t nodeMotor = 02;//**
//*****************nrf**********
//=============sensor bmp========
#include <Adafruit_BMP280.h>
Adafruit_BMP280 bmp; // use I2C interface
Adafruit_Sensor *bmp_temp = bmp.getTemperatureSensor();
Adafruit_Sensor *bmp_pressure = bmp.getPressureSensor();

//**************sensor bmp*************

//************************kursor*******************
char kursor[8] = {// kursor ke kanan
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
//=======================kursor==================

//=============button==========
#define button_Pin A2
#define x_Pin A0
#define y_Pin A1
#define atas 0
#define bawah 1
#define kiri 2
#define kanan 3
#define yes 4
#define unpressed 5
#define tekan 6
//******************button**************

LiquidCrystal_I2C lcd(0x27, 16, 2); // set the LCD address to 0x27 for a 16 chars and 2 line display
enum Exaust {nodeSensorE, nodeMasterE, nodeMotorE};
struct joyStick {
  int x_Position = 0;
  int y_Position = 0;
  int buttonState = 0;
  int dibagiDua = 1022 / 2;
  int xHasilMap = 0;
  int yHasilMap = 0;
  double derajat = 0;
  double polar = 0;

} joy;

struct motorAc {
  int minMotor, maxMotor;
  int setPoint, dp, dpSet, set;
  unsigned int kp, kd;
  double pressureLuar;
  double pressureDalam;
  bool statusHidup = 0;
  byte modeKirim;

};
struct motorAcEepfrom {
  int16_e minMotor, maxMotor;
  int16_e set, setPoint;
  uint16_e kp, kd;


};
motorAc dataKom;
motorAc data;
motorAcEepfrom save EEMEM;
struct waktu {
  unsigned long last;
} a0, a1, a2, a3, a4, a5;
struct statusNode {
  boolean statusConnect = 0;
  boolean statusGagal = 0;
  byte countPing = 0;
} sensor, motor, master;
String lcdStatusStartStop = "";
String lcdStatusStartStopManual = "";
//enum Exaust {nodeSensorE, nodeMasterE, nodeMotorE};
bool sudahDiTekan = 0;
int kesalahanLalu = 0;
int lastDpSet = 0;
bool statusHidupManual = 0;
int speedMotorManual = 0;
int16_e speedMotorManualS EEMEM;
//menuCounti.menu=4;
//=============mengubah node==========
Exaust exaust = nodeSensorE;
//**************************************

class Stack tampilan;

void setup() {
  // put your setup code here, to run once:
  // initialize the lcd
  Serial.begin(9600);
  lcd.init();
  // Print a message to the LCD.
  lcd.backlight();
  deklarasiJoy();
  //  lcd.setCursor(0, 0); lcd.print("test");
  //  delay(1000);
  lcd.clear();
  if (exaust != nodeMotorE) {
    bmpConfig();
  }
  lcd.createChar(0, kursor);//membuat karakter bayte
  lcd.createChar(1, kursor1);// memb
  switch (exaust) {
    case nodeSensorE:
      nrfConfig(90, nodeSensor);
      break;
    case nodeMasterE:
      nrfConfig(90, nodeMaster);
      break;
    case nodeMotorE:
      nrfConfig(90, nodeMotor);
      break;
    default:
      Serial.println("masukan nodenya!!");
  }

  if (button == kiri) {
    lcd.setCursor(0, 0); lcd.print("FACTORY SET.....");// di lcd set cursor 0,0
    delay(800);// jeada waktu 800ms
    lcd.clear();// lcd bersih
    lcd.setCursor(0, 0); lcd.print("Initialization  ");// lcd initialization 0,0
    for (byte x = 0; x <= 15; ++x) {//buat efek garis
      lcd.setCursor(x, 1); lcd.write(0xff);
      delay(25);
    }

    save.minMotor = 0;
    save.maxMotor = 0;// memasukan setingan ke awal
    save.kp = 0;
    save.kd = 0;
    save.setPoint = 0;
    save.set = 0;
    speedMotorManualS = 100;

    lcd.setCursor(0, 1); lcd.print("    Complete    ");
    delay(800);
    lcd.clear();

  }
  //  lcd.setCursor(0, 0); lcd.print("    exaust    ");
  //  delay(1000);
  lcd.clear();

  data.maxMotor =  save.maxMotor;// memasukan setingan ke awal


  data.maxMotor = save.maxMotor;
  data.minMotor = save.minMotor;
  data.setPoint = save.setPoint;
  data.set = save.set;
  data.kp = save.kp;
  data.kd = save.kd;
  speedMotorManual = speedMotorManualS;
  if (exaust == nodeMasterE) {
    tampilan.push(0);
  } else if (exaust == nodeMotorE) {
    tampilan.push(0);
  }

  Serial.println("setup");
}

void loop() {
  // data.pressureLuar=10;
  //dataKom.pressureLuar=5; // put your main code here, to run repeatedly:





  switch (exaust) {
    case nodeSensorE:
      nodeSensorF();
      break;
    case nodeMasterE:
      nodeMasterF();
      break;
    case nodeMotorE:
      nodeMotorF();
      break;
    default:
      Serial.println("masukan nodenya!!");
  }

}


\
