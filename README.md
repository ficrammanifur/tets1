<h1 align="center">✈️ SISTEM LANDING GEAR OTOMATIS</h1>
<p align="center"> <img src="/placeholder.svg?height=400&width=700" alt="Automatic Landing Gear Prototype" width="700"/></p>
<p align="center"> <em>Sistem prototipe landing gear pesawat yang otomatis naik/turun berdasarkan deteksi jarak menggunakan sensor ultrasonik dan Arduino.</em></p>
<p align="center">
  <img src="https://img.shields.io/badge/last%20commit-today-brightgreen" />
  <img src="https://img.shields.io/badge/language-C%2B%2B-blue" />
  <img src="https://img.shields.io/badge/platform-Arduino%20%7C%20ESP32-informational" />
  <img src="https://img.shields.io/badge/sensor-Ultrasonic-orange" />
  <img src="https://img.shields.io/badge/actuator-Servo-red" />
  <a href="https://github.com/ficrammanifur/gesture-clone-robot/blob/main/LICENSE">
    <img src="https://img.shields.io/badge/license-MIT-blue" alt="License: MIT" />
  </a>
</p>

---

# Arduino™ UNO R3 Board

> **Note:** Arduino™ is a trademark of Arduino AG.  
> This project is not affiliated with or endorsed by Arduino.  
> All trademarks and copyrights belong to their respective owners.

