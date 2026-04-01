#include "smb.h"
#include "motor_control.h"

// IMPORTANT: sensors file
void sensorsInit();
void updateSensors();

#define I2C_SLAVE_ADDR 0x22

void setup() 
{
    Serial.begin(115200);
    smb.begin(I2C_SLAVE_ADDR);

    for (int a=0;a<I2C_NUM_REGISTERS;a++) smb.writeByteRegister(a,a); //Fill register list with non zero values
}


void loop() {
    motorUpdate();   // read I2C registers → control motor


    updateSensors(); // write current + rpm back to registers

    delay(10); // 100 Hz control loop
}