#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <EEPROM.h>
#include <EEWrap.h>
//===============nrf=======
#include <RF24Network.h>
#include <RF24.h>
#include <SPI.h>
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
  int MAX_KI, MAX_KA, VH, VL;
  unsigned int SPEED, SETPOINT_KA, SETPOINT_KI, SETPOINT_MID, KP, KD;
  double pressureLuar;
  double pressureDalam;
};

motorAc motor EEMEM;
const unsigned long interval = 2000; //ms  // How often to send 'hello world to the other unit

unsigned long last_sent;     
void setup() {
  // put your setup code here, to run once:
  // initialize the lcd
  Serial.begin(9600);
  lcd.init();
  // Print a message to the LCD.
  lcd.backlight();
  deklarasiJoy();
  lcd.setCursor(0, 0); lcd.print("test");
  delay(1000);
  lcd.clear();
  bmpConfig();
  nrfConfig(90, nodeMaster);

}

void loop() {
  // put your main code here, to run repeatedly:



}
