#ifndef _COLORS_H
#define _COLORS_H

#include "inttypes.h"

#define RGB 0
#define HSV 1

extern void HsvToRgb(uint16_t* hsv_color, uint8_t* rgb_color);
extern void hsv_to_rgb(uint16_t* hsv_color, uint16_t* rgb_color,uint16_t region);

#endif
