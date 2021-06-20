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
#include "ws2812.h"
//----------------------------------------------------------------------------
extern TIM_HandleTypeDef htim2;
//----------------------------------------------------------------------------
#define LED_COUNT 150
#define ARRAY_LEN DELAY_LEN + LED_COUNT*24
uint32_t BUF_DMA [ARRAY_LEN] = {0};


/**
  * @brief WS2812 initialization
  * @param[in] None
	* @date 23.03.2021
  * @retval None
  */
void ws2812_init(uint16_t led_count)
{
	SystemCoreClockUpdate();
	__HAL_TIM_SET_AUTORELOAD(&htim2,SystemCoreClock/800000 - 1);
  int i;
  for(i=DELAY_LEN;i<ARRAY_LEN;i++) BUF_DMA[i] = LOW;
}

/**
  * @brief WS2812 initialization
  * @param[in] None
	* @date 23.03.2021
  * @retval None
  */
void ws2812_pixel_rgb_to_buf_dma(uint8_t Rpixel , uint8_t Gpixel, uint8_t Bpixel, uint16_t posX)
{
  volatile uint16_t i;
  for(i=0;i<8;i++)
  {
    if (BitIsSet(Rpixel,(7-i)) == 1)
    {
      BUF_DMA[DELAY_LEN+posX*24+i+8] = HIGH;
    }else
    {
      BUF_DMA[DELAY_LEN+posX*24+i+8] = LOW;
    }
    if (BitIsSet(Gpixel,(7-i)) == 1)
    {
      BUF_DMA[DELAY_LEN+posX*24+i+0] = HIGH;
    }else
    {
      BUF_DMA[DELAY_LEN+posX*24+i+0] = LOW;
    }
    if (BitIsSet(Bpixel,(7-i)) == 1)
    {
      BUF_DMA[DELAY_LEN+posX*24+i+16] = HIGH;
    }else
    {
      BUF_DMA[DELAY_LEN+posX*24+i+16] = LOW;
    }
  }
} 
/**
  * @brief Send led buffer to ws2812
	*
	*
	* Start timer + DMA PWM generation
  * @param[in] None
	* @date 23.03.2021
  * @retval None
  */
void ws2812_light()
{
	HAL_TIM_PWM_Start_DMA(&htim2,TIM_CHANNEL_2,(uint32_t*)&BUF_DMA,ARRAY_LEN);
}

