#include <LiquidCrystal.h>

LiquidCrystal lcd(7, 8, 10, 11, 12, 13);

const int TEMP_SENSOR_PIN = A0;   
const int FAN_PIN         = 9;    

// ── Temperature Thresholds (°C) ───────────────────────────────
const float TEMP_LOW  = 30.0;    // Below → fan off
const float TEMP_HIGH = 40.0;    // Above → fan full speed

// ── Fan Speed Values (PWM 0–255) ──────────────────────────────
const int FAN_OFF  = 0;
const int FAN_LOW  = 120;
const int FAN_HIGH = 255;

void setup() {
  pinMode(FAN_PIN, OUTPUT);
  
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

void loop() {
  float temperature = readTemperature();

  lcd.setCursor(0, 0);
  lcd.print("T: ");
  lcd.print(temperature, 2);   
  lcd.print((char)223);        
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

  lcd.setCursor(0, 1);
  lcd.print(fanStatus);

  // ── Serial Monitor Output ────────────────────────────────────
  Serial.print("Temperature: ");
  Serial.print(temperature, 2);
  Serial.print(" C  |  ");
  Serial.println(fanStatus);

  delay(1000);
}

float readTemperature() {
  int rawValue = analogRead(TEMP_SENSOR_PIN);
  float voltage = rawValue * (5.0 / 1023.0);
  float tempC = (voltage - 0.5) * 100.0;

  return tempC;
}
