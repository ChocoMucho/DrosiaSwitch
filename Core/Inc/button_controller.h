/*
 * button_controller.h
 *
 *  Created on: Sep 9, 2026
 *      Author: vkcls
 */

#ifndef INC_BUTTON_CONTROLLER_H_
#define INC_BUTTON_CONTROLLER_H_

#include "main.h"
#include "defines.h"
#include <stdbool.h>

void ProcessButtonEvents();
void ButtonController_OnExti(uint16_t GPIO_Pin);
OnOffState GetSlideSWState(void);


#endif /* INC_BUTTON_CONTROLLER_H_ */
