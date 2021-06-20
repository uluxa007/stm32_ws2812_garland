/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           garl.h
  * @brief          Garland
  ******************************************************************************
  *
  * <h3>&copy; Copyright (c) Somov Ilia Andreevich.
  * All rights reserved.</center></h3>
  ******************************************************************************
  */
#ifndef GARL_H
#define GARL_H

#include "inttypes.h"
#include "main.h"
#include "ws2812.h"
#include "colors.h"
#include "stdbool.h"
#include "settings.h"

#define OFF 0                                     ///< State - off
#define ON 1                                      ///< State - on
//FLEFT FMIDDLE 
//FRIGHT BLEFT  
//BMIDDLE BRIGHT
#define FRONT_LEFT 			0                         ///< Front left section
#define FRONT_MIDDLE 		1                         ///< Front middle section
#define FRONT_RIGHT 		2                         ///< Front right section
#define BACK_LEFT 			3                         ///< Back  left section
#define BACK_MIDDLE 		4                         ///< Back  middle section
#define BACK_RIGHT 			5                         ///< Back  right section

#define NONE 						0                         ///< State - NONE
#define WASTE 					1                         ///< State - turning off now
#define FILL 						2                         ///< State - turning on now



#define COLOR_MODE_RGB  										0			///< Color mode - RGB
#define COLOR_MODE_HSV 											2			///< Color mode - HSV
#define COLOR_MODE_AUTO 										4			///< Color mode - AUTO
#define COLOR_MODE_RAINBOW 									6			///< Color mode - RAINBOW

#define OPERATING_MODE_OFF                 	0			///< Operating mode - Off
#define OPERATING_MODE_AUTO                	2			///< Operating mode - Auto
#define OPERATING_MODE_ALL_ON              	4			///< Operating mode - All on
#define OPERATING_MODE_FRONT_ON            	6			///< Operating mode - Front on
#define OPERATING_MODE_BACK_ON             	8			///< Operating mode - Back on
#define OPERATING_MODE_MIDDLE_ON           	10		///< Operating mode - Middle on
#define OPERATING_MODE_FRONT_LEFT_ON       	12		///< Operating mode - Front left on
#define OPERATING_MODE_FRONT_RIGHT_ON      	14		///< Operating mode - Front right on
#define OPERATING_MODE_FRONT_MIDDLE_ON     	16		///< Operating mode - Front middle on
#define OPERATING_MODE_BACK_LEFT_ON        	18		///< Operating mode - Back left on
#define OPERATING_MODE_BACK_RIGHT_ON       	20		///< Operating mode - Back right on
#define OPERATING_MODE_BACK_MIDDLE_ON      	22		///< Operating mode - Back middle on

void Garl_Handler(void);
void Garl_init(void);

void Garl_Turn_On(uint8_t what);
void Garl_Turn_Off(uint8_t what);
void Garl_Turn_Front_On(void);
void Garl_Turn_Front_Off(void);
void Garl_Turn_Back_On(void);
void Garl_Turn_Back_Off(void);
void Garl_Turn_All_On(void);
void Garl_Turn_All_Off(void);


#endif
