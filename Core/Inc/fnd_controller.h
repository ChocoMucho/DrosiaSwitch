/*
 * fnd_controller.h
 *
 *  Created on: Jul 15, 2026
 *      Author: vkcls
 */

#ifndef INC_FND_CONTROLLER_H_
#define INC_FND_CONTROLLER_H_

#include "main.h"
void FND_Init(SPI_HandleTypeDef *hspi);

void Send(uint8_t X);


void Send_Value_Port(uint8_t X, uint8_t port);

void Digit4_Temper(int temper);
void Digit4_Error(void);

void Digit4_Replay_ShowZero(int n, int replay, int showZero);

void Digit4_Replay(int n, int replay);

void Digit4(int n);

void digit4showZero(int n, int replay);

void Digit4showZero(int n);


void Digit2_Replay(int n, int port, int replay);

void Digit2(int n, int port);


#endif /* SRC_FND_CONTROLLER_H_ */
