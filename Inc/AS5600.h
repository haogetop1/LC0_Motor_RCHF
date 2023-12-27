#ifndef __BSP_AS5600_H
#define __BSP_AS5600_H

#include "fm33lc0xx.h"                  // Device header


//#define AS5600_I2C_HANDLE hi2c1

//#define I2C_TIME_OUT_BASE   10
//#define I2C_TIME_OUT_BYTE   1

/*
AS5600的地址0x36
*/

#define AS5600_RAW_ADDR    0x36
#define AS5600_ADDR        (AS5600_RAW_ADDR<<1)
#define AS5600_WRITE_ADDR  (AS5600_RAW_ADDR << 1)
#define AS5600_READ_ADDR   ((AS5600_RAW_ADDR << 1) | 1)


#define AS5600_RESOLUTION 4096 //12bit Resolution 

#define AS5600_RAW_ANGLE_REGISTER  0x0C  //寄存器高位地址


void bsp_as5600Init(void);
uint16_t bsp_as5600GetRawAngle(void);
float bsp_as5600GetAngle(void);

#endif /* __BSP_AS5600_H */
