#include "PID_out.h"
#include "include.h"
#include <math.h>
#include <stdio.h>




struct _camera_PID_ctrl camera_PID_ctrl;
#define TO_angle  180/3.1416



void Ctrl_PID_init(void)
{
	camera_PID_ctrl.Pitch.camera_KP = 1;
	camera_PID_ctrl.Pitch.camera_KI = 0;
	camera_PID_ctrl.Pitch.camera_KD = 0;
	
	camera_PID_ctrl.Roll.camera_KP = 1;
	camera_PID_ctrl.Roll.camera_KI = 0;
	camera_PID_ctrl.Roll.camera_KD = 0;
	
	camera_PID_ctrl.Yaw.camera_KP = 1;
	camera_PID_ctrl.Yaw.camera_KI = 0;
	camera_PID_ctrl.Yaw.camera_KD = 0;
	
	
}

int Tracking_mode(uint16_t state_buff[2][100])
{
	int i,j;
	static int turn_flag=0;
	
	for(i=30;i<50;i++)
	{
		if(state_buff[horizontal][i] == 0)        //前方都有白点
		{
			if((state_buff[horizontal][i+1] == 0)&&(state_buff[horizontal][i-1] == 0))		//有连续的白点
			{
				if(state_buff[horizontal][20] == 0)               //确定前方没有黑线
				{
					
					if(state_buff[vertical][10]&&state_buff[vertical][90])
					{
						return stop;
					}
					else if(state_buff[vertical][10]&&turn_flag == 0)
					{
						turn_flag++;
						return turn_left;
					}
					else if(state_buff[vertical][90]&&turn_flag== 0)
					{
						turn_flag++;
						return turn_right;
					}
				}
			}
		}
		else
		{
			turn_flag=0;
			
		}
	}
	return forward;
}



int flight_PID(uint16_t date_buff[2][100])
{
	int i;
	double angle=0;
/***********************************
	噪点不消除总会有误差，不能很好的定住
************************************/
	i=30;
	do
	{
		camera_PID_ctrl.Pitch.camera_pid_error =   50- i;
		i++;
		
	}while(camera_min_data[0][i] == 0&&i< 80);

	if(camera_min_data[0][50] != 0)															//roll根据飞行器坐标的X轴确定，保证黑点在原点中心
		camera_PID_ctrl.Roll.camera_pid_error =   50- camera_min_data[0][50];
	else 
		camera_PID_ctrl.Roll.camera_pid_error = 0;
	
//	if(date_buff[0][40] && date_buff[0][50])
//	{
//		angle=10/(date_buff[0][40]- date_buff[0][50]);
//		camera_PID_ctrl.Yaw.camera_pid_error = atan(angle) * TO_angle;
//	}
//	else camera_PID_ctrl.Yaw.camera_pid_error=0;
	
	
	/**************************/
	if(camera_PID_ctrl.Pitch.camera_pid_error>-3&&camera_PID_ctrl.Pitch.camera_pid_error<3)
		camera_PID_ctrl.Pitch.camera_pid_error=0;
	camera_PID_ctrl.Pitch.camera_pid_KP_out = camera_PID_ctrl.Pitch.camera_KP * camera_PID_ctrl.Pitch.camera_pid_error;
	
	camera_PID_ctrl.Pitch.camera_pid_deriv = camera_PID_ctrl.Pitch.camera_pid_error - camera_PID_ctrl.Pitch.camera_pid_error_old ;
	camera_PID_ctrl.Pitch.camera_pid_KD_out = camera_PID_ctrl.Pitch.camera_KD * camera_PID_ctrl.Pitch.camera_pid_deriv ;
	camera_PID_ctrl.Pitch.camera_pid_error_old = camera_PID_ctrl.Pitch.camera_pid_error ;
	
	camera_PID_ctrl.Pitch.camera_pid_out = camera_PID_ctrl.Pitch.camera_pid_KP_out + camera_PID_ctrl.Pitch.camera_pid_KD_out;
	
	/******************************/
	if(camera_PID_ctrl.Roll.camera_pid_error>-3&&camera_PID_ctrl.Roll.camera_pid_error<3)
		camera_PID_ctrl.Roll.camera_pid_error=0;
	camera_PID_ctrl.Roll.camera_pid_KP_out = camera_PID_ctrl.Roll.camera_KP * camera_PID_ctrl.Roll.camera_pid_error;
	
	camera_PID_ctrl.Roll.camera_pid_deriv = camera_PID_ctrl.Roll.camera_pid_error - camera_PID_ctrl.Roll.camera_pid_error_old;
	camera_PID_ctrl.Roll.camera_pid_KD_out = camera_PID_ctrl.Roll.camera_KD *camera_PID_ctrl.Roll.camera_pid_deriv;
	camera_PID_ctrl.Roll.camera_pid_error_old = camera_PID_ctrl.Roll.camera_pid_error;
	
	camera_PID_ctrl.Roll.camera_pid_out = camera_PID_ctrl.Roll.camera_pid_KP_out + camera_PID_ctrl.Roll.camera_pid_KD_out;
	
	/********************************************/
	if(camera_PID_ctrl.Yaw.camera_pid_error>-3&&camera_PID_ctrl.Yaw.camera_pid_error<3)
		camera_PID_ctrl.Yaw.camera_pid_error=0;
	camera_PID_ctrl.Yaw.camera_pid_KP_out = camera_PID_ctrl.Yaw.camera_KP * camera_PID_ctrl.Yaw.camera_pid_error;
	
	camera_PID_ctrl.Yaw.camera_pid_deriv = camera_PID_ctrl.Yaw.camera_pid_error - camera_PID_ctrl.Yaw.camera_pid_error_old;
	camera_PID_ctrl.Yaw.camera_pid_KD_out = camera_PID_ctrl.Yaw.camera_KD *camera_PID_ctrl.Yaw.camera_pid_deriv;
	camera_PID_ctrl.Yaw.camera_pid_error_old = camera_PID_ctrl.Yaw.camera_pid_error;
	
	camera_PID_ctrl.Yaw.camera_pid_out = camera_PID_ctrl.Yaw.camera_pid_KP_out + camera_PID_ctrl.Yaw.camera_pid_KD_out;
	

	oled_dis_data(camera_PID_ctrl.Pitch.camera_pid_out,camera_PID_ctrl.Roll.camera_pid_out,camera_PID_ctrl.Yaw.camera_pid_out,0);
}



