/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           menu.c
  * @brief          Menu interface
  ******************************************************************************
  *
  * <h3>&copy; Copyright (c) Somov Ilia Andreevich.
  * All rights reserved.</center></h3>
	******************************************************************************
  */
#include "menu.h"

//#define DEBUG
//#define BLUETOOTH
#ifdef BLUETOOTH
extern UART_HandleTypeDef huart6;
uint8_t uart_buffer[3]={0};
#endif

#ifdef DEBUG
#include "stdio.h"
uint8_t buffer[128] = {0};
extern UART_HandleTypeDef huart6;
#endif

void page1_Draw(void);
void page2_Draw(void);
void page3_Draw(void);
void page4_Draw(void);
void page5_Draw(void);
void page6_Draw(void);

/**
  * @brief Field names
	*
	* Leave blank if not used.
  */
char parameters_names[PAGE_COUNT][LINE_COUNT][13]=
{
	{"÷¬≈“",				"–≈∆»Ã",			"— Œ–. 1",		"— Œ–. 2",	},
	{"“ŒÕ",					"Õ¿—€Ÿ.",			"ﬂ– Œ—“‹",		"",					},
	{" –¿—Õ€…",			"«≈À≈Õ€…",		"—»Õ»…",			"",					},
	{"ƒÀ»Õ¿ FL",		"ƒÀ»Õ¿ FM",		"ƒÀ»Õ¿ FR",		"",					},
	{"ƒÀ»Õ¿ BL",		"ƒÀ»Õ¿ BM",		"ƒÀ»Õ¿ BR",		"",					},
	{"RB STEP",			"",						"",						"",					}
};

/**
  * @brief Max values
	*
	* If max value equal to 0 field does not showed.
  */
uint16_t max_value[PAGE_COUNT][LINE_COUNT]=
{
	{6,							22,						254,					254},
	{360,						254,					254,					0},
	{254,						254,					254,					0},
	{100,						100,					100,					0},
	{100,						100,					100,					0},
	{128,						0,						0,						0}
};

/**
  * @brief Splash screen 1
	*
	* Image converted to array. Displays on start
  */
uint8_t splash_screen_1[1024] ={
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,128,96,56,56,60,60,60,60,60,62,62,62,62,62,62,62,62,254,254,126,62,62,126,62,126,126,254,254,254,254,62,30,30,30,30,30,30,30,30,30,30,30,30,30,30,14,14,14,14,14,14,14,14,12,12,12,12,28,28,28,28,28,24,24,24,16,16,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,128,240,14,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,240,255,63,3,0,0,0,0,0,0,0,0,1,7,63,255,240,128,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,192,255,240,240,240,240,224,224,224,224,224,224,224,224,192,192,96,112,127,255,255,192,128,128,128,128,128,0,0,128,0,0,0,0,3,255,255,252,224,192,192,192,192,192,192,192,192,192,192,192,192,192,192,192,192,192,192,192,192,192,192,192,192,192,192,192,192,192,192,192,192,192,192,192,192,192,192,192,192,192,192,192,192,192,192,192,192,192,192,192,192,192,128,128,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,252,252,252,255,255,255,255,255,255,255,255,255,255,255,255,255,254,254,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,15,247,247,247,247,247,247,247,247,247,247,239,239,223,223,191,63,191,191,191,63,63,63,63,63,63,63,63,63,63,63,63,63,63,63,63,63,63,191,191,191,191,191,191,191,190,254,196,216,60,248,248,240,192,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,1,128,192,225,225,195,15,123,225,227,227,195,195,195,195,195,135,135,135,135,135,135,143,15,15,15,15,15,31,31,31,31,63,63,255,255,63,15,7,7,7,7,7,7,15,15,31,31,15,7,7,7,0,3,3,7,7,7,7,7,7,7,7,7,7,7,7,6,1,7,7,7,7,7,7,7,5,5,5,5,5,5,4,4,4,0,4,4,4,4,6,2,2,2,2,2,3,3,3,3,3,0,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,31,127,255,255,127,31,0,7,15,15,15,15,15,15,15,31,31,31,31,31,63,63,63,63,63,63,127,127,126,126,254,254,254,255,255,0,0,0,224,248,248,252,252,252,252,252,248,248,240,128,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,15,31,63,127,127,255,255,127,127,127,63,15,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
};

