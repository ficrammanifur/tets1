#include <Wire.h>
#include <LiquidCrystal_I2C.h>
//lihat hasil scan tadi
//Scanning...
//21:33:33.026 -> I2C device ditemukan pada alamat 0x27
//21:33:33.059 -> Selesai scan
LiquidCrystal_I2C lcd(0x27, 16, 2); //taro alamatnye disini 0x27

void setup() {
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("HELLOW WORLD!"); //baris atas
  lcd.setCursor(0, 1);
  lcd.print("LCD I2C OK"); //baris bawah
}

void loop() {
  // LCD hanya tampil sekali
}
