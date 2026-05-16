# 🔧 Troubleshooting Guide
## Arduino-Based Smart Temperature Monitoring and Fan Automation System

---

## 📋 Table of Contents

1. [Temperature Reading Issues](#1-temperature-reading-issues)
2. [Fan Not Working](#2-fan-not-working)
3. [LCD Display Issues](#3-lcd-display-issues)
4. [Arduino & Upload Issues](#4-arduino--upload-issues)
5. [Tinkercad Simulation Issues](#5-tinkercad-simulation-issues)
6. [Serial Monitor Issues](#6-serial-monitor-issues)
7. [General Tips](#7-general-tips)

---

## 1. Temperature Reading Issues

### ❌ Temperature shows 0°C or negative values constantly
**Cause:** Wrong sensor formula or sensor wired incorrectly.
**Fix:**
- Verify you are using a **TMP36** sensor and the correct formula is in the code:
  ```cpp
  float tempC = (voltage - 0.5) * 100.0;  // TMP36
  ```
- Check sensor wiring: flat face toward you → left = VCC, middle = Output → A0, right = GND

---

### ❌ Temperature reads extremely high (e.g. 300°C+)
**Cause:** Sensor VCC and GND are swapped.
**Fix:**
- Power off immediately to protect the sensor
- Re-check polarity and rewire correctly

---

### ❌ Temperature fluctuates wildly / unstable readings
**Cause:** Electrical noise on the analog pin or loose connections.
**Fix:**
- Add a **100nF decoupling capacitor** between VCC and GND of the sensor
- Average multiple readings in code:
  ```cpp
  int sum = 0;
  for (int i = 0; i < 10; i++) {
    sum += analogRead(TEMP_SENSOR_PIN);
    delay(10);
  }
  int rawValue = sum / 10;
  ```

---

## 2. Fan Not Working

### ❌ Fan does not turn ON at any temperature
**Cause:** Transistor not switching or wrong PWM pin.
**Fix:**
- Confirm fan is connected to **Pin 9** (PWM-capable)
- Check transistor orientation: Base → Pin 9 (via 1kΩ resistor), Collector → Fan –, Emitter → GND
- Add a **flyback diode** (1N4007) across fan terminals for protection
- Test directly: add `analogWrite(FAN_PIN, 255);` in `setup()` to isolate

---

### ❌ Fan runs at full speed regardless of temperature
**Cause:** PWM not working or wrong pin used.
**Fix:**
- Only pins **3, 5, 6, 9, 10, 11** support PWM on Arduino UNO
- Confirm `analogWrite()` is used, not `digitalWrite()`

---

### ❌ Arduino resets when fan turns ON
**Cause:** Motor current spike drops supply voltage.
**Fix:**
- Power the fan from a **separate supply**, not Arduino's 5V pin
- Add a **100µF capacitor** across the motor supply rails

---

## 3. LCD Display Issues

### ❌ LCD shows nothing / completely blank
**Cause:** Contrast too low or incorrect wiring.
**Fix:**
- **Adjust the potentiometer** — this controls LCD contrast (Vo pin). Turn it slowly until characters appear
- Verify LCD wiring matches code pin definitions:
  ```cpp
  LiquidCrystal lcd(7, 8, 10, 11, 12, 13);
  //              RS EN D4  D5  D6  D7
  ```
- Check that LCD VCC → 5V and GND → GND are connected

---

### ❌ LCD shows random characters or boxes
**Cause:** Incorrect pin mapping or `lcd.begin()` not called.
**Fix:**
- Confirm `lcd.begin(16, 2)` is in `setup()`
- Double-check every wire from Arduino to LCD matches the pin order in `LiquidCrystal lcd(...)` constructor
- Call `lcd.clear()` at the start of `setup()`

---

### ❌ Temperature on LCD doesn't update
**Cause:** `lcd.setCursor()` not repositioning correctly or missing `delay()`.
**Fix:**
- Ensure `lcd.setCursor(0, 0)` is called at the beginning of every loop before printing
- Add trailing spaces after the value to overwrite old characters:
  ```cpp
  lcd.print(temperature, 2);
  lcd.print(" C  ");   // Spaces clear leftover digits
  ```

---

### ❌ Degree symbol (°) not displaying correctly
**Cause:** Wrong character code used.
**Fix:**
- Use the correct LCD degree character:
  ```cpp
  lcd.print((char)223);  // Correct degree symbol for LCD
  ```

---

### ❌ LCD library not found / compile error
**Cause:** LiquidCrystal library not installed.
**Fix:**
- In Arduino IDE: **Sketch → Include Library → Manage Libraries**
- Search for **"LiquidCrystal"** and install it
- The `#include <LiquidCrystal.h>` line must be at the top of the sketch

---

## 4. Arduino & Upload Issues

### ❌ "Port not found" or "No device on selected port"
**Fix:**
- Reconnect the USB cable
- Go to **Tools → Port** and select the correct COM port
- Try a different USB cable (some cables are charge-only)
- Install CH340 or FTDI drivers if using a clone Arduino

---

### ❌ "avrdude: stk500_recv(): programmer is not responding"
**Fix:**
- Press the **Reset button** on Arduino just before clicking Upload
- Select correct board: **Tools → Board → Arduino UNO**
- Close Serial Monitor before uploading

---

### ❌ Code compiles but behavior is wrong
**Fix:**
- Open **Serial Monitor** (Ctrl+Shift+M) at **9600 baud**
- Observe live temperature and fan status output to identify the issue

---

## 5. Tinkercad Simulation Issues

### ❌ Simulation won't start
**Fix:**
- Fix any red syntax errors highlighted in the code editor
- Ensure all components are wired with no floating connections
- Click **"Stop"** then **"Start Simulation"** to reset

---

### ❌ LCD stays blank in simulation
**Fix:**
- Click on the **potentiometer** during simulation and rotate it to adjust contrast
- Verify the LCD's Vo (contrast) pin is connected to the potentiometer wiper

---

### ❌ Temperature sensor always reads the same value
**Cause:** Tinkercad uses a fixed default temperature.
**Fix:**
- Click on the **TMP sensor** during simulation
- A temperature slider appears — drag it to simulate different temperatures
- Observe the LCD update and fan speed change in real time

---

### ❌ DC Motor (fan) doesn't spin in simulation
**Fix:**
- Ensure the motor is driven through a **PN2222 transistor**
- Verify the PWM signal reaches the transistor base through a resistor
- Check that the motor's supply rail is connected to 5V

---

### ❌ Serial Monitor not showing output in Tinkercad
**Fix:**
- Click the **Serial Monitor** button at the bottom of the code panel during simulation
- Baud rate must be set to **9600** in both code and monitor

---

## 6. Serial Monitor Issues

### ❌ Garbage characters / unreadable output
**Cause:** Baud rate mismatch.
**Fix:**
- Set Serial Monitor to **9600 baud** (bottom-right dropdown)
- Must match `Serial.begin(9600)` in code

---

### ❌ Serial Monitor shows nothing
**Fix:**
- Open Serial Monitor **after** uploading
- Press the **Reset button** on Arduino after opening Serial Monitor
- Confirm `Serial.begin(9600)` is in `setup()`

---

## 7. General Tips

| Tip | Details |
|-----|---------|
| 🔁 Reset simulation | Stop and restart Tinkercad simulation after any wiring change |
| 🌡️ Use the TMP slider | Click the TMP sensor during simulation to change temperature manually |
| 🖥️ Check LCD contrast | Always adjust the potentiometer first if the LCD appears blank |
| 📏 Use correct PWM pins | Only pins 3, 5, 6, 9, 10, 11 support `analogWrite()` on UNO |
| 💾 Save Tinkercad project | Save frequently to avoid losing circuit and code progress |
| 📋 Use Serial Monitor | Print temperature every loop — best way to debug sensor readings |
| 🧪 Test components solo | Test LCD separately before integrating with sensor and fan |

---

## 📬 Still Having Issues?

- Review the [Arduino Documentation](https://docs.arduino.cc/)
- Review the [LiquidCrystal Library Reference](https://www.arduino.cc/reference/en/libraries/liquidcrystal/)
- Visit [Tinkercad Support](https://www.tinkercad.com/learn)
- Refer to the project README for circuit wiring details

---

*Troubleshooting Guide — Arduino Temperature Fan Automation System*  
*Author: Mamoon | Course: Engr. Fazeel Abbas*