/**
  * @brief Splash screen 2
	*
	* Image converted to array. Displays on start
  */
uint8_t splash_screen_2[1024] ={
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,128,96,56,56,60,60,60,60,60,62,62,62,62,62,62,62,62,254,254,126,62,62,126,62,126,126,254,254,254,254,62,30,30,30,30,30,30,30,30,30,30,30,30,30,30,14,14,14,14,14,14,14,14,12,12,12,12,28,28,28,28,28,24,24,24,16,16,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,128,240,14,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,240,255,63,3,0,0,0,0,0,0,0,0,1,7,63,255,240,128,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,192,255,240,240,240,240,224,224,224,224,224,224,224,224,192,192,96,112,127,255,255,192,128,128,128,128,128,0,0,128,0,0,0,0,3,255,255,252,224,192,192,192,192,192,192,192,192,192,192,192,192,192,192,192,192,192,192,192,192,192,192,192,192,192,192,192,192,192,192,192,192,192,192,192,192,192,192,192,192,192,192,192,192,192,192,192,192,192,192,192,192,192,128,128,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,252,252,252,255,255,255,255,255,255,255,255,255,255,255,255,255,254,254,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,15,7,7,7,7,7,7,7,7,7,7,15,15,31,31,63,63,191,191,191,63,63,63,63,63,63,63,63,63,63,63,63,63,63,63,63,63,63,191,191,191,191,191,191,191,190,254,196,192,32,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,1,128,192,225,225,195,15,123,225,227,227,195,195,195,195,195,135,135,135,135,135,135,143,15,15,15,15,15,31,31,31,31,63,63,255,255,63,15,7,7,7,7,7,7,15,15,31,31,15,7,7,7,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,7,7,7,7,7,7,7,5,5,5,5,5,5,4,4,4,0,4,4,4,4,6,2,2,2,2,2,3,3,3,3,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,31,127,255,255,127,31,0,7,15,15,15,15,15,15,15,31,31,31,31,31,63,63,63,63,63,63,127,127,126,126,254,254,254,255,255,0,0,0,224,248,248,252,252,252,252,252,248,248,240,128,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,15,31,63,127,127,255,255,127,127,127,63,15,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
};
/**
  * @brief Settings wheel 1
	*
	* Image converted to array. Displays on start
  */
uint8_t settings_wheel_1 [1024] ={
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,32,248,248,252,252,252,254,254,252,252,224,128,128,128,128,248,252,254,254,254,252,252,252,248,248,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,112,248,252,254,255,255,255,255,254,252,248,248,252,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,254,252,248,248,252,254,255,255,255,255,254,252,248,48,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,128,224,240,240,240,224,224,224,241,255,255,255,255,255,255,255,255,255,127,31,15,15,7,3,3,3,1,1,1,1,1,1,1,1,1,1,3,3,3,7,15,15,31,127,255,255,255,255,255,255,255,255,255,241,224,240,240,240,240,240,224,128,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,31,63,63,63,63,255,255,255,255,255,255,255,255,255,255,31,3,0,0,0,0,0,0,0,128,240,248,252,252,252,254,254,252,252,252,248,240,192,0,0,0,0,0,0,0,3,31,255,255,255,255,255,255,255,255,255,255,63,63,31,31,15,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,240,248,248,252,252,255,255,255,255,255,255,255,255,255,255,248,192,0,0,0,0,0,0,0,1,15,31,63,63,63,127,127,63,63,63,31,15,3,0,0,0,0,0,0,0,192,248,255,255,255,255,255,255,255,255,255,255,252,252,252,252,248,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,1,7,15,15,15,15,15,7,15,191,255,255,255,255,255,255,255,255,254,248,240,240,224,192,192,192,128,128,128,128,128,128,128,128,128,128,192,192,192,224,240,240,248,254,255,255,255,255,255,255,255,255,255,143,7,7,7,15,15,15,7,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,4,30,63,127,255,255,255,255,127,63,31,31,63,127,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,63,31,31,63,127,255,255,255,255,127,63,31,14,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,31,31,63,63,63,127,127,127,63,31,1,1,1,1,7,31,63,127,127,63,63,63,31,31,12,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
};
/**
  * @brief Settings wheel 2
	*
	* Image converted to array. Displays on start
  */