---
## 📑 Table of Contents
- [✨ Overview](#-overview)
- [🚀 Fitur](#-fitur)
- [🏗️ Arsitektur Sistem](#️-arsitektur-sistem)
- [🛠 Komponen](#-komponen)
- [📁 Struktur File](#-struktur-file)
- [⚙️ Instalasi](#️-instalasi)
- [🚀 Cara Menjalankan](#-cara-menjalankan)
- [🐞 Troubleshooting](#-troubleshooting)
- [🤝 Kontribusi](#-kontribusi)
- [👨‍💻 Pengembang](#-pengembang)
- [📄 Lisensi](#-lisensi)

---

## ✨ Overview
**Sistem Landing Gear Otomatis** adalah prototipe yang mensimulasikan mekanisme landing gear pada pesawat terbang. Sistem ini menggunakan sensor ultrasonik untuk mendeteksi jarak ke permukaan (misalnya, landasan pacu) dan secara otomatis mengontrol servo motor untuk menaikkan atau menurunkan roda pendaratan. Status posisi roda akan ditampilkan pada layar LCD I2C.

### 🎯 Tujuan Proyek
- **Otomatisasi** - Mengembangkan sistem yang dapat beroperasi secara mandiri.
- **Edukasi Elektronika** - Platform pembelajaran dasar mikrokontroler, sensor, dan aktuator.
- **Simulasi** - Memberikan pemahaman dasar tentang mekanisme landing gear pesawat.
- **Proyek Hobi** - Proyek yang menarik untuk penggemar elektronika dan robotika.

---

## Arduino UNO R3 Pinout
<p align="center">
  <img src="Arduino-UNO-R3.png" alt="Arduino Uno R3 pinout" width="700"/>
</p>

## Arduino UNO R3 Schematics
<p align="center">
  <img src="schematics.png" alt="Arduino Schematics" width="700"/>
</p>

## Arduino UNO R3 Datasheet
[📄 Download Datasheet](https://docs.arduino.cc/resources/datasheets/A000066-datasheet.pdf)

## Official Documentation
🔗 [Arduino UNO Rev3 - Official Page](https://docs.arduino.cc/hardware/uno-rev3/)

---

## 🚀 Fitur
- ✅ **Deteksi Jarak Otomatis** Menggunakan sensor ultrasonik HC-SR04 untuk mengukur jarak secara real-time.
- ✅ **Kontrol Servo Motor** Menggerakkan 3 servo motor untuk meniru gerakan roda pendaratan (depan, belakang kiri, belakang kanan).
- ✅ **Indikator Status LCD** Menampilkan status "TURUN" atau "NAIK" pada layar LCD 16x2 I2C.
- ✅ **Responsif** Mengubah posisi landing gear secara cepat berdasarkan perubahan jarak.
- ✅ **Open Source** Sistem berbasis open source, ideal untuk pembelajaran dan modifikasi.

---

## 🏗️ Arsitektur Sistem
### 🔗 Diagram Blok Hardware/Software
```text
┌──────────────────┐       ┌────────────────────┐       ┌────────────────────────┐
│ Sensor Ultrasonik│──────►│      Arduino       │──────►│      Servo Motor       │
│     (HC-SR04)    │       │ (Mikrokontroler)   │       │  Depan, Blkg Kiri,     │
└──────────────────┘       │                    │       │   Blkg Kanan (x3)      │
                           │                    │       └────────────────────────┘
                           │                    │
                           │                    │       ┌────────────────────────┐
                           │                    ├──────►│      LCD I2C 16x2      │
                           │                    │       │ (Tampilan Mode, Gear,  │
                           │                    │       │  dan Jarak Sensor)     │
                           │                    │       └────────────────────────┘
                           │                    │
                           │                    │       ┌────────────────────────┐
                           │                    ├──────►│  LED Merah & Hijau     │
                           │                    │       │ (Indikator Gear Naik/  │
                           │                    │       │  Turun)                │
                           │                    │       └────────────────────────┘
                           │                    │
                           │                    │       ┌────────────────────────┐
                           │                    ├──────►│ Tombol Mode & Manual   │
                           │                    │       │ (Ganti Mode & Kontrol) │
                           └────────────────────┘       └────────────────────────┘
                                                        
```

### 📊 Flowchart Sistem
```mermaid
graph TD
    A([Mulai atau Power ON]) --> B[Inisialisasi LCD, Servo, LED, Sensor, dan Tombol]
    B --> C{Tombol Mode ditekan?}
    C -- Ya --> D[Ubah mode AUTO ke MANUAL atau sebaliknya]
    C -- Tidak --> E[Gunakan mode terakhir]

    E --> F{Apakah Mode MANUAL?}
    F -- Ya --> G[Tombol Manual ditekan?]
    G -- Ya --> H[Ubah status Gear Naik atau Turun]
    H --> I[Gerakkan tiga Servo secara bersamaan]
    I --> J[Perbarui LED indikator dan LCD]
    G -- Tidak --> J

    F -- Tidak --> K[Baca jarak dari sensor ultrasonik]
    K --> L[Filter pembacaan stabil minimal tiga kali]
    L --> M{Jarak kurang dari 28 cm dan Gear Naik?}
    M -- Ya --> N[Turunkan Gear ke posisi 180 derajat]
    M -- Tidak --> O{Jarak lebih dari 32 cm dan Gear Turun?}
    O -- Ya --> P[Naikkan Gear ke posisi 90 derajat]
    N --> Q[LED Merah berkedip dan LCD tampilkan TURUN]
    P --> R[LED Hijau berkedip dan LCD tampilkan NAIK]
    O -- Tidak --> S[Tidak ada aksi karena Cooldown aktif]

    Q --> T[Reset stabilitas dan tunggu sebentar]
    R --> T
    S --> T
    T --> C

    style A fill:#e1f5fe,stroke:#90caf9
    style B fill:#e1f5fe,stroke:#90caf9
    style C fill:#f1f8e9,stroke:#aed581
    style D fill:#f1f8e9,stroke:#aed581
    style F fill:#fff9c4,stroke:#fff176
    style G fill:#fff9c4,stroke:#fff176
    style H fill:#ffe0b2,stroke:#ffb74d
    style I fill:#ffe0b2,stroke:#ffb74d
    style J fill:#bbdefb,stroke:#64b5f6
    style K fill:#e1f5fe,stroke:#90caf9
    style L fill:#fff3e0,stroke:#ffcc80
    style N fill:#ffcdd2,stroke:#ef9a9a
    style P fill:#c8e6c9,stroke:#81c784
    style Q fill:#ffcdd2,stroke:#ef9a9a
    style R fill:#c8e6c9,stroke:#81c784
    style S fill:#eeeeee,stroke:#bdbdbd
```

---

## 🛠 Komponen
### 📦 Perangkat Keras
| Komponen | Spesifikasi | Quantity | Pin Connection | Fungsi |
|----------|-------------|----------|----------------|---------|
| **Arduino/ESP32** | Arduino Uno R3 | 1 | - | Mikrokontroler utama |
| **Servo Motor** | SG90/MG90S | 3 | 10, 9, 11 | Aktuator jari |
| **Sensor Ultrasonik** | HC-SR04 | 1 | Trig: 4, Echo: 8 | Deteksi jarak |
| **LCD I2C** | 16x2, Address 0x27 | 1 | SDA, SCL (A4, A5 pada Uno) | Menampilkan status |
| **Push Button (Mode)** | Tactile Switch | 1 | 5 | Mengubah mode antara AUTO ↔ MANUAL |
| **Push Button (Manual Control)** | Tactile Switch | 1 | 3 | Mengontrol gerakan gear secara manual |
| **LED Merah** | 5 mm | 1 | 7 | Indikator Gear TURUN (DOWN) |
| **LED Hijau** | 5 mm | 1 | 6 | Indikator Gear NAIK (UP) |
| **Power Supply** | MB102 Power Supply Module | 1 | Input: 12 V (dari 3×18650 seri) | Menyediakan tegangan 5 V stabil ke seluruh rangkaian |
| **Baterai Li-ion 18650** | 3.7 V, 2200–3000 mAh | 3 (seri) | - | Sumber daya utama (total ≈ 11.1–12.6 V) |
| **Jumper Wires** | Male-Male, Male-Female | ~10 | - | Koneksi |
| **Breadboard** | Opsional | 1 | - | Memudahkan wiring |

### 💻 Perangkat Lunak
| Software | Version | Fungsi |
|----------|---------|---------|
| **Arduino IDE** | 1.8+ atau 2.0+ | Lingkungan pemrograman |
| **Wire Library** | Built-in | Komunikasi I2C |
| **LiquidCrystal_I2C Library** | Latest | Kontrol LCD I2C |
| **Servo Library** | Built-in | Kontrol servo motor |

---

## 📁 Struktur File
```text
landing-gear-project/
├── 📄 README.md             # Dokumentasi proyek
└── 🤖 landing_gear_auto.ino # Kode utama Arduino
```

---

## ⚙️ Instalasi
### 1. 🔧 Clone Repository
```bash
git clone https://github.com/ficrammanifur/test1.git
cd test1
```

### 2. 💻 Setup Arduino IDE
1.  **Download Arduino IDE** dari [arduino.cc](https://www.arduino.cc/en/software).
2.  **Install Board Package**:
    *   Untuk Arduino Uno/Nano: Biasanya sudah terinstal.
    *   Untuk ESP32: Ikuti panduan instalasi board ESP32 di Arduino IDE (File > Preferences > Additional Boards Manager URLs).
3.  **Install Libraries**:
    *   Buka Arduino IDE.
    *   Pergi ke \`Sketch > Include Library > Manage Libraries...\`
    *   Cari dan instal:
        *   `LiquidCrystal I2C` oleh Frank de Brabander
        *   `Servo` (biasanya sudah terinstal)
        *   `Wire` (biasanya sudah terinstal)

### 3. 🔌 Hardware Assembly
#### Schematic
<p align="center">
  <img src="Schematic_Ficrammanifur.png" alt="Schematic" width="700"/>
</p>

#### Pin Connections
```text
Arduino UNO R3    │ Komponen             │ Keterangan
──────────────────┼──────────────────────┼──────────────────────────
│ D12 (GPIO 12)    │ Trig Ultrasonik      │ Output sinyal trigger         
│ D13 (GPIO 13)    │ Echo Ultrasonik      │ Input sinyal pantulan         
│ D10 (GPIO 10)    │ Servo Depan (Signal) │ Kontrol servo bagian depan    
│ D9  (GPIO 9)     │ Servo Belakang Kiri  │ Kontrol servo bagian kiri     
│ D11 (GPIO 11)    │ Servo Belakang Kanan │ Kontrol servo bagian kanan    
│ SDA (A4 pada Uno)│ LCD I2C (SDA)        │ Jalur data komunikasi I2C     
│ SCL (A5 pada Uno)│ LCD I2C (SCL)        │ Jalur clock komunikasi I2C    
│ 5V               │ VCC Ultrasonik, Servo│ Sumber daya 5V dari MB102     
│ GND              │ GND Ultrasonik, Servo│ Ground sistem                 
```
*Catatan: Pastikan semua komponen memiliki ground yang sama. Untuk servo, disarankan menggunakan catu daya eksternal jika menggunakan banyak servo atau servo besar untuk menghindari kerusakan pada mikrokontroler.*

---

## 🚀 Cara Menjalankan

### Arduino IDE Settings
<p align="center">
  <img src="Arduino_Settings.png" alt="Arduino IDE Settings" width="700"/>
</p>

1.  **Buka Kode**: Buka file \`landing_gear_auto.ino\` di Arduino IDE.
2.  **Pilih Board**: Pergi ke \`Tools > Board\` dan pilih board Arduino/ESP32 yang Anda gunakan.
3.  **Pilih Port**: Pergi ke \`Tools > Port\` dan pilih port serial yang terhubung dengan mikrokontroler Anda.
4.  **Upload Kode**: Klik tombol \`Upload\` (panah kanan) di Arduino IDE.
5.  **Monitor Serial (Opsional)**: Buka Serial Monitor (Baud Rate: 9600) untuk melihat output debug jika ada.
6.  **Uji Sistem**:
    *   Posisikan objek di depan sensor ultrasonik.
    *   Jika jarak kurang dari 30cm, servo akan bergerak ke posisi "TURUN" (180 derajat).
    *   Jika jarak 30cm atau lebih, servo akan bergerak ke posisi "NAIK" (90 derajat).
    *   Amati perubahan status pada layar LCD.

---

## 🐞 Troubleshooting
### ❌ Common Issues & Solutions
#### **1. LCD Tidak Menyala/Menampilkan Teks**
**Gejala:**
- Layar LCD kosong atau hanya kotak-kotak hitam.
- Tidak ada teks yang muncul.
**Solusi:**
- ✅ **Periksa Wiring I2C**: Pastikan pin SDA dan SCL terhubung dengan benar.
- ✅ **Periksa Alamat I2C**: Alamat default adalah \`0x27\`, tetapi beberapa modul menggunakan \`0x3F\`. Anda bisa menggunakan I2C Scanner sketch untuk menemukan alamat yang benar.
- ✅ **Sesuaikan Potensiometer**: Putar potensiometer kecil di bagian belakang modul LCD I2C untuk mengatur kontras.
- ✅ **Periksa Power**: Pastikan LCD mendapatkan daya 5V dan ground yang stabil.

#### **2. Servo Tidak Bergerak atau Bergerak Erratic**
**Gejala:**
- Servo tidak merespons.
- Gerakan servo tidak halus atau bergetar.
**Solusi:**
- ✅ **Periksa Wiring Servo**: Pastikan pin sinyal, VCC, dan GND terhubung dengan benar.
- ✅ **Catu Daya Eksternal**: Servo membutuhkan arus yang cukup. Jika menggunakan banyak servo atau servo besar, gunakan catu daya 5V eksternal terpisah untuk servo, bukan langsung dari Arduino. Pastikan GND Arduino dan GND catu daya servo terhubung.
- ✅ **Pin PWM**: Pastikan pin yang digunakan untuk servo adalah pin PWM (biasanya ditandai dengan \`~\` pada Arduino Uno).

#### **3. Sensor Ultrasonik Tidak Akurat/Tidak Membaca**
**Gejala:**
- Jarak yang ditampilkan tidak masuk akal.
- Sensor tidak mendeteksi objek.
**Solusi:**
- ✅ **Periksa Wiring Trig/Echo**: Pastikan pin Trig dan Echo terhubung ke pin yang benar pada mikrokontroler.
- ✅ **Periksa Power Sensor**: Pastikan sensor mendapatkan daya 5V dan ground yang stabil.
- ✅ **Lingkungan**: Hindari permukaan yang menyerap suara (kain, busa) atau terlalu reflektif (kaca).
- ✅ **Interferensi**: Jauhkan sensor dari sumber suara atau getaran lain.

#### **4. Kode Tidak Terupload**
**Gejala:**
- Error saat mengupload kode ke board.
- \`avrdude: stk500_getsync(): not in sync: resp=0x00\`
**Solusi:**
- ✅ **Pilih Port yang Benar**: Pastikan Anda memilih port serial yang benar di \`Tools > Port\`.
- ✅ **Pilih Board yang Benar**: Pastikan Anda memilih jenis board yang benar di \`Tools > Board\`.
- ✅ **Driver USB**: Pastikan driver USB untuk board Anda terinstal dengan benar.
- ✅ **Kabel USB**: Coba kabel USB lain.

---

## 🤝 Kontribusi
Kontribusi sangat diterima! Mari bersama-sama mengembangkan proyek ini.

### 📋 How to Contribute
1.  **🍴 Fork** repository ini
2.  **🌿 Create** feature branch (\`git checkout -b feature/new-feature\`)
3.  **💾 Commit** changes (\`git commit -m 'Add new feature'\`)
4.  **📤 Push** to branch (\`git push origin feature/new-feature\`)
5.  **🔄 Open** Pull Request

### 🎯 Areas for Contribution
- [ ] **Optimasi Kode** - Peningkatan efisiensi dan keandalan kode.
- [ ] **Integrasi Sensor Lain** - Tambahkan sensor jarak lain (misalnya, IR).
- [ ] **Kalibrasi Servo** - Implementasi kalibrasi servo otomatis.
- [ ] **Desain Mekanik** - Desain 3D untuk prototipe landing gear.
- [ ] **Dokumentasi** - Perbaikan dokumentasi dan penambahan tutorial.

### 🐛 Bug Reports
Gunakan GitHub Issues dengan informasi:
- Deskripsi bug yang jelas
- Steps to reproduce
- Expected vs actual behavior
- Environment (Board, Arduino IDE version, dll)
- Screenshots/video jika memungkinkan

---

## 👨‍💻 Pengembang
**Ficram Manifur**
- 🐙 GitHub: [@ficrammanifur](https://github.com/ficrammanifur)
- 🌐 Portfolio: [ficrammanifur.github.io](https://ficrammanifur.github.io/ficram-portfolio)
- 📧 Email: ficramm@gmail.com

### 🙏 Acknowledgments
- **Arduino Community** - Untuk platform dan library yang luar biasa.
- **Library Developers** - Untuk `LiquidCrystal_I2C` dan `Servo` libraries.

---

## 📄 Lisensi
Proyek ini dilisensikan di bawah **MIT License** - lihat file [LICENSE](LICENSE) untuk detail lengkap.
```text
MIT License

Copyright (c) 2025 ficrammanifur

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
```

---
<div align="center">
  
**✈️ Otomatisasi Pendaratan dengan Presisi**

**⚡ Dibangun dengan Arduino, Ultrasonik & Servo**

**⭐ Star this repo if you like it!**

<p><a href="#top">⬆ Back on Top</a></p>
</div>
