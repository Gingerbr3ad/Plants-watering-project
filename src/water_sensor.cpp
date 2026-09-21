 #include "water_sensor.h"

hw_timer_t *Timer0_Cfg = NULL;
extern volatile bool waterSensorCheckFlag;

void IRAM_ATTR Timer0_ISR() {
    waterSensorCheckFlag = 1;
}

void water_sensor_init() {
    waterSensorCheckFlag = 1;

    pinMode(WATER_SENSOR_ACTIVE_PIN, OUTPUT);
    pinMode(WATER_SENSOR_PASSIVE_PIN, INPUT);
    pinMode(ALARM_PIN, OUTPUT);

    Timer0_Cfg = timerBegin(0, 48000, true); // Prescaler of 48000 with 80 Mhz clock gives us 0.0006 s per clock tick
    timerAttachInterrupt(Timer0_Cfg, &Timer0_ISR, true);
    timerAlarmWrite(Timer0_Cfg, 1000000/(10*6), true); // 1 000 000 clock tick when each clock tick is 0.0006s means we get an interrupt every 10 minutes
    timerAlarmEnable(Timer0_Cfg);
}


void water_sensor_check() {
    Serial.print("Water level check... ");
    bool alarmFlag = 0;
    digitalWrite(WATER_SENSOR_ACTIVE_PIN, HIGH);
    delay(50);
    alarmFlag = !digitalRead(WATER_SENSOR_PASSIVE_PIN);
    delay(50);
    digitalWrite(WATER_SENSOR_ACTIVE_PIN, LOW);

    if (alarmFlag) {
        Serial.println("Water Alarm Triggered");
        digitalWrite(ALARM_PIN, HIGH);
        delay(50);
        digitalWrite(ALARM_PIN, LOW);
    } else {Serial.println("OK");}

    waterSensorCheckFlag = 0;
}
