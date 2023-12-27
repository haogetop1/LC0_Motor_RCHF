/**
******************************************************************************
* @file           : mf_config.c
* @brief          : MCU FUNCTION CONFIG               
******************************************************************************
* @attention
*
* Copyright (c) [2021] [Fudan Microelectronics]
* THIS SOFTWARE is licensed under Mulan PSL v2.
* can use this software according to the terms and conditions of the Mulan PSL v2.
* You may obtain a copy of Mulan PSL v2 at:
*          http://license.coscl.org.cn/MulanPSL2
* THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND, 
* EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT, 
* MERCHANTABILITY OR FIT FOR A PARTICULAR PURPOSE.
* See the Mulan PSL v2 for more details.
*
******************************************************************************
*/

/* Includes ------------------------------------------------------------------*/
#include "mf_config.h"

/* Private function prototypes -----------------------------------------------*/

 
/**
  * @brief  ATIM_TimerBase Initialization function
  * @param  void
  * @retval None
  */
void MF_ATIM_TimerBase_Init(void)
{
    FL_ATIM_InitTypeDef    TimerBase_InitStruct;

    TimerBase_InitStruct.clockSource = FL_RCC_ATIM_CLK_SOURCE_APB2CLK;
    TimerBase_InitStruct.prescaler = 64-1;
    TimerBase_InitStruct.counterMode = FL_ATIM_COUNTER_DIR_UP;
    TimerBase_InitStruct.autoReload = 100-1;
    TimerBase_InitStruct.autoReloadState = FL_ENABLE;
    TimerBase_InitStruct.clockDivision = FL_ATIM_CLK_DIVISION_DIV1;
    TimerBase_InitStruct.repetitionCounter = 0;

    FL_ATIM_Init(ATIM, &TimerBase_InitStruct);    
}
 
/**
  * @brief  ATIM_Channel1 Initialization function
  * @param  void
  * @retval None
  */
void MF_ATIM_Channel1_Init(uint16_t duty_value)
{
    FL_GPIO_InitTypeDef    GPIO_InitStruct;

    FL_ATIM_OC_InitTypeDef    ATIM_InitStruct;

    /* PB2 ATIM_CH1N */ 
    GPIO_InitStruct.pin = FL_GPIO_PIN_2;
    GPIO_InitStruct.mode = FL_GPIO_MODE_DIGITAL;
    GPIO_InitStruct.outputType = FL_GPIO_OUTPUT_PUSHPULL;
    GPIO_InitStruct.pull = FL_DISABLE;
    GPIO_InitStruct.remapPin = FL_ENABLE;
    FL_GPIO_Init(GPIOB, &GPIO_InitStruct);

    /* PB4 ATIM_CH1 */ 
    GPIO_InitStruct.pin = FL_GPIO_PIN_4;
    GPIO_InitStruct.mode = FL_GPIO_MODE_DIGITAL;
    GPIO_InitStruct.outputType = FL_GPIO_OUTPUT_PUSHPULL;
    GPIO_InitStruct.pull = FL_DISABLE;
    GPIO_InitStruct.remapPin = FL_DISABLE;
    FL_GPIO_Init(GPIOB, &GPIO_InitStruct);

    ATIM_InitStruct.OCMode = FL_ATIM_OC_MODE_PWM1;
    ATIM_InitStruct.OCState = FL_ENABLE;
    ATIM_InitStruct.OCNState = FL_ENABLE;
    ATIM_InitStruct.OCPolarity = FL_ATIM_OC_POLARITY_NORMAL;
    ATIM_InitStruct.OCNPolarity = FL_ATIM_OCN_POLARITY_NORMAL;
    ATIM_InitStruct.OCFastMode = FL_DISABLE;
    ATIM_InitStruct.OCPreload = FL_DISABLE;
    ATIM_InitStruct.compareValue = duty_value;
    ATIM_InitStruct.OCIdleState = FL_ATIM_OC_IDLE_STATE_LOW;
    ATIM_InitStruct.OCETRFStatus = FL_DISABLE;
    ATIM_InitStruct.OCNIdleState = FL_ATIM_OCN_IDLE_STATE_LOW;

    FL_ATIM_OC_Init(ATIM, FL_ATIM_CHANNEL_1, &ATIM_InitStruct);    
}
 


