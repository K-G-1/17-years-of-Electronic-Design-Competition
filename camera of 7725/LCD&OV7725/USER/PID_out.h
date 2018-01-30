#ifndef __DELAY_H
#define __DELAY_H 			   
#include <sys.h>	  
#include "ov7725.h"



struct PID_data{
	
	float camera_KP;
	float camera_KI;
	float camera_KD;
	
	float camera_pid_error;
	float camera_pid_merrer;
	float camera_pid_deriv;
	
	float camera_pid_KP_out;
	float camera_pid_KI_out;
	float camera_pid_KD_out;
	
	float camera_pid_out;
	
	float camera_pid_error_old;
	
};
struct _camera_PID_ctrl
{
	struct PID_data Pitch;
	struct PID_data Roll;
	struct PID_data Yaw;
	
};

extern struct _camera_PID_ctrl camera_PID_ctrl;

int Camera_PID_Ctrl(uint16_t state_buff[2][100]);
int Tracking_mode(uint16_t state_buff[2][100]);
int flight_PID(uint16_t date_buff[2][100]);
	
void Ctrl_PID_init(void);
void CCD_PID_data(u8 mid_data,float T);
u8 CCD_Tracking_mode(_mid_x_line mid_point,unsigned char state_buff[][128],int sizee);



#endif