int Camera_PID_Ctrl(uint16_t state_buff[2][100])
{
	int state_flag;
	
	state_flag = Tracking_mode(state_buff);
	OLED_P6x8data(0,1,state_flag);
	if(state_flag == forward)
	{
		flight_PID(state_buff);
	}
	else if(state_flag == turn_left)
	{
		camera_PID_ctrl.Pitch.camera_pid_out = 0;
		camera_PID_ctrl.Roll.camera_pid_out = 0;
		
		
		
	}
	else if(state_flag == turn_right)
	{
		camera_PID_ctrl.Pitch.camera_pid_out = 0;
		camera_PID_ctrl.Roll.camera_pid_out = 0;
	}
	else if(state_flag == stop)
	{
		camera_PID_ctrl.Pitch.camera_pid_out = 0;
		camera_PID_ctrl.Roll.camera_pid_out = 0;
	}
	
}
 extern u8 camera_width;

/**************************************************************/
void CCD_PID_data(u8 mid_data,float T)
{
	static u8 i,k;
	static int ccd_fifter[10];
	int sum =0;
	
	camera_data.error = 64 - mid_data;

//	camera_data.devir = (camera_data.error - camera_data.error_old)/0.07f* 50/camera_data.width;         
//	camera_data.error_old = camera_data.error;
	
	sand_data(&camera_data,USART2_Tx_data);
	OLED_P6x8data(30,1, camera_data.error);
//	OLED_P6x8data(60,1,camera_data.error_old );
//	OLED_P6x8data(90,1,camera_data.devir);
}
u8 CCD_Tracking_mode(_mid_x_line mid_point,unsigned char state_buff[][128],int sizee)
{
	int i,j;
	static int turn_flag=0;
	u8 white_count_H_64=0,white_count_H_32=0;
	u8 left_flag,right_flag;
	
	if(state_buff[0][10] == BLACK)                          //左边有黑线
	 {
		 left_flag=1;
	 }
	 else if(state_buff[0][118] == BLACK)                       //右边有黑线
	 {
		 right_flag=1;
	 }
	 else
	 {
		left_flag =0 ;
		right_flag = 0;
	 }
	
	 
	for(i=0;i<128;i++)                                      //计算黑线的长度
	{
		 if(state_buff[0][i]==BLACK)
			white_count_H_64++;
		 
		
	}
	for(i=0;i<128;i++)                                    //计算前方有没黑线
	{
		 if(state_buff[3][i]==WHITE)
			white_count_H_32++;
		
	}
	if(white_count_H_64 >= 125)                          //T型or十字型
	{
		if(white_count_H_32 >= 125)                     //T型
		{
			 return stop;
		}
		else                                            //十字型
			return forward;
	}
    else if(white_count_H_64 >= 50)                     //转向
	{
		 if(left_flag == 1)
			 return turn_left;
		 else if(right_flag == 1)
			 return turn_right ;
		 else
			 return forward;
	}
	 else 
		 return forward;
	
//	for(i=30;i<50;i++)
//	{
//		if(state_buff[horizontal][i] == 0)        //前方都有白点
//		{
//			if((state_buff[horizontal][i+1] == 0)&&(state_buff[horizontal][i-1] == 0))		//有连续的白点
//			{
//				if(state_buff[horizontal][20] == 0)               //确定前方没有黑线
//				{
//					
//					if(mid_point.vertical_64 >50&&mid_point.vertical_172 >50)
//					{
//						return stop;
//					}
//					else if(state_buff[vertical][10]&&turn_flag == 0)
//					{
//						turn_flag++;
//						return turn_left;
//					}
//					else if(state_buff[vertical][90]&&turn_flag== 0)
//					{
//						turn_flag++;
//						return turn_right;
//					}
//				}
//			}
//		}
//		else
//		{
//			turn_flag=0;
//			
//		}
//	}
//	return forward;
}