uint8_t settings_wheel_2 [1024] ={
0,0,0,0,0,0,0,0,0,0,0,0,0,128,192,224,224,240,240,240,240,224,192,0,0,0,128,252,254,254,254,254,254,254,254,254,252,128,0,0,0,192,224,240,240,240,240,224,224,192,128,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,128,192,224,224,192,192,128,128,195,207,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,239,199,128,128,192,192,224,224,192,128,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,28,63,127,127,255,255,255,255,255,255,255,255,255,255,255,255,127,31,15,15,7,3,3,3,1,1,1,1,1,1,1,1,1,1,3,3,3,7,15,15,31,127,255,255,255,255,255,255,255,255,255,255,255,255,127,127,63,28,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
224,240,248,248,248,248,248,255,255,255,255,255,255,255,255,255,31,3,0,0,0,0,0,0,0,128,240,248,252,252,252,254,254,252,252,252,248,240,192,0,0,0,0,0,0,0,3,31,255,255,255,255,255,255,255,255,255,248,248,248,248,248,240,224,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
7,15,31,31,31,31,31,255,255,255,255,255,255,255,255,255,248,192,0,0,0,0,0,0,0,1,15,31,63,63,63,127,127,63,63,63,31,15,3,0,0,0,0,0,0,0,192,248,255,255,255,255,255,255,255,255,255,31,31,31,31,31,15,7,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,56,252,254,254,255,255,255,255,255,255,255,255,255,255,255,255,254,248,240,240,224,192,192,192,128,128,128,128,128,128,128,128,128,128,192,192,192,224,240,240,248,254,255,255,255,255,255,255,255,255,255,255,255,255,254,254,252,56,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,1,3,7,7,3,3,1,1,195,243,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,247,227,1,1,3,3,7,7,3,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,1,3,7,7,15,15,15,15,7,3,0,0,0,1,63,127,127,127,127,127,127,127,127,63,1,0,0,0,3,7,15,15,15,15,7,7,3,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
};



extern TIM_HandleTypeDef htim1;	///< TIM1 handler

bool update_screen = true;
//bool line_changed = false;	///< Flag used to track if line was changed. If changed screen needs to update.
//bool val_changed = true;		///< Flag used to track if value was changed. If changed screen needs to update.

uint16_t prev_tim_val;					///< Previous timer value.
uint32_t last_changes_time=0;		///< Previous changes time.

uint32_t time_irq;
uint32_t hold_time;

char name_1[]="Smart";		///< String 1 to display on splash screen.
char name_2[]="Light";		///< String 2 to display on splash screen.
char name_3[]="v1";				///< String 3 to display on splash screen.
uint8_t x_name_1 = 82;		///< String 1 x offset.
uint8_t x_name_2 = 92;		///< String 2 x offset.
uint8_t x_name_3 = 113;		///< String 3 x offset.

SSD1306_COLOR font_color=White;	///< Font color

/**
  * @brief Function to display Splash screen
  * @param[in] splash_screen Splash screen buffer.
	* @date 23.03.2021
  * @retval None
  */
void showSplashScreen(uint8_t* splash_screen)
{
	ssd1306_CopyToBuffer(splash_screen);
	ssd1306_SetCursor(x_name_1,0);
	ssd1306_WriteString(name_1,Font_7x9,White);
	ssd1306_SetCursor(x_name_2,12);
	ssd1306_WriteString(name_2,Font_7x9,White);
	ssd1306_SetCursor(x_name_3,24);
	ssd1306_WriteString(name_3,Font_7x9,White);
	ssd1306_UpdateScreen();
}

