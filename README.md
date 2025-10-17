
# IoT-Based Environmental Monitoring


## **Abstract**

This project aims to manage the environment of a room using the dust sensor GP2Y1014AU to monitor particulate matter, the DHT11 sensor to measure temperature and humidity, and the MQ135 sensor to assess air quality. When the temperature exceeds a predefined threshold, the system automatically turns on the fan to reduce the temperature in the room.

---

## **I. INTRODUCTION**

This project is part of the IoT102 – Internet of Things course at FPT University, which introduces students to the fundamental concepts and applications of IoT through hands-on exercises using hardware kits. The course focuses on understanding how IoT devices interact, collect data, and perform automation to solve real-world problems.

Air quality is now a major concern in urban areas. High temperature, humidity, dust, and harmful gases can negatively affect people's health. In modern life, the Internet of Things (IoT) plays a vital role in monitoring and improving living conditions by connecting devices and enabling real-time data collection and automated responses.

This project presents a simple and low-cost IoT-based system to measure air quality in a room. When the air becomes too hot, the system automatically turns on a fan to improve the environment, providing a smarter and healthier living space.

---

## **II. MAIN PROPOSAL**

### **A. System models and block diagram**

The system consists of hardware components and software programs. Sensors measure temperature, dust, and gas concentration. Arduino Uno and NodeMCU ESP8266 are the main IoT platforms. The NodeMCU sends data to the Blynk IoT cloud via Wi-Fi. Arduino communicates wirelessly via LoRa, controlling sensors and activating a fan through an L298N driver when temperature thresholds are exceeded.

![System Block Diagram]
![494822712_1045809337461490_2889074490691037943_n](https://hackmd.io/_uploads/HytFy91Axl.png)


**Figure 1:** System Block Diagram

---

### **B. Components and Peripheral Devices**

| No | Name | Amount |
|----|------|---------|
| 1 | Gas Sensor (MQ135) | 1 |
| 2 | Humidity Sensor (DHT11) | 1 |
| 3 | Dust Sensor (GP2Y1014AU0F) | 1 |
| 4 | Microcontroller (ESP8266) | 1 |
| 5 | Wireless Module (LoRa) | 2 |
| 6 | Arduino Uno 3 | 1 |
| 7 | 16x2 LCD | 1 |
| 8 | I2C Controller | 1 |
| 9 | Micro USB cable (ESP8266 port) | 1 |
| 10 | Jumper Wires (JW) | Multiple |
| 11 | Resistors (R) | Multiple |
| 12 | Breadboard (BB) | 1 |
| 13 | L298N DC Motor Driver Circuit | 1 |
| 14 | 9V Battery | 1 |
| 15 | F505 High-Speed Motor 3–9VDC | 1 |

---

### **C. Software Programming**

Arduino Uno and NodeMCU ESP8266-12E make decisions based on sensor input. The air quality, dust, and temperature sensors connect to the Arduino’s analog and digital pins; the NodeMCU controls the LCD and sends data to the cloud.

![Circuit Schematic (Room)]
![490993091_532360376614554_4223646647095521737_n](https://hackmd.io/_uploads/BJjT1qkRll.png)

**Figure 2:** Circuit schematic (room setup)

![8f7064e7-040b-4ac8-9357-38a5e17c96e2](https://hackmd.io/_uploads/rJmglcJ0le.jpg)

**Figure 3:** Circuit schematic (internet-access area)

#### **Arduino Uno Connections**

| Arduino Uno | MQ135 | DHT11 | GP2Y1010AU0F | LoRa | L298N |
|--------------|--------|-------|---------------|-------|--------|
| GND | GND | GND | GND, LED-GND | M0, M1, GND | GND |
| V | VCC | VCC | VCC | | |
| A0 | A0 | | | | |
| A5 | | | V0 | | |
| D2 | | | LED | | |
| D5 | | Data | | | |
| D10 | | | | TXD | |
| D11 | | | | RXD | |
| D12 | | | | | INPUT3 |
| D13 | | | | | INPUT4 |
| 3.3V | | | | VCC | |

#### **ESP8266 Connections**

| ESP8266 | LoRa | LCD (I2C) |
|----------|------|------------|
| D1 | RXD | |
| D2 | TXD | |
| D4 | | SDA |
| D7 | | SCL |
| 3V | VCC | |
| VU | | VCC |
| GND | M0, M1, GND | GND |

#### **L298N Motor Driver**

| L298N | 9V Battery | F505 Motor |
|--------|-------------|-------------|
| GND | Cathode | |
| +12V | Anode | |
| OUTPUT3 | | Cathode |
| OUTPUT4 | | Anode |

---

### **D. Programming Flowchart**

Both Arduino Uno and NodeMCU are programmed via Arduino IDE. The following flowchart describes the program logic.

![494358388_2284065918656072_727888823742888322_n](https://hackmd.io/_uploads/r1t7g5JCxx.png)

**Figure 4:** Flowchart of the system

---





## **III. CONCLUSION**

Our IoT-based environmental monitoring system helps users maintain healthy indoor air quality. It automatically triggers ventilation when conditions exceed safety thresholds, transmits data via LoRa, and allows remote monitoring on the Blynk platform.

Challenges included maintaining stable communication, managing power, and optimizing LoRa performance. After troubleshooting, we achieved reliable system performance.

Future improvements include adding more sensors (e.g., gas types), automation of ventilation and fire suppression, and smarter indoor control.

**Demo Link:** [https://drive.google.com/file/d/1jOQKqcsD8zQsP5NPcMECNk_r_0lGb3Oo/view?usp=drive_link](https://drive.google.com/file/d/1jOQKqcsD8zQsP5NPcMECNk_r_0lGb3Oo/view?usp=drive_link)

---




