#include <Arduino.h>
#include "smb.h"
#include "motor_registers.h"

// ===================== CURRENT SENSOR =====================

// adjust later when you know your sensor
float currentOffsetVoltage = 2.5;
float currentSensitivity   = 0.185; // sensor ACS712 5A

#define CURRENT_PIN A0

float readCurrent() {
    int raw = analogRead(CURRENT_PIN);
    float voltage = raw * (5.0 / 1023.0);

    return (voltage - currentOffsetVoltage) / currentSensitivity;
}

void updateCurrent() {
    float current = readCurrent();

    // scale to 0–255 (0.1A resolution)
    uint8_t value = constrain((int)(current * 10), 0, 255);

    smb.writeByteRegister(REG_CURRENT, value);
}

// ===================== RPM ENCODER =====================

#define ENCODER_PIN 2
#define PULSES_PER_REV 20   // CHANGE THIS based on your encoder

volatile int pulseCount = 0;
unsigned long lastRPMTime = 0;

void encoderISR() {
    pulseCount++;
}

void sensorsInit() {
    pinMode(CURRENT_PIN, INPUT);

    pinMode(ENCODER_PIN, INPUT_PULLUP);
    attachInterrupt(digitalPinToInterrupt(ENCODER_PIN), encoderISR, RISING);
}

void updateRPM() {
    unsigned long now = millis();

    if (now - lastRPMTime >= 100) {  // 100ms update rate
        noInterrupts();
        int pulses = pulseCount;
        pulseCount = 0;
        interrupts();

        float rpm = (pulses * 600.0) / PULSES_PER_REV;

        uint16_t rpmInt = (uint16_t)rpm;

        smb.writeWordRegister(REG_RPM_L, rpmInt);

        lastRPMTime = now;
    }
}

// ===================== MASTER FUNCTION =====================

void updateSensors() {
    updateCurrent();
    updateRPM();
}