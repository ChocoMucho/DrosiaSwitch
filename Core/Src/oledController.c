/*
 * oledController.c
 *
 *  Created on: Sep 8, 2026
 *      Author: vkcls
 */
#include "oledController.h"
#include <stdbool.h>

#include "main.h"

#include "fonts.h"
#include "ssd1306.h"
#include "test.h"
#include "bitmap.h"
#include "horse_anim.h"
#include "Custom.h"

#include "defines.h"
#include "heater_controller.h"

static volatile uint32_t lastBlinkTick = 0;

static volatile bool isTempInitialized = false;
static volatile bool isTempVisible = true;
static volatile bool isTempEdited = false; // temp fixed

void ShowOpening()
{
	SSD1306_Clear();
	SSD1306_DrawBitmap(0, 0, zaku_heads[0], 128, 64, 1);
	SSD1306_UpdateScreen();
	HAL_Delay(500);

	SSD1306_Clear();
	SSD1306_DrawBitmap(0, 0, zaku_heads[1], 128, 64, 1);
	SSD1306_UpdateScreen();
	HAL_Delay(500);

	SSD1306_Clear();
	SSD1306_DrawBitmap(0, 0, zaku_heads[2], 128, 64, 1);
	SSD1306_UpdateScreen();
	HAL_Delay(500);

	SSD1306_Clear();
	SSD1306_DrawBitmap(0, 0, zaku_heads[3], 128, 64, 1);
	SSD1306_UpdateScreen();
	HAL_Delay(500);

	SSD1306_Clear();
	SSD1306_DrawBitmap(0, 0, zaku_heads[4], 128, 64, 1);
	SSD1306_UpdateScreen();
	HAL_Delay(500);

	SSD1306_Clear();
	SSD1306_DrawBitmap(0, 0, zaku_heads[5], 128, 64, 1);
	SSD1306_UpdateScreen();
	HAL_Delay(500);

	SSD1306_Clear();
	SSD1306_DrawBitmap(0, 0, zaku_heads[6], 128, 64, 1);
	SSD1306_UpdateScreen();
	HAL_Delay(500);

	SSD1306_Clear();
	SSD1306_DrawBitmap(0, 0, zaku_heads[7], 128, 64, 1);
	SSD1306_UpdateScreen();
	HAL_Delay(500);

	SSD1306_Clear();
	SSD1306_DrawBitmap(0, 0, zaku_heads[0], 128, 64, 1);
	SSD1306_UpdateScreen();
	HAL_Delay(1000);

	ShowDefault();
	ShowWork(STATE_OFF);
}

void ShowDefault()
{
	SSD1306_Clear();
	SSD1306_GotoXY(0, 0);
	SSD1306_Puts("Temper Work", &Font_11x18, 1);
	SSD1306_GotoXY(0, 20);
	SSD1306_Puts("-----------", &Font_11x18, 1);
	SSD1306_UpdateScreen();
}

void ShowTemper(int setTemp, bool isTempVisible)
{
	if (isTempVisible)
	{
		char str[10];
		sprintf(str, "%2d.0", setTemp);

		SSD1306_GotoXY(0, 40);
		SSD1306_Puts(str, &Font_11x18, 1);
		SSD1306_UpdateScreen();
	}
	else
	{
		SSD1306_GotoXY(0, 40);
		SSD1306_Puts("    ", &Font_11x18, 1);
		SSD1306_UpdateScreen();
	}

}

void ShowWork(OnOffState state)
{
	if (state == STATE_ON)
	{
		SSD1306_GotoXY(60, 40);
		SSD1306_Puts("ON ", &Font_11x18, 1);
		SSD1306_UpdateScreen();
	}
	else
	{
		SSD1306_GotoXY(60, 40);
		SSD1306_Puts("OFF", &Font_11x18, 1);
		SSD1306_UpdateScreen();
	}
}

void ProcessOled(void)
{
	uint32_t nowTick = HAL_GetTick();

	if (!isTempInitialized) // The First
	{
		ShowTemper(GetFixedTemper(), true);
		isTempInitialized = true;
	}

	if (GetIsTempEditing())
	{
		if (nowTick - lastBlinkTick >= OLED_BLINK_TIME)
		{
			isTempVisible = !isTempVisible;
			ShowTemper(GetDesiredTemper(), isTempVisible);
			lastBlinkTick = nowTick;
			isTempEdited = false;
		}

	}
	else // 온도 편집중이 아니면
	{
		if (!isTempEdited) // didn't print fixed temper?
		{
			isTempVisible = true;
			isTempEdited = true;
			ShowTemper(GetFixedTemper(), isTempVisible);
		}
	}
}
