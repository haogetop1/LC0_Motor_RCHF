#include "fm33lc0xx_fl.h"
#include "stdarg.h"
#include "stdio.h"

uint8_t RxData;

void Send_Byte(uint8_t Byte)
{
	
	FL_UART_WriteTXBuff(UART0, Byte); 
	while(FL_UART_IsActiveFlag_TXBuffEmpty(UART0)!=FL_SET);
}

void Serial_SendArray(uint8_t *Array, uint16_t Length)
{
	uint16_t i;
	
	for(i=0;i<Length;i++)
	{
		Send_Byte(Array[i]);
	}
}

void Serial_SendString(char *String)
{
	uint8_t i;
	
	for(i=0;String[i]!='\0';i++)
	{
		
		Send_Byte(String[i]);
	}
}

uint32_t Serial_Pow(uint32_t X, uint32_t Y)
{
	uint32_t Result = 1;
	while (Y --)
	{
		Result *= X;
	}
	return Result;
}

void Serial_SendNumber(uint32_t Number, uint8_t Length)
{
	uint8_t i;
		
	for (i = 0; i < Length; i ++)
	{
		Send_Byte(Number / Serial_Pow(10, Length - i - 1) % 10 + '0');
	}
}

int fputc(int ch, FILE *f)
{
	Send_Byte(ch);
	return ch;
}

void Serial_Printf(char *format, ...)
{
	char String[100];
	va_list arg;
	va_start(arg, format);
	vsprintf(String, format, arg);
	va_end(arg);
	Serial_SendString(String);
}


void UART0_IRQHandler(void)
{
    //接收中断处理
    if((FL_ENABLE == FL_UART_IsEnabledIT_RXBuffFull(UART0))
            && (FL_SET == FL_UART_IsActiveFlag_RXBuffFull(UART0)))
    {
        //中断转发接收到的数据
        RxData = FL_UART_ReadRXBuff(UART0);//接收中断标志可通过读取rxreg寄存器清除
    }

    //发送中断处理
    if((FL_ENABLE == FL_UART_IsEnabledIT_TXShiftBuffEmpty(UART0))
            && (FL_SET == FL_UART_IsActiveFlag_TXShiftBuffEmpty(UART0)))
    {
        //发送中断标志可通过写txreg寄存器清除或txif写1清除
        //发送指定长度的数据

        FL_UART_ClearFlag_TXShiftBuffEmpty(UART0);  //清除发送中断标志		
		FL_UART_DisableIT_TXShiftBuffEmpty(UART0);
				
    }
}
