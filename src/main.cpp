#include "system_definitions.h"
#include "water_sensor.h"

int moisture_value = 0;
volatile bool waterSensorCheckFlag;

void setup() {
  Serial.begin(115200);
  pinMode(PUMP_PIN, OUTPUT);

  water_sensor_init();
}

void loop() {
  if (waterSensorCheckFlag) {water_sensor_check(); }
  moisture_value = analogRead(MOISTURE_SENSOR_PIN);
  Serial.println(moisture_value);

  if(moisture_value > 2000){
    digitalWrite(PUMP_PIN, HIGH); }
  else {digitalWrite(PUMP_PIN, LOW); }
  

  delay(500);
}


