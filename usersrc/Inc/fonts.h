/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           fonts.h
  * @brief          Fonts
  ******************************************************************************
  *
  * <h3>&copy; Copyright (c) Somov Ilia Andreevich.
  * All rights reserved.</center></h3>
	******************************************************************************
  */
#ifndef __FONTS_H
#define __FONTS_H

/**
  * @brief Font parameters main structure
	*
  */
typedef struct {
  const unsigned char FontWidth;
  const unsigned char FontHeight;
  const unsigned char *fontEn;
  const unsigned char *fontRu;
} FontDef;

/**
  * @brief Available fonts
	*
  */
extern FontDef Font_7x9;

#endif

