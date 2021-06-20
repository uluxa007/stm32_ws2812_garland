/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           garl.c
  * @brief          Garland
  ******************************************************************************
  *
  * <h3>&copy; Copyright (c) Somov Ilia Andreevich.
  * All rights reserved.</center></h3>
  ******************************************************************************
  */
#include "garl.h"

static uint8_t starts[6]={0};								///< Start leds of sections
static uint8_t ends[6]={0};									///< End leds of sections
			
uint16_t result_color[3]={0,0,0};						///< Result color of leds after calculation
			
uint16_t hsv_color_rainbow;									///< Color of leds in rainbow color mode
uint16_t rainbow_offset=0;									///< Led offset in rainbow color mode
			
uint8_t current_led[6]={0};									///< Current leds

int16_t light_brightness[150] ={0};					///< Current brightness of led
uint8_t state[6]={0};												///< Current state of sections

uint16_t current_hue=0;											///< Current hue value in auto color mode
uint16_t tmp_hsv_color[3]={0,255,255};			///< HSV color to calculation
			

/**
  * @brief Garland initialization
  * @param[in] None
	* @date 23.03.2021
  * @retval None
  */
void Garl_init()
{
	memset(light_brightness,0,300);
	memset(current_led,0,6);
	
	
		
	Settings.parameters.front_left_lenght = 8;
	Settings.parameters.front_middle_lenght = 4;
	Settings.parameters.front_right_lenght = 8;
	Settings.parameters.back_left_lenght = 8;
	Settings.parameters.back_middle_lenght = 4;
	Settings.parameters.back_right_lenght = 8;
	
	Settings.parameters.hsv_color[0] = 0;
	Settings.parameters.hsv_color[1] = 254;
	Settings.parameters.hsv_color[2] = 32;
	
	Settings.parameters.turn_on_off_speed = 32;
	Settings.parameters.change_color_speed = 8;
	
	Settings.parameters.color_mode = COLOR_MODE_HSV;
	Settings.parameters.operating_mode = OPERATING_MODE_ALL_ON;
	
	starts[0]=0;
	starts[1]=Settings.parameters.front_left_lenght;
	starts[2]=Settings.parameters.front_left_lenght+Settings.parameters.front_middle_lenght;
	starts[3]=Settings.parameters.front_left_lenght+Settings.parameters.front_middle_lenght+Settings.parameters.front_right_lenght;
	starts[4]=Settings.parameters.front_left_lenght+Settings.parameters.front_middle_lenght+Settings.parameters.front_right_lenght+Settings.parameters.back_left_lenght;
	starts[5]=Settings.parameters.front_left_lenght+Settings.parameters.front_middle_lenght+Settings.parameters.front_right_lenght+Settings.parameters.back_left_lenght+Settings.parameters.back_middle_lenght;
	
	ends[0]=Settings.parameters.front_left_lenght-1;
	ends[1]=Settings.parameters.front_left_lenght+Settings.parameters.front_middle_lenght-1;
	ends[2]=Settings.parameters.front_left_lenght+Settings.parameters.front_middle_lenght+Settings.parameters.front_right_lenght-1;
	ends[3]=Settings.parameters.front_left_lenght+Settings.parameters.front_middle_lenght+Settings.parameters.front_right_lenght+Settings.parameters.back_left_lenght-1;
	ends[4]=Settings.parameters.front_left_lenght+Settings.parameters.front_middle_lenght+Settings.parameters.front_right_lenght+Settings.parameters.back_left_lenght+Settings.parameters.back_middle_lenght-1;
	ends[5]=Settings.parameters.front_left_lenght+Settings.parameters.front_middle_lenght+Settings.parameters.front_right_lenght+Settings.parameters.back_left_lenght+Settings.parameters.back_middle_lenght+Settings.parameters.back_right_lenght-1;
	
	current_led[0]=starts[0];
	current_led[1]=starts[1];
	current_led[2]=starts[2];
	current_led[3]=starts[3];
	current_led[4]=starts[4];
	current_led[5]=starts[5];
}

/**
  * @brief Turning on/off handler
  * @param[in] None
	* @date 23.03.2021
  * @retval None
  */
