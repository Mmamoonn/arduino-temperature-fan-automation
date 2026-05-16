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
 * Reads temperature from a TMP36/LM35 sensor and controls a DC fan
 * and LED indicators based on defined temperature thresholds.
 *
 * Thresholds:
 *   < 30°C  → Fan OFF  | Green LED ON
 *   30–40°C → Fan LOW  | Yellow LED ON
 *   > 40°C  → Fan HIGH | Red LED ON
 * ============================================================
 */

// ── Pin Definitions ──────────────────────────────────────────
const int TEMP_SENSOR_PIN = A0;   // TMP36 / LM35 analog input
const int FAN_PIN         = 9;    // PWM pin for fan (via transistor)
const int LED_GREEN       = 2;    // Green LED  → Normal temp
const int LED_YELLOW      = 3;    // Yellow LED → Medium temp
const int LED_RED         = 4;    // Red LED    → High temp

// ── Temperature Thresholds (°C) ──────────────────────────────
const float TEMP_LOW    = 30.0;   // Below this → fan off
const float TEMP_HIGH   = 40.0;   // Above this → fan full speed

// ── Fan Speed Values (PWM 0–255) ─────────────────────────────
const int FAN_OFF    = 0;
const int FAN_LOW    = 120;
const int FAN_HIGH   = 255;

// ── Setup ─────────────────────────────────────────────────────
void setup() {
  pinMode(FAN_PIN,    OUTPUT);
  pinMode(LED_GREEN,  OUTPUT);
  pinMode(LED_YELLOW, OUTPUT);
  pinMode(LED_RED,    OUTPUT);

  Serial.begin(9600);
  Serial.println("=== Temperature Fan Control System ===");
  Serial.println("Monitoring started...\n");
}

// ── Main Loop ─────────────────────────────────────────────────
void loop() {
  float temperature = readTemperature();

  Serial.print("Temperature: ");
  Serial.print(temperature);
  Serial.println(" °C");

  // Turn off all LEDs before setting the correct one
  allLEDsOff();

  if (temperature >= TEMP_HIGH) {
    // HIGH temperature zone
    analogWrite(FAN_PIN, FAN_HIGH);
    digitalWrite(LED_RED, HIGH);
    Serial.println("Status: HIGH TEMP → Fan FULL SPEED 🔴\n");

  } else if (temperature >= TEMP_LOW) {
    // MEDIUM temperature zone
    analogWrite(FAN_PIN, FAN_LOW);
    digitalWrite(LED_YELLOW, HIGH);
    Serial.println("Status: MEDIUM TEMP → Fan LOW SPEED 🟡\n");

  } else {
    // NORMAL temperature zone
    analogWrite(FAN_PIN, FAN_OFF);
    digitalWrite(LED_GREEN, HIGH);
    Serial.println("Status: NORMAL TEMP → Fan OFF 🟢\n");
  }

  delay(1000);  // Read every 1 second
}

// ── Helper: Read Temperature in °C ───────────────────────────
float readTemperature() {
  int rawValue = analogRead(TEMP_SENSOR_PIN);

  // Convert ADC reading to voltage (5V reference, 10-bit ADC)
  float voltage = rawValue * (5.0 / 1023.0);

  // TMP36: Temp(°C) = (Voltage - 0.5) × 100
  // LM35:  Temp(°C) = Voltage × 100
  float tempC = (voltage - 0.5) * 100.0;  // Use for TMP36
  // float tempC = voltage * 100.0;        // Uncomment for LM35

  return tempC;
}

// ── Helper: Turn Off All LEDs ─────────────────────────────────
void allLEDsOff() {
  digitalWrite(LED_GREEN,  LOW);
  digitalWrite(LED_YELLOW, LOW);
  digitalWrite(LED_RED,    LOW);
}
