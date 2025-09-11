#include <Wire.h>

void setup() {
  Wire.begin();
  Serial.begin(9600);
  while (!Serial); // tunggu serial siap (untuk board baru)
  Serial.println("\nI2C Scanner siap...");
}

void loop() {
  byte error, address;
  int nDevices;

  Serial.println("Scanning...");

  nDevices = 0;
  for (address = 1; address < 127; address++) {
    Wire.beginTransmission(address);
    error = Wire.endTransmission();

    if (error == 0) {
      Serial.print("I2C device ditemukan pada alamat 0x");
      if (address < 16)
        Serial.print("0");
      Serial.print(address, HEX);
      Serial.println();

      nDevices++;
    }
    else if (error == 4) {
      Serial.print("Error pada alamat 0x");
      if (address < 16)
        Serial.print("0");
      Serial.println(address, HEX);
    }
  }

  if (nDevices == 0)
    Serial.println("Tidak ada device I2C terdeteksi\n");
  else
    Serial.println("Selesai scan\n");

  delay(2000); // tunggu 2 detik sebelum scan lagi
}
