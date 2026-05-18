#include "motor_control.h"
#include "motor_registers.h"
#include "smb.h"
#include "software_pwm.h"
#include <Arduino.h>

constexpr uint8_t ENABLE_PIN = PD0; //Verwacht PWM-signaal
constexpr uint8_t BRAKE_PIN = PD1; //HIGH = remmen
constexpr uint8_t MODE_PIN = PD2; //Bepaalt welke stroomrichting we monitoren.
constexpr uint8_t DIRECTION_PIN = PD3; //HIGH = vooruit

//Motor draaien met opgegeven snelheid (0-255)
static void setMotorPWM(uint8_t pwm)
{
    analogWrite(ENABLE_PIN, pwm);
}

}

//Bepaalt richting motor. (HIGH = vooruit, LOW = achteruit)
static void setMotorDirection(uint8_t direction)
{
        //Richting instellen
    if (direction == 0){
        digitalWrite(DIRECTION_PIN, HIGH);
    }
    else (direction == 1){
        digitalWrite(DIRECTION_PIN, LOW);
    }
}

//Stuurt de rem. (HIGH = remmen)
static void setMotorBrake(uint8_t brake)
{
    if (brake != 0)
    {
        digitalWrite(BRAKE_PIN, HIGH);
    }
    else
    {
        digitalWrite(BRAKE_PIN, LOW);
    }
}

//Initialiseert de registersen de pinnen.
void motorInit()
{
  softwarePwmInit();

  pinMode(DIRECTION_PIN, OUTPUT);
  pinMode(ENABLE_PIN, OUTPUT);
  pinMode(MODE_PIN, OUTPUT);
  pinMode(BRAKE_PIN, OUTPUT);

  smb.writeByteRegister(REG_SPEED, 0);
  smb.writeByteRegister(REG_DIRECTION, 0);
  smb.writeByteRegister(REG_CURRENT, 0);
  smb.writeWordRegister(REG_RPM_L, 0);
  smb.writeByteRegister(REG_BRAKE, 0);

  digitalWrite(MODE_PIN, LOW);
  digitalWrite(BRAKE_PIN, LOW);
  digitalWrite(DIRECTION_PIN, LOW);
  analogWrite(ENABLE_PIN, 0);
}

//Dit staat in loop() van dc_motor_slave.ino en bepaalt aan de hand van de registers de snelheid en richting.
void motorUpdate()
{
    uint8_t speed = smb.readByteRegister(REG_SPEED);
    uint8_t direction = smb.readByteRegister(REG_DIRECTION);
	uint8_t brake = smb.readByteRegister(REG_BRAKE);

    if (brake != 0)
    {
        setMotorPWM(0);
        setMotorBrake(1);
    }
    else
    {
        setMotorBrake(0);
        setMotorDirection(direction);
        setMotorPWM(speed);
    }
}
}