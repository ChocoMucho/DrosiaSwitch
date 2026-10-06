/*
 * led_controller.c
 *
 *  Created on: Sep 9, 2026
 *      Author: vkcls
 */

#include "led_controller.h"
#include "main.h"
#include "defines.h"

void LED1_OnOff(OnOffState state)
{
	HAL_GPIO_WritePin(
			PB6_LED1_GPIO_Port,
			PB6_LED1_Pin,
			state == STATE_ON ? GPIO_PIN_SET : GPIO_PIN_RESET);
}

void LED2_OnOff(OnOffState state) {
	HAL_GPIO_WritePin(
			PB7_LED2_GPIO_Port,
			PB7_LED2_Pin,
			state == STATE_ON ? GPIO_PIN_SET : GPIO_PIN_RESET);
}
