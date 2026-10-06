/*
 * oledController.h
 *
 *  Created on: Sep 8, 2026
 *      Author: vkcls
 */

#ifndef INC_OLEDCONTROLLER_H_
#define INC_OLEDCONTROLLER_H_

#include <stdbool.h>
#include "defines.h"

#define OLED_BLINK_TIME 400

void ShowOpening();
void ShowDefault();
void ShowTemper(int setTemp, bool isTempVisible);
void ShowWork(OnOffState state);
void ProcessOled(void);

#endif /* SRC_OLEDCONTROLLER_H_ */
