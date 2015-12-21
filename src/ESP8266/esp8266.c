/*
 * esp8266.c
 *
 *  Created on: Dec 20, 2015
 *      Author: Jacob
 */

#include "esp8266.h"

void esp_GPIO_Init();

void ESP_Init(USART_TypeDef *usart, uint32_t baud)
{
	USART_StartInit(usart, baud);
	esp_GPIO_Init();
}


void esp_GPIO_Init()
{
	//ESP Control pin (CH_PD) config
	GPIO_InitTypeDef ESP8266_Control_Config; //Does not include USART thats taken care of with USART
	ESP8266_Control_Config.GPIO_Speed = GPIO_Speed_10MHz;
	ESP8266_Control_Config.GPIO_Mode = GPIO_Mode_Out_PP;
	ESP8266_Control_Config.GPIO_Pin = ESP_CHPD_PIN;
	GPIO_Init(ESP_CHPD_PORT, &ESP8266_Control_Config);
}

void ESP_On()
{
	ESP_CHPD_PORT->BSRR = ESP_CHPD_PIN;
}

void ESP_Off()
{
	ESP_CHPD_PORT->BRR = ESP_CHPD_PIN;
}
