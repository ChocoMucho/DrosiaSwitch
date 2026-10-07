/*
 * defines.h
 *
 *  Created on: Sep 9, 2026
 *      Author: vkcls
 */

#ifndef INC_DEFINES_H_
#define INC_DEFINES_H_

#define BTN_EVENT_PB0	(1U << 0)
#define BTN_EVENT_PB1  	(1U << 1)
#define BTN_EVENT_PB2  	(1U << 2)

typedef enum {
	STATE_OFF = 0,
	STATE_ON = 1
} OnOffState;


#define SWITCH_BOUNCE_TIME 100
#define DEADBAND_GAP 2

#define minTemper 15
#define maxTemper 40

#endif /* INC_DEFINES_H_ */
