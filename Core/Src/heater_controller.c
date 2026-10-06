#include "heater_controller.h"
#include "oledController.h"
#include "ds18b20.h"

#include <stdbool.h>

static OnOffState m_state = 0;

static volatile uint16_t fixedTemper = 0;
static volatile uint16_t desiredTemper = 30;

static volatile bool isTempEditing = false;

static volatile bool isDeadband = false;

void HeaterControllerInit(void)
{
	fixedTemper = desiredTemper;
}

void HeaterControll(OnOffState state)
{
	HAL_GPIO_WritePin(
	PB5_RELAY_ON_OFF_CTRL_GPIO_Port,
	PB5_RELAY_ON_OFF_CTRL_Pin,
			(state == STATE_ON) ? GPIO_PIN_SET : GPIO_PIN_RESET);

	if (m_state == STATE_OFF && state == STATE_ON)
	{
		ShowWork(STATE_ON);
	}
	else if (m_state == STATE_ON && state == STATE_OFF)
	{
		ShowWork(STATE_OFF);
	}

	m_state = state;
}

uint8_t GetHeaterState()
{
	return m_state;
}

void RisingTemper()
{
	//ShowTemper(++desiredTemper);
	++desiredTemper;
	isTempEditing = true;
}

void DescentTemper()
{
	//ShowTemper(--desiredTemper);
	--desiredTemper;
	isTempEditing = true;
}

void FixTemper()
{
	fixedTemper = desiredTemper;
	isTempEditing = false;
}

void ProcessHeater()
{
	float nowTemper = GetTemper();

	if (isDeadband)
	{
		if ((float) fixedTemper - DEADBAND_GAP >= nowTemper)
		{// 데드밴드면서 목표 - 갭 보다 측정이 낮음
			// OFF
			HeaterControll(STATE_OFF);
			// !Deadband
			isDeadband = false;
		}
		else
		{// 데드밴드면서 목표 - 갭 보다 측정온도가 높음
			// 현상 유지
		}
	}
	else
	{
		if ((float) fixedTemper < nowTemper)
		{// 데드밴드 아니면서 목표보다 측정 온도 높음
			// ON
			HeaterControll(STATE_ON);
			// Deadband
			isDeadband = true;
		}
		else
		{// 데드밴드 아니면서 목표보다 측정 온도 낮음
			// 현상유지
		}
	}
}

uint16_t GetDesiredTemper(void)
{
	return desiredTemper;
}

bool GetIsTempEditing(void)
{
	return isTempEditing;
}

uint16_t GetFixedTemper(void)
{
	return fixedTemper;
}
