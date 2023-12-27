#include "fm33lc0xx_fl.h"                  // Device header

#include "MyI2c.h"
#include <string.h>

#define I2CREAD     1   //I2C������
#define I2CWRITE    0   //I2Cд����

#define STARTBIT 0
#define RESTARTBIT 1
#define STOPBIT 2


/** @brief ����һλ
*	@param 0,1,2:��ʼλSTARTBIT���ظ���ʼλRESTARTBIT����ֹλSTOPBIT
*	@retval 0:�ɹ�
*
*/
uint8_t I2C_Send_Bit(uint8_t BIT_def)
{

    uint32_t counter =0;
	  uint32_t stopstatus,startstatus;

    switch(BIT_def)
    {
        case STARTBIT:
            FL_I2C_Master_EnableI2CStart(I2C);
				    do
						{
						    startstatus = FL_I2C_Master_IsActiveFlag_Start(I2C);
							  counter++;
						}while((startstatus != 0x01U) && (counter != I2C_TIMEOUT));

            break;

        case RESTARTBIT:
            FL_I2C_Master_EnableI2CRestart(I2C);
						do
						{
						    startstatus = FL_I2C_Master_IsActiveFlag_Start(I2C);
							  counter++;
						}while((startstatus != 0x01U) && (counter != I2C_TIMEOUT));
            break;

        case STOPBIT:
            FL_I2C_Master_EnableI2CStop(I2C);
						do
						{
						    stopstatus = FL_I2C_Master_IsActiveFlag_Stop(I2C);
							  counter++;
						}while((stopstatus != 0x01U) && (counter != I2C_TIMEOUT));
            break;

        default:
            break;
    }

    return 0; //ok

}

/** @brief I2C����һ���ֽ�
*
*
*
*/
uint8_t I2C_Send_Byte(uint8_t x_byte)
{

    FL_I2C_Master_WriteTXBuff(I2C, x_byte);//���͵�����Ĵ���

    while(!FL_I2C_Master_IsActiveFlag_TXComplete(I2C));

    FL_I2C_Master_ClearFlag_TXComplete(I2C);

    if(!FL_I2C_Master_IsActiveFlag_NACK(I2C))
    {
        return 0;
    }

    else
    {
        FL_I2C_Master_ClearFlag_NACK(I2C);
        return 1;
    }

}


/** @brief I2C���͵�ַ
*	@param �豸��
*	@param �豸��ַ
*	@param �豸��ַ����
*	@param Opt��1--����0--д
*	@retval 0���ɹ� 1��ʧ��
*/
uint8_t Sendaddr(uint8_t Device, uint16_t Addr, uint8_t AddrLen, uint8_t Opt)
{
    uint8_t result, Devi_Addr;

    Devi_Addr = Device;


    /*-------------- start bit ---------------*/
    result = I2C_Send_Bit(STARTBIT);  //������ʼλ

    if(result != 0) { return 1; }   //failure.

    /*-------------- disable read -------------*/
    FL_I2C_Master_DisableRX(I2C);
    /*-------------- device addr -------------*/
    result = I2C_Send_Byte(Devi_Addr);   //����������ַ

    if(result != 0) 
		{ return 2; }   //failure.

    /*--------------- data addr --------------*/
    if(AddrLen == 2)
    {
        result = I2C_Send_Byte(Addr >> 8); //�������ݵ�ַ��8λ

        if(result != 0) { return 3; }   //failure.
    }

    result = I2C_Send_Byte(Addr >> 0); //�������ݵ�ַ��8λ

    if(result != 0) { return 3; }   //failure.

    if(Opt == I2CREAD)   
    {
        result = I2C_Send_Bit(RESTARTBIT);   //��������ʼλ

        if(result != 0) { return 5; }   //failure.

        result = I2C_Send_Byte(Devi_Addr | 1); //����������ַ����ȡ

        if(result != 0) { return 5; }   //failure.
    }

    return 0; //ok
}



