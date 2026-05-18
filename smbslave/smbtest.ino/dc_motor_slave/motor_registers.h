#ifndef SMBSLAVE_MOTOR_REGISTERS_H
#define SMBSLAVE_MOTOR_REGISTERS_H

#include <Arduino.h>

constexpr uint8_t REG_SPEED     = 0; // 0-255
constexpr uint8_t REG_DIRECTION = 1; // 0 = forward, 1 = reverse
constexpr uint8_t REG_CURRENT   = 2;
constexpr uint8_t REG_RPM_L     = 3;
constexpr uint8_t REG_RPM_H     = 4;
constexpr uint8_t BRAKE         = 5; // 1 = brake

#endif // SMBSLAVE_MOTOR_REGISTERS_H