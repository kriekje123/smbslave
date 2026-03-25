#include "motor_control.h"
#include "motor_registers.h"
#include "smb.h"

void motorInit()
{
    smb.writeByteRegister(REG_SPEED, 0);
    smb.writeByteRegister(REG_DIRECTION, 0);
    smb.writeWordRegister(REG_RPM_L, 0);

    setMotorPWM(0);
    setMotorDirection(0);
}

void motorUpdate()
{
    uint8_t speed = smb.readByteRegister(REG_SPEED);
    uint8_t direction = smb.readByteRegister(REG_DIRECTION);

    setMotorDirection(direction);
    setMotorPWM(speed);
}

void setMotorPWM(uint8_t pwm)
{
    //Snelheid initialiseren
}

void setMotorDirection(uint8_t direction)
{
    //Richting instellen
}