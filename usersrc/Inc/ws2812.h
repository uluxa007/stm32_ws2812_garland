/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           ws2812.c
  * @brief          WS2812 led lib
  ******************************************************************************
  *
  * <h3>&copy; Copyright (c) Somov Ilia Andreevich.
  * All rights reserved.</center></h3>
	******************************************************************************
  */
#ifndef WS2812_H_
#define WS2812_H_
//--------------------------------------------------
#include "stm32f4xx_hal.h"
#include <string.h>
#include <stdlib.h>
#include <stdint.h>
//--------------------------------------------------
#define BitIsSet(reg, bit) ((reg & (1<<bit)) != 0)

#define DELAY_LEN 48
#define HIGH 72
#define LOW 28
//#define LED_COUNT 150
//#define ARRAY_LEN DELAY_LEN + LED_COUNT*24
//--------------------------------------------------
void ws2812_init(uint16_t led_count);
void ws2812_pixel_rgb_to_buf_dma(uint8_t Rpixel , uint8_t Gpixel, uint8_t Bpixel, uint16_t posX);
void ws2812_light(void);
#endif /* WS2812_H_ */
