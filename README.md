# 🔐 STM32 FreeRTOS Password Authentication System
---

## 📌 Overview
This project implements a **Password Authentication System** using **FreeRTOS** on an **STM32F407 Discovery Board**. It uses a **4x4 Keypad**, **I2C LCD**, and a **Servo Motor** for lock/unlock operations. The system supports two modes:  
- **NORMAL** → Password validation  
- **UPDATE** → Change password stored in Flash  

---

## ✅ Features
- **FreeRTOS multitasking** with dedicated tasks
- **Keypad input with debounce**
- **LCD feedback using I2C**
- **Servo lock/unlock mechanism**
- **Flash memory integration for password persistence**
- Toggle modes using `#` key

---

## 🛠 Hardware Requirements
- STM32F407 Discovery (or compatible STM32 board)
- 4x4 Matrix Keypad
- 16x2 I2C LCD
- SG90 Servo Motor
- Breadboard, jumper wires, 5V power supply

---
## 🔄 How It Works
1. At startup, password is **loaded from Flash**.
2. User enters password via **4x4 keypad**.
3. `#` key toggles between **NORMAL** and **UPDATE** modes.
4. **NORMAL Mode** → Validates password and locks/unlocks servo.
5. **UPDATE Mode** → Accepts new password and stores it in Flash.
6. LCD provides real-time feedback.

---

## 🔧 Tools & Software
- **STM32CubeIDE**
- **FreeRTOS**
- **STM32 HAL Drivers**
- **HD44780 I2C LCD Library**

---

## 🚀 Future Improvements
- Add IoT control (Wi-Fi/Bluetooth)
- Password encryption
- Implement binary semaphore for shared resources in complex systems

---
### ✨ Author
**Vasanth Nayak**  
Embedded Systems Developer | RTOS Enthusiast