void turn_on_off_handler()
{
	
	for(uint8_t i=0;i<6;i++)
	{
		if(true)//(i!=FRONT_MIDDLE&&i!=BACK_MIDDLE)//((i!=FRONT_MIDDLE&&i!=BACK_MIDDLE))
		{
			if(state[i]==FILL)
			{
				if(current_led[i]<=ends[i])
				{
					light_brightness[current_led[i]]+=Settings.parameters.turn_on_off_speed;
					if(light_brightness[current_led[i]]>=256)
					{
						light_brightness[current_led[i]]=256;
						if(current_led[i]==ends[i])
						{
							state[i]=NONE;
						}
						else
						{
							current_led[i]++;
						}
					}
				}
				else
				{
					state[i]=NONE;
				}
			}
			else if(state[i]==WASTE)
			{
				if(current_led[i]>=starts[i])
				{
					light_brightness[current_led[i]]-=Settings.parameters.turn_on_off_speed;
					if(light_brightness[current_led[i]]<=0)
					{
						light_brightness[current_led[i]]=0;
						if(current_led[i]==starts[i])
						{
							state[i]=NONE;
						}
						else
						{
							current_led[i]--;
						}
					}
				}
				else
				{
					state[i]=NONE;
				}
			}
		}
	}
}

/**
  * @brief Calculate color depending on color mode
  * @param[in] None
	* @date 23.03.2021
  * @retval None
  */
void colorMode_handler()
{
		
	if(Settings.parameters.color_mode == COLOR_MODE_HSV) 
	{
		//HsvToRgb(hsv_color,result_color);
		hsv_to_rgb(Settings.parameters.hsv_color,result_color,60);
	}
	else if(Settings.parameters.color_mode == COLOR_MODE_RGB) 
	{
		memcpy(result_color,Settings.parameters.rgb_color,6);
	}
	else if(Settings.parameters.color_mode == COLOR_MODE_RAINBOW)
	{
		
	}
	else if(Settings.parameters.color_mode == COLOR_MODE_AUTO)
	{
		current_hue+=Settings.parameters.change_color_speed;
		if(current_hue>23040)
			current_hue=0;
		
		tmp_hsv_color[0]=current_hue/64;
		tmp_hsv_color[1]=Settings.parameters.hsv_color[1];
		tmp_hsv_color[2]=Settings.parameters.hsv_color[2];
		
		hsv_to_rgb(tmp_hsv_color,result_color,60);
	}
}

/**
  * @brief Switching garland states depending on selected operating mode
  * @param[in] None
	* @date 23.03.2021
  * @retval None
  */
void operatingMode_handler()
{
		
	switch(Settings.parameters.operating_mode)
	{
		case OPERATING_MODE_OFF:
		{
			Garl_Turn_All_Off();
			break;
		}
		case OPERATING_MODE_ALL_ON:
		{
			Garl_Turn_All_Off();
			Garl_Turn_All_On();
			break;
		}
		case OPERATING_MODE_FRONT_ON:
		{
			Garl_Turn_All_Off();
			Garl_Turn_Front_On();
			break;
		}
		case OPERATING_MODE_BACK_ON:
		{
			Garl_Turn_All_Off();
			Garl_Turn_Back_On();
			break;
		}
		case OPERATING_MODE_MIDDLE_ON:
		{
			Garl_Turn_All_Off();
			Garl_Turn_On(FRONT_MIDDLE);
			Garl_Turn_On(BACK_MIDDLE);
			break;
		}
		case OPERATING_MODE_FRONT_LEFT_ON:
		{
			Garl_Turn_All_Off();
			Garl_Turn_On(FRONT_LEFT);
			break;
		}
		case OPERATING_MODE_FRONT_RIGHT_ON:
		{
			Garl_Turn_All_Off();
			Garl_Turn_On(FRONT_RIGHT);
			break;
		}
		case OPERATING_MODE_FRONT_MIDDLE_ON:
		{
			Garl_Turn_All_Off();
			Garl_Turn_On(FRONT_MIDDLE);
			break;
		}
		case OPERATING_MODE_BACK_LEFT_ON:
		{
			Garl_Turn_All_Off();
			Garl_Turn_On(BACK_LEFT);
			break;
		}
		case OPERATING_MODE_BACK_RIGHT_ON:
		{
			Garl_Turn_All_Off();
			Garl_Turn_On(BACK_RIGHT);
			break;
		}
		case OPERATING_MODE_BACK_MIDDLE_ON:
		{
			Garl_Turn_All_Off();
			Garl_Turn_On(BACK_MIDDLE);
			break;
		}
	}
}

