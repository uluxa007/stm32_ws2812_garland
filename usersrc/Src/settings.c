#include "settings.h"

NVRAM Settings;

/**
  * @brief Setting load
	*
	*	Load setting values from FLASH or external memory or backup registers (not yet implemented)
  * @param[in] None
	* @date 23.03.2021
  * @retval None
  */
void loadSettings()
{
	//uint32_t l_Address;
	//uint32_t l_Index;
	//
	//l_Address = FLASH_SETTINGS_START_ADDR;
	//l_Index = 0;
	//
	//while (l_Address<FLASH_SETTINGS_END_ADDR)
	//{
	//	DevNWRAM.data32[l_Index] = *(__IO uint32_t*)l_Address;
	//	l_Index++;
	//	l_Address += 4;
	//}
	//
	//if (DevNWRAM.settings.MagicNum != MAGIC_KEY)
	//{
	//	//clear memory
	//	memset(DevNWRAM.data32,0,sizeof(DevNWRAM.data32));
	//	
	//	DevNWRAM.settings.turn_on_off_speed=128;
	//	DevNWRAM.settings.change_color_speed=2;
	//	DevNWRAM.settings.operating_mode = OPERATING_MODE_ALL_ON;
	//	DevNWRAM.settings.color_mode = COLOR_MODE_HSV;
	//	DevNWRAM.settings.front_left_lenght=30;
	//	DevNWRAM.settings.front_middle_lenght=15;
	//	DevNWRAM.settings.front_right_lenght=30;
	//	DevNWRAM.settings.back_left_lenght=30;
	//	DevNWRAM.settings.back_middle_lenght=15;
	//	DevNWRAM.settings.back_right_lenght=30;
	//	
	//	DevNWRAM.settings.rgb_color[0]=254;
	//	DevNWRAM.settings.rgb_color[1]=0;
	//	DevNWRAM.settings.rgb_color[2]=0;
	//	
	//	DevNWRAM.settings.hsv_color[0]=0;
	//	DevNWRAM.settings.hsv_color[1]=254;
	//	DevNWRAM.settings.hsv_color[2]=254;
	//	
	//	
	//	DevNWRAM.settings.MagicNum = MAGIC_KEY;
	//	DevNWRAM.sector.NWrite =0;
	//	
	//	saveSettings();
	//}
}

/**
  * @brief Setting save
	*
	*	Save setting values to FLASH or external memory or backup registers (not yet implemented)
  * @param[in] None
	* @date 23.03.2021
  * @retval None
  */
void saveSettings()
{
	//DevNWRAM.settings.turn_on_off_speed=turn_on_off_speed;
	//DevNWRAM.settings.change_color_speed=change_color_speed;
	//DevNWRAM.settings.operating_mode=operating_mode;
	//DevNWRAM.settings.color_mode=color_mode;
	//
	//DevNWRAM.settings.front_left_lenght=front_left_lenght;
	//DevNWRAM.settings.front_middle_lenght=front_middle_lenght;
	//DevNWRAM.settings.front_right_lenght=front_right_lenght;
	//DevNWRAM.settings.back_left_lenght=back_left_lenght;
	//DevNWRAM.settings.back_middle_lenght=back_middle_lenght;
	//DevNWRAM.settings.back_right_lenght=back_right_lenght;
	//
	//DevNWRAM.settings.rgb_color[0]=rgb_color[0];
	//DevNWRAM.settings.rgb_color[1]=rgb_color[1];
	//DevNWRAM.settings.rgb_color[2]=rgb_color[2];
	//																					 
	//DevNWRAM.settings.hsv_color[0]=hsv_color[0];
	//DevNWRAM.settings.hsv_color[1]=hsv_color[1];
	//DevNWRAM.settings.hsv_color[2]=hsv_color[2];
	//
	//static FLASH_EraseInitTypeDef EraseInitStruct;
	//EraseInitStruct.TypeErase = FLASH_TYPEERASE_PAGES;
	//EraseInitStruct.PageAddress = FLASH_SETTINGS_START_ADDR;
	//EraseInitStruct.NbPages = 0x01;
	//
	//uint32_t l_Address;
	//uint32_t l_Index;
	//uint32_t l_Error;
	//
	//HAL_FLASH_Unlock();
	//HAL_FLASHEx_Erase(&EraseInitStruct,&l_Error);
	//
	//l_Address = FLASH_SETTINGS_START_ADDR;
	//l_Error = 0;
	//l_Index = 0;
	//DevNWRAM.sector.NWrite++;
	//
	//while(l_Address<FLASH_SETTINGS_END_ADDR)
	//{
	//	HAL_Delay(5);
	//	
	//	if(HAL_FLASH_Program(FLASH_TYPEPROGRAM_WORD,l_Address,DevNWRAM.data32[l_Index]) == HAL_OK)
	//	{
	//		l_Index++;
	//		l_Address+=4;
	//	}
	//}
	//
	//
	//HAL_FLASH_Lock();
}
