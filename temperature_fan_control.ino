/*
 * ============================================================
 * Arduino-Based Smart Temperature Monitoring and Fan Automation
 * ============================================================
 * Platform  : Arduino UNO
 * Simulation: Autodesk Tinkercad
 * Author    : Mamoon
 * Course    : Engr. Fazeel Abbas
 * ============================================================
 *
 * Description:
 * Reads temperature from a TMP sensor and controls a DC fan
 * via PWM based on temperature thresholds. Real-time temperature
 * is displayed on a 16x2 LCD screen.
 *
 * Components:
 *   - TMP Temperature Sensor    → Analog Pin A0
 *   - DC Fan (via transistor)   → Digital PWM Pin 9
 *   - 16x2 LCD Display          → Pins 7,8,10,11,12,13
 *   - Potentiometer             → LCD contrast (Vo pin)
 *
 * Thresholds:
 *   < 30°C  → Fan OFF
 *   30–40°C → Fan LOW speed
 *   > 40°C  → Fan FULL speed
 * ============================================================
 */

#include <LiquidCrystal.h>

// ── LCD Pin Configuration ─────────────────────────────────────
// RS, EN, D4, D5, D6, D7
LiquidCrystal lcd(7, 8, 10, 11, 12, 13);

// ── Pin Definitions ───────────────────────────────────────────
const int TEMP_SENSOR_PIN = A0;   // TMP sensor analog input
const int FAN_PIN         = 9;    // PWM pin → transistor → fan

// ── Temperature Thresholds (°C) ───────────────────────────────
const float TEMP_LOW  = 30.0;    // Below → fan off
const float TEMP_HIGH = 40.0;    // Above → fan full speed

// ── Fan Speed Values (PWM 0–255) ──────────────────────────────
const int FAN_OFF  = 0;
const int FAN_LOW  = 120;
const int FAN_HIGH = 255;

// ── Setup ─────────────────────────────────────────────────────
void setup() {
  pinMode(FAN_PIN, OUTPUT);

  // Initialize 16x2 LCD
  lcd.begin(16, 2);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("  Temp Monitor  ");
  lcd.setCursor(0, 1);
  lcd.print("  Fan Control   ");
  delay(2000);
  lcd.clear();

  Serial.begin(9600);
  Serial.println("=== Temperature Fan Control System ===");
  Serial.println("Monitoring started...\n");
}

// ── Main Loop ─────────────────────────────────────────────────
void loop() {
  float temperature = readTemperature();

  // ── Update LCD ──────────────────────────────────────────────
  lcd.setCursor(0, 0);
  lcd.print("T: ");
  lcd.print(temperature, 2);   // 2 decimal places e.g. "T: 74.71"
  lcd.print((char)223);        // Degree symbol °
  lcd.print("C  ");

  // ── Fan Control Logic ────────────────────────────────────────
  String fanStatus;
  if (temperature >= TEMP_HIGH) {
    analogWrite(FAN_PIN, FAN_HIGH);
    fanStatus = "Fan: HIGH  ";
  } else if (temperature >= TEMP_LOW) {
    analogWrite(FAN_PIN, FAN_LOW);
    fanStatus = "Fan: LOW   ";
  } else {
    analogWrite(FAN_PIN, FAN_OFF);
    fanStatus = "Fan: OFF   ";
  }

  // ── Display Fan Status on LCD Row 2 ─────────────────────────
  lcd.setCursor(0, 1);
  lcd.print(fanStatus);

  // ── Serial Monitor Output ────────────────────────────────────
  Serial.print("Temperature: ");
  Serial.print(temperature, 2);
  Serial.print(" C  |  ");
  Serial.println(fanStatus);

  delay(1000);  // Refresh every 1 second
}

// ── Helper: Read Temperature in °C ───────────────────────────
float readTemperature() {
  int rawValue = analogRead(TEMP_SENSOR_PIN);

  // Convert ADC reading to voltage (5V reference, 10-bit ADC)
  float voltage = rawValue * (5.0 / 1023.0);

  // TMP36: Temp(°C) = (Voltage - 0.5) × 100
  float tempC = (voltage - 0.5) * 100.0;

  return tempC;
}
