/*
 * fnd_controller.c
 *
 *  Created on: Jul 15, 2026
 *      Author: vkcls
 */
#include "fnd_controller.h"

uint8_t _LED_0F[29];

SPI_HandleTypeDef *spiHandle;

void FND_Init(SPI_HandleTypeDef *hspi) {
	spiHandle = hspi;

	_LED_0F[0] = 0xC0; //0
	_LED_0F[1] = 0xF9; //1
	_LED_0F[2] = 0xA4; //2
	_LED_0F[3] = 0xB0; //3
	_LED_0F[4] = 0x99; //4
	_LED_0F[5] = 0x92; //5
	_LED_0F[6] = 0x82; //6
	_LED_0F[7] = 0xF8; //7
	_LED_0F[8] = 0x80; //8
	_LED_0F[9] = 0x90; //9
	_LED_0F[10] = 0x88; //A
	_LED_0F[11] = 0x83; //b
	_LED_0F[12] = 0xC6; //C
	_LED_0F[13] = 0xA1; //d
	_LED_0F[14] = 0x86; //E
	_LED_0F[15] = 0x8E; //F
	_LED_0F[16] = 0xC2; //G
	_LED_0F[17] = 0x89; //H
	_LED_0F[18] = 0xF9; //I
	_LED_0F[19] = 0xF1; //J
	_LED_0F[20] = 0xC3; //L
	_LED_0F[21] = 0xA9; //n
	_LED_0F[22] = 0xC0; //O
	_LED_0F[23] = 0x8C; //P
	_LED_0F[24] = 0x98; //q
	_LED_0F[25] = 0x92; //S
	_LED_0F[26] = 0xC1; //U
	_LED_0F[27] = 0x91; //Y
	_LED_0F[28] = 0xFE; //hight
}

void Send(uint8_t X) {
	/*for (int i = 8; i >= 1; --i) {
		if (X & 0x80) // why?
				{
			HAL_GPIO_WritePin(FND_DIO_GPIO_Port, FND_DIO_Pin, 1);
		} else {
			HAL_GPIO_WritePin(FND_DIO_GPIO_Port, FND_DIO_Pin, 0);
		}
		X <<= 1;
		HAL_GPIO_WritePin(FND_SCLK_GPIO_Port, FND_SCLK_Pin, 1);
		HAL_GPIO_WritePin(FND_SCLK_GPIO_Port, FND_SCLK_Pin, 0);
	}
	// 1010 1010 & 1000 0000
	// 0101 0100 & 1000 0000
	// 맨 앞자리부터 따지는 듯
	// DIO로 high, low 보내고
	// sclk변화로 한 바이트 보냈다는 표시로 한 클럭 진행.
	// 한 비트마다 sclk한 번 진행*/

	HAL_SPI_Transmit(spiHandle, &X, 1, 100);
}

void Send_Value_Port(uint8_t X, uint8_t port) {
	Send(X);
	Send(port);
	HAL_GPIO_WritePin(FND_RCLK_GPIO_Port, FND_RCLK_Pin, 1);
	HAL_GPIO_WritePin(FND_RCLK_GPIO_Port, FND_RCLK_Pin, 0);
	// trouble shooting / 여기는 High -> Low였음
}

static uint8_t m_temperCount = 0;

void Digit4_Error(void)
{
	static uint8_t errorDigit = 0U;

	m_temperCount = 0U;
	Send_Value_Port(0xBF, (uint8_t)(1U << errorDigit));
	errorDigit = (uint8_t)((errorDigit + 1U) % 4U);
}

void Digit4_Temper(int temper) {
	int n1, n2, n3, n4;
	n1 = (int) temper % 10;
	n2 = (int) (temper % 100) / 10;
	n3 = (int) (temper % 1000) / 100;
	n4 = (int) (temper % 10000) / 1000;

	switch(m_temperCount){
	case 0:
		Send_Value_Port(_LED_0F[n1], 0b0001);
		break;
	case 1:
		Send_Value_Port(_LED_0F[n2] & 0x7F, 0b0010); // & 0111 1111
		break;
	case 2:
		Send_Value_Port(_LED_0F[n3], 0b0100);
		break;
	case 3:
		Send_Value_Port(_LED_0F[n4], 0b1000);
		break;
	default:
		break;
	}

	++m_temperCount;
	if(temper > 999 && m_temperCount >= 4)
		m_temperCount = 0;
	else if ((temper > 99 && temper < 999) && m_temperCount >= 3)
		m_temperCount = 0;
	else if ((temper > 9 && temper < 99) && m_temperCount >= 2)
		m_temperCount = 0;
}

void Digit4_Replay_ShowZero(int n, int replay, int showZero) {
	int n1, n2, n3, n4;
	n1 = (int) n % 10;
	n2 = (int) (n % 100) / 10;
	n3 = (int) (n % 1000) / 100;
	n4 = (int) (n % 10000) / 1000;

	for (int i = 0; i <= replay; i++) {
		Send_Value_Port(_LED_0F[n1], 0b0001);
		if (showZero | n > 9)
			Send_Value_Port(_LED_0F[n2], 0b0010);
		if (showZero | n > 99)
			Send_Value_Port(_LED_0F[n3], 0b0100);
		if (showZero | n > 999)
			Send_Value_Port(_LED_0F[n4], 0b1000);
	}
}

void Digit4_Replay(int n, int replay) {
	Digit4_Replay_ShowZero(n, replay, 0);
}

void Digit4(int n) {
	Digit4_Replay_ShowZero(n, 0, 0);
}

void digit4showZero(int n, int replay) {
	Digit4_Replay_ShowZero(n, replay, 1);
}

void Digit4showZero(int n) {
	Digit4_Replay_ShowZero(n, 0, 1);
}

void Digit2_Replay(int n, int port, int replay) {
	int n1, n2;
	n1 = (int) n % 10;
	n2 = (int) ((n % 100) - n1) / 10;

	for (int i = 0; i <= replay; i++) {
		Send_Value_Port(_LED_0F[n1], port);
		Send_Value_Port(_LED_0F[n2], port << 1);
	}
}

void Digit2(int n, int port) {
	Digit2_Replay(n, port, 0);
}