/**
  * @brief  ATIM_Channel2 Initialization function
  * @param  void
  * @retval None
  */
void MF_ATIM_Channel2_Init(uint16_t duty_value)
{
    FL_GPIO_InitTypeDef    GPIO_InitStruct;

    FL_ATIM_OC_InitTypeDef    ATIM_InitStruct;

    /* PB3 ATIM_CH2N */ 
    GPIO_InitStruct.pin = FL_GPIO_PIN_3;
    GPIO_InitStruct.mode = FL_GPIO_MODE_DIGITAL;
    GPIO_InitStruct.outputType = FL_GPIO_OUTPUT_PUSHPULL;
    GPIO_InitStruct.pull = FL_DISABLE;
    GPIO_InitStruct.remapPin = FL_ENABLE;
    FL_GPIO_Init(GPIOB, &GPIO_InitStruct);

    /* PB5 ATIM_CH2 */ 
    GPIO_InitStruct.pin = FL_GPIO_PIN_5;
    GPIO_InitStruct.mode = FL_GPIO_MODE_DIGITAL;
    GPIO_InitStruct.outputType = FL_GPIO_OUTPUT_PUSHPULL;
    GPIO_InitStruct.pull = FL_DISABLE;
    GPIO_InitStruct.remapPin = FL_DISABLE;
    FL_GPIO_Init(GPIOB, &GPIO_InitStruct);

    ATIM_InitStruct.OCMode = FL_ATIM_OC_MODE_PWM1;
    ATIM_InitStruct.OCState = FL_ENABLE;
    ATIM_InitStruct.OCNState = FL_ENABLE;
    ATIM_InitStruct.OCPolarity = FL_ATIM_OC_POLARITY_NORMAL;
    ATIM_InitStruct.OCNPolarity = FL_ATIM_OCN_POLARITY_NORMAL;
    ATIM_InitStruct.OCFastMode = FL_DISABLE;
    ATIM_InitStruct.OCPreload = FL_DISABLE;
    ATIM_InitStruct.compareValue = duty_value;
    ATIM_InitStruct.OCIdleState = FL_ATIM_OC_IDLE_STATE_LOW;
    ATIM_InitStruct.OCETRFStatus = FL_DISABLE;
    ATIM_InitStruct.OCNIdleState = FL_ATIM_OCN_IDLE_STATE_LOW;

    FL_ATIM_OC_Init(ATIM, FL_ATIM_CHANNEL_2, &ATIM_InitStruct);    
}
 
/**
  * @brief  ATIM_Channel3 Initialization function
  * @param  void
  * @retval None
  */
