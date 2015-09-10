#include <SPI.h>
#include "Adafruit_MAX31855.h"

// Defining Temperature Sensor
#define DO   13
#define CS   12
#define CLK  11
Adafruit_MAX31855 thermocouple(CLK, CS, DO);

// Defining Heatbed
#define HB 8
#define TEMP_HIGH 72
#define TEMP_LOW 67

bool heating = 0;

void setup() {
  Serial.begin(9600);
  pinMode(HB, OUTPUT);

  Serial.println("FLODA Heated Printbed");

  // wait for MAX chip to stabilize
  delay(500);
}

void loop() {


  double temp = thermocouple.readCelsius();
  if (isnan(temp)) {
    Serial.println("Something wrong with thermocouple!");
  } else {

    // TURN OFF, WHEN HOT
    if ((heating == 1) && temp > TEMP_HIGH) {
      digitalWrite(HB, LOW);
      digitalWrite(HB, LOW);
      heating = 0;
    }
    else if ((heating == 0) && temp < TEMP_LOW) {
      digitalWrite(HB, HIGH);
      digitalWrite(13, HIGH);
      heating = 1;
    }

    Serial.print("C = ");
    Serial.println(temp);
    Serial.print("heating = ");
    Serial.println(heating);
    Serial.println("");

  }

  delay(1000);
}
