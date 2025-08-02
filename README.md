# 🔥 ESP32 Advanced Soft Access Point (SoftAP) with Captive Portal

This project turns your ESP32 into a **Wi-Fi Access Point** with an integrated **Captive Portal**, a DNS redirect server, and a basic web interface. It allows other devices to connect directly to the ESP32 without any external Wi-Fi router.

---

## ✨ Features

- 📡 ESP32 as a Wi-Fi Access Point (SoftAP)
- 🌐 Captive Portal with DNS redirection
- 🌍 Custom local IP configuration
- 📲 Device MAC address logging (connected stations)
- 🧑‍💻 Embedded HTML web page served from ESP32
- 🔒 WPA2 password-protected network

---

## 📦 Dependencies

Make sure you have the following installed in **Arduino IDE**:

- **ESP32 Board Package**
- `WiFi.h` (included)
- `WebServer.h` (included)
- `DNSServer.h` (included)

---

## 🛠️ Setup Instructions

### 1. 🔧 Configure Arduino IDE
- Install the ESP32 board via Board Manager
- Select your ESP32 board model
- Choose correct COM port

### 2. 🚀 Upload the Code
- Open the provided `.ino` file
- Connect your ESP32 to your PC
- Upload the code via Arduino IDE

---

## 📲 Connect to ESP32

1. On any device, search for the Wi-Fi network:
