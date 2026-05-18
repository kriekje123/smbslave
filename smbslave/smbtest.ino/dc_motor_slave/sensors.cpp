#include "sensors.h"
#include "motor_registers.h"
#include "smb.h"

#include <Arduino.h>

constexpr uint8_t CURRENT_PIN = A2;
constexpr uint8_t BACKEMF_PIN = A3;

static void updateCurrent()
{
    uint16_t rawCurrent = analogRead(CURRENT_PIN);

    //schalen naar 8-bit
    uint8_t currentValue = rawCurrent >> 2;

    smb.writeByteRegister(REG_CURRENT, currentValue);
}

static void updateRPM()
{
    uint16_t rawBackEMF = analogRead(BACKEMF_PIN);

    smb.writeWordRegister(REG_RPM_L, rawBackEMF);
}

void sensorsInit()
{
    pinMode(CURRENT_PIN, INPUT);
    pinMode(BACKEMF_PIN, INPUT);
}

void updateSensors()
{
    updateCurrent();
    updateRPM();
}