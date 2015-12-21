/*
 * usart.c
 *
 *  Created on: Dec 20, 2015
 *      Author: Jacob
 */

#include "usart.h"

Current_USART Active_USART;
GPIO_InitTypeDef Config_USART;

void usart_Config_CLK(USART_TypeDef *usart_num);
void usart_Config_GPIO(Current_USART *this_usart);

void USART_StartInit(USART_TypeDef *usart_num, uint32_t baud)
{
	if(usart_num == USART1)
	{
		Active_USART.USART_GPIO = USART1_PORT;
		Active_USART.Tx_Pin = USART1_TX;
		Active_USART.Tx_Pin = USART1_RX;
	}
	else if (usart_num == USART2) {
		Active_USART.USART_GPIO = USART2_PORT;
		Active_USART.Tx_Pin = USART2_TX;
		Active_USART.Tx_Pin = USART2_RX;
	}
	else if (usart_num == USART3) {
		Active_USART.USART_GPIO = USART3_PORT;
		Active_USART.Tx_Pin = USART3_TX;
		Active_USART.Tx_Pin = USART3_RX;
	}

	usart_Config_CLK(usart_num);
	usart_Config_GPIO(&Active_USART);
}

void usart_Config_CLK(USART_TypeDef *usart_num)
{
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);

		if(usart_num == USART3)
		{
			RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
			RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3, ENABLE);
		}
		else if (usart_num == USART2) {
			RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
			RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);
		}
		else if (usart_num == USART1){
			RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
			RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);
		}
}

void usart_Config_GPIO(Current_USART *this_usart)
{
	Config_USART.GPIO_Speed = GPIO_Speed_50MHz;
	Config_USART.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	Config_USART.GPIO_Pin = Active_USART.Rx_Pin;
	GPIO_Init(Active_USART.USART_GPIO, &Config_USART); // Saves above configuration to associated registers

	//--------------------------------------------

	//For TX Pin ---------------------------------
	Config_USART.GPIO_Mode = GPIO_Mode_AF_PP; // Alternate Function Push-Pull
	Config_USART.GPIO_Pin = Active_USART.Tx_Pin;
	GPIO_Init(Active_USART.USART_GPIO, &Config_USART);
}

void usart_Config_Interrupt()
{

}
