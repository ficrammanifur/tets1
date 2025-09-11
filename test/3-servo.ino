#include <Servo.h>

// Daftar pin servo
const int servoPins[] = {9, 10, 11}; // 0=Depan, 1=BelakangKiri, 2=BelakangKanan
Servo servos[3]; // array servo

void setup() {
  Serial.begin(9600);
  Serial.println("=== TEST SERVO 3 PIN ===");

  // Attach semua servo
  for (int i = 0; i < 3; i++) {
    servos[i].attach(servoPins[i]);
    Serial.print("Servo ");
    Serial.print(i);
    Serial.print(" terhubung ke pin ");
    Serial.println(servoPins[i]);
  }
}

void loop() {
  // Test servo satu per satu
  for (int i = 0; i < 3; i++) {
    Serial.print(">> Servo ");
    Serial.print(i);
    Serial.println(" ke 0 derajat");
    servos[i].write(0);
    delay(1000);

    Serial.print(">> Servo ");
    Serial.print(i);
    Serial.println(" ke 90 derajat");
    servos[i].write(90);
    delay(1000);

    Serial.print(">> Servo ");
    Serial.print(i);
    Serial.println(" ke 180 derajat");
    servos[i].write(180);
    delay(1000);

    Serial.print(">> Servo ");
    Serial.print(i);
    Serial.println(" kembali ke 90 derajat");
    servos[i].write(90);
    delay(1000);

    Serial.println("-------------------");
  }
}
