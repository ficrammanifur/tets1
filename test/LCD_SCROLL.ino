#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2); // alamat hasil scan + ukuran LCD

void setup() {
  lcd.begin();       // inisialisasi LCD
  lcd.backlight();   // nyalakan lampu latar
  lcd.setCursor(0, 0);
  lcd.print("Halo Ficram!");
  lcd.setCursor(0, 1);
  lcd.print("LCD Siap :)");
}

void loop() {
  lcd.scrollDisplayLeft();
  delay(400);
}
