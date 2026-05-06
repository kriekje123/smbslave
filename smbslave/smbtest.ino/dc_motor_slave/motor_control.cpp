#include "motor_control.h"
#include "motor_registers.h"
#include "smb.h"
#include <Arduino.h>

constexpr uint8_t ENABLE_PIN = PD0;
constexpr uint8_t BRAKE_PIN = PD1;
constexpr uint8_t MODE_PIN = PD2;
constexpr uint8_t DIRECTION_PIN = PD3;

static void setMotorPWM(uint8_t pwm)
{
    analogWrite(ENABLE_PIN, pwm);
}

static void setMotorDirection(uint8_t direction)
{
        //Richting instellen
    if(direction == 0){
        digitalWrite(DIRECTION_PIN, HIGH);
    }
    else if(direction == 1){
        digitalWrite(DIRECTION_PIN, LOW);
    }
	else{
		Serial.println("ERROR: Invalid direction value: ");
		Serial.println(direction);
		Serial.println("\nOnly 0 or 1 are valid direction values. (0 = forward, 1 = reverse)");
	}
}

void motorInit()
{
  pinMode(DIRECTION_PIN, OUTPUT);
  pinMode(ENABLE_PIN, OUTPUT);

    smb.writeByteRegister(REG_SPEED, 0);
    smb.writeByteRegister(REG_DIRECTION, 0);
    smb.writeByteRegister(REG_CURRENT, 0);
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