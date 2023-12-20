/**
  ****************************************************************************************************
  * @file    main.c
  * @author  FMSH Application Team
  * @brief   Header file of FL Module
  ****************************************************************************************************
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
  ****************************************************************************************************
  */

#include "main.h"
#include "fm33_assert.h"
#include "MyUART.h"
#include "FOC_kernal.h"

extern float voltage_power;

/**    
* Chip Series: FM33LC0xx;
* FL Version: v2.3;
* Project Name: LC0_Motor_RCHF;
* Project Version: v2.3.0.0;
* Project ID: 1734825908599566338;
* Create Date: 2023-12-13;
*/

  
int main(void)
{
	float angle_el=0;
	voltage_power=24;
    /* Initialize FL Driver Library */
    FL_Init();

    /* Configure the system clock */
    MF_Clock_Init();
    
   
    /* Initialize all configured peripherals */
    MF_Config_Init();

	//使能ATIM
    FL_ATIM_Enable(ATIM);
    //主控输出使能
    FL_ATIM_EnableALLOutput(ATIM);
	
	Serial_SendString("hello");
	
	

    while(1)
    {     
		SetPhaseVoltage(1.2,0,angle_el);    //uq<2.
		angle_el=angle_el+0.1;              //估计电角度
		

    }

}


