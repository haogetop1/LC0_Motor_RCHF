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
    //�����жϴ���
    if((FL_ENABLE == FL_UART_IsEnabledIT_RXBuffFull(UART0))
            && (FL_SET == FL_UART_IsActiveFlag_RXBuffFull(UART0)))
    {
        //�ж�ת�����յ�������
        RxData = FL_UART_ReadRXBuff(UART0);//�����жϱ�־��ͨ����ȡrxreg�Ĵ������
    }

    //�����жϴ���
    if((FL_ENABLE == FL_UART_IsEnabledIT_TXShiftBuffEmpty(UART0))
            && (FL_SET == FL_UART_IsActiveFlag_TXShiftBuffEmpty(UART0)))
    {
        //�����жϱ�־��ͨ��дtxreg�Ĵ��������txifд1���
        //����ָ�����ȵ�����

        FL_UART_ClearFlag_TXShiftBuffEmpty(UART0);  //��������жϱ�־		
		FL_UART_DisableIT_TXShiftBuffEmpty(UART0);
				
    }
}
