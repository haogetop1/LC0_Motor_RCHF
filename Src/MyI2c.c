#include "fm33lc0xx_fl.h"                  // Device header

#include "MyI2c.h"
#include <string.h>

#define I2CREAD     1   //I2C读操作
#define I2CWRITE    0   //I2C写操作

#define STARTBIT 0
#define RESTARTBIT 1
#define STOPBIT 2


/** @brief 发送一位
*	@param 0,1,2:起始位STARTBIT、重复起始位RESTARTBIT、终止位STOPBIT
*	@retval 0:成功
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

/** @brief I2C发送一个字节
*
*
*
*/
uint8_t I2C_Send_Byte(uint8_t x_byte)
{

    FL_I2C_Master_WriteTXBuff(I2C, x_byte);//发送到缓冲寄存器

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


/** @brief I2C发送地址
*	@param 设备码
*	@param 设备地址
*	@param 设备地址长度
*	@param Opt：1--读；0--写
*	@retval 0：成功 1：失败
*/
uint8_t Sendaddr(uint8_t Device, uint16_t Addr, uint8_t AddrLen, uint8_t Opt)
{
    uint8_t result, Devi_Addr;

    Devi_Addr = Device;


    /*-------------- start bit ---------------*/
    result = I2C_Send_Bit(STARTBIT);  //发送起始位

    if(result != 0) { return 1; }   //failure.

    /*-------------- disable read -------------*/
    FL_I2C_Master_DisableRX(I2C);
    /*-------------- device addr -------------*/
    result = I2C_Send_Byte(Devi_Addr);   //发送器件地址

    if(result != 0) 
		{ return 2; }   //failure.

    /*--------------- data addr --------------*/
    if(AddrLen == 2)
    {
        result = I2C_Send_Byte(Addr >> 8); //发送数据地址高8位

        if(result != 0) { return 3; }   //failure.
    }

    result = I2C_Send_Byte(Addr >> 0); //发送数据地址低8位

    if(result != 0) { return 3; }   //failure.

    if(Opt == I2CREAD)   
    {
        result = I2C_Send_Bit(RESTARTBIT);   //发送重起始位

        if(result != 0) { return 5; }   //failure.

        result = I2C_Send_Byte(Devi_Addr | 1); //发送器件地址，读取

        if(result != 0) { return 5; }   //failure.
    }

    return 0; //ok
}



/** @brief I2C发送字节完整时序
*
*
*	@retval 1--失败；0--成功
*/
uint8_t I2C_Write_Bottom(uint8_t Device, uint16_t Addr, uint8_t AddrLen, uint8_t *Buf, uint8_t Len)
{
    uint8_t k, n, status;

    if(Len > 128) { return 0xFF; }//一次最多操作128字节

    for(k = 0; k < 3; k++) //每遍最多写3次
    {
        status = 0;

        if(Sendaddr(Device, Addr, AddrLen, I2CWRITE))//已包含起始位、设备地址、数据地址
        {
            status = 1; //写入失败
        }
        else
        {
            for(n = 0; n < Len; n++)//循环发送Len个字节
            {
                //发送一个字节
                if(I2C_Send_Byte(Buf[n]))//写入数据
                {
                    status = 1;
                    break;
                } //写入失败
            }
        }
         
		//发送停止位
        if(I2C_Send_Bit(STOPBIT))
        { status = 1; }   //失败

        if(status == 0) { break; }  //读正确
    }

    return(status);

}


/** @brief 发送起始与设备地址后结束
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
        I2C_Send_Bit(STARTBIT);      //发送起始位
        result = I2C_Send_Byte(Devi_Addr);   //发送器件地址
        I2C_Send_Bit(STOPBIT);   //发送停止位
	    counter++;
    }while((result == 0x01U) && (counter != I2C_TIMEOUT));
    
		if(result == 0)//设置地址成功, 写周期结束
     { 
			 return 0; 
		 } 
    else
		{			
       return 1; //设置地址失败,超时
		}
}




/** @brief I2C接受一个字节
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


/** @brief I2C接受地址完整时序
*
*
*
*/
uint8_t I2C_Read_Bottom(uint8_t Device, uint16_t Addr, uint8_t AddrLen, uint8_t *Buf, uint8_t Len)
{
    uint8_t k, n, status;

    if(Len > 128) { return 0xFF; }//一次最多操作128字节

    for(k = 0; k < 3; k++) //每遍最多读3次
    {
        status = 0;

        if(Sendaddr(Device, Addr, AddrLen, I2CREAD))//已包含起始位、设备地址、数据地址
        { status = 1; } //写入失败

        else
        {
            for(n = 0; n < Len; n++)
            {
                if(n < (Len - 1))
                { FL_I2C_Master_SetRespond(I2C, FL_I2C_MASTER_RESPOND_ACK); }//非最后一个字节主机回发应答

                else
                { FL_I2C_Master_SetRespond(I2C, FL_I2C_MASTER_RESPOND_NACK); }//最后一个字节不应答

                //接受一个字节
                if(I2C_Receive_Byte(Buf + n))
                {
                    status = 1;
                    break;
                }
								
            }
			
        }

        //发送停止位
        if(I2C_Send_Bit(STOPBIT))
        { status = 1; }   //失败
		
		if(status == 0) { break; }  //读正确
    }

    return(status);
}



