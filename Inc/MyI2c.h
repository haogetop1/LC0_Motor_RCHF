#ifndef __MyI2c_H
#define __MyI2c_H

#ifdef __cplusplus
extern "C" {
#endif
#include "fm33lc0xx.h"                  // Device header

#define  I2C_TIMEOUT   0x5FFFFU
#define STARTBIT    0
#define RESTARTBIT  1
#define STOPBIT     2

uint8_t I2C_Read_Bottom(uint8_t Device, uint16_t Addr, uint8_t AddrLen, uint8_t *Buf, uint8_t Len);
uint8_t I2C_Write_Bottom(uint8_t Device, uint16_t Addr, uint8_t AddrLen, uint8_t *Buf, uint8_t Len);
uint8_t I2C_Send_Bit(uint8_t BIT_def);
uint8_t I2C_Send_Byte(uint8_t x_byte);
uint8_t I2C_Receive_Byte(uint8_t *x_byte);

#ifdef __cplusplus
}
#endif

#endif
