int button_Pin = A2;
int x_Pin = A0; //Nama alias pin A1 yaitu xPin
int y_Pin = A1; //Nama aliasa pin A0 yaitu yPin
 
//nilai default
int x_Position = 0;
int y_Position = 0;
int buttonState = 0;
int dibagiDua=1022/2;
int xHasilMap=0;
int yHasilMap=0;
double derajat=0;
 
void setup() {
//inisialisasi komunikasi serial pada 9600bps
Serial.begin(9600);
//deklarasi xPin dan yPin sebagai input
pinMode(x_Pin, INPUT);pinMode(y_Pin, INPUT);
//deklarasi buttonPin sebagai input dengan kondisi pull-up
pinMode(button_Pin, INPUT_PULLUP);
}
 
void loop() {
//Pembacaan kondisi
x_Position = analogRead(x_Pin);y_Position = analogRead(y_Pin);
buttonState = digitalRead(button_Pin);
if(x_Position>dibagiDua){
  xHasilMap=map(x_Position,(dibagiDua+1),1022,0,255);
}else if(x_Position<=dibagiDua){
  xHasilMap=map(x_Position,0,(dibagiDua),-255,0);
}

if(y_Position>dibagiDua){
  yHasilMap=map(y_Position,(dibagiDua+1),1022,0,255);
}else if(y_Position<=dibagiDua){
  yHasilMap=map(y_Position,0,(dibagiDua),-255,0);
}
derajat= atan2(yHasilMap,xHasilMap)*180/PI;
if(derajat<0){
  derajat=360+derajat;
}

 
//menampilkan hasil pada serial monitor
Serial.print(" |variable");Serial.print(xHasilMap);
Serial.print("variable");Serial.print(yHasilMap);
Serial.print("X: ");Serial.print(x_Position);
Serial.print(" | Y: ");Serial.print(y_Position);
Serial.print(" | Button: ");Serial.println(buttonState);
Serial.print("hasil  ");Serial.print(derajat);
 
delay(100); //waktu tunda sebesar 100ms
}
