/*
 * heater_controller.h
 *
 *  Created on: Aug 13, 2026
 *      Author: vkcls
 */

#ifndef INC_HEATER_CONTROLLER_H_
#define INC_HEATER_CONTROLLER_H_

#include "main.h"
#include "defines.h"

#include <stdbool.h>

void HeaterControllerInit(void);
void HeaterControll(OnOffState state);
uint8_t GetHeaterState();
void RisingTemper();
void DescentTemper();
void FixTemper();
void ProcessHeater();
uint16_t GetDesiredTemper(void);
bool GetIsTempEditing(void);
uint16_t GetFixedTemper(void);

#endif /* INC_HEATER_CONTROLLER_H_ */
