# Gas Leak Alarm System using LPC1768

A real-time embedded gas detection and alarm system designed for early detection of flammable gas leaks using the MQ-2 sensor and NXP LPC1768 microcontroller. The system provides visual, auditory, and emergency control responses, making it suitable for both home and industrial environments.

---

## 🔧 Features

- 🧪 **Real-time gas detection** using MQ-2 sensor
- ⚡ **Automatic power cutoff** via relay module during leak conditions
- 📟 **LCD display** for live gas level readings and system status
- 🔊 **Auditory buzzer alert** and flashing LED alarm
- ⚙️ **Interrupt-driven state switching** (SAFE ↔ LEAK)
- 🔄 **Automatic recovery** after safe conditions are restored

---

## 🛠 Technology Stack

- **Microcontroller:** NXP LPC1768 (ARM Cortex-M3)
- **Sensor:** MQ-2 (detects LPG, propane, methane, etc.)
- **Language:** Embedded C
- **Display:** 16x2 LCD
- **Alert Modules:** Buzzer, Relay, LED indicators

---

## ⚙️ System Workflow

1. **Monitoring:**  
   ADC continuously polls MQ-2 analog output to read gas concentration.

2. **Leak Detected:**  
   External interrupt (EINT1) is triggered → System state switches to `LEAK`
   - Relay turns OFF (cuts main power)
   - Buzzer and LEDs are activated
   - LCD shows “LEAK” and ADC reading

3. **Safe Condition Restored:**  
   External interrupt (EINT2) triggered → State returns to `SAFE`
   - Relay turns ON (restores power)
   - Alerts are deactivated
   - LCD shows “SAFE” and ADC reading

---

## 📦 Components Used

| Component       | Description                                      |
|----------------|--------------------------------------------------|
| LPC1768         | ARM Cortex-M3 based microcontroller              |
| MQ-2 Sensor     | Flammable gas sensor for LPG, propane, methane  |
| 16x2 LCD        | Displays system status and gas levels           |
| Relay Module    | Disconnects power supply in emergency           |
| Buzzer & LEDs   | Provide immediate audio-visual alerts           |

---

## 🚀 Getting Started

1. **Hardware Setup:**
   - Connect MQ-2 analog output to ADC channel P0.23
   - Use digital output for interrupts (P2.11 and P2.12)
   - Connect buzzer (P2.13), relay (P2.10), and LEDs (P0.4–P0.11)
   - Connect LCD using P0.15–P0.20

2. **Software Setup:**
   - Flash the Embedded C code to LPC1768 using Keil or equivalent IDE
   - Power the board and simulate gas presence (e.g., lighter test)

3. **Run:**
   - Monitor LCD and observe buzzer/LED behavior during leak and safe conditions

---

## 💡 Future Improvements

- Integrate Bluetooth/Wi-Fi module for remote alerting/logging
- Add adjustable alarm thresholds via external input
- Log data to SD card or cloud for historical analysis
- Web/mobile dashboard for industrial SCADA applications

---

## 🎯 SDGs Addressed

- **SDG 3:** Good Health and Well-being  
- **SDG 9:** Industry, Innovation, and Infrastructure  
- **SDG 12:** Responsible Consumption and Production

---

## 👨‍💻 Authors
Created by divs.