/**
  * @brief Function to display 2 splash screen.
  * @param None
	* @date 23.03.2021
  * @retval None
  */
void splashScreen()
{
	ssd1306_SetContrast(255);
	showSplashScreen(splash_screen_1);
	HAL_Delay(TIME_START_SPLASH_1);
	showSplashScreen(splash_screen_2);
	HAL_Delay(50);
	showSplashScreen(splash_screen_1);
	HAL_Delay(50);
	showSplashScreen(splash_screen_2);
	HAL_Delay(50);
	showSplashScreen(splash_screen_1);
	HAL_Delay(50);
	showSplashScreen(splash_screen_2);
	HAL_Delay(50);
	showSplashScreen(splash_screen_1);
	HAL_Delay(TIME_START_SPLASH_2);
}

/**
  * @brief Menu initialization
  * @param None
	* @date 23.03.2021
  * @retval None
  */
void menu_init()
{
	Settings.parameters.front_left_lenght = 8;
	Settings.parameters.front_middle_lenght = 8;
	Settings.parameters.front_right_lenght = 8;
	Settings.parameters.back_left_lenght = 8;
	Settings.parameters.back_middle_lenght = 8;
	Settings.parameters.back_right_lenght = 8;
	__HAL_TIM_SET_COUNTER(&htim1,Settings.values[0][0]);
	prev_tim_val = TIM1->CNT;
	last_changes_time = HAL_GetTick();
	time_irq = 0;
	hold_time =0;
	//Splash
	splashScreen();
	#ifdef BLUETOOTH
	HAL_UART_Receive_IT(&huart6,uart_buffer,3);
	#endif
}

/**
  * @brief Line switcher

	Switches the current line to the next
  * @param None
  * @retval None
  */
void nextLine()
{
	last_changes_time = HAL_GetTick();
	update_screen = true;
	
	Settings.parameters.current_line++;
	if(Settings.parameters.current_line>LINE_COUNT)
		Settings.parameters.current_line =0;
	
	if(Settings.parameters.current_line==LINE_5)
		__HAL_TIM_SET_COUNTER(&htim1,Settings.parameters.current_page*2);
	else
		__HAL_TIM_SET_COUNTER(&htim1,Settings.values[Settings.parameters.current_page][Settings.parameters.current_line]);
	
	if(Settings.parameters.current_line!= LINE_5 && max_value[Settings.parameters.current_page][Settings.parameters.current_line]==0)
		nextLine();
}

/**
  * @brief Menu draw handler
	* 
	*	Draws current page and updates screen if values was changed.
  * @param None
	* @date 23.03.2021
  * @retval None
  */
