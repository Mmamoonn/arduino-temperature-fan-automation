# 🔧 Troubleshooting Guide
## Arduino-Based Smart Temperature Monitoring and Fan Automation System

---

## 📋 Table of Contents

1. [Temperature Reading Issues](#1-temperature-reading-issues)
2. [Fan Not Working](#2-fan-not-working)
3. [LED Issues](#3-led-issues)
4. [Arduino & Upload Issues](#4-arduino--upload-issues)
5. [Tinkercad Simulation Issues](#5-tinkercad-simulation-issues)
6. [Serial Monitor Issues](#6-serial-monitor-issues)
7. [General Tips](#7-general-tips)

---

## 1. Temperature Reading Issues

### ❌ Temperature shows 0°C or negative values constantly
**Cause:** Wrong sensor type selected in code or sensor wired incorrectly.
**Fix:**
- Check if you are using **TMP36** or **LM35** and make sure the correct formula is uncommented in the code:
  ```cpp
  // For TMP36:
  float tempC = (voltage - 0.5) * 100.0;

  // For LM35:
  float tempC = voltage * 100.0;
  ```
- Verify sensor pin connections: VCC → 5V, GND → GND, Output → A0

---

### ❌ Temperature reads extremely high (e.g. 300°C+)
**Cause:** Sensor is wired in reverse (VCC and GND swapped).
**Fix:**
- Power off immediately to avoid damaging the sensor
- Re-check polarity: flat face of TMP36 faces you → left pin = VCC, middle = Output, right = GND

---

### ❌ Temperature fluctuates wildly / unstable readings
**Cause:** Electrical noise on the analog pin or loose connections.
**Fix:**
- Add a **100nF decoupling capacitor** between VCC and GND of the sensor
- Add a **10kΩ pull-down resistor** on the analog input pin
- Use shorter jumper wires in simulation/hardware
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
**Cause:** Transistor not switching, wrong pin, or PWM issue.
**Fix:**
- Confirm fan is connected to **Pin 9** (PWM-capable pin)
- Check transistor orientation — Base → Arduino pin (via resistor), Collector → Fan –, Emitter → GND
- Add a **1kΩ resistor** between Arduino pin 9 and transistor Base
- Verify flyback diode is placed correctly across the fan terminals (cathode to +, anode to –)
- Test with a direct `analogWrite(FAN_PIN, 255)` in `setup()` to isolate the issue

---

### ❌ Fan runs at full speed always, ignoring temperature
**Cause:** PWM not working or wrong pin used.
**Fix:**
- Only pins **3, 5, 6, 9, 10, 11** support PWM on Arduino UNO — make sure FAN_PIN is one of these
- Confirm `analogWrite()` is being called, not `digitalWrite()`

---

### ❌ Fan makes noise but doesn't spin
**Cause:** Insufficient current — Arduino cannot directly drive a motor.
**Fix:**
- Always use a **transistor or MOSFET** as a driver between Arduino and the fan
- Check that the fan's rated voltage matches the supply voltage

---

### ❌ Arduino resets when fan turns ON
**Cause:** Motor draws a large current spike that drops the supply voltage.
**Fix:**
- Power the fan from a **separate power supply**, not the Arduino's 5V pin
- Add a **100µF capacitor** across the motor supply rails to absorb current spikes

---

## 3. LED Issues

### ❌ None of the LEDs light up
**Cause:** Missing current-limiting resistors or wrong pin assignment.
**Fix:**
- Ensure each LED has a **220Ω resistor** in series
- Double-check pin numbers match the code (GREEN=2, YELLOW=3, RED=4)
- Test each LED individually with `digitalWrite(LED_GREEN, HIGH)` in `setup()`

---

### ❌ Wrong LED lights up for a given temperature
**Cause:** LED pin assignments are swapped in code or wiring.
**Fix:**
- Review the pin definitions at the top of the `.ino` file:
  ```cpp
  const int LED_GREEN  = 2;
  const int LED_YELLOW = 3;
  const int LED_RED    = 4;
  ```
- Match these exactly to your circuit wiring

---

### ❌ LED stays ON even after temperature drops
**Cause:** `allLEDsOff()` not being called before setting new LED state.
**Fix:**
- Confirm `allLEDsOff()` is called at the start of every loop cycle before any `digitalWrite(LED_x, HIGH)`

---

### ❌ LED is very dim
**Cause:** Resistor value too high.
**Fix:**
- Replace with a **220Ω** resistor instead of a higher value like 1kΩ

---

## 4. Arduino & Upload Issues

### ❌ "Port not found" or "No device on selected port"
**Fix:**
- Reconnect the USB cable
- In Arduino IDE: **Tools → Port** → select the correct COM port
- Try a different USB cable (some are charge-only, not data)
- Install CH340 or FTDI drivers if using a clone Arduino board

---

### ❌ "avrdude: stk500_recv(): programmer is not responding"
**Fix:**
- Press the **Reset button** on the Arduino just before clicking Upload
- Select correct board: **Tools → Board → Arduino UNO**
- Close Serial Monitor before uploading

---

### ❌ Code compiles but behavior is wrong
**Fix:**
- Open **Serial Monitor** (Ctrl+Shift+M) at **9600 baud** to see real-time temperature readings and status messages
- Check that threshold values match your expected environment temperature

---

## 5. Tinkercad Simulation Issues

### ❌ Simulation won't start
**Fix:**
- Check for red error highlights in the code editor — fix any syntax errors first
- Make sure all components are properly connected (no floating wires)
- Click **"Stop"** then **"Start Simulation"** again to reset

---

### ❌ Temperature sensor always reads room temperature in simulation
**Cause:** Tinkercad uses a default temperature; you need to manually adjust it.
**Fix:**
- Click on the **TMP36 sensor** during simulation
- A slider will appear — drag it to simulate different temperatures and observe fan/LED response

---

### ❌ DC Motor (fan) doesn't spin in simulation
**Fix:**
- Make sure the motor is connected through a **PN2222 transistor** in Tinkercad
- Verify the PWM signal reaches the transistor base
- Check that the motor's power rail is connected to 5V, not floating

---

### ❌ Serial Monitor not showing output in Tinkercad
**Fix:**
- Click the **Serial Monitor** button at the bottom of the code panel during simulation
- Ensure `Serial.begin(9600)` is in `setup()` and baud rate matches

---

## 6. Serial Monitor Issues

### ❌ Garbage characters / unreadable output
**Cause:** Baud rate mismatch.
**Fix:**
- Set Serial Monitor baud rate to **9600** (bottom-right dropdown in Arduino IDE)
- Must match `Serial.begin(9600)` in the code

---

### ❌ Serial Monitor shows nothing
**Fix:**
- Make sure the Serial Monitor is open **after** uploading
- Check `Serial.begin(9600)` exists in `setup()`
- Try pressing the **Reset button** on the Arduino after opening Serial Monitor

---

## 7. General Tips

| Tip | Details |
|-----|---------|
| 🔁 Always reset simulation | Stop and restart Tinkercad simulation after any wiring change |
| 🧪 Test components individually | Test fan, LEDs, and sensor separately before combining |
| 📏 Check pin numbers | Arduino UNO has limited PWM pins — only 3, 5, 6, 9, 10, 11 |
| 🌡️ Adjust thresholds | If testing at room temperature (~25°C), lower `TEMP_LOW` to 20°C temporarily |
| 💾 Save frequently | Save your Tinkercad project regularly to avoid losing work |
| 📋 Use Serial Monitor | It's the best debugging tool — print temperature values every loop |

---

## 📬 Still Having Issues?

- Review the [Arduino Documentation](https://docs.arduino.cc/)
- Visit [Tinkercad Support](https://www.tinkercad.com/learn)
- Refer to the project README for circuit wiring details

---

*Troubleshooting Guide — Arduino Temperature Fan Automation System*
*Author: Mamoon | Course: Engr. Fazeel Abbas*
