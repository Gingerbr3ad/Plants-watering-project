 #include "waterSensor.h"

hw_timer_t *Timer0_Cfg = NULL;
extern volatile bool waterSensorCheckFlag;

void IRAM_ATTR Timer0_ISR() {
    waterSensorCheckFlag = 1;
}

void waterSensorInit() {
    pinMode(waterSensorActivePin, OUTPUT);
    pinMode(waretSensorSensingPin, INPUT);

    Timer0_Cfg = timerBegin(0, 48000, true); // Prescaler of 48000 with 240 Mhz clock gives us 0.0006 s per clock tick
    timerAttachInterrupt(Timer0_Cfg, &Timer0_ISR, true);
    timerAlarmWrite(Timer0_Cfg, 1000000/(10*6), true); // 1 000 000 clock tick when each clock tick is 0.0006s means we get an interrupt every 10 minutes
    timerAlarmEnable(Timer0_Cfg);
}


void waterSensorCheck() {
    Serial.print("Water level check... ");
    bool alarmFlag = 0;
    digitalWrite(waterSensorActivePin, HIGH);
    delay(50);
    alarmFlag = !digitalRead(waretSensorSensingPin);
    delay(50);
    digitalWrite(waterSensorActivePin, LOW);

    if (alarmFlag) {
        Serial.print("Water Alarm Triggered");
        digitalWrite(alarmPin, HIGH);
        delay(50);
        digitalWrite(alarmPin, LOW);
    } else {Serial.println("OK");}

    waterSensorCheckFlag = 0;
}