void menuDrawHandler()
{
	ssd1306_Fill(Black);
	//CURSOR
	for(int8_t j=0;j<6;j++)
		for(uint8_t i=5-j;i<123+j;i++)
			ssd1306_DrawPixel(i,1+j+LINE_HEIGHT*Settings.parameters.current_line + TOP_OFFSET-4,White);
	for(int8_t j=0;j<6;j++)
		for(uint8_t i=j;i<128-j;i++)
			ssd1306_DrawPixel(i,7+j+LINE_HEIGHT*Settings.parameters.current_line + TOP_OFFSET-4,White);
	//
	#ifdef DEBUG
	//if(update_screen)
	//{
	//	//sprintf((char*)buffer,"\n");
	//	//HAL_UART_Transmit(&huart6,buffer,strlen((char*)buffer),200);
	//	//HAL_UART_Transmit(&huart6,(uint8_t*)Settings.values,8,200);
	//	//sprintf((char*)buffer,"\n");
	//	//HAL_UART_Transmit(&huart6,buffer,strlen((char*)buffer),200);
	//	
	//	sprintf((char*)buffer,"Current page: %d",Settings.parameters.current_page+1);
	//	HAL_UART_Transmit(&huart6,buffer,strlen((char*)buffer),200);
	//	if(Settings.parameters.current_line == LINE_5)
	//	{
	//		sprintf((char*)buffer,"<---------");
	//		HAL_UART_Transmit(&huart6,buffer,strlen((char*)buffer),200);
	//	}
	//	sprintf((char*)buffer,"\n");
	//	HAL_UART_Transmit(&huart6,buffer,strlen((char*)buffer),200);
	//	
	//	sprintf((char*)buffer,"Current line: %d\n",Settings.parameters.current_line+1);
	//	HAL_UART_Transmit(&huart6,buffer,strlen((char*)buffer),200);
	//	
	//	for(uint8_t page = 0;page<PAGE_COUNT;page++)
	//	{
	//		sprintf((char*)buffer,"\n");
	//		HAL_UART_Transmit(&huart6,buffer,strlen((char*)buffer),200);
	//		for(uint8_t line =0;line<LINE_COUNT;line++)
	//		{
	//			sprintf((char*)buffer,"%s %d",parameters_names[page][line],Settings.values[page][line]);
	//			HAL_UART_Transmit(&huart6,buffer,strlen((char*)buffer),200);
	//			if(Settings.parameters.current_line == line && Settings.parameters.current_page == page)
	//			{
	//				sprintf((char*)buffer,"<---------");
	//				HAL_UART_Transmit(&huart6,buffer,strlen((char*)buffer),200);
	//			}
	//			sprintf((char*)buffer,"\n");
	//			HAL_UART_Transmit(&huart6,buffer,strlen((char*)buffer),200);
	//		}
	//	}
	//}
	#endif
	for(uint8_t i=0;i<LINE_COUNT;i++)
	{
		if(i==Settings.parameters.current_line)
			font_color = Black;
		else
			font_color = White;
		ssd1306_SetCursor(COLUMN_START_1, LINE_HEIGHT*i+TOP_OFFSET);
		ssd1306_WriteString(parameters_names[Settings.parameters.current_page][i], Font_7x9, font_color);
		if(max_value[Settings.parameters.current_page][i])
		{
			ssd1306_SetCursor(COLUMN_START_2, LINE_HEIGHT*i+TOP_OFFSET);
			ssd1306_WriteInt(Settings.values[Settings.parameters.current_page][i], Font_7x9, font_color);
		}
	}
	
	switch(Settings.parameters.current_page)
	{
		case PAGE_1:
		{
			page1_Draw();
			break;
		}
		case PAGE_2:
		{
			page2_Draw();
			break;
		}
		case PAGE_3:
		{
			page3_Draw();
			break;
		}
		case PAGE_4:
		{
			page4_Draw();
			break;
		}
		case PAGE_5:
		{
			page5_Draw();
			break;
		}
		case PAGE_6:
		{
			page6_Draw();
			break;
		}
	}
	
	//PAGE
	if(Settings.parameters.current_line==LINE_5)
			font_color = Black;
		else
			font_color = White;
	ssd1306_SetCursor(COLUMN_START_1, LINE_HEIGHT*4+TOP_OFFSET);
	ssd1306_WriteString("Str", Font_7x9, font_color);
	
	ssd1306_SetCursor(COLUMN_START_2, LINE_HEIGHT*4+TOP_OFFSET);
	ssd1306_WriteInt(Settings.parameters.current_page+1, Font_7x9, font_color);
	
	if(update_screen)
	{
		ssd1306_SetContrast(255);
		HAL_GPIO_WritePin(GPIOC,GPIO_PIN_13,GPIO_PIN_RESET);
		ssd1306_UpdateScreen();
		update_screen = false;
		HAL_GPIO_WritePin(GPIOC,GPIO_PIN_13,GPIO_PIN_SET);
	}
	
	//if(HAL_GetTick()-last_changes_time>5000&&HAL_GetTick()-last_changes_time<5100)
	//{
	//	ssd1306_SetContrast(200);
	//	showSplashScreen(splash_screen_1);
	//}
	//else if(HAL_GetTick()-last_changes_time>10000&&HAL_GetTick()-last_changes_time<10100)
	//{
	//	ssd1306_SetContrast(1);
	//	showSplashScreen(splash_screen_1);
	//}
}

