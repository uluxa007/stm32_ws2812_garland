/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           menu.h
  * @brief          Menu interface
  ******************************************************************************
  *
  * <h3>&copy; Copyright (c) Somov Ilia Andreevich.
  * All rights reserved.</center></h3>
  ******************************************************************************
  */
#ifndef MENU_H
#define MENU_H

#define PAGE_COUNT 6 ///< Page count on menu. To add page increment
#define LINE_COUNT 4 ///< Lines count on menu

#include "inttypes.h"
#include "ssd1306.h"
#include "stdbool.h"
#include "settings.h"
#include "garl.h"

#define TOP_OFFSET 4						///< Offset from the top of the screen

#define COLUMN_START_1 7				///< Start of the first column of the menu
#define COLUMN_START_2 72				///< Start of the second column of the menu
#define COLUMN_START_3 112			///< Start of the third column of the menu (not used now)

#define LINE_HEIGHT 12

#define PAGE_1 0								///< Page 1 index
#define PAGE_2 1								///< Page 2 index
#define PAGE_3 2								///< Page 3 index
#define PAGE_4 3								///< Page 4 index
#define PAGE_5 4								///< Page 5 index
#define PAGE_6 5								///< Page 6 index

#define LINE_1 0								///< Line 1 index
#define LINE_2 1								///< Line 2 index
#define LINE_3 2								///< Line 3 index
#define LINE_4 3								///< Line 4 index
#define LINE_5 4								///< Line 5 index

#define ENCODER_KEY_PORT 	GPIOA					///< Encoder button port
#define ENCODER_KEY_PIN		GPIO_PIN_0		///< Encoder button pin
		
#define TIME_START_SPLASH_1 1000 		///< Time before splash screen
#define TIME_START_SPLASH_2 1000 		///< Time after splash screen

void menu_init(void);
void menuDrawHandler(void);
void menuInputHandler(void);
void nextLine(void);
void menuHandler(void);
void buttonHandler(void);
void updateMenu(void);
void uartHandler(void);

#endif
