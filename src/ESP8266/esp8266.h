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

typedef enum
{
	WIFI_CHECK_MODULE_CONNECTION = 0,
	WIFI_CURRENT_STATUS, //Get current status
	WIFI_AP_LIST, // Get available AP's
	WIFI_FIRMWARE_VERSION, // Get current firmware version on ESP8266
	WIFI_GET_CURRENT_MODE, // Gets the current mode (Access Point, Station, both)
	WIFI_SET_MODE_BOTH_AP_ST, // Set Mode as both, Access Point, Station
	WIFI_JOIN_NONYA,
	WIFI_SHOW_CURRENT_CONNECTED_AP,
	WIFI_MODULE_RESET,
	WIFI_SET_MULTICONNECTION,
	WIFI_SET_BAUD_115200,
	WIFI_START_LOCAL_SERVER_PORT_80,
	WIFI_GET_CURRENT_IP,
	WIFI_SHOW_ACTIVE_CONNECTIONS,
	WIFI_LIST_CONNECTED_DEVICES_inAPModeOnly,
	WIFI_QUIT_CURRENT_AP,
	WIFI_START_ACCESS_POINT,
	WIFI_DISABLE_ECHO,
	WIFI_CLOSE_CONNECTION,
	WIFI_CLIENT_ONLY //No AP
}ESP_Commands;

typedef enum
{
	OPEN,
	WEP,
	WPA_PSK,
	WPA2_PSK,
	WPA_WPA2_PSK
}Available_Encyption;

typedef struct{
	uint8_t ConnectionNum;
	char *DataSize;
	char *RequestType; //ie.. POST, GET, PUT, DELETE
	char *URI; //ie.. /api/foo?id=123
	char *Headers;
	char *Body;
	uint8_t Valid;
}IPD_Data;

typedef struct{
 char *AccessPoint_IP;
 char *AccessPoint_MAC;
 char *Station_IP;
 char *Station_MAC;
 uint16_t ResetCount;
 uint32_t LastResetTime;

}ESP_Status;

#ifdef __ESP_AT__
extern const char *ATCommandsArray[20];
#define ESP_COMMAND(commandEnum) (ATCommandsArray[(commandEnum)])
#endif

#ifdef __ESP_NODE__
extern const char *NODECommandsArray[20];
#define ESP_COMMAND(commandEnum) (NODECommandsArray[(commandEnum)])
#endif

/* ESP Config */
#define ESP_USART USART3
#define ESP_CHPD_PORT GPIOB
#define ESP_CHPD_PIN GPIO_Pin_7


/* ESP Public Functions */
void ESP_Init(USART_TypeDef *usart, uint32_t baud);
//void ESP_GPIO_Init();
void ESP_On();
void ESP_Off();
void ESP_SendCommand(ESP_Commands command );
void ESP_WaitForAnswer();
void ESP_WaitForAnswerCMD(char *cmdToWaitFor, uint16_t cmdSize);
void ESP_CloseConnection(uint8_t connectionNum);
void ESP_SendCustomCommand(char *customMessage);
void ESP_SendCustomCommand_External_Wait(char *customMessage);
void ESP_SendCommand(ESP_Commands command );

#endif /* ESP8266_H_ */
