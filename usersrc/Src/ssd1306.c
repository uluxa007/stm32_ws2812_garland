/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           ssd1306.c
  * @brief          SSD1306 Display lib
  ******************************************************************************
  *
  * <h3>&copy; Copyright (c) Somov Ilia Andreevich.
  * All rights reserved.</center></h3>
	******************************************************************************
  */
#include "ssd1306.h"

// Databuffer voor het scherm
static uint8_t SSD1306_Buffer[SSD1306_WIDTH * SSD1306_HEIGHT / 8];

// Een scherm-object om lokaal in te werken
static SSD1306_t SSD1306;

/**
  * @brief Function to copy buffer to display buffer
  * @param[in] uint8_t buffer[] buffer
	* @date 23.03.2021
  * @retval None
  */
void ssd1306_CopyToBuffer(uint8_t buffer[SSD1306_WIDTH * SSD1306_HEIGHT / 8])
{
	memcpy(SSD1306_Buffer,buffer,SSD1306_WIDTH * SSD1306_HEIGHT / 8);
}

/**
  * @brief Function to copy buffer to display buffer
  * @param[in] I2C_HandleTypeDef i2c_port - i2c port
	* @param[in] uint8_t address - I2C address
	* @date 23.03.2021
  * @retval None
  */
void ssd1306_Init(I2C_HandleTypeDef i2c_port, uint8_t address)
{	
  SSD1306.I2C_port = i2c_port;
  SSD1306.Address = address;
  // Waiting for SEG/COM ON after reset
  HAL_Delay(100);
  // Initialize LCD
  uint8_t init_data[] = {0xAE, 0xA6, 0x20, 0x00, 0x21, 0x00, 0x7F, 0x22, 0x00, 0x07, 0xA1, 0xC8, 0xA8, 0x3F, 0x81, 0x7F, 0x8D, 0x14, 0xAF};
  // 0xAE - display off
  // 0xA6 - normal (not inversed)
  // 0x20, 0x00 - page horizontal adressing mode
  // 0x21, 0x00, 0x7F - column address from 0 to 127
  // 0x22, 0x00, 0x07 - page address from 0 to 7
  // 0xA1 - segment re-map (vertical mirroring)
  // 0xC8 - COM scan direction (horizontal mirroring)
  // 0xA8, 0x3F - multiplex ratio
  // 0x81, 0x7F - contrast ratio 127 
  // 0x8D, 0x14 - enable charge pump
  // 0xAF - display on (only just after enabling charge pump)
  ssd1306_SendToDisplay(Commands, init_data, sizeof(init_data));
  // clearing screen
  ssd1306_Fill(Black);
  ssd1306_UpdateScreen();
  // setting default position
  SSD1306.CurrentX = 0;
  SSD1306.CurrentY = 0;
}

/**
  * @brief Function to fill buffer with selected color
  * @param[in] SSD1306_COLOR color - color
	* @date 23.03.2021
  * @retval None
  */
void ssd1306_Fill(SSD1306_COLOR color) 
{
	if(color == White)
		memset(SSD1306_Buffer,0xFF,sizeof(SSD1306_Buffer));
	else
		memset(SSD1306_Buffer,0x00,sizeof(SSD1306_Buffer));
}


void ssd1306_ThinOut(SSD1306_COLOR color,uint8_t thin) 
{
	for(uint8_t i=0;i<128;i+=thin)
	{
		for(uint8_t j=0;j<64;j+=thin)
		{
			ssd1306_DrawPixel(i,j,color);
		}
	}
}


/**
  * @brief Function to update screen
  * @param[in] None
	* @date 23.03.2021
  * @retval None
  */
void ssd1306_UpdateScreen(void) 
{
  //uint8_t update_region_data[6] = {0x21, 0x00, 0x7F, 0x22, 0x00, 0x07};
  ////0x21, 0x00, 0x7F - column address from 0 to 127
  ////0x22, 0x00, 0x07 - page address from 0 to 7
  //ssd1306_SendToDisplay(Commands, update_region_data, 6);

  //update pages from 0 to 7
  for(uint32_t page = 0; page < 8; page++) 
  {
    ssd1306_SendToDisplay(Datas, &SSD1306_Buffer[SSD1306_WIDTH * page], SSD1306_WIDTH);
  }
}

/**
  * @brief Draw pixel on screen buffer
  * @param[in] uint32_t x - x coordinate of pixel
  * @param[in] uint32_t y - y coordinate of pixel
	* @param[in] SSD1306_COLOR color - color of pixel
	* @date 23.03.2021
  * @retval None
  */
