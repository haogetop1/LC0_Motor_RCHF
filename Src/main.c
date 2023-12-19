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
    /* Initialize FL Driver Library */
    FL_Init();

    /* Configure the system clock */
    MF_Clock_Init();
    
   
    /* Initialize all configured peripherals */
    MF_Config_Init();

	//ʹ��ATIM
    FL_ATIM_Enable(ATIM);
    //�������ʹ��
    FL_ATIM_EnableALLOutput(ATIM);
	
	Serial_SendString("hello");
	
	
//	FL_ATIM_WriteCompareCH2(ATIM,50);
//	FL_ATIM_WriteCompareCH3(ATIM,50);
    while(1)
    {     
		FL_ATIM_WriteCompareCH1(ATIM,10);//����ռ�ձ�Ϊ10%
		FL_ATIM_WriteCompareCH2(ATIM,0);
		FL_ATIM_WriteCompareCH3(ATIM,0);
		FL_DelayMs(8);
		
		FL_ATIM_WriteCompareCH1(ATIM,0);
		FL_ATIM_WriteCompareCH2(ATIM,10);//����ռ�ձ�Ϊ10%
		FL_ATIM_WriteCompareCH3(ATIM,0);
		FL_DelayMs(8);
		
		FL_ATIM_WriteCompareCH1(ATIM,0);
		FL_ATIM_WriteCompareCH2(ATIM,0);
		FL_ATIM_WriteCompareCH3(ATIM,10);//����ռ�ձ�Ϊ10%
		FL_DelayMs(8);
    }

}


