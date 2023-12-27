#ifndef __MyUART_H
#define __MyUART_H

void UART0_Init(void);
void NVIC_Init(void);
void Serial_SendString(char *String);
void Serial_SendArray(uint8_t *Array, uint16_t Length);
void Send_Byte(uint16_t Byte);
void Serial_SendNumber(uint32_t Number, uint8_t Length);
void Serial_Printf(char *format, ...);

#endif