/**
  * @brief Menu input handler
	* 
	*	Process input data from button and timer value.
  * @param None
	* @date 23.03.2021
  * @retval None
  */
void menuInputHandler()
{
	if(TIM1->CNT%2==0)
	{
		if(prev_tim_val!=TIM1->CNT)
		{
			last_changes_time = HAL_GetTick();
			update_screen = true;
		}
		prev_tim_val = TIM1->CNT;
		
		if(Settings.parameters.current_line<LINE_5)
		{
			__HAL_TIM_SetAutoreload(&htim1,max_value[Settings.parameters.current_page][Settings.parameters.current_line]+1);
			Settings.values[Settings.parameters.current_page][Settings.parameters.current_line]=TIM1->CNT;
		}
		else
		{
			__HAL_TIM_SetAutoreload(&htim1,PAGE_COUNT*2-1);
			Settings.parameters.current_page = TIM1->CNT/2;
		}
	}
}
/**
  * @brief Menu handler
  * @param None
	* @date 23.03.2021
  * @retval None
  */
void menuHandler()
{
	menuInputHandler();
	menuDrawHandler();
	buttonHandler();
	uartHandler();
}

/**
  * @brief Encoder button handler
  * @param None
  * @retval None
  */
void buttonHandler()
{
	if(!HAL_GPIO_ReadPin(ENCODER_KEY_PORT,ENCODER_KEY_PIN))
	{
		if( (HAL_GetTick()-time_irq)>200 && TIM1->CNT%2==0)
		{
			if(HAL_GetTick()-hold_time > 1000)
			{
				//stop uart receiving
				
				//for(uint8_t i =0;i<2;i++)
				//{
				//	ssd1306_CopyToBuffer(settings_wheel_1);
				//	ssd1306_SetCursor(70,10);
				//	ssd1306_WriteString("Saving",Font_7x9,White);
				//	ssd1306_SetCursor(70,20);
				//	ssd1306_WriteString(". . . .",Font_7x9,White);
				//	ssd1306_UpdateScreen();
				//	HAL_Delay(100);
				//	ssd1306_CopyToBuffer(settings_wheel_2);
				//	ssd1306_SetCursor(70,10);
				//	ssd1306_WriteString("Saving",Font_7x9,White);
				//	ssd1306_SetCursor(70,20);
				//	ssd1306_WriteString(" . . .",Font_7x9,White);
				//	ssd1306_UpdateScreen();
				//	HAL_Delay(100);
				//}
				
				//start uart receiving
				hold_time = HAL_GetTick();
			}
			nextLine();
			time_irq = HAL_GetTick();
			//HAL_Delay(200);
		}
	}
	else
	{
		hold_time = HAL_GetTick();
	}
}

/**
  * @brief Individual handler for the page 1
  * @param None
  * @retval None
  */