void MF_ATIM_Channel3_Init(uint16_t duty_value)
{
    FL_GPIO_InitTypeDef    GPIO_InitStruct;

    FL_ATIM_OC_InitTypeDef    ATIM_InitStruct;

    /* PB6 ATIM_CH3 */ 
    GPIO_InitStruct.pin = FL_GPIO_PIN_6;
    GPIO_InitStruct.mode = FL_GPIO_MODE_DIGITAL;
    GPIO_InitStruct.outputType = FL_GPIO_OUTPUT_PUSHPULL;
    GPIO_InitStruct.pull = FL_DISABLE;
    GPIO_InitStruct.remapPin = FL_DISABLE;
    FL_GPIO_Init(GPIOB, &GPIO_InitStruct);

    /* PB8 ATIM_CH3N */ 
    GPIO_InitStruct.pin = FL_GPIO_PIN_8;
    GPIO_InitStruct.mode = FL_GPIO_MODE_DIGITAL;
    GPIO_InitStruct.outputType = FL_GPIO_OUTPUT_PUSHPULL;
    GPIO_InitStruct.pull = FL_DISABLE;
    GPIO_InitStruct.remapPin = FL_ENABLE;
    FL_GPIO_Init(GPIOB, &GPIO_InitStruct);

    ATIM_InitStruct.OCMode = FL_ATIM_OC_MODE_PWM1;
    ATIM_InitStruct.OCState = FL_ENABLE;
    ATIM_InitStruct.OCNState = FL_ENABLE;
    ATIM_InitStruct.OCPolarity = FL_ATIM_OC_POLARITY_NORMAL;
    ATIM_InitStruct.OCNPolarity = FL_ATIM_OCN_POLARITY_NORMAL;
    ATIM_InitStruct.OCFastMode = FL_DISABLE;
    ATIM_InitStruct.OCPreload = FL_DISABLE;
    ATIM_InitStruct.compareValue = duty_value;
    ATIM_InitStruct.OCIdleState = FL_ATIM_OC_IDLE_STATE_LOW;
    ATIM_InitStruct.OCETRFStatus = FL_DISABLE;
    ATIM_InitStruct.OCNIdleState = FL_ATIM_OCN_IDLE_STATE_LOW;

    FL_ATIM_OC_Init(ATIM, FL_ATIM_CHANNEL_3, &ATIM_InitStruct);    
}

/**
  * @brief  I2C_MASTER Initialization function
  * @param  void
  * @retval None
  */
void MF_I2C_MASTER_Init(void)
{
    FL_GPIO_InitTypeDef    GPIO_InitStruct;

    FL_I2C_MasterMode_InitTypeDef    I2C_InitStruct;

    /* PA11 I2C_SCL */ 
    GPIO_InitStruct.pin = FL_GPIO_PIN_11;
    GPIO_InitStruct.mode = FL_GPIO_MODE_DIGITAL;
    GPIO_InitStruct.outputType = FL_GPIO_OUTPUT_PUSHPULL;
    GPIO_InitStruct.pull = FL_DISABLE;
    GPIO_InitStruct.remapPin = FL_DISABLE;
    FL_GPIO_Init(GPIOA, &GPIO_InitStruct);

    /* PA12 I2C_SDA */ 
    GPIO_InitStruct.pin = FL_GPIO_PIN_12;
    GPIO_InitStruct.mode = FL_GPIO_MODE_DIGITAL;
    GPIO_InitStruct.outputType = FL_GPIO_OUTPUT_PUSHPULL;
    GPIO_InitStruct.pull = FL_DISABLE;
    GPIO_InitStruct.remapPin = FL_DISABLE;
    FL_GPIO_Init(GPIOA, &GPIO_InitStruct);

    I2C_InitStruct.clockSource = FL_RCC_I2C_CLK_SOURCE_RCHF;
    I2C_InitStruct.baudRate = 40000;

    FL_I2C_MasterMode_Init(I2C, &I2C_InitStruct); 

}
 
/**
  * @brief  UART0 Initialization function
  * @param  void
  * @retval None
  */
