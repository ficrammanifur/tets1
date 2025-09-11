#include <Servo.h>

// Daftar pin servo
const int servoPins[] = {9, 10, 11}; // Depan, BelakangKiri, BelakangKanan
Servo servos[3]; // array servo

void setup() {
  // Attach semua servo
  for (int i = 0; i < 3; i++) {
    servos[i].attach(servoPins[i]);
  }
}

void loop() {
  // Gerak semua servo ke 0 derajat
  for (int i = 0; i < 3; i++) {
    servos[i].write(0);
  }
  delay(1000);

  // Gerak semua servo ke 90 derajat
  for (int i = 0; i < 3; i++) {
    servos[i].write(90);
  }
  delay(1000);

  // Gerak semua servo ke 180 derajat
  for (int i = 0; i < 3; i++) {
    servos[i].write(180);
  }
  delay(1000);
}
