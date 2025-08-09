#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <Servo.h>

// Inisialisasi LCD I2C
LiquidCrystal_I2C lcd(0x27, 16, 2);

// Inisialisasi servo
Servo servoDepan;
Servo servoBelakangKiri;
Servo servoBelakangKanan;

// Pin sensor ultrasonik
const int trigPin = 12;
const int echoPin = 13;

// Pin servo
const int servoDepanPin = 10;
const int servoBelakangKiriPin = 9;
const int servoBelakangKananPin = 11;

// Variabel untuk jarak
long duration;
int distance;

// Status gear
bool gearDown = false;

// Histeresis batas jarak
const int thresholdDown = 28; // Gear turun jika < 28 cm
const int thresholdUp = 32;   // Gear naik jika > 32 cm

void setup() {
  // Inisialisasi pin sensor
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  // Attach servo ke pin
  servoDepan.attach(servoDepanPin);
  servoBelakangKiri.attach(servoBelakangKiriPin);
  servoBelakangKanan.attach(servoBelakangKananPin);

  // Inisialisasi LCD
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("Landing Gear:");
}

void loop() {
  // Kirim pulsa trigger ke sensor
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // Baca durasi echo
  duration = pulseIn(echoPin, HIGH);
  distance = duration * 0.034 / 2;

  // Logika histeresis
  if (distance < thresholdDown && !gearDown) {
    gearDown = true;
    gerakkanServo(90, 180); // Turunkan gear pelan
  } else if (distance > thresholdUp && gearDown) {
    gearDown = false;
    gerakkanServo(180, 90); // Naikkan gear pelan
  }

  // Tampilkan status & jarak di LCD
  lcd.setCursor(0, 1);
  lcd.print(gearDown ? "TURUN " : "NAIK  ");

  lcd.setCursor(10, 1);
  lcd.print(distance);
  lcd.print("cm ");

  delay(200);
}

// Fungsi untuk gerakkan semua servo perlahan
void gerakkanServo(int dari, int ke) {
  int step = (dari < ke) ? 1 : -1;
  for (int angle = dari; angle != ke + step; angle += step) {
    servoDepan.write(angle);
    servoBelakangKiri.write(angle);
    servoBelakangKanan.write(angle);
    delay(5);
  }
}
