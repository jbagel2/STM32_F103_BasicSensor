/*
 * Motion.h
 *
 *  Created on: Dec 19, 2015
 *      Author: Jacob
 */

#ifndef MOTION_H_
#define MOTION_H_

#include "stm32f10x_gpio.h"
#include "stm32f10x_rcc.h"



#define MOTION_PIN GPIO_Pin_8
#define MOTION_PORT	GPIOB
#define MOTION_EXTI_Line EXTI_Line8
#define MOTION_PINSOURCE GPIO_PinSource8

/* External variables */
extern volatile uint8_t Motion_Detected;

// Public Motion Functions
void Motion_Init();
//void Motion_Detect_Handled();



#endif /* MOTION_H_ */
