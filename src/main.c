/**
*****************************************************************************
**
**  File        : main.c
**
**  Abstract    : main function.
**
**  Functions   : main
**
**  Environment : Atollic TrueSTUDIO/STM32
**                STMicroelectronics STM32F10x Standard Peripherals Library
**
**  Distribution: The file is distributed "as is", without any warranty
**                of any kind.
**
**  (c)Copyright Atollic AB.
**  You may use this file as-is or modify it according to the needs of your
**  project. This file may only be built (assembled or compiled and linked)
**  using the Atollic TrueSTUDIO(R) product. The use of this file together
**  with other tools than Atollic TrueSTUDIO(R) is not permitted.
**
*****************************************************************************
*/

/* Includes */
#include <stddef.h>
#include "stm32f10x.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_rcc.h"
#include "Time/time.h"
#include "DHT22/dht22.h"
#include "Motion/Motion.h"
#include "ESP8266/esp8266.h"

/* Private macro */
#define TEST_LED_PIN GPIO_Pin_13
#define TEST_LED_PORT GPIOC
#define DHT_UPDATE_INTERVAL 10000
/* Public variables */
volatile uint8_t Motion_Detected = 0;

/* Private variables */
 USART_InitTypeDef USART_InitStructure;
 GPIO_InitTypeDef GPIO_InitStructure;
 DHT22_Data Current_DHT22_Reading;
 DHT22_Data Previous_DHT22_Reading;
 uint32_t lastDHT22update = 0;
/* Private function prototypes */
/* Private functions */

/**
**===========================================================================
**
**  Abstract: main program
**
**===========================================================================
*/
int main(void)
{

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);

	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13;
	GPIO_Init(GPIOC, &GPIO_InitStructure);

	Init_Time(MILLISEC,64);
	DHT22_Init();
	Motion_Init();
	ESP_Init(USART3, 9600);
  /* Infinite loop */
  while (1)
  {
	  if((Millis() - lastDHT22update) >= DHT_UPDATE_INTERVAL)
	      	{

	      		lastDHT22update = Millis();
	      		DHT22_Start_Read(&Current_DHT22_Reading, &Previous_DHT22_Reading);

	      	}
	  if(Motion_Detected)
			{
				GPIOC->BSRR = GPIO_Pin_13;
				ESP_On();
			}
			else
			{
				GPIOC->BRR = GPIO_Pin_13;
				ESP_Off();
			}


  }
}



/*
 * Minimal __assert_func used by the assert() macro
 * */
void __assert_func(const char *file, int line, const char *func, const char *failedexpr)
{
  while(1)
  {}
}

/*
 * Minimal __assert() uses __assert__func()
 * */
void __assert(const char *file, int line, const char *failedexpr)
{
   __assert_func (file, line, NULL, failedexpr);
}

#ifdef USE_SEE
#ifndef USE_DEFAULT_TIMEOUT_CALLBACK
/**
  * @brief  Basic management of the timeout situation.
  * @param  None.
  * @retval sEE_FAIL.
  */
uint32_t sEE_TIMEOUT_UserCallback(void)
{
  /* Return with error code */
  return sEE_FAIL;
}
#endif
#endif /* USE_SEE */

