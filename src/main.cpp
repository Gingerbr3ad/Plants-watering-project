#include "systemDefinitions.h"
#include "waterSensor.h"

int val = 0;
extern volatile bool waterSensorCheckFlag = 0;

void setup() {
  Serial.begin(115200);
  pinMode(pumpPin, OUTPUT);
  pinMode(alarmPin, OUTPUT);

  waterSensorInit();
}

void loop() {
  if (waterSensorCheckFlag) {waterSensorCheck();}
  val = analogRead(sensorPin);
  Serial.println(val);

  if(val > 2000){
    digitalWrite(pumpPin, HIGH); }
  else {digitalWrite(pumpPin, LOW);}
  

  delay(500);
}


