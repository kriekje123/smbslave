#include "smb.h"
#include <Arduino.h>

//#define I2C_DEBUG

Smb smb;

uint8_t Smb::regIdx = 0;
uint8_t Smb::registerList[I2C_NUM_REGISTERS];

//Public functions
void Smb::begin(uint8_t slaveAddr)
{
    #ifdef I2C_DEBUG
      pinMode(2,OUTPUT);
      pinMode(3,OUTPUT);
    #endif

    Wire.onReceive(Smb::handleReceive);
    Wire.onRequest(Smb::handleRequest);
    Wire.begin(slaveAddr);

    regIdx=0;
}

uint8_t Smb::readByteRegister(uint8_t reg)
{
    uint8_t ret;
    if (reg>=I2C_NUM_REGISTERS) return 0; //Invalid register index
    cli();
    ret=registerList[reg];
    sei();
    return ret;
}

uint16_t Smb::readWordRegister(uint8_t reg)
{
    uint16_t ret;
    if (reg>=I2C_NUM_REGISTERS) return 0; //Invalid register index   
    cli();
    ((uint8_t *) (&ret))[0]=registerList[reg+0];
    ((uint8_t *) (&ret))[1]=registerList[reg+1];
    sei();
    return ret;
}

void Smb::writeByteRegister(uint8_t reg,uint8_t value)
{
    if (reg>=I2C_NUM_REGISTERS) return; //Invalid register index
    cli();
    registerList[reg]=value;
    sei();
}

void Smb::writeWordRegister(uint8_t reg,uint16_t value)
{
    if (reg>=I2C_NUM_REGISTERS) return; //Invalid register index    
    cli();
    registerList[reg+0]=((uint8_t *) (&value))[0];
    registerList[reg+1]=((uint8_t *) (&value))[1];
    sei();
}

//Private functions
void Smb::handleReceive(int numBytes) 
{
    int i=0;

    #ifdef I2C_DEBUG
        digitalWrite(2,1);
        digitalWrite(2,0);

        Serial.print("I2C Rcv:");
        Serial.print(numBytes);
        Serial.print("\n");
    #endif

    while (Wire.available()) {
        char c = Wire.read();
        if (i==0)
        {
            regIdx=c;
        }
        else
        {
            registerList[regIdx]=c;
            regIdx++;
            if (regIdx>=I2C_NUM_REGISTERS) regIdx=0;
        }
        i++;
        #ifdef I2C_DEBUG
            Serial.print((int) c);
            Serial.print(" ");
        #endif
    }

    #ifdef I2C_DEBUG
        Serial.println();
    #endif
}

void Smb::handleRequest()
{
    int res;
    int a;
    #ifdef I2C_DEBUG
        digitalWrite(3,1);
        digitalWrite(3,0);
        Serial.print("request\n");
    #endif

    for (a=0;a<I2C_READ_MAX_LEN;a++)
    {
        Wire.write(registerList[regIdx]);
        regIdx++;
        if (regIdx>=I2C_NUM_REGISTERS) regIdx=0;
    }
}