/*
 * esp8266.c
 *
 *  Created on: Dec 20, 2015
 *      Author: Jacob
 */

#include "esp8266.h"

volatile uint8_t waitingForReponse = 0;
volatile uint8_t OKFound = 0;
volatile uint8_t ERRORFound = 0;
volatile uint32_t TxWaitForResponse_TimeStmp = 0;

void _esp_GPIO_Init();

void ESP_Init(USART_TypeDef *usart, uint32_t baud)
{
	USART_StartInit(usart, baud);
	esp_GPIO_Init();
}


void _esp_GPIO_Init()
{
	//ESP Control pin (CH_PD) config
	GPIO_InitTypeDef ESP8266_Control_Config; //Does not include USART thats taken care of with USART lib
	ESP8266_Control_Config.GPIO_Speed = GPIO_Speed_2MHz;
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

void ESP_ReadyWaitForAnswer()
{
	TxWaitForResponse_TimeStmp = Millis();
	waitingForReponse = 1;

}

void ESP_WaitForAnswer()
{
	while(waitingForReponse == 1 && (Millis() - TxWaitForResponse_TimeStmp) < ESP_ResponseTimeout_ms);
	OKFound=0;
	ERRORFound=0;
}

char *WaitForAnswer_cmd_Buffer;
char *WaitForAnswer_ans_Buffer;
//TODO: Need To Change waiting String to be variable from implementation (AT vs NODEMCU_LUA)
void ESP_WaitForAnswerCMD(char *cmdToWaitFor, uint16_t cmdSize)
{

	while(waitingForReponse == 1 && (Millis() - TxWaitForResponse_TimeStmp) < ESP_ResponseTimeout_ms)
		{
		WaitForAnswer_cmd_Buffer = memmem(USART3_RxBuffer,RxBuffSize,cmdToWaitFor,cmdSize);
		if(strlen(WaitForAnswer_cmd_Buffer)>0)
		{
			if(WaitForAnswer_ans_Buffer = memmem(WaitForAnswer_cmd_Buffer,strlen(WaitForAnswer_cmd_Buffer),"OK\r\n",4))
			{
				ClearArray_Size(WaitForAnswer_cmd_Buffer, strlen(WaitForAnswer_cmd_Buffer));
				OKFound=1;
				waitingForReponse = 0;
			}
			//Check for OK or Error Message

		}

		};
	//OKFound=0;
	//ERRORFound=0;
}

char closeConnectionBuffer[15];
//TODO: Change close command to be implementation specific (AT vs NODE)
void ESP_CloseConnection(uint8_t connectionNum)
{
	sprintf(closeConnectionBuffer, "AT+CIPCLOSE=%d",connectionNum);
	Wifi_SendCustomCommand(closeConnectionBuffer);
}

void ESP_SendCustomCommand(char *customMessage)
{
			Wifi_SendCustomCommand_External_Wait(customMessage);

			Wifi_WaitForAnswer();
			//for (wi=0;wi<735000;wi++);
}

void ESP_SendCustomCommand_External_Wait(char *customMessage)
{
		while(*customMessage)
		{
			while(USART_GetFlagStatus(ESP_USART,USART_FLAG_TXE) == RESET);
			USART_SendData(ESP_USART,*customMessage++);
		}

		while(USART_GetFlagStatus(ESP_USART, USART_FLAG_TXE) == RESET);
			USART_SendData(ESP_USART,'\r');

		while(USART_GetFlagStatus(ESP_USART, USART_FLAG_TXE) == RESET);
			Wifi_ReadyWaitForAnswer();
			USART_SendData(ESP_USART,'\n');

			//Wifi_WaitForAnswer();
			//for (wi=0;wi<735000;wi++);
}

//TODO: Update to be implementation agnostic (AT vs NODE)
void ESP_SendCommand(ESP_Commands command )
{
	const char *commandToSend = ATCommandsArray[command];

	while(*commandToSend)
	{
		while(USART_GetFlagStatus(ESP_USART,USART_FLAG_TXE) == RESET);
		USART_SendData(ESP_USART,*commandToSend++);
	}
	Wifi_ReadyWaitForAnswer();

	while(USART_GetFlagStatus(ESP_USART, USART_FLAG_TXE) == RESET);
	USART_SendData(ESP_USART,'\r');

	//Wifi_ReadyWaitForAnswer();
	while(USART_GetFlagStatus(ESP_USART, USART_FLAG_TXE) == RESET);

	USART_SendData(ESP_USART,'\n');

	if(command == WIFI_GET_CURRENT_IP)
	{
		Wifi_WaitForAnswerCMD("OK\r\n", 4);
	}
	else
	{
		Wifi_WaitForAnswerCMD(ATCommandsArray[command], strlen(ATCommandsArray[command]));
	}
}

char *IPD_Processing_buf;
char *ConnectNum;
//TODO: UPDATE TO BE PLATFORM AGNOSTIC or call specific implementation based on
// defined variable. (__AT__ or __NODE__)
//Breaks the IPD message into a proper request object
IPD_Data ProcessIPD_Data(char *IPD_Buffer)
{

	IPD_Data thisIPDMessage;

	strtok(IPD_Buffer,",");

	ConnectNum = strtok(NULL,",");
	thisIPDMessage.ConnectionNum = atoi(ConnectNum);

	thisIPDMessage.DataSize = strtok(NULL,":");
	//TODO: Probably need to add a check to make sure actual datasize matches expected..

	thisIPDMessage.RequestType = strtok(NULL," ");

	thisIPDMessage.URI = strtok(NULL," ");

	strtok(NULL,"\r\n");

	thisIPDMessage.Headers = strtok(NULL,"{");

	thisIPDMessage.Body = strtok(NULL,"}");
	return thisIPDMessage;

}
