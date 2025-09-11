#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <Servo.h>

// === LCD I2C ===
LiquidCrystal_I2C lcd(0x27, 16, 2);

// === Servo ===
Servo servoDepan, servoBelakangKiri, servoBelakangKanan;
const int servoPins[] = {9, 10, 11}; // Depan, BelakangKiri, BelakangKanan

// === Ultrasonik ===
const int trigPin = 4;
const int echoPin = 8;
long duration;
int distance;

// === Button & LED ===
const int buttonManualPin = 3;
const int buttonModePin = 5;
const int ledRed = 7;
const int ledGreen = 6;

// === Threshold Jarak ===
const int thresholdDown = 28; // Gear turun jika < 28 cm
const int thresholdUp = 32;   // Gear naik jika > 32 cm

// === Variabel Status ===
bool gearDown = false;     // false = naik, true = turun
bool manualMode = false;   // false = AUTO, true = MANUAL
unsigned long lastDebounceTime = 0, lastManualPressTime = 0;
const unsigned long debounceDelay = 300;

void setup() {
  // Pin Setup
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(buttonManualPin, INPUT_PULLUP);
  pinMode(buttonModePin, INPUT_PULLUP);
  pinMode(ledRed, OUTPUT);
  pinMode(ledGreen, OUTPUT);

  // Servo Attach
  servoDepan.attach(servoPins[0]);
  servoBelakangKiri.attach(servoPins[1]);
  servoBelakangKanan.attach(servoPins[2]);

  // LCD
  lcd.init();
  lcd.backlight();
  lcd.print("Landing Gear:");

  // Serial Debug
  Serial.begin(9600);
  Serial.println("=== System Start ===");

  // LED Blink Start
  for (int i = 0; i < 3; i++) {
    digitalWrite(ledRed, HIGH);
    digitalWrite(ledGreen, HIGH);
    delay(200);
    digitalWrite(ledRed, LOW);
    digitalWrite(ledGreen, LOW);
    delay(200);
  }
}

void loop() {
  // Cek tombol mode (AUTO <-> MANUAL)
  if (digitalRead(buttonModePin) == LOW && (millis() - lastDebounceTime > debounceDelay)) {
    manualMode = !manualMode;
    lastDebounceTime = millis();
    Serial.print("Mode changed: ");
    Serial.println(manualMode ? "MANUAL" : "AUTO");
  }

  // LED indikator status gear
  digitalWrite(ledRed, gearDown);
  digitalWrite(ledGreen, !gearDown);

  // LCD baris 0: mode
  lcd.setCursor(0, 0);
  lcd.print(manualMode ? "Mode: MANUAL   " : "Mode: AUTO     ");

  // Eksekusi sesuai mode
  manualMode ? kontrolManual() : kontrolOtomatis();
}

// === Fungsi AUTO ===
void kontrolOtomatis() {
  bacaJarak();
  Serial.print("AUTO: Distance = ");
  Serial.print(distance);
  Serial.println(" cm");

  if (distance < thresholdDown && !gearDown) {
    gearDown = true;
    gerakkanServo(90, 180);
    flashLed(ledRed);
    Serial.println("AUTO: Gear TURUN");
  } else if (distance > thresholdUp && gearDown) {
    gearDown = false;
    gerakkanServo(180, 90);
    flashLed(ledGreen);
    Serial.println("AUTO: Gear NAIK");
  }

  // LCD baris 1
  lcd.setCursor(0, 1);
  lcd.print(gearDown ? "TURUN " : "NAIK  ");
  lcd.setCursor(10, 1);
  lcd.print(distance);
  lcd.print("cm ");
}

// === Fungsi MANUAL ===
void kontrolManual() {
  if (digitalRead(buttonManualPin) == LOW && (millis() - lastManualPressTime > debounceDelay)) {
    gearDown = !gearDown;
    gerakkanServo(gearDown ? 90 : 180, gearDown ? 180 : 90);
    flashLed(gearDown ? ledRed : ledGreen);
    lastManualPressTime = millis();
    Serial.print("MANUAL: Gear ");
    Serial.println(gearDown ? "TURUN" : "NAIK");
  }

  // LCD baris 1
  lcd.setCursor(0, 1);
  lcd.print(gearDown ? "TURUN " : "NAIK  ");
  lcd.setCursor(10, 1);
  lcd.print("      ");
}

// === Fungsi Servo ===
void gerakkanServo(int dari, int ke) {
  int step = (dari < ke) ? 1 : -1;
  for (int angle = dari; angle != ke + step; angle += step) {
    servoDepan.write(angle);
    servoBelakangKiri.write(angle);
    servoBelakangKanan.write(angle);
    delay(5);
  }
}

// === Fungsi LED Flash ===
void flashLed(int ledPin) {
  digitalWrite(ledRed, LOW);
  digitalWrite(ledGreen, LOW);
  delay(50);
  digitalWrite(ledPin, HIGH);
  delay(300);
  digitalWrite(ledPin, LOW);
  delay(50);
  digitalWrite(ledRed, gearDown);
  digitalWrite(ledGreen, !gearDown);
}

// === Fungsi Baca Ultrasonik ===
void bacaJarak() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH, 20000); // timeout 20ms biar gak ngehang
  if (duration == 0) {
    distance = 999; // kalau tidak terbaca
  } else {
    distance = duration * 0.034 / 2;
  }
}
