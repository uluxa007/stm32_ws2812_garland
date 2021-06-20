#ifndef SETTINGS_H
#define SETTINGS_H

#include "inttypes.h"
#include "menu.h"

//#define MAGIC_KEY 0xF7A90E1C
//#define FLASH_SETTINGS_START_ADDR ((uint32_t)0x0801FC00)
//#define FLASH_SETTINGS_END_ADDR FLASH_SETTINGS_START_ADDR + FLASH_PAGE_SIZE

/**
  * @brief Settings values
	*
	* Structure for easy access to fields
  */
typedef struct 
{
//-------------------------------------
	uint16_t color_mode;
	uint16_t operating_mode;
	uint16_t turn_on_off_speed;
	uint16_t change_color_speed;
//-------------------------------------
	uint16_t hsv_color[3];
	uint16_t _not_used_1;
//-------------------------------------
	uint16_t rgb_color[3];
	uint16_t _not_used_2;
//-------------------------------------
	uint16_t front_left_lenght;
	uint16_t front_middle_lenght;
	uint16_t front_right_lenght;
	uint16_t _not_used_3;
//-------------------------------------
	uint16_t back_left_lenght;
	uint16_t back_middle_lenght;
	uint16_t back_right_lenght;
	uint16_t _not_used_4;
//-------------------------------------
	uint16_t rainbow_step;
	uint16_t _not_used_5;
	uint16_t _not_used_6;
	uint16_t _not_used_7;
//-------------------------------------
	uint8_t current_page;
	uint8_t current_line;
	uint32_t MagicNum;
} Parameters;

/**
  * @brief Union to concatenate structure and array in memory
	*
	* Union for easy access to fields
  */
typedef union  {
	Parameters parameters;
	uint16_t values[PAGE_COUNT][LINE_COUNT];
	uint32_t data32[256];
} NVRAM;
extern NVRAM Settings;

void loadSettings(void);
void saveSettings(void);





#endif