void ssd1306_DrawPixel(uint32_t x, uint32_t y, SSD1306_COLOR color)
{
  if((x < SSD1306_WIDTH) && (y < SSD1306_HEIGHT)) 
  {
    if (color == White)
    {
      SSD1306_Buffer[x + (y / 8) * SSD1306_WIDTH] |= 1 << (y % 8);
    } 
    else 
    {
      SSD1306_Buffer[x + (y / 8) * SSD1306_WIDTH] &= ~(1 << (y % 8));
    }
  }
}

/**
  * @brief Write char on buffer
  * @param[in] char ch - char to write
  * @param[in] FontDef Font - font of char
	* @param[in] SSD1306_COLOR color - color of char
	* @date 23.03.2021
  * @retval None
  */
void ssd1306_WriteChar(char ch, FontDef Font, SSD1306_COLOR color)
{
  uint32_t pixel, x;
  
  if ((((SSD1306.CurrentX + Font.FontWidth) < SSD1306_WIDTH)  && ((SSD1306.CurrentY + Font.FontHeight) < SSD1306_HEIGHT)))
  {
    // write char to display buffer
    for (uint32_t y = 0; y < Font.FontHeight; y++)
    {
      // get font pixel
      if(ch < 127)
       pixel = Font.fontEn[(ch - 32) * Font.FontHeight + y];
      else
       pixel = Font.fontRu[(ch - 192) * Font.FontHeight + y]; 
      // write pixel to display buffer
      x = Font.FontWidth;
      while(x--)
      {
        if (pixel & 0x0001) 
        {
          ssd1306_DrawPixel(SSD1306.CurrentX + x, (SSD1306.CurrentY + y), color);
        } 
        else 
        {
          ssd1306_DrawPixel(SSD1306.CurrentX + x, (SSD1306.CurrentY + y), (SSD1306_COLOR)!color);
        }
        pixel >>= 1;
      }
    } 
  }
  
  // going to next position
  SSD1306.CurrentX += Font.FontWidth;
}

/**
  * @brief Write string on buffer
  * @param[in] char* str - string to write
  * @param[in] FontDef Font - font of string
	* @param[in] SSD1306_COLOR color - color of string
	* @date 23.03.2021
  * @retval None
  */
void ssd1306_WriteString(char* str, FontDef Font, SSD1306_COLOR color)
{
  // We schrijven alle char tot een nulbyte
  while (*str) 
  {
    ssd1306_WriteChar(*str, Font, color);
    
    // Volgende char
    str++;
  }
  
}

void ssd1306_WriteInt(int number, FontDef Font, SSD1306_COLOR color)
{
	int count=0,copy=number;
	while(copy>9)
	{
		count++;
		copy=copy/10;
	}
	copy=number;
	count++;
	char result[16];
	int v=0;
	while(copy>9)
	{
		result[v++]=(copy%10)+'0';
		copy=copy/10;
	}
	result[v++]=copy+'0';
	result[v]='\0';
	char t;
	for (int i = 0; i < v / 2; i++)
    {
        t = result[i];
        result[i] = result[v - 1 - i];
        result[v - 1 - i] = t;
    }
	ssd1306_WriteString(result, Font, color);
}

/**
  * @brief Set cursor on buffer
  * @param[in] uint32_t x - x coordinate of cursor
  * @param[in] uint32_t y - y coordinate of cursor
	* @date 23.03.2021
  * @retval None
  */
void ssd1306_SetCursor(uint32_t x, uint32_t y) 
{
	SSD1306.CurrentX = x;
	SSD1306.CurrentY = y;
}

/**
  * @brief Set contrast of display
  * @param[in] uint8_t contrast - contrast
	* @date 23.03.2021
  * @retval None
  */
void ssd1306_SetContrast(uint8_t contrast)
{
  //contrast command with empty data
  uint8_t contrast_data[2] = {0x81};
  //adding contrast data
  contrast_data[1] = contrast;
  //and send to display
  ssd1306_SendToDisplay(Commands, contrast_data, 2);
}


/**
  * @brief Send data to display
  * @param[in] SSD1306_DATA_TYPE type - data type (Commands or Datas)
  * @param[in] uint8_t *data - data buffer
  * @param[in] uint8_t length - data lenght
	* @date 23.03.2021
  * @retval None
  */
static void ssd1306_SendToDisplay(SSD1306_DATA_TYPE type, uint8_t *data, uint16_t length)
{
	//HAL_I2C_Mem_Write_IT(&(SSD1306.I2C_port), SSD1306.Address, type, 1, data, length);
	//HAL_Delay(5);
  HAL_I2C_Mem_Write(&(SSD1306.I2C_port), SSD1306.Address, type, 1, data, length, 10);
}
