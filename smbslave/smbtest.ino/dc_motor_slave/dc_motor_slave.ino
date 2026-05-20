#include "smb.h"
#include "motor_control.h"
#include "sensors.h"

// Eerste 3 bits voor DC-motormodule
#define DC_MODULE_PREFIX 0b1110000

// DIP-switch pinnen
#define ADDR_BIT0 PD4
#define ADDR_BIT1 PD5
#define ADDR_BIT2 PD6
#define ADDR_BIT3 PD7

uint8_t readModuleAddress()
{
    uint8_t module_id = 0;

    // Lees elke DIP-switch bit uit
    module_id |= (digitalRead(ADDR_BIT0) << 0);
    module_id |= (digitalRead(ADDR_BIT1) << 1);
    module_id |= (digitalRead(ADDR_BIT2) << 2);
    module_id |= (digitalRead(ADDR_BIT3) << 3);

    // Voeg vaste DC-prefix toe
    return DC_MODULE_PREFIX | module_id;
}

void setup() 
{
    // DIP-switch pinnen als input
    pinMode(ADDR_BIT0, INPUT);
    pinMode(ADDR_BIT1, INPUT);
    pinMode(ADDR_BIT2, INPUT);
    pinMode(ADDR_BIT3, INPUT);

    // Volledig I2C-adres bepalen
    uint8_t slave_address = readModuleAddress();

    smb.begin(slave_address);

    motorInit();
    sensorsInit();
}


void loop() {
    motorUpdate();

    updateSensors();

    delay(10); // 100 Hz control loop
}