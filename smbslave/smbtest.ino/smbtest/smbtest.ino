#include "smb.h"

#define I2C_SLAVE_ADDR 0x22

void setup() 
{
    Serial.begin(115200);
    smb.begin(I2C_SLAVE_ADDR);

    for (int a=0;a<I2C_NUM_REGISTERS;a++) smb.writeByteRegister(a,a); //Fill register list with non zero values
}

void loop() 
{
    char sbuf[80];
    Serial.println("Register dump:");
    for (int a=0;a<I2C_NUM_REGISTERS;a++) 
    {
        sprintf(sbuf,"%d:%02xH  ",a,smb.readByteRegister(a));
        Serial.print(sbuf);
    }
    Serial.print("\n");

    delay(500);

}