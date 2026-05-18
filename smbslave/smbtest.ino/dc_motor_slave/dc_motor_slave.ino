#include "smb.h"
#include "motor_control.h"
#include "sensors.h"

#define I2C_SLAVE_ADDR 0x07 (0b0111)

void setup() 
{
    smb.begin(I2C_SLAVE_ADDR);

    motorInit();
    sensorsInit();
}


void loop() {
    motorUpdate();   // read I2C registers → control motor


    updateSensors(); // write current + rpm back to registers

    delay(10); // 100 Hz control loop
}