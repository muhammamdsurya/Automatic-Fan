#include <Arduino.h>
#line 1 "C:\\Users\\muham\\AppData\\Local\\Temp\\.arduinoIDE-unsaved2023415-18580-1qri0i6.up24\\sketch_may15a\\sketch_may15a.ino"
#include <Servo.h> // library untuk mengontrol servo
//#include <Adafruit_LiquidCrystal.h> library lain
//Adafruit_LiquidCrystal lcd(0); 
#include <LiquidCrystal.h>

#define servoPin 7 // pin servo terhubung ke pin 7 pada Arduino
#define tempPin A0 // pin sensor temperatur terhubung ke pin A0 pada Arduino
#define ledYellowPin 2 // pin LED kuning terhubung ke pin 2 pada Arduino
#define ledRedPin 4 // pin LED merah terhubung ke pin 4 pada Arduino

const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
Servo myservo; // membuat objek servo
int tempVal; // variabel untuk menyimpan nilai suhu
int servoPos = 0; // posisi awal servo
int ledYellowState = LOW; // status awal LED kuning (mati)
int ledRedState = LOW; // status awal LED merah (mati)

#line 19 "C:\\Users\\muham\\AppData\\Local\\Temp\\.arduinoIDE-unsaved2023415-18580-1qri0i6.up24\\sketch_may15a\\sketch_may15a.ino"
void setup();
#line 29 "C:\\Users\\muham\\AppData\\Local\\Temp\\.arduinoIDE-unsaved2023415-18580-1qri0i6.up24\\sketch_may15a\\sketch_may15a.ino"
void loop();
#line 44 "C:\\Users\\muham\\AppData\\Local\\Temp\\.arduinoIDE-unsaved2023415-18580-1qri0i6.up24\\sketch_may15a\\sketch_may15a.ino"
float convertToCelcius(int tempVal);
#line 50 "C:\\Users\\muham\\AppData\\Local\\Temp\\.arduinoIDE-unsaved2023415-18580-1qri0i6.up24\\sketch_may15a\\sketch_may15a.ino"
void controlServo(float temperature);
#line 61 "C:\\Users\\muham\\AppData\\Local\\Temp\\.arduinoIDE-unsaved2023415-18580-1qri0i6.up24\\sketch_may15a\\sketch_may15a.ino"
void controlLED(float temperature);
#line 19 "C:\\Users\\muham\\AppData\\Local\\Temp\\.arduinoIDE-unsaved2023415-18580-1qri0i6.up24\\sketch_may15a\\sketch_may15a.ino"
void setup() {
  myservo.attach(servoPin); // menghubungkan servo ke pin 7
  pinMode(ledYellowPin, OUTPUT); // mengatur pin LED kuning sebagai output
  pinMode(ledRedPin, OUTPUT); // mengatur pin LED merah sebagai output
  pinMode(LED_BUILTIN, OUTPUT);
  lcd.begin(16, 2);
  Serial.begin(9600); // mengaktifkan komunikasi serial
  
}

void loop() {
  tempVal = analogRead(tempPin); // membaca nilai suhu dari sensor temperatur
  float temperature = convertToCelcius(tempVal); // mengonversi nilai analog menjadi suhu dalam derajat Celcius
  lcd.setCursor(0,0);
  lcd.print("Suhu Saat Ini:    ");
  lcd.setCursor(0,1);
  lcd.print(String(temperature) + "C                ");
  
  controlServo(temperature); // mengontrol servo sesuai dengan suhu
  controlLED(temperature); // mengontrol LED sesuai dengan suhu
  digitalWrite(ledRedPin,ledRedState); 
  digitalWrite(ledYellowPin,ledYellowState);
  delay(500); // jeda sebelum membaca suhu kembali
}

float convertToCelcius(int tempVal) {
  float voltage = tempVal * 5.0 / 1023.0; // mengonversi nilai analog menjadi tegangan
  float temperature = (voltage - 0.5) * 100; // mengonversi tegangan menjadi suhu dalam derajat Celcius
  return temperature;
}

void controlServo(float temperature) {
  if (temperature > 30) { // jika suhu lebih dari 30 derajat Celcius
    servoPos = 110; // memutar servo ke posisi 110 derajat
  } else if (temperature >= 25 && temperature <= 30) { // jika suhu di antara 25 dan 30 derajat Celcius
    servoPos = 50; // memutar servo ke posisi 50 derajat
  } else { // jika suhu kurang dari 25 derajat Celcius
    servoPos = 0; // memutar servo ke posisi 0 derajat
  }
  myservo.write(servoPos); // menggerakkan servo ke posisi yang ditentukan
}

void controlLED(float temperature) {
  if (temperature > 30) { // jika suhu lebih dari 30 derajat Celcius
    ledYellowState = LOW; // mematikan LED kuning
    ledRedState = HIGH;
  } else if (temperature >= 25 && temperature <= 30) {
   	ledYellowState = HIGH; // mematikan LED kuning
    ledRedState = LOW;
  } else {
   	ledYellowState = LOW; // mematikan LED kuning
    ledRedState = LOW;
  }
}

