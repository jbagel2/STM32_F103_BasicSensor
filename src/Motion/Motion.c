/*
 * Motion.c
 *
 *  Created on: Dec 19, 2015
 *      Author: Jacob
 *
 *      Motion pin/port/interrupt definitions in Motion.h
 */


#include "Motion/Motion.h"



void motion_CLK_Config();
void motion_GPIO_Config(GPIO_TypeDef *port, uint16_t pin);
void motion_NVIC_Config();
void motion_INT_Config();

/* Public Functions */
void Motion_Init()
{
	//printf("Initializing Motion");
	motion_CLK_Config();
	motion_GPIO_Config(MOTION_PORT, MOTION_PIN);
	motion_INT_Config();
	motion_NVIC_Config();
}


//void Motion_Detect_Handled()
//{
//	Motion_Detected = 0
//}

/* Private Functions */

void motion_CLK_Config()
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
}

void motion_NVIC_Config()
{
	NVIC_InitTypeDef motion_Interrupt;
	motion_Interrupt.NVIC_IRQChannel = EXTI9_5_IRQn;
	motion_Interrupt.NVIC_IRQChannelPreemptionPriority = 4;
	motion_Interrupt.NVIC_IRQChannelSubPriority = 4;
	motion_Interrupt.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&motion_Interrupt);

	NVIC_SetPriority(EXTI9_5_IRQn, NVIC_EncodePriority(4,15,4));
}

void motion_GPIO_Config(GPIO_TypeDef *port, uint16_t pin)
{

	GPIO_InitTypeDef motion_GPIO_TypeDef;
	motion_GPIO_TypeDef.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	motion_GPIO_TypeDef.GPIO_Speed = GPIO_Speed_2MHz;
	motion_GPIO_TypeDef.GPIO_Pin = pin;
	GPIO_Init(port, &motion_GPIO_TypeDef);

}

void motion_INT_Config()
{
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOB, MOTION_PINSOURCE);
	EXTI_InitTypeDef motion_Int_TypeDef;
	motion_Int_TypeDef.EXTI_Line = MOTION_EXTI_Line;
	motion_Int_TypeDef.EXTI_Mode = EXTI_Mode_Interrupt;
	motion_Int_TypeDef.EXTI_Trigger = EXTI_Trigger_Rising_Falling;
	motion_Int_TypeDef.EXTI_LineCmd = ENABLE;

	EXTI_Init(&motion_Int_TypeDef);
}

void EXTI9_5_IRQHandler()
{
	if(EXTI_GetITStatus(MOTION_EXTI_Line) != RESET)
	{
		if(GPIO_ReadInputDataBit(MOTION_PORT,MOTION_PIN))
		{
			Motion_Detected = 1;
		}
		else
		{
			Motion_Detected = 0;
		}

		EXTI_ClearITPendingBit(MOTION_EXTI_Line);
	}
}
