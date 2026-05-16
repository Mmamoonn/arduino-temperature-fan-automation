# 🌡️ Arduino-Based Smart Temperature Monitoring and Fan Automation System

A simulation-based project built on **Autodesk Tinkercad** that uses an Arduino UNO to monitor ambient temperature via a sensor and automatically control a DC fan and LED indicators based on predefined temperature thresholds — no analog design required.

---

## 📌 Overview

This project is the digital/microcontroller counterpart to an analog fan control design. Instead of op-amps and thermistors, an Arduino reads temperature data, makes decisions in software, and drives a fan and LEDs accordingly. The entire circuit is simulated in **Autodesk Tinkercad**.

---

## 🖥️ Simulation Platform

| Tool | Details |
|------|---------|
| Platform | Autodesk Tinkercad |
| Type | Circuit + Code Simulation |
| Board | Arduino UNO |
| Link | *(Add your Tinkercad project link here)* |

---

## ⚙️ How It Works

```
[Temperature Sensor (TMP36 / LM35)]
              │
              ▼
     [Arduino UNO - Analog Pin]
              │
       ┌──────┴──────┐
       ▼             ▼
  [DC Fan via     [LED Indicators]
   Transistor]    🔴 High Temp
                  🟡 Medium Temp
                  🟢 Normal Temp
```

1. **Sensing:** The temperature sensor outputs an analog voltage proportional to temperature, read by Arduino's ADC.
2. **Processing:** Arduino converts the raw analog value to °C and compares against thresholds.
3. **Fan Control:** Fan is turned ON/OFF (or speed-controlled via PWM) based on temperature level.
4. **LED Indication:** LEDs provide a visual status of the current temperature zone.

---

## 🌡️ Temperature Thresholds

| Temperature Range | Fan State | LED Indicator |
|-------------------|-----------|---------------|
| Below 30°C        | OFF       | 🟢 Green ON   |
| 30°C – 40°C       | LOW speed | 🟡 Yellow ON  |
| Above 40°C        | HIGH speed| 🔴 Red ON     |

---

## 🧰 Components Used (Tinkercad Simulation)

| Component | Quantity | Purpose |
|-----------|----------|---------|
| Arduino UNO | 1 | Main microcontroller |
| TMP36 / LM35 Temperature Sensor | 1 | Temperature sensing |
| DC Motor (Fan) | 1 | Cooling fan |
| NPN Transistor (e.g. PN2222) | 1 | Fan driver |
| LEDs (Red, Yellow, Green) | 3 | Temperature indicators |
| Resistors (220Ω) | 3 | LED current limiting |
| Flyback Diode (1N4007) | 1 | Motor protection |
| Breadboard | 1 | Circuit assembly |
| Power Supply (5V) | 1 | Via Arduino USB |

---

## 💻 Arduino Code

The main sketch is located in the `/src` folder:

```
/src
  └── temperature_fan_control.ino
```

### Code Logic Summary

```cpp
// Pseudocode overview
readTemperature();         // Read analog pin → convert to °C

if (temp > 40) {
  fanSpeed = HIGH;         // Full speed
  digitalWrite(RED_LED, HIGH);
} else if (temp > 30) {
  fanSpeed = MEDIUM;       // Half speed (PWM)
  digitalWrite(YELLOW_LED, HIGH);
} else {
  fanSpeed = OFF;          // Fan off
  digitalWrite(GREEN_LED, HIGH);
}
```

---

## 🖼️ Simulation Screenshot

The Tinkercad simulation screenshot is available in the `/simulation` folder:

```
/simulation
  └── tinkercad_simulation.png   ← Circuit simulation screenshot
```

---

## 📁 Repository Structure

```
arduino-temperature-fan-automation/
├── src/
│   └── temperature_fan_control.ino
├── simulation/
│   └── tinkercad_simulation.png
├── README.md
└── LICENSE
```

---

## 🚀 Getting Started

### Run in Tinkercad (Simulation)
1. Open [Autodesk Tinkercad](https://www.tinkercad.com)
2. Import or recreate the circuit as shown in the simulation screenshot
3. Paste the `.ino` code into the code editor
4. Click **"Start Simulation"**

### Run on Real Hardware
1. Assemble the circuit on a breadboard as per the schematic
2. Open the `.ino` file in **Arduino IDE**
3. Connect your Arduino UNO via USB
4. Select the correct **Board** and **Port**
5. Click **Upload**

---

## 🔗 Tinkercad Project Link

> *(Paste your Tinkercad shared project URL here)*

---

## 📄 License

This project is licensed under the **Creative Commons Attribution 4.0 International (CC BY 4.0)** license.
You are free to share and adapt this work as long as appropriate credit is given.

See the [LICENSE](LICENSE) file for full details.

---

## 👤 Author

**Mamoon**
Electronics Engineering Student

---

## 🙏 Acknowledgements

- Course Instructor: **Engr. Fazeel Abbas**
- Simulation Tool: [Autodesk Tinkercad](https://www.tinkercad.com)
- References: Arduino documentation and analog electronics coursework
