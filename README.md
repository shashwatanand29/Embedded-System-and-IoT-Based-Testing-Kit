# 🔧 Embedded System and IoT-Based Testing Kit

This repository contains the design and firmware for an **Embedded System and IoT-Based Testing Kit**. The kit is built to help users test various components and sensors used in embedded and IoT systems. It integrates hardware modules like sensors, displays, buzzers, and push buttons with cloud-based data monitoring using **ThingSpeak**.


![Versatile Component Testing Kit](./Versatile%20Component%20Testing%20Kit.jpg)

<p align="center">
  <img src="./circuit%20diagram.jpg" alt="Circuit Diagram" width="600"/>
</p>





---

## 🎯 Project Objectives

- Test and simulate real-world embedded & IoT systems
- Monitor live sensor data via ThingSpeak cloud platform
- Enable hands-on learning and development for students and hobbyists

---

## 🔋 Features & Components

| Component               | Function                                         |
|-------------------------|--------------------------------------------------|
| DHT11 Sensor            | Measures temperature and humidity                |
| OLED Display (I2C)      | Displays sensor readings/status messages         |
| 7-Segment Display       | Shows numeric values (e.g., counter, temp)       |
| LEDs (Red/Green)        | Indicators for output testing                    |
| Push Buttons (x2)       | Manual input controls                            |
| IR Sensor Module        | Detects motion/obstacles                         |
| Buzzer                  | Produces alerts/sounds                           |
| Potentiometer           | Simulates analog values                          |
| Female Headers          | For plugging in Arduino, ATmega, or ESP modules |

---

## 🌐 ThingSpeak IoT Integration

The system uploads temperature and humidity data to [ThingSpeak](https://thingspeak.com/), where it is visualized in real time.

### 🔗 ThingSpeak Setup:

- **Field 1**: Temperature (°C)  
- **Field 2**: Humidity (%)

**Data Format (GET Request):**


Firmware uses HTTP requests to transmit data over Wi-Fi using **ESP8266/ESP32** or similar modules.

---

## 🧠 Workflow

1. Sensors collect data →  
2. Microcontroller reads sensor values →  
3. Data displayed on OLED/7-segment →  
4. Data sent to ThingSpeak using Wi-Fi →  
5. Monitor live on ThingSpeak dashboard.

---

## ▶️ How to Run the Project

1. Clone this repository or download it as a ZIP.
2. Open the `.ino` file (or relevant firmware) in the Arduino IDE or Microchip Studio.
3. Update the following in code:
   - Wi-Fi SSID & Password
   - ThingSpeak API Key
4. Upload the code to your ESP8266/ESP32 or ATmega microcontroller.
5. Power the board and observe:
   - Local readings on OLED/7-segment display
   - Live data updates on ThingSpeak

---
## 🎥 Demo Videos 

📽️ [Watch Videos on Google Drive](https://drive.google.com/drive/folders/16-zL126pYZx2GTLVYJRyYUxE0Hsn8juX?usp=drive_link)

---
  
## 📁 Files Included

Individual Codes are uploaded to the root  




