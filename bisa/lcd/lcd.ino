#include <Wire.h>
#include <LiquidCrystal_I2C.h>
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
}

void loop() {
  // put your main code here, to run repeatedly:

  lcd.setCursor(5, 0);
  switch (read_button()) {
    case atas: lcd.print("Atas");
      break;
    case bawah: lcd.print("bawah   ");
      break;
    case kanan: lcd.print("Kanan      ");
      break;
    case kiri: lcd.print("Kiri  ");
      break;
    case unpressed: lcd.print("None       ");
      break;
    case tekan: lcd.print("tekan");
      break;
  }

}
