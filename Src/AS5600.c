#include "AS5600.h"
#include "MyI2C.h"
#include "MyUART.h"

#define abs(x) ((x)>0?(x):-(x))
#define _2PI 6.28318530718

static float angle_data_prev; //上次位置
static float full_rotation_offset; //转过的整圈数


void bsp_as5600Init(void) {
  /* init i2c interface */
  
  /* init var */
  full_rotation_offset = 0;
  angle_data_prev = bsp_as5600GetRawAngle();
}


uint16_t bsp_as5600GetRawAngle(void) {
  uint16_t raw_angle;
  uint8_t buffer[2] = {0};
  uint8_t raw_angle_register = AS5600_RAW_ANGLE_REGISTER;
  uint8_t AddrLen=1,DataLen=2;
  static uint8_t status;
  

  status=I2C_Read_Bottom(AS5600_ADDR, raw_angle_register, AddrLen,buffer,DataLen);
  
  if(status)
  {
	Serial_SendString("fail\n");
  }
  else
  {
	Serial_Printf("succuss\n");
  }
  raw_angle = ((uint16_t)buffer[0] << 8) | (uint16_t)buffer[1];
  
  
  return raw_angle;
}

float bsp_as5600GetAngle(void) {
  float angle_data = bsp_as5600GetRawAngle();
  
  float d_angle = angle_data - angle_data_prev;
  if(abs(d_angle) > (0.8 * AS5600_RESOLUTION)) {
    full_rotation_offset += (d_angle > 0 ? -_2PI : _2PI);
  }
  angle_data_prev = angle_data;
  
  return (full_rotation_offset + (angle_data / (float)AS5600_RESOLUTION)*_2PI);
}

