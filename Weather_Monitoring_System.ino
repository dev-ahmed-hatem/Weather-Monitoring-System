// LiquidCrystal
#include <LiquidCrystal.h>
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

// Define the current parameter to be displayed
unsigned int currentState;

// DHT11 Sensor
#include "dht11.h"
#define DHT11PIN 6
dht11 DHT11;

// LDR Sensor
const int ldrPin = A0;
float ldrValue, lightIntensity;

// Sound Sensor
unsigned long lastEvent = 0;
int soundValue;

// MQ2 Sensor
const int MQ2Pin = A1;
float MQ2Value;

void setup() {
  lcd.begin(16, 2);

  currentState = 0;
  pinMode(7, INPUT);
  pinMode(8, INPUT);
  Serial.begin(9600);
}

void loop() {

  if (digitalRead(7)) {
    currentState == 4 ? currentState = 1 : currentState++;
    Serial.println("Button Pressed - currentState: " + String(currentState));
    lcd.clear();
    delay(200);
  }


  if (currentState == 0) {
    lcd.setCursor(0, 0);
    lcd.print("Environment");
    lcd.setCursor(0, 1);
    lcd.print("Monitoring");
    currentState = 1;
    delay(3000);
  } else if (currentState == 1) {
    // Displaying Temperature

    // Serial.print("Humidity (%): ");
    // Serial.println((float)DHT11.humidity, 2);
    // Serial.print("Temperature  (C): ");
    // Serial.println((float)DHT11.temperature, 2);

    int chk = DHT11.read(DHT11PIN);
    lcd.setCursor(0, 0);
    lcd.print("Temp.:    " + String((float)DHT11.temperature) + "C");
    lcd.setCursor(0, 1);
    lcd.print("Humidity: " + String((float)DHT11.humidity) + "%");
    delay(800);

  } else if (currentState == 2) {
    // Displaying Light Intensity

    ldrValue = analogRead(ldrPin);

    lcd.setCursor(0, 0);
    lcd.print("Raw LDR:  " + String(ldrValue));
    lcd.setCursor(0, 1);
    lightIntensity = (1 - ((float)ldrValue / 1024.00)) * 100;
    lcd.print("LI.:      " + String(lightIntensity) + "%");
    delay(800);

  } else if (currentState == 3) {
    // Displaying Sound Condition
    lcd.setCursor(0, 0);
    lcd.print("Detecting sounds");

    soundValue = digitalRead(8);

    if (soundValue == LOW) {
      if (millis() - lastEvent > 25) {
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Clap Detected");
        delay(1800);
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Detecting sounds");
      }
      lastEvent = millis();
    }

  } else {
    // Displaying Gas State
    MQ2Value = analogRead(MQ2Pin);

    lcd.setCursor(0, 0);
    lcd.print("Gas Raw:  " + String(MQ2Value));
    lcd.setCursor(0, 1);
    lcd.print("No threshold!");
    delay(800);
  }
  // Serial.println("end");
}