/*
 * esp8266.h
 *
 *  Created on: Dec 20, 2015
 *      Author: Jacob
 *
 *      This small library is for the basic config and control that is irrelevent to the esp firmware
 */

#ifndef ESP8266_H_
#define ESP8266_H_

#include "stm32f10x_usart.h"
#include "stm32f10x_gpio.h"
#include "USART/usart.h"


/* ESP Config */
#define ESP_UART USART3
#define ESP_CHPD_PORT GPIOB
#define ESP_CHPD_PIN GPIO_Pin_7


/* ESP Public Functions */
void ESP_Init(USART_TypeDef *usart, uint32_t baud);
//void ESP_GPIO_Init();
void ESP_On();
void ESP_Off();


#endif /* ESP8266_H_ */
