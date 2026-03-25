#ifndef SMB_H
#define SMB_H

#include <Wire.h>

/**
 * @def I2C_NUM_REGISTERS
 * @brief Number of registers exposed over I2C.
 */
#define I2C_NUM_REGISTERS 16

/**
 * @def I2C_READ_MAX_LEN
 * @brief Maximum number of bytes that can be read in a single I2C transaction.
 */
#define I2C_READ_MAX_LEN 4

/**
 * @class Smb
 * @brief Simple SMBus/I2C slave register interface.
 *
 * This class implements a basic register-based I2C (SMBus-like) interface.
 * A fixed number of registers are exposed to an I2C master. 
 */
class Smb
{
public:
  /**
   * @brief Initialize the I2C interface as a slave.
   *
   * Configures the library with the given slave address.
   *
   * @param slaveAddr 7-bit I2C slave address.
   */
  void begin(uint8_t slaveAddr);

  /**
   * @brief Read an 8-bit value from a register.
   *
   * @param reg Register index.
   * @return Value stored in the register.
   */
  uint8_t readByteRegister(uint8_t reg);

  /**
   * @brief Read a 16-bit value from a register.
   *
   * Reads two consecutive bytes starting at the given register index.
   *
   * @param reg Register index.
   * @return 16-bit value composed from two registers.
   */
  uint16_t readWordRegister(uint8_t reg);

  /**
   * @brief Write an 8-bit value to a register.
   *
   * @param reg Register index.
   * @param value Value to store.
   */
  void writeByteRegister(uint8_t reg, uint8_t value);

  /**
   * @brief Write a 16-bit value to a register.
   *
   * Writes the value into two consecutive registers.
   *
   * @param reg Register index.
   * @param value 16-bit value to store.
   */
  void writeWordRegister(uint8_t reg, uint16_t value);

private:
  static uint8_t registerList[I2C_NUM_REGISTERS];
  static uint8_t regIdx;
  static void handleReceive(int numBytes);
  static void handleRequest();
};

/**
 * @brief Global Smb instance.
 *
 * Allows easy access without manual instantiation.
 */
extern Smb smb;

#endif