/**
  * @brief Set led color and start TIM+DMA PWM generation
  * @param[in] None
	* @date 23.03.2021
  * @retval None
  */
void set_garl_color()
{
	if(Settings.parameters.color_mode == COLOR_MODE_RAINBOW)
	{
		memcpy(tmp_hsv_color,Settings.parameters.hsv_color,6);
		if(rainbow_offset>=3620)
			rainbow_offset=0;
		else
			rainbow_offset+=Settings.parameters.change_color_speed/4;
		
		for(uint8_t section = FRONT_LEFT;section<=BACK_RIGHT;section++)
		{
			for(uint8_t i=starts[section];i<=ends[section];i++)
			{
				tmp_hsv_color[0]=(Settings.parameters.rainbow_step*(i-starts[section])+rainbow_offset/10)%360;
				hsv_to_rgb(tmp_hsv_color,result_color,60);
				ws2812_pixel_rgb_to_buf_dma(result_color[0]*light_brightness[i]/256, result_color[1]*light_brightness[i]/256, result_color[2]*light_brightness[i]/256, i);
			}
		}
	}
	else
	{
		for(int i=0;i<150;i++)
		{
			ws2812_pixel_rgb_to_buf_dma(result_color[0]*light_brightness[i]/256, result_color[1]*light_brightness[i]/256, result_color[2]*light_brightness[i]/256, i);
		}
	}
	
	ws2812_light();
}

/**
  * @brief Garland handler
  * @param[in] None
	* @date 23.03.2021
  * @retval None
  */
void Garl_Handler()
{
	turn_on_off_handler();
	colorMode_handler();
	operatingMode_handler();
	set_garl_color();
}

/**
  * @brief Function of turning on the garland section
  * @param[in] uint8_t what - section
	* @date 23.03.2021
  * @retval None
  */
void Garl_Turn_On(uint8_t what)
{
	state[what] = FILL;
}

/**
  * @brief Function of turning off the garland section
  * @param[in] uint8_t what - section
	* @date 23.03.2021
  * @retval None
  */
void Garl_Turn_Off(uint8_t what)
{
	state[what] = WASTE;
}


/**
  * @brief Function of turning on front sections
  * @param[in] None
	* @date 23.03.2021
  * @retval None
  */
void Garl_Turn_Front_On()
{
	Garl_Turn_On(FRONT_LEFT);
	Garl_Turn_On(FRONT_MIDDLE);
	Garl_Turn_On(FRONT_RIGHT);
}

/**
  * @brief Function of turning off front sections
  * @param[in] None
	* @date 23.03.2021
  * @retval None
  */
void Garl_Turn_Front_Off()
{
	Garl_Turn_Off(FRONT_LEFT);
	Garl_Turn_Off(FRONT_MIDDLE);
	Garl_Turn_Off(FRONT_RIGHT);
}

/**
  * @brief Function of turning on back sections
  * @param[in] None
	* @date 23.03.2021
  * @retval None
  */
void Garl_Turn_Back_On()
{
	Garl_Turn_On(BACK_LEFT);
	Garl_Turn_On(BACK_MIDDLE);
	Garl_Turn_On(BACK_RIGHT);
}

/**
  * @brief Function of turning off back sections
  * @param[in] None
	* @date 23.03.2021
  * @retval None
  */
void Garl_Turn_Back_Off()
{
	Garl_Turn_Off(BACK_LEFT);
	Garl_Turn_Off(BACK_MIDDLE);
	Garl_Turn_Off(BACK_RIGHT);
}

/**
  * @brief Function of turning on all sections
  * @param[in] None
	* @date 23.03.2021
  * @retval None
  */
void Garl_Turn_All_On()
{
	Garl_Turn_Front_On();
	Garl_Turn_Back_On();
}

/**
  * @brief Function of turning on off sections
  * @param[in] None
	* @date 23.03.2021
  * @retval None
  */
void Garl_Turn_All_Off()
{
	Garl_Turn_Front_Off();
	Garl_Turn_Back_Off();
}


