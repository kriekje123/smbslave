#ifndef SMBSLAVE_MOTOR_CONTROL_H
#define SMBSLAVE_MOTOR_CONTROL_H
#include <Arduino.h>

void motorInit();
void motorUpdate();
void setMotorPWM();
void setMotorDirection(uint8_t direction);

#endif //SMBSLAVE_MOTOR_CONTROL_H