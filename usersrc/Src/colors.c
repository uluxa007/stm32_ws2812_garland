#include "colors.h"

void hsv_to_rgb(uint16_t* hsv_color, uint16_t* rgb_color, uint16_t region)
{
	uint16_t H_i = (hsv_color[0] / region) % 6;

	uint16_t V_min = ((255 - hsv_color[1]) * hsv_color[2]) / 255;
	uint16_t a = ((hsv_color[2] - V_min) * (hsv_color[0] % region)) / region;
	uint16_t V_inc = V_min + a;
	uint16_t V_dec = hsv_color[2] - a;
	uint16_t V = hsv_color[2];

	switch (H_i)
	{
	case 0:
	{
		rgb_color[0] = V;
		rgb_color[1] = V_inc;
		rgb_color[2] = V_min;
		break;
	}
	case 1:
	{
		rgb_color[0] = V_dec;
		rgb_color[1] = V;
		rgb_color[2] = V_min;
		break;
	}
	case 2:
	{
		rgb_color[0] = V_min;
		rgb_color[1] = V;
		rgb_color[2] = V_inc;
		break;
	}
	case 3:
	{
		rgb_color[0] = V_min;
		rgb_color[1] = V_dec;
		rgb_color[2] = V;
		break;
	}
	case 4:
	{
		rgb_color[0] = V_inc;
		rgb_color[1] = V_min;
		rgb_color[2] = V;
		break;
	}
	case 5:
	{
		rgb_color[0] = V;
		rgb_color[1] = V_min;
		rgb_color[2] = V_dec;
		break;
	}
	}
}