void MF_UART0_Init(void)
{
    FL_GPIO_InitTypeDef    GPIO_InitStruct;

    FL_UART_InitTypeDef    UART0_InitStruct;

    /* PA13 UART0_RX */ 
    GPIO_InitStruct.pin = FL_GPIO_PIN_13;
    GPIO_InitStruct.mode = FL_GPIO_MODE_DIGITAL;
    GPIO_InitStruct.outputType = FL_GPIO_OUTPUT_PUSHPULL;
    GPIO_InitStruct.pull = FL_DISABLE;
    GPIO_InitStruct.remapPin = FL_DISABLE;
    FL_GPIO_Init(GPIOA, &GPIO_InitStruct);

    /* PA14 UART0_TX */ 
    GPIO_InitStruct.pin = FL_GPIO_PIN_14;
    GPIO_InitStruct.mode = FL_GPIO_MODE_DIGITAL;
    GPIO_InitStruct.outputType = FL_GPIO_OUTPUT_PUSHPULL;
    GPIO_InitStruct.pull = FL_DISABLE;
    GPIO_InitStruct.remapPin = FL_DISABLE;
    FL_GPIO_Init(GPIOA, &GPIO_InitStruct);

    UART0_InitStruct.clockSrc = FL_RCC_UART0_CLK_SOURCE_APB1CLK;
    UART0_InitStruct.baudRate = 115200;
    UART0_InitStruct.dataWidth = FL_UART_DATA_WIDTH_8B;
    UART0_InitStruct.stopBits = FL_UART_STOP_BIT_WIDTH_1B;
    UART0_InitStruct.parity = FL_UART_PARITY_EVEN;
    UART0_InitStruct.transferDirection = FL_UART_DIRECTION_TX_RX;

    FL_UART_Init(UART0, &UART0_InitStruct);    
}

/**
  * @brief  HFDET_IRQHandler
  * @param  void
  * @retval None
  */
void HFDET_IRQHandler(void)
{
    //停振检测中断处理
    if((FL_FDET_IsEnabledIT_XTHFFail() == 0x01UL)
        && (FL_FDET_IsActiveFlag_XTHFFail() == 0x01UL))
    {
        FL_FDET_ClearFlag_XTHFFail();
        /*应用处理逻辑*/
    }
}


/**
  * @brief  Clock Initialization.
  * @retval None
  */
void MF_Clock_Init(void)
{
    /* Initial Low Speed Clock */
    FL_RCC_SetLSCLKClockSource(FL_RCC_LSCLK_CLK_SOURCE_LPOSC);

    /* Initial RCHF */
    FL_RCC_RCHF_SetFrequency(FL_RCC_RCHF_FREQUENCY_8MHZ);
    FL_RCC_RCHF_Enable();

    /* Initial PLL */
    FL_RCC_PLL_Disable();
    FL_RCC_PLL_SetClockSource(FL_RCC_PLL_CLK_SOURCE_RCHF);
    FL_RCC_PLL_SetPrescaler(FL_RCC_PLL_PSC_DIV8);
    FL_RCC_PLL_WriteMultiplier(63);    /* 输出64MHz */
    FL_RCC_PLL_SetOutputMultiplier(FL_RCC_PLL_OUTPUT_X1);
    FL_RCC_PLL_Enable();
    while(FL_RCC_IsActiveFlag_PLLReady() != FL_SET);

    /* Initial System Clock */
    FL_FLASH_SetReadWait(FLASH, FL_FLASH_READ_WAIT_2CYCLE);    /* 设置FLASH读等待为 2 个周期 */
    FL_RCC_SetSystemClockSource(FL_RCC_SYSTEM_CLK_SOURCE_PLL);    /* 设置系统主时钟为 PLL */
    FL_RCC_SetAHBPrescaler(FL_RCC_AHBCLK_PSC_DIV1);
    FL_RCC_SetAPB1Prescaler(FL_RCC_APB1CLK_PSC_DIV1);
    FL_RCC_SetAPB2Prescaler(FL_RCC_APB2CLK_PSC_DIV1);

    SystemCoreClockUpdate(); 
}

void MF_Config_Init(void)
{
    /* Initial ATIM */
    MF_ATIM_TimerBase_Init();
    MF_ATIM_Channel1_Init(0);//初始化时占空比为0
	MF_ATIM_Channel2_Init(0);
	MF_ATIM_Channel3_Init(0);

    /* Initial I2C */
    MF_I2C_MASTER_Init();

    /* Initial UART0 */
    MF_UART0_Init();
}


/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{

}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{ 

}
#endif /* USE_FULL_ASSERT */

/*************************(C) COPYRIGHT Fudan Microelectronics **** END OF FILE*************************/
