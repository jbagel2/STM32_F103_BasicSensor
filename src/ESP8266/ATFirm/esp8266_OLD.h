
/********************************************************
 * Author: Jacob Pagel
 * Date: 03/05/2015
 * esp8266.h (esp8266 wifi library include file)
 ********************************************************/

#ifndef _ESP8266_H_
#define _ESP8266_H_

#include "stm32f10x_usart.h"
#include <stdio.h>
#include "string.h"
#include "time.h"
//#include "globalDefines.h"
#include "stm32f10x_gpio.h"
#include "DHT22/dht22.h"

volatile uint8_t waitingForReponse;
volatile uint8_t OKFound;
volatile uint8_t ERRORFound;

//#define ESP_ResponseTimeout_ms 3000
//#define ESP_USART USART3


const typedef enum {ESP_RESPONSE_READY,ESP_RESPONSE_Link,ESP_RESPONSE_Unlink,ESP_RESPONSE_OK,
					ESP_RESPONSE_SEND_OK,ESP_RESPONSE_IPD,ESP_RESPONSE_ERROR,
					ESP_RESPONSE_Wrong_Syntax,ESP_RESPONSE_BUSY_P,ESP_RESPONSE_BUSY_INET}ESP_Messages;

#ifdef __USE_ESP_AT__

#endif

typedef enum
{
	OPEN,
	WEP,
	WPA_PSK,
	WPA2_PSK,
	WPA_WPA2_PSK
}Available_Encyption;

//TYPEDEF DECLARATIONS
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

extern const char *ATCommandsArray[20];

#define WIFI_COMMAND(commandEnum) (ATCommandsArray[(commandEnum)])


void Wifi_Init();
void Wifi_OFF();
void Wifi_ON();

//void Wifi_ReadyWaitForAnswer();
//void Wifi_WaitForAnswer();
//void Wifi_CloseConnection(uint8_t connectionNum);
//void Wifi_SendCustomCommand(char *customMessage);
//void Wifi_SendCustomCommand_External_Wait(char *customMessage);
//void Wifi_SendCommand(Wifi_Commands command );
void Wifi_CheckDMABuff_ForCIFSRData();
uint8_t Wifi_CheckDMABuff_ForReady();
IPD_Data Wifi_CheckDMABuff_ForIPDData(DHT22_Data *Current_DHT22_Reading);
void ConnectToAP(char *apName, char *password);
void StartLocalAP(char *SSID, char *password, uint8_t channel, Available_Encyption encypt);


#endif //_ESP8266_H_
