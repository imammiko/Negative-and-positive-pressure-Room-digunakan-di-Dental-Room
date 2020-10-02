int button_Pin = A2;
int x_Pin = A0; //Nama alias pin A1 yaitu xPin
int y_Pin = A1; //Nama aliasa pin A0 yaitu yPin
 
//nilai default
int x_Position = 0;
int y_Position = 0;
int buttonState = 0;
 
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
 
//menampilkan hasil pada serial monitor
Serial.print("X: ");Serial.print(x_Position);
Serial.print(" | Y: ");Serial.print(y_Position);
Serial.print(" | Button: ");Serial.println(buttonState);
 
delay(100); //waktu tunda sebesar 100ms
}
