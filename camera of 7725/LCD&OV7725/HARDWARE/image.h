#ifndef __image_H
#define __image_H
#include "sys.h"


struct _position
{
	int H_x_min;
	int H_x_max;
	
	int V_y_min;
	int V_y_max;
	
	int x_min;
	int x_max;
	
	int y_min;
	int y_max;
	
	int position_x;
	int position_y;
	
	int position_x_old;
	int position_y_old;
	
	
	int dri_flag;
	int Y_old;
	
	u8 sound_flag ;
	u8 take_off_flag;

};

extern struct _position position;

void ImagDisp(uint16_t sx,uint16_t sy,uint16_t width,uint16_t height);


int midline_deal(void);
int mid_line_deal(unsigned char data[128],u8 mid_old);
int flight_data(float T);
void DT_usart1(u8 com_data);






#endif