/** @brief I2C�����ֽ�����ʱ��
*
*
*	@retval 1--ʧ�ܣ�0--�ɹ�
*/
uint8_t I2C_Write_Bottom(uint8_t Device, uint16_t Addr, uint8_t AddrLen, uint8_t *Buf, uint8_t Len)
{
    uint8_t k, n, status;

    if(Len > 128) { return 0xFF; }//һ��������128�ֽ�

    for(k = 0; k < 3; k++) //ÿ�����д3��
    {
        status = 0;

        if(Sendaddr(Device, Addr, AddrLen, I2CWRITE))//�Ѱ�����ʼλ���豸��ַ�����ݵ�ַ
        {
            status = 1; //д��ʧ��
        }
        else
        {
            for(n = 0; n < Len; n++)//ѭ������Len���ֽ�
            {
                //����һ���ֽ�
                if(I2C_Send_Byte(Buf[n]))//д������
                {
                    status = 1;
                    break;
                } //д��ʧ��
            }
        }
         
		//����ֹͣλ
        if(I2C_Send_Bit(STOPBIT))
        { status = 1; }   //ʧ��

        if(status == 0) { break; }  //����ȷ
    }

    return(status);

}


/** @brief ������ʼ���豸��ַ�����
*
*
*
*/
uint8_t Wait_for_end(uint8_t Device)
{
		uint8_t result, Devi_Addr;
	  uint32_t counter =0;
    Devi_Addr = Device;
	  do
	  {
        I2C_Send_Bit(STARTBIT);      //������ʼλ
        result = I2C_Send_Byte(Devi_Addr);   //����������ַ
        I2C_Send_Bit(STOPBIT);   //����ֹͣλ
	    counter++;
    }while((result == 0x01U) && (counter != I2C_TIMEOUT));
    
		if(result == 0)//���õ�ַ�ɹ�, д���ڽ���
     { 
			 return 0; 
		 } 
    else
		{			
       return 1; //���õ�ַʧ��,��ʱ
		}
}




/** @brief I2C����һ���ֽ�
*
*
*
*/
uint8_t I2C_Receive_Byte(uint8_t *x_byte)
{
    //i2c en, rcen
    FL_I2C_Master_EnableRX(I2C);

    while(!FL_I2C_Master_IsActiveFlag_RXComplete(I2C));

    FL_I2C_Master_ClearFlag_RXComplete(I2C);
    *x_byte = FL_I2C_Master_ReadRXBuff(I2C);
    return 0;
}


/** @brief I2C���ܵ�ַ����ʱ��
*
*
*
*/
uint8_t I2C_Read_Bottom(uint8_t Device, uint16_t Addr, uint8_t AddrLen, uint8_t *Buf, uint8_t Len)
{
    uint8_t k, n, status;

    if(Len > 128) { return 0xFF; }//һ��������128�ֽ�

    for(k = 0; k < 3; k++) //ÿ������3��
    {
        status = 0;

        if(Sendaddr(Device, Addr, AddrLen, I2CREAD))//�Ѱ�����ʼλ���豸��ַ�����ݵ�ַ
        { status = 1; } //д��ʧ��

        else
        {
            for(n = 0; n < Len; n++)
            {
                if(n < (Len - 1))
                { FL_I2C_Master_SetRespond(I2C, FL_I2C_MASTER_RESPOND_ACK); }//�����һ���ֽ������ط�Ӧ��

                else
                { FL_I2C_Master_SetRespond(I2C, FL_I2C_MASTER_RESPOND_NACK); }//���һ���ֽڲ�Ӧ��

                //����һ���ֽ�
                if(I2C_Receive_Byte(Buf + n))
                {
                    status = 1;
                    break;
                }
								
            }
			
        }

        //����ֹͣλ
        if(I2C_Send_Bit(STOPBIT))
        { status = 1; }   //ʧ��
		
		if(status == 0) { break; }  //����ȷ
    }

    return(status);
}