void page1_Draw()
{
		if(Settings.parameters.current_line==LINE_1)
			font_color = Black;
		else
			font_color = White;
		
	ssd1306_SetCursor(COLUMN_START_2, 0+TOP_OFFSET);
	switch(Settings.parameters.color_mode)
	{
		case COLOR_MODE_RGB:
		{
			ssd1306_WriteString("RGB", Font_7x9, font_color);
			break;
		}
		case COLOR_MODE_HSV:
		{
			ssd1306_WriteString("HSV", Font_7x9, font_color);
			break;
		}
		case COLOR_MODE_AUTO:
		{
			ssd1306_WriteString("AUTO", Font_7x9, font_color);
			break;
		}
		case COLOR_MODE_RAINBOW:
		{
			ssd1306_WriteString("RAINBOW", Font_7x9, font_color);
			break;
		}
	}
	
	if(Settings.parameters.current_line==LINE_2)
		font_color = Black;
	else
		font_color = White;
	
	ssd1306_SetCursor(COLUMN_START_2, LINE_HEIGHT+TOP_OFFSET);
	switch(Settings.parameters.operating_mode)
	{
		case OPERATING_MODE_OFF:
		{
			ssd1306_WriteString("OFF", Font_7x9, font_color);
			break;
		}
		case OPERATING_MODE_AUTO:
		{
			ssd1306_WriteString("AUTO", Font_7x9, font_color);
			break;
		}
		case OPERATING_MODE_ALL_ON:
		{
			ssd1306_WriteString("ALL", Font_7x9, font_color);
			break;
		}
		case OPERATING_MODE_FRONT_ON:
		{
			ssd1306_WriteString("FRONT", Font_7x9, font_color);
			break;
		}
		case OPERATING_MODE_BACK_ON:
		{
			ssd1306_WriteString("BACK", Font_7x9, font_color);
			break;
		}
		case OPERATING_MODE_MIDDLE_ON:
		{
			ssd1306_WriteString("MID", Font_7x9, font_color);
			break;
		}
		case OPERATING_MODE_FRONT_LEFT_ON:
		{
			ssd1306_WriteString("FLEFT", Font_7x9, font_color);
			break;
		}
		case OPERATING_MODE_FRONT_RIGHT_ON:
		{
			ssd1306_WriteString("FRIGHT", Font_7x9, font_color);
			break;
		}
		case OPERATING_MODE_FRONT_MIDDLE_ON:
		{
			ssd1306_WriteString("FMID", Font_7x9, font_color);
			break;
		}
		case OPERATING_MODE_BACK_LEFT_ON:
		{
			ssd1306_WriteString("BLEFT", Font_7x9, font_color);
			break;
		}
		case OPERATING_MODE_BACK_RIGHT_ON:
		{
			ssd1306_WriteString("BRIGHT", Font_7x9, font_color);
			break;
		}
		case OPERATING_MODE_BACK_MIDDLE_ON:
		{
			ssd1306_WriteString("BMID", Font_7x9, font_color);
			break;
		}
	}
}

/**
  * @brief Individual handler for the page 2
  * @param None
  * @retval None
  */
void page2_Draw()
{
	
}

/**
  * @brief Individual handler for the page 3
  * @param None
  * @retval None
  */
void page3_Draw()
{
	
}

/**
  * @brief Individual handler for the page 4
  * @param None
  * @retval None
  */
void page4_Draw()
{
	
}

/**
  * @brief Individual handler for the page 5
  * @param None
  * @retval None
  */
void page5_Draw()
{
	
}

/**
  * @brief Individual handler for the page 6
  * @param None
  * @retval None
  */
void page6_Draw()
{
	
}

/**
  * @brief Function initiates screen update
  * @param None
  * @retval None
  */
void updateMenu()
{
	update_screen = true;
}

/**
  * @brief Bluetooth handler
  * @param None
  * @retval None
  */
void uartHandler()
{	
	#ifdef BLUETOOTH
	if(huart6.RxXferCount==0)
	{
		HAL_UART_AbortReceive_IT(&huart6);
		if(uart_buffer[0]<PAGE_COUNT && uart_buffer[1]<LINE_COUNT && uart_buffer[2]%2==0 && uart_buffer[2] <= max_value[uart_buffer[0]][uart_buffer[1]])
		{
			if(Settings.parameters.current_page == uart_buffer[0] && Settings.parameters.current_line == uart_buffer[1])
				TIM1->CNT = uart_buffer[2];
			Settings.values[uart_buffer[0]][uart_buffer[1]] = uart_buffer[2];
			//updateMenu();
			
			ssd1306_SetCursor(100,40);
			ssd1306_WriteString("UP",Font_7x9,White);
			ssd1306_UpdateScreen();
			sprintf((char*)buffer,"OK\n");
			HAL_UART_Transmit(&huart6,buffer,strlen((char*)buffer),200);
		}
		else
		{
			ssd1306_SetCursor(100,50);
			ssd1306_WriteString("ER",Font_7x9,White);
			ssd1306_UpdateScreen();
			sprintf((char*)buffer,"ERR\n");
			HAL_UART_Transmit(&huart6,buffer,strlen((char*)buffer),200);
		}
		HAL_Delay(100);
		updateMenu();
		HAL_UART_Receive_IT(&huart6,uart_buffer,3);
	}
	#endif
}
