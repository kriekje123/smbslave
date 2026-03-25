#include "motor_control.h"
#include "motor_registers.h"
#include "smb.h"

void motorInit()
{
    //hardware initialiseren
}

void motorUpdate()
{
    //waardes uitlezen

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