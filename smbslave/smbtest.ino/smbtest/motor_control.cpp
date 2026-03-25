#include "motor_control.h"
#include "motor_registers.h"
#include "smb.h"
#include <Arduino.h>

#define MOTOR_EN 5
#define MOTOR_PHASE 6
#define MOTOR_PWM_PIN 7

static void setMotorPWM(uint8_t pwm)
{
    analogWrite(MOTOR_PWM_PIN, pwm);
}

static void setMotorDirection(uint8_t direction)
{
    //Richting instellen
    if(direction == 0){
        digitalWrite(MOTOR_PHASE, HIGH);
    }
    else if(direction == 1){
        digitalWrite(MOTOR_PHASE, LOW);
    }
}

void motorInit()
{
  pinMode(MOTOR_EN, OUTPUT);
  pinMode(MOTOR_PHASE, OUTPUT);
  pinMode(MOTOR_PWM_PIN, OUTPUT);

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