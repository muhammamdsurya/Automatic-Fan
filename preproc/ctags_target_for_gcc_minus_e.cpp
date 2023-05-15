# 1 "C:\\Users\\muham\\AppData\\Local\\Temp\\.arduinoIDE-unsaved2023415-18580-1qri0i6.up24\\sketch_may15a\\sketch_may15a.ino"
# 2 "C:\\Users\\muham\\AppData\\Local\\Temp\\.arduinoIDE-unsaved2023415-18580-1qri0i6.up24\\sketch_may15a\\sketch_may15a.ino" 2
//#include <Adafruit_LiquidCrystal.h> library lain
//Adafruit_LiquidCrystal lcd(0); 
# 5 "C:\\Users\\muham\\AppData\\Local\\Temp\\.arduinoIDE-unsaved2023415-18580-1qri0i6.up24\\sketch_may15a\\sketch_may15a.ino" 2






const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
Servo myservo; // membuat objek servo
int tempVal; // variabel untuk menyimpan nilai suhu
int servoPos = 0; // posisi awal servo
int ledYellowState = 0x0; // status awal LED kuning (mati)
int ledRedState = 0x0; // status awal LED merah (mati)

void setup() {
  myservo.attach(7 /* pin servo terhubung ke pin 7 pada Arduino*/); // menghubungkan servo ke pin 7
  pinMode(2 /* pin LED kuning terhubung ke pin 2 pada Arduino*/, 0x1); // mengatur pin LED kuning sebagai output
  pinMode(4 /* pin LED merah terhubung ke pin 4 pada Arduino*/, 0x1); // mengatur pin LED merah sebagai output
  pinMode(13, 0x1);
  lcd.begin(16, 2);
  Serial.begin(9600); // mengaktifkan komunikasi serial

}

void loop() {
  tempVal = analogRead(A0 /* pin sensor temperatur terhubung ke pin A0 pada Arduino*/); // membaca nilai suhu dari sensor temperatur
  float temperature = convertToCelcius(tempVal); // mengonversi nilai analog menjadi suhu dalam derajat Celcius
  lcd.setCursor(0,0);
  lcd.print("Suhu Saat Ini:    ");
  lcd.setCursor(0,1);
  lcd.print(String(temperature) + "C                ");

  controlServo(temperature); // mengontrol servo sesuai dengan suhu
  controlLED(temperature); // mengontrol LED sesuai dengan suhu
  digitalWrite(4 /* pin LED merah terhubung ke pin 4 pada Arduino*/,ledRedState);
  digitalWrite(2 /* pin LED kuning terhubung ke pin 2 pada Arduino*/,ledYellowState);
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
    ledYellowState = 0x0; // mematikan LED kuning
    ledRedState = 0x1;
  } else if (temperature >= 25 && temperature <= 30) {
    ledYellowState = 0x1; // mematikan LED kuning
    ledRedState = 0x0;
  } else {
    ledYellowState = 0x0; // mematikan LED kuning
    ledRedState = 0x0;
  }
}
