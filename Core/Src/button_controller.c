/*
 * button_controller.c
 *
 *  Created on: Sep 9, 2026
 *      Author: vkcls
 */

#include "button_controller.h"
#include "main.h"
#include "defines.h"
#include "heater_controller.h"

static volatile uint32_t button_events = 0U;

static volatile uint32_t pb0_tick = 0U;
static volatile uint32_t pb1_tick = 0U;
static volatile uint32_t pb2_tick = 0U;



uint32_t events;
uint32_t tick0;
uint32_t tick1;
uint32_t tick2;
uint32_t primask;

void ProcessButtonEvents() {
	primask = __get_PRIMASK();
	__disable_irq();

	events = button_events;
	button_events = 0;

	tick0 = pb0_tick;
	tick1 = pb1_tick;
	tick2 = pb2_tick;

	__set_PRIMASK(primask);

	if (events & BTN_EVENT_PB0) { // up
		//printf("EXTI 0\r\n");
		RisingTemper();
		/**/
	}

	if (events & BTN_EVENT_PB1) { // fix
		//printf("EXTI 1\r\n");
		FixTemper();
	}

	if (events & BTN_EVENT_PB2) { // down
		//printf("EXTI 2\r\n");
		//printf("Relay State Switch\r\n");
		DescentTemper();
	}
}

// Debouncing
void ButtonController_OnExti(uint16_t GPIO_Pin) {
	static uint32_t pb0_lastTick;
	static uint32_t pb1_lastTick;
	static uint32_t pb2_lastTick;

	uint32_t currentTick = HAL_GetTick();

	switch (GPIO_Pin) {
	case PB0_TEMP_SET_UP_Pin:

		if ((currentTick - pb0_lastTick) >= SWITCH_BOUNCE_TIME) {
			pb0_lastTick = currentTick;
			pb0_tick = currentTick;
			button_events |= BTN_EVENT_PB0;
		}
		break;

	case PB1_TEMP_SET_FIX_Pin:

		if ((currentTick - pb1_lastTick) >= SWITCH_BOUNCE_TIME) {
			pb1_lastTick = currentTick;
			pb1_tick = currentTick;
			button_events |= BTN_EVENT_PB1;
		}
		break;

	case PB2_TEMP_SET_DOWN_Pin:

		if ((currentTick - pb2_lastTick) >= SWITCH_BOUNCE_TIME) {
			pb2_lastTick = currentTick;
			pb2_tick = currentTick;
			button_events |= BTN_EVENT_PB2;
		}
		break;


	default:
		break;
	}
}

OnOffState GetSlideSWState(void)
{
	if(HAL_GPIO_ReadPin(PB12_START_SW_PIN_GPIO_Port, PB12_START_SW_PIN_Pin))
	{
		return STATE_ON;
	}
	else
	{
		return STATE_OFF;
	}
}

