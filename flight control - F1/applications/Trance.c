#include "Trance.h"
#include "ctrl.h"
#include "ultrasonic.h"
#include "fly_mode.h"
#include "PID.h"
#include "ano_of.h"
#include "warn.h"



struct _CCD_PID  CCD_CTRL_PID;
struct _CCD_PID_H CCD_CTRL_PID_H;
struct _camera_Tance camera_Trance;
struct _Duty Duty;

// void CCD_ctrl(u8 mid,float T,u8 mode)
//{

//	if(camera_Trance.take_off_flag == 1) 
//	{
//		CCD_CTRL_PID.KI_out = 5;
//		CCD_CTRL_PID_H.KI_out = 5;
//	}
//	else 
//	{
//		CCD_CTRL_PID.KI_out =0 ;
//		CCD_CTRL_PID_H.KI_out =0;
//	}
//	
////	camera_Trance.PID_out = camera_Trance.KP_out + camera_Trance.KI_out + camera_Trance.KD_out ;
//	
////   camera_Trance.PID_out =  pid_setup.groups.ctrl4.kp * CCD_CTRL_PID.shell_Pout;	
///******************************************/  
//	if(mode == 0)
//	{
//	   CCD_CTRL_PID.KP_out =  pid_setup.groups.ctrl3.kp *  (CCD_CTRL_PID.error + camera_Trance.PID_out_H) ;
////	   CCD_CTRL_PID.KP_out =  pid_setup.groups.ctrl3.kp* CCD_CTRL_PID.shell_Pout ;
////	   CCD_CTRL_PID.KI_out = pid_setup.groups.ctrl3.ki * CCD_CTRL_PID.merrer ;
//	   CCD_CTRL_PID.KD_out = pid_setup.groups.ctrl3.kd * CCD_CTRL_PID.devir ;
//	 
//	   CCD_CTRL_PID.PID_out = CCD_CTRL_PID.KP_out + CCD_CTRL_PID.KI_out + CCD_CTRL_PID.KD_out ;


//		CCD_CTRL_PID_H.KP_out = pid_setup.groups.ctrl3.kp * (CCD_CTRL_PID_H.error + camera_Trance.PID_out_V) ;
////		CCD_CTRL_PID_H.KI_out = pid_setup.groups.ctrl3.ki * CCD_CTRL_PID_H.merrer ;
//		CCD_CTRL_PID_H.KD_out = pid_setup.groups.ctrl3.kd * CCD_CTRL_PID_H.devir ;
//		
//		CCD_CTRL_PID_H.PID_out = CCD_CTRL_PID_H.KP_out + CCD_CTRL_PID_H.KI_out + CCD_CTRL_PID_H.KD_out ;
//	}
//	else if(mode == 1)
//	{
//		CCD_CTRL_PID.KP_out =  pid_setup.groups.ctrl3.kp *  (CCD_CTRL_PID.error + CCD_CTRL_PID.shell_Pout) ;
////	   CCD_CTRL_PID.KP_out =  pid_setup.groups.ctrl3.kp* CCD_CTRL_PID.shell_Pout ;
//	   CCD_CTRL_PID.KI_out = pid_setup.groups.ctrl3.ki * CCD_CTRL_PID.merrer ;
//	   CCD_CTRL_PID.KD_out = pid_setup.groups.ctrl3.kd * CCD_CTRL_PID.devir ;
//	 
//	   CCD_CTRL_PID.PID_out = CCD_CTRL_PID.KP_out + CCD_CTRL_PID.KI_out + CCD_CTRL_PID.KD_out ;


////		CCD_CTRL_PID_H.KP_out = pid_setup.groups.ctrl3.kp * (CCD_CTRL_PID_H.error ) ;
////		CCD_CTRL_PID_H.KI_out = pid_setup.groups.ctrl3.ki * CCD_CTRL_PID_H.merrer ;
////		CCD_CTRL_PID_H.KD_out = pid_setup.groups.ctrl3.kd * CCD_CTRL_PID_H.devir ;
//		
//		CCD_CTRL_PID_H.PID_out = 0 ;
//	}
//	else if(mode == 2)
//	{
//		 CCD_CTRL_PID.KP_out =  pid_setup.groups.ctrl3.kp *  (CCD_CTRL_PID.error + camera_Trance.PID_out_H) ;
////	   CCD_CTRL_PID.KP_out =  pid_setup.groups.ctrl3.kp* CCD_CTRL_PID.shell_Pout ;
////	   CCD_CTRL_PID.KI_out = pid_setup.groups.ctrl3.ki * CCD_CTRL_PID.merrer ;
//	   CCD_CTRL_PID.KD_out = pid_setup.groups.ctrl3.kd * CCD_CTRL_PID.devir ;
//	 
//	   CCD_CTRL_PID.PID_out = CCD_CTRL_PID.KP_out + CCD_CTRL_PID.KI_out + CCD_CTRL_PID.KD_out ;


//		CCD_CTRL_PID_H.KP_out = pid_setup.groups.ctrl3.kp * (CCD_CTRL_PID_H.error + camera_Trance.PID_out_V) ;
////		CCD_CTRL_PID_H.KI_out = pid_setup.groups.ctrl3.ki * CCD_CTRL_PID_H.merrer ;
//		CCD_CTRL_PID_H.KD_out = pid_setup.groups.ctrl3.kd * CCD_CTRL_PID_H.devir ;
//		
//		CCD_CTRL_PID_H.PID_out = CCD_CTRL_PID_H.KP_out + CCD_CTRL_PID_H.KI_out + CCD_CTRL_PID_H.KD_out ;
//	}
//		
//}

///*******************************************************
//    mode_state 						飞行模式，姿态，定高
//    change_CCD_data     			开始循迹标志位
//    camera_Trance.take_off_flag     自动降落标志位	降落时不前进
//    camera_Trance.trance_flag       飞行方向
//	duty_mode :     				飞行模式   下位机结合按键模式
//									0  ：定点 1：前进     2：跟踪  
//    Duty.fly_mode ：			    0 定点，1 前进
//	Duty.time：						按时降落
//    Duty.time_cycle ： 				运行时间
//*******************************************************/

//void direction_control(float T,u8 duty_mode)
//{
////	u8 mode ;
//	
//	if( mode_state ==2 )
//	{

//		if(change_CCD_data ==1)
//		{
//			Duty.time_cycle += T;
//			 if(duty_mode == 0)
//			 {
//				Duty.fly_mode=0 ; 
//				 
//			 }
//			 else if(duty_mode == 1)
//			 {
//			    Duty.fly_mode=1 ;
//			 }
//			 else if(duty_mode == 2 )
//			 {
//				Duty.fly_mode=2 ; 
//			 }
//			
//			CCD_ctrl(mid_line,T,Duty.fly_mode);
//			if(Duty.fly_mode == 0)
//			{
//				except_A.x  = MAX_CTRL_ANGLE  *( my_deathzoom( (0) ,0,30 )/500.0f );   //30 ;   //max 30度	
//				except_A.y  = MAX_CTRL_ANGLE  *( my_deathzoom( (0) ,0,30 )/500.0f ); 
//				
//				Duty.time += T;
//				if(Duty.time >= 15.0f && Switch.count_mode== 0 )
//				{
//					camera_Trance.take_off_flag = 1;
//				}
////				if(Duty.time >= 20.0f && Switch.count_mode== 1 )
////				{
////					camera_Trance.take_off_flag = 1;
////				}
//				
//			}
//			else if(Duty.fly_mode ==1)
//			{
//				except_A.x  = MAX_CTRL_ANGLE  *( my_deathzoom( (0) ,0,30 )/500.0f );   //30 ;   //max 30度	
//				except_A.y  = MAX_CTRL_ANGLE  *( my_deathzoom( (-70) ,0,30 )/500.0f ); 
//				
//				Duty.time= 0;
//			}
//			else if(Duty.fly_mode == 2)
//			{
//				except_A.x  = MAX_CTRL_ANGLE  *( my_deathzoom( (0) ,0,30 )/500.0f );   //30 ;   //max 30度	
//				except_A.y  = MAX_CTRL_ANGLE  *( my_deathzoom( (0) ,0,30 )/500.0f ); 
//	
//				Duty.time += T;
//				if(Duty.time >= 40.0f)
//				{
//					camera_Trance.take_off_flag = 1;
////					camera_Trance.trance_flag = 1;
//				}
//			}
//			

//			
//		}
//		else 
//		{
//			Duty.time_cycle = 0;
//			Duty.time = 0;
//			except_A.x  = MAX_CTRL_ANGLE  *( my_deathzoom( ( CH_filter[ROL]) ,0,30 )/500.0f );   //30
//			except_A.y  = MAX_CTRL_ANGLE  *( my_deathzoom( (-CH_filter[PIT]) ,0,30 )/500.0f );  //30
//			
//			CCD_CTRL_PID.PID_out =0 ;
//			CCD_CTRL_PID.shell_Pout = 0;
//			CCD_CTRL_PID.merrer = 0;
//			CCD_CTRL_PID_H.shell_Pout = 0;
//			CCD_CTRL_PID_H.PID_out  = 0;
//			CCD_CTRL_PID_H.merrer = 0;
//			
//			camera_Trance.merrer_H = 0;
//			camera_Trance.merrer_V = 0;
//			camera_Trance.PID_out_H = 0 ;
//			camera_Trance.PID_out_V = 0 ;
//  		}
//	    
//		
//	}
//	else 
//	{
//		Duty.time_cycle = 0;
//			Duty.time = 0;
//		except_A.x  = MAX_CTRL_ANGLE  *( my_deathzoom( ( CH_filter[ROL]) ,0,30 )/500.0f );   //30
//		except_A.y  = MAX_CTRL_ANGLE  *( my_deathzoom( (-CH_filter[PIT]) ,0,30 )/500.0f );  //30


//		CCD_CTRL_PID.PID_out =0 ;
//		CCD_CTRL_PID.shell_Pout = 0;
//	    CCD_CTRL_PID.merrer = 0;
//		CCD_CTRL_PID_H.shell_Pout = 0;
//		CCD_CTRL_PID_H.PID_out  = 0;
//		CCD_CTRL_PID_H.merrer = 0;
//		
//		camera_Trance.merrer_H = 0;
//		camera_Trance.merrer_V = 0;
//		camera_Trance.PID_out_H = 0 ;
//		camera_Trance.PID_out_V = 0 ;
//	}
//}

extern u8 CCD_OK_flag;
extern int16_t Openmv_err_x,Openmv_err_y,Openmv_err_flag;
void camera_shell_pid(void)
{
//	if(Openmv_err_flag == 1)
//	{
//		if( camera_Trance.data >-50 && camera_Trance.data< 50)
//			camera_Trance.error_H  =  (float)(camera_Trance.data  - OF_ALT2 * tan(Roll / 57.3f));
//		if( camera_Trance.data_V >-50 && camera_Trance.data_V< 50)
//			camera_Trance.error_V  =  (float)(camera_Trance.data_V  - OF_ALT2 * tan(Pitch / 57.3f));
		camera_Trance.error_H =  LIMIT(Openmv_err_y,-30,30);
		camera_Trance.KP_out_H = pid_setup.groups.ctrl4.kp * camera_Trance.error_H;

		camera_Trance.merrer_H += camera_Trance.error_H;
		camera_Trance.merrer_H = LIMIT(camera_Trance.merrer_H,-50,50);
		camera_Trance.KI_out_H = pid_setup.groups.ctrl4.ki *   camera_Trance.merrer_H;
		
//		camera_Trance.devir_H = (camera_Trance.error_H - camera_Trance.error_H_old);
		camera_Trance.KD_out_H = pid_setup.groups.ctrl4.kd * camera_Trance.devir_H;
//		camera_Trance.error_H_old = camera_Trance.error_H;
/***********************************************************************/
        camera_Trance.error_V =  LIMIT(Openmv_err_x,-30,30);
		camera_Trance.KP_out_V = pid_setup.groups.ctrl4.kp * camera_Trance.error_V;

		camera_Trance.merrer_V += camera_Trance.error_V;
		camera_Trance.merrer_V = LIMIT(camera_Trance.merrer_V,-50,50);
		camera_Trance.KI_out_V = pid_setup.groups.ctrl4.ki *   camera_Trance.merrer_V;
		
//		camera_Trance.devir_V = (camera_Trance.error_V - camera_Trance.error_V_old);
		camera_Trance.KD_out_V = pid_setup.groups.ctrl4.kd * camera_Trance.devir_V;
//		camera_Trance.error_V_old = camera_Trance.error_V;

		
		camera_Trance.PID_out_H = camera_Trance.KP_out_H + camera_Trance.KI_out_H + camera_Trance.KD_out_H ; 
		camera_Trance.PID_out_V = camera_Trance.KP_out_V + camera_Trance.KI_out_V + camera_Trance.KD_out_V ;
        
        camera_Trance.PID_out_H = LIMIT(camera_Trance.PID_out_H,-30,30);
        camera_Trance.PID_out_V = LIMIT(camera_Trance.PID_out_V,-30,30);
        Openmv_err_flag = 0;
//	}
}
void mode_0_duty(float T,u8 mode)
{
	static u8 control_count = 0;
	Duty.time += T;                         //计时器  开始之后15s之后降落       由于启动油门需要时间只有10s左右悬停
	//期望角度
	except_A.x  = MAX_CTRL_ANGLE  *( my_deathzoom( (0) ,0,30 )/500.0f );   //30 ;   //max 30度	
	except_A.y  = MAX_CTRL_ANGLE  *( my_deathzoom( (0) ,0,30 )/500.0f ); 
	
	//计算PID  CCD_CTRL_PID.PID_out 横轴方向 CCD_CTRL_PID_H.PID_out 纵轴方向
	CCD_CTRL_PID.KP_out =  pid_setup.groups.ctrl3.kp *  (CCD_CTRL_PID.error) ;
	CCD_CTRL_PID.KD_out = pid_setup.groups.ctrl3.kd * CCD_CTRL_PID.devir ;

	CCD_CTRL_PID.PID_out = CCD_CTRL_PID.KP_out + CCD_CTRL_PID.KI_out + CCD_CTRL_PID.KD_out ;


	CCD_CTRL_PID_H.KP_out = pid_setup.groups.ctrl3.kp * (CCD_CTRL_PID_H.error) ;
	CCD_CTRL_PID_H.KD_out = pid_setup.groups.ctrl3.kd * CCD_CTRL_PID_H.devir ;

	CCD_CTRL_PID_H.PID_out = CCD_CTRL_PID_H.KP_out + CCD_CTRL_PID_H.KI_out + CCD_CTRL_PID_H.KD_out ;
	
	if(Duty.time > 15.0f)
		camera_Trance.take_off_flag = 1;
//	else 
//		hight_PID_ctrl.core.set_hight = 1200; 
}

 
void mode_1_duty(float T,u8 mode)
{
	Duty.time += T;
	
	if(Duty.time <= 3.0f)
	{
		except_A.x  = MAX_CTRL_ANGLE  *( my_deathzoom( (0) ,0,30 )/500.0f );   //30 ;   //max 30度	
		except_A.y  = MAX_CTRL_ANGLE  *( my_deathzoom( (0) ,0,30 )/500.0f ); 
		
		CCD_CTRL_PID.KP_out =  pid_setup.groups.ctrl3.kp *  (CCD_CTRL_PID.error ) ;
		CCD_CTRL_PID.KD_out = pid_setup.groups.ctrl3.kd * CCD_CTRL_PID.devir ;

		CCD_CTRL_PID.PID_out = CCD_CTRL_PID.KP_out + CCD_CTRL_PID.KI_out + CCD_CTRL_PID.KD_out ;


		CCD_CTRL_PID_H.KP_out = pid_setup.groups.ctrl3.kp * (CCD_CTRL_PID_H.error ) ;
		CCD_CTRL_PID_H.KD_out = pid_setup.groups.ctrl3.kd * CCD_CTRL_PID_H.devir ;

		CCD_CTRL_PID_H.PID_out = CCD_CTRL_PID_H.KP_out + CCD_CTRL_PID_H.KI_out + CCD_CTRL_PID_H.KD_out ;

	}
	else if(Duty.time <=13.0f)
	{
		if(mode == 1)
		{                        
			except_A.x  = MAX_CTRL_ANGLE  *( my_deathzoom( (0) ,0,30 )/500.0f );   //30 ;   //max 30度	
			except_A.y  = MAX_CTRL_ANGLE  *( my_deathzoom( (-80) ,0,30 )/500.0f ); 

			CCD_CTRL_PID.KP_out =  pid_setup.groups.ctrl3.kp *  (CCD_CTRL_PID.error + CCD_CTRL_PID.shell_Pout) ;
			CCD_CTRL_PID.KD_out = pid_setup.groups.ctrl3.kd * CCD_CTRL_PID.devir ;

			CCD_CTRL_PID.PID_out = CCD_CTRL_PID.KP_out + CCD_CTRL_PID.KI_out + CCD_CTRL_PID.KD_out ;

			CCD_CTRL_PID_H.PID_out = 0 ;
			CCD_CTRL_PID.shell_Pout = 0;
		}
		else if(mode == 0)
		{
			except_A.x  = MAX_CTRL_ANGLE  *( my_deathzoom( (0) ,0,30 )/500.0f );   //30 ;   //max 30度	
			except_A.y  = MAX_CTRL_ANGLE  *( my_deathzoom( (0) ,0,30 )/500.0f ); 

			CCD_CTRL_PID.KP_out =  pid_setup.groups.ctrl3.kp *  (CCD_CTRL_PID.error ) ;
			CCD_CTRL_PID.KD_out = pid_setup.groups.ctrl3.kd * CCD_CTRL_PID.devir ;
			CCD_CTRL_PID.PID_out = CCD_CTRL_PID.KP_out + CCD_CTRL_PID.KI_out + CCD_CTRL_PID.KD_out ;


			CCD_CTRL_PID_H.KP_out = pid_setup.groups.ctrl3.kp * (CCD_CTRL_PID_H.error ) ;
			CCD_CTRL_PID_H.KD_out = pid_setup.groups.ctrl3.kd * CCD_CTRL_PID_H.devir ;

			CCD_CTRL_PID_H.PID_out = CCD_CTRL_PID_H.KP_out + CCD_CTRL_PID_H.KI_out + CCD_CTRL_PID_H.KD_out ;
		}
	}
	else if(Duty.time >13.0f)
	{
		 camera_Trance.take_off_flag = 1;
		 except_A.x  = MAX_CTRL_ANGLE  *( my_deathzoom( (50) ,0,30 )/500.0f );   //右停;   //max 30度	  后右
		except_A.y  = MAX_CTRL_ANGLE  *( my_deathzoom( (40) ,0,30 )/500.0f );
	}
	
	
}

void mode_2_duty(float T,u8 mode)
{
	Duty.time += T;
	
	if(Duty.time <= 3.0f)
	{
		except_A.x  = MAX_CTRL_ANGLE  *( my_deathzoom( (0) ,0,30 )/500.0f );   //30 ;   //max 30度	
		except_A.y  = MAX_CTRL_ANGLE  *( my_deathzoom( (0) ,0,30 )/500.0f ); 
		
		CCD_CTRL_PID.KP_out =  pid_setup.groups.ctrl3.kp *  (CCD_CTRL_PID.error ) ;
		CCD_CTRL_PID.KD_out = pid_setup.groups.ctrl3.kd * CCD_CTRL_PID.devir ;

		CCD_CTRL_PID.PID_out = CCD_CTRL_PID.KP_out + CCD_CTRL_PID.KI_out + CCD_CTRL_PID.KD_out ;


		CCD_CTRL_PID_H.KP_out = pid_setup.groups.ctrl3.kp * (CCD_CTRL_PID_H.error ) ;
		CCD_CTRL_PID_H.KD_out = pid_setup.groups.ctrl3.kd * CCD_CTRL_PID_H.devir ;

		CCD_CTRL_PID_H.PID_out = CCD_CTRL_PID_H.KP_out + CCD_CTRL_PID_H.KI_out + CCD_CTRL_PID_H.KD_out ;
		CCD_CTRL_PID.shell_Pout= 0;

	}
	else
	{
		if(mode == 1)
		{
			except_A.x  = MAX_CTRL_ANGLE  *( my_deathzoom( (0) ,0,30 )/500.0f );   //30 ;   //max 30度	
			except_A.y  = MAX_CTRL_ANGLE  *( my_deathzoom( (-80) ,0,30 )/500.0f ); 

			CCD_CTRL_PID.KP_out =  pid_setup.groups.ctrl3.kp *  (CCD_CTRL_PID.error + CCD_CTRL_PID.shell_Pout) ;
			CCD_CTRL_PID.KD_out = pid_setup.groups.ctrl3.kd * CCD_CTRL_PID.devir ;

			CCD_CTRL_PID.PID_out = CCD_CTRL_PID.KP_out + CCD_CTRL_PID.KI_out + CCD_CTRL_PID.KD_out ;

			CCD_CTRL_PID_H.PID_out = 0 ;
		}
		else if(mode == 0)
		{
			except_A.x  = MAX_CTRL_ANGLE  *( my_deathzoom( (0) ,0,30 )/500.0f );   //30 ;   //max 30度	
			except_A.y  = MAX_CTRL_ANGLE  *( my_deathzoom( (0) ,0,30 )/500.0f ); 

			CCD_CTRL_PID.KP_out =  pid_setup.groups.ctrl3.kp *  (CCD_CTRL_PID.error ) ;
			CCD_CTRL_PID.KD_out = pid_setup.groups.ctrl3.kd * CCD_CTRL_PID.devir ;
			CCD_CTRL_PID.PID_out = CCD_CTRL_PID.KP_out + CCD_CTRL_PID.KI_out + CCD_CTRL_PID.KD_out ;


			CCD_CTRL_PID_H.KP_out = pid_setup.groups.ctrl3.kp * (CCD_CTRL_PID_H.error ) ;
			CCD_CTRL_PID_H.KD_out = pid_setup.groups.ctrl3.kd * CCD_CTRL_PID_H.devir ;
			CCD_CTRL_PID_H.PID_out = CCD_CTRL_PID_H.KP_out + CCD_CTRL_PID_H.KI_out + CCD_CTRL_PID_H.KD_out ;
		}
	}

	

}

/******
mode_3_duty
    巡航

*******/

u8 usart3_enable = 0;
u8 usart3_err = 40;

struct _mode3_duty mode_3_duty;


enum 
{
	Forward = 0,
    Back,
    Left,
    Right,
    Fix_point,
    Take_land
};

void mode3_flight_duty(float T)
{
    

    /****/
    if(usart3_enable == 0)
    {
        camera_Trance.sound = 0;
        mode_3_duty.flight_state = 0;
        mode_3_duty.flight_time += T;
        mode_3_duty.flight_ole_time = mode_3_duty.flight_time;
    }     
    else if(usart3_enable == 1)
    {
        camera_Trance.sound =1; 
        mode_3_duty.flight_state = 1;
        if(Openmv_err_x <10 &&Openmv_err_x>-10)
            mode_3_duty.fixed_point_time += T;
        else
        {
            mode_3_duty.flight_time += T;
            mode_3_duty.flight_ole_time = mode_3_duty.flight_time;
            
        }
        
        if(mode_3_duty.fixed_point_time >= 3)
        {
            mode_3_duty.flight_state = 2;
            mode_3_duty.fixed_point_cnt ++;
        }
        
//        if(mode_3_duty.flight_state != 1)
//        {
//            mode_3_duty.flight_time ++;
//            mode_3_duty.flight_ole_time = mode_3_duty.flight_time;
//        }

    } 
    
  /***/
    if(mode_3_duty.flight_time >(pid_setup.groups.hc_sp.ki*100))
        camera_shell_pid();
    
    if(mode_3_duty.flight_state ==0 )
    {
        //cruise
        Direction_flight(mode_3_duty.flight_time);  
        
    }
    else if(mode_3_duty.flight_state == 1)
    {
        //fix point
        mode_3_duty.direction = Fix_point;
        
    }
    else if(mode_3_duty.flight_state == 2)
    {
        
        
        mode_3_duty.flight_time +=T;
        mode_3_duty.flight_ole_time = mode_3_duty.flight_time;
        Direction_flight(mode_3_duty.flight_time);   
        
        if(mode_3_duty.direction != mode_3_duty.direction_old)
        {
            mode_3_duty.fixed_point_time = 0;
            mode_3_duty.flight_state = 0;
        }
            
    }
    
}

int Direction_flight(u32 flight_t)
{
    u32 forword_time_1 = pid_setup.groups.hc_sp.ki*100 +(pid_setup.groups.Forward_time.kp*100);
    u32 left_time_1 = forword_time_1 +(pid_setup.groups.Left_time.kp*100) +1;
    u32 back_time_1 = left_time_1 +(pid_setup.groups.Forward_time.ki*100) +1;
    u32 left_time_2 = back_time_1 + (pid_setup.groups.Left_time.ki*100) +1;
    u32 forword_time_2 = left_time_2 + (pid_setup.groups.Forward_time.kd*100) +1;
    u32 back_time_2 = forword_time_2 +(pid_setup.groups.Left_time.kd*100)+1;
    u32 all_time = forword_time_1+left_time_1+back_time_1+left_time_2+forword_time_2+back_time_2;
    
    if(flight_t<(pid_setup.groups.hc_sp.ki*100))
    {
        mode_3_duty.direction = Fix_point;  //定点
    }
    //前进之后定点1秒
    else if(flight_t<forword_time_1)
    {
        mode_3_duty.direction = Forward;
    }
    else if(flight_t<forword_time_1+1)
    {
        mode_3_duty.direction = Fix_point;
    }
    //左移
    else if(flight_t<left_time_1)
    {
        mode_3_duty.direction = Left;
    }
    else if(flight_t<left_time_1+1)
    {
        mode_3_duty.direction = Fix_point;
    }
    //后退
    else if(flight_t<back_time_1)
    {
        mode_3_duty.direction = Back;
    }
    else if(flight_t<back_time_1+1)
    {
        mode_3_duty.direction = Fix_point;
    }
    //左移
    else if(flight_t< left_time_2)
    {
        mode_3_duty.direction = Left;
    }
    else if(flight_t<left_time_2+1)
    {
        mode_3_duty.direction = Fix_point;
    }
//    //前进之后定点1秒
//    else if(flight_t<forword_time_2)
//    {
//        mode_3_duty.direction = Forward;
//    }
//    else if(flight_t<forword_time_2+1)
//    {
//        mode_3_duty.direction = Fix_point;
//    }
//    //后退
//    else if(flight_t< back_time_2)
//    {
//        mode_3_duty.direction = Back;
//    }
//    else if(flight_t<back_time_2+1)
//    {
//        mode_3_duty.direction = Fix_point;
//    }
    
    else 
    {
        mode_3_duty.direction = Take_land;
    }
    
    if(mode_3_duty.fixed_point_cnt >=2 &&flight_t >= forword_time_2)
    {
        mode_3_duty.direction = Back;
        if(flight_t >= forword_time_2 +3)
            mode_3_duty.direction = Take_land;
    }
    return mode_3_duty.direction;
}

//#define FORWORD_ANGLE -0.3f
//#define LEFT_ANGLE -1.0f
//#define BACK_ANGLE 0.6f
#define RIGHT_ANGLE 0.3f


void Mode_3_duty(float T,u8 mode )
{
    
    
//    Duty.time += T;
    float FORWORD_ANGLE =  - pid_setup.groups.exp_angle.exp_forward*1000;
    float LEFT_ANGLE  =  - pid_setup.groups.exp_angle.exp_left *1000;
    float BACK_ANGLE = pid_setup.groups.exp_angle.exp_back *1000;

    
    if(mode == 0)
    {
        CCD_CTRL_PID.KP_out =  pid_setup.groups.ctrl3.kp *  (CCD_CTRL_PID.error ) ;
        CCD_CTRL_PID.KI_out =  pid_setup.groups.ctrl3.ki *  (CCD_CTRL_PID.merrer ) ;
        CCD_CTRL_PID.KD_out = pid_setup.groups.ctrl3.kd * CCD_CTRL_PID.devir ;

        CCD_CTRL_PID.PID_out = CCD_CTRL_PID.KP_out + CCD_CTRL_PID.KI_out + CCD_CTRL_PID.KD_out ;


        CCD_CTRL_PID_H.KP_out = pid_setup.groups.ctrl3.kp * (CCD_CTRL_PID_H.error ) ;
        CCD_CTRL_PID_H.KI_out = pid_setup.groups.ctrl3.ki * CCD_CTRL_PID_H.merrer ;
        CCD_CTRL_PID_H.KD_out = pid_setup.groups.ctrl3.kd * CCD_CTRL_PID_H.devir ;

        CCD_CTRL_PID_H.PID_out = CCD_CTRL_PID_H.KP_out + CCD_CTRL_PID_H.KI_out + CCD_CTRL_PID_H.KD_out ;
    }
    else
    {
        camera_shell_pid();
        mode3_flight_duty(T);
/**    
        if(mode_3_duty.direction != mode_3_duty.direction_old && mode_3_duty.direction == Fix_point) 
        {
            CCD_CTRL_PID_H.merrer = 0;
            CCD_CTRL_PID.merrer = 0;
        }   
    
        if(mode_3_duty.direction == Forward)
        {
            CCD_CTRL_PID_H.KP_out = pid_setup.groups.ctrl3.kp * (CCD_CTRL_PID_H.error ) ;
            CCD_CTRL_PID_H.KI_out = pid_setup.groups.ctrl3.ki * CCD_CTRL_PID_H.merrer ;
            CCD_CTRL_PID_H.KD_out = pid_setup.groups.ctrl3.kd * CCD_CTRL_PID_H.devir ;

            CCD_CTRL_PID_H.PID_out = CCD_CTRL_PID_H.KP_out + CCD_CTRL_PID_H.KI_out + CCD_CTRL_PID_H.KD_out ;
            
            CCD_CTRL_PID.PID_out = FORWORD_ANGLE;
        }
        else if(mode_3_duty.direction == Left)
        {
            CCD_CTRL_PID.KP_out =  pid_setup.groups.ctrl3.kp *  (CCD_CTRL_PID.error + CCD_CTRL_PID.error_ff) ;
            CCD_CTRL_PID.KI_out =  pid_setup.groups.ctrl3.ki *  (CCD_CTRL_PID.merrer + CCD_CTRL_PID.merrer_ff ) ;
            CCD_CTRL_PID.KD_out = pid_setup.groups.ctrl3.kd * CCD_CTRL_PID.devir ;

            CCD_CTRL_PID.PID_out = CCD_CTRL_PID.KP_out + CCD_CTRL_PID.KI_out + CCD_CTRL_PID.KD_out ;
            
            CCD_CTRL_PID_H.PID_out = LEFT_ANGLE;
        }
        else if(mode_3_duty.direction == Right)
        {
            CCD_CTRL_PID.KP_out =  pid_setup.groups.ctrl3.kp *  (CCD_CTRL_PID.error + CCD_CTRL_PID.error_ff) ;
            CCD_CTRL_PID.KI_out =  pid_setup.groups.ctrl3.ki *  (CCD_CTRL_PID.merrer + CCD_CTRL_PID.merrer_ff ) ;
            CCD_CTRL_PID.KD_out = pid_setup.groups.ctrl3.kd * CCD_CTRL_PID.devir ;

            CCD_CTRL_PID.PID_out = CCD_CTRL_PID.KP_out + CCD_CTRL_PID.KI_out + CCD_CTRL_PID.KD_out ;
            CCD_CTRL_PID_H.PID_out = RIGHT_ANGLE;
        }
        else if(mode_3_duty.direction == Back)
        {
            CCD_CTRL_PID_H.KP_out = pid_setup.groups.ctrl3.kp * (CCD_CTRL_PID_H.error ) ;
            CCD_CTRL_PID_H.KI_out = pid_setup.groups.ctrl3.ki * CCD_CTRL_PID_H.merrer ;
            CCD_CTRL_PID_H.KD_out = pid_setup.groups.ctrl3.kd * CCD_CTRL_PID_H.devir ;

            CCD_CTRL_PID_H.PID_out = CCD_CTRL_PID_H.KP_out + CCD_CTRL_PID_H.KI_out + CCD_CTRL_PID_H.KD_out ;
            
            CCD_CTRL_PID.PID_out = BACK_ANGLE;
        }
        else if(mode_3_duty.direction == Fix_point)
        {
            
            CCD_CTRL_PID.KP_out =  pid_setup.groups.ctrl3.kp *  (CCD_CTRL_PID.error + CCD_CTRL_PID.error_ff) ;
            CCD_CTRL_PID.KI_out =  pid_setup.groups.ctrl3.ki *  (CCD_CTRL_PID.merrer + CCD_CTRL_PID.merrer_ff ) ;
            CCD_CTRL_PID.KD_out = pid_setup.groups.ctrl3.kd * CCD_CTRL_PID.devir ;

            CCD_CTRL_PID.PID_out = CCD_CTRL_PID.KP_out + CCD_CTRL_PID.KI_out + CCD_CTRL_PID.KD_out ; 
            
            CCD_CTRL_PID_H.KP_out = pid_setup.groups.ctrl3.kp * (CCD_CTRL_PID_H.error ) ;
            CCD_CTRL_PID_H.KI_out = pid_setup.groups.ctrl3.ki * CCD_CTRL_PID_H.merrer ;
            CCD_CTRL_PID_H.KD_out = pid_setup.groups.ctrl3.kd * CCD_CTRL_PID_H.devir ;

            CCD_CTRL_PID_H.PID_out = CCD_CTRL_PID_H.KP_out + CCD_CTRL_PID_H.KI_out + CCD_CTRL_PID_H.KD_out ;
            
        }
        else if(mode_3_duty.direction == Take_land)
        {

            CCD_CTRL_PID.KP_out =  pid_setup.groups.ctrl3.kp *  (CCD_CTRL_PID.error + CCD_CTRL_PID.error_ff) ;
            CCD_CTRL_PID.KI_out =  pid_setup.groups.ctrl3.ki *  (CCD_CTRL_PID.merrer + CCD_CTRL_PID.merrer_ff ) ;
            CCD_CTRL_PID.KD_out = pid_setup.groups.ctrl3.kd * CCD_CTRL_PID.devir ;

            CCD_CTRL_PID.PID_out = CCD_CTRL_PID.KP_out + CCD_CTRL_PID.KI_out + CCD_CTRL_PID.KD_out ;

            CCD_CTRL_PID_H.KP_out = pid_setup.groups.ctrl3.kp * (CCD_CTRL_PID_H.error ) ;
            CCD_CTRL_PID_H.KI_out = pid_setup.groups.ctrl3.ki * CCD_CTRL_PID_H.merrer ;
            CCD_CTRL_PID_H.KD_out = pid_setup.groups.ctrl3.kd * CCD_CTRL_PID_H.devir ;

            CCD_CTRL_PID_H.PID_out = CCD_CTRL_PID_H.KP_out + CCD_CTRL_PID_H.KI_out + CCD_CTRL_PID_H.KD_out ;            
            
            if(camera_Trance.take_off_flag != 1)
            {
                camera_Trance.take_off_flag = 1;
            }
        }
**/
        if(mode_3_duty.direction_old != mode_3_duty.direction&& mode_3_duty.direction == Fix_point) 
        {
//            CCD_CTRL_PID_H.merrer = CCD_CTRL_PID_H.data_old;
//            CCD_CTRL_PID.merrer = CCD_CTRL_PID.CCD_death_old;
        }   
        
//改变期望   
        if(mode_3_duty.direction == Forward)
        {
            CCD_CTRL_PID.error_ff = FORWORD_ANGLE;
            CCD_CTRL_PID_H.error_ff = 0;
//            CCD_CTRL_PID_H.merrer = 0;
        }
        else if(mode_3_duty.direction == Left)
        {
            CCD_CTRL_PID.error_ff = 0;
            CCD_CTRL_PID_H.error_ff = LEFT_ANGLE;
//            CCD_CTRL_PID.merrer = 0;
        }
        else if(mode_3_duty.direction == Right)
        {
            CCD_CTRL_PID.error_ff = 0;
            CCD_CTRL_PID_H.error_ff = 0;
//            CCD_CTRL_PID_H.merrer = 0;
        }
        else if(mode_3_duty.direction == Back)
        {
            CCD_CTRL_PID.error_ff = BACK_ANGLE;
            CCD_CTRL_PID_H.error_ff = 0;
//            CCD_CTRL_PID_H.merrer = 0;
        }
        else if(mode_3_duty.direction == Fix_point)
        {
            CCD_CTRL_PID.error_ff = 0;
            CCD_CTRL_PID_H.error_ff = 0;
            
            CCD_CTRL_PID.data_old = CCD_CTRL_PID.merrer;
            CCD_CTRL_PID_H.data_old = CCD_CTRL_PID_H.merrer;
        }
        else if(mode_3_duty.direction == Take_land)
        {
            CCD_CTRL_PID.error_ff = 0;
            CCD_CTRL_PID_H.error_ff = 0;           
            
            if(camera_Trance.take_off_flag != 1)
            {
                camera_Trance.take_off_flag = 1;
            }
        }
       
        CCD_CTRL_PID.KP_out =  pid_setup.groups.ctrl3.kp *  (CCD_CTRL_PID.error ) ;
        CCD_CTRL_PID.KI_out =  pid_setup.groups.ctrl3.ki *  (CCD_CTRL_PID.merrer ) ;
        CCD_CTRL_PID.KD_out = pid_setup.groups.ctrl3.kd * CCD_CTRL_PID.devir ;

        CCD_CTRL_PID.PID_out = CCD_CTRL_PID.KP_out + CCD_CTRL_PID.KI_out + CCD_CTRL_PID.KD_out ;


        CCD_CTRL_PID_H.KP_out = pid_setup.groups.ctrl3.kp * (CCD_CTRL_PID_H.error ) ;
        CCD_CTRL_PID_H.KI_out = pid_setup.groups.ctrl3.ki * (CCD_CTRL_PID_H.merrer);
        CCD_CTRL_PID_H.KD_out = pid_setup.groups.ctrl3.kd * CCD_CTRL_PID_H.devir ;

        CCD_CTRL_PID_H.PID_out = CCD_CTRL_PID_H.KP_out + CCD_CTRL_PID_H.KI_out + CCD_CTRL_PID_H.KD_out ;
      
        mode_3_duty.direction_old = mode_3_duty.direction ;
    }
}    
 /*******************************************************
    mode_state 						飞行模式，姿态，定高
    change_CCD_data     			开始循迹标志位  
    camera_Trance.take_off_flag     自动降落标志位	降落时不前进
    camera_Trance.trance_flag       飞行方向
	duty_mode :     				飞行模式   下位机结合按键模式		电赛要求的前进定点与直接定点
									0  ：定点 1：前进     2：跟踪  	3:巡航
    Duty.fly_mode ：	 		    0 定点，1 前进
	Duty.time：						按时降落
    Duty.time_cycle ： 				运行时间
*******************************************************/

void direction_control(float T,u8 duty_mode)
{
	static u8 control_flag= 0;
    static u8 mode_state_old = 0;
//	camera_shell_pid();
	if( mode_state ==2 )
	{

		if(change_CCD_data ==1)
		{
			Duty.time_cycle += T;
			

			Mode_3_duty(T,duty_mode);
            
//            CCD_CTRL_PID.KP_out =  pid_setup.groups.ctrl3.kp *  (CCD_CTRL_PID.error ) ;
//            CCD_CTRL_PID.KI_out =  pid_setup.groups.ctrl3.ki *  (CCD_CTRL_PID.merrer ) ;
//            CCD_CTRL_PID.KD_out = pid_setup.groups.ctrl3.kd * CCD_CTRL_PID.devir ;

//            CCD_CTRL_PID.PID_out = CCD_CTRL_PID.KP_out + CCD_CTRL_PID.KI_out + CCD_CTRL_PID.KD_out ;


//            CCD_CTRL_PID_H.KP_out = pid_setup.groups.ctrl3.kp * (CCD_CTRL_PID_H.error ) ;
//            CCD_CTRL_PID_H.KI_out = pid_setup.groups.ctrl3.ki * CCD_CTRL_PID_H.merrer ;
//            CCD_CTRL_PID_H.KD_out = pid_setup.groups.ctrl3.kd * CCD_CTRL_PID_H.devir ;

//            CCD_CTRL_PID_H.PID_out = CCD_CTRL_PID_H.KP_out + CCD_CTRL_PID_H.KI_out + CCD_CTRL_PID_H.KD_out ;
            
            Fix_point_except.x = LIMIT(CCD_CTRL_PID.PID_out , -30,30);
            Fix_point_except.y  = LIMIT(CCD_CTRL_PID_H.PID_out , -30,30);
            
            
			 if(camera_Trance.take_off_flag == 1 && duty_mode ==0)               //开始降落 停在旁边
			 {
				Fix_point_except.x  = MAX_CTRL_ANGLE  *( my_deathzoom( (0) ,0,30 )/500.0f );   //右停;   //max 30度	
				Fix_point_except.y  = MAX_CTRL_ANGLE  *( my_deathzoom( (0) ,0,30 )/500.0f ); 
			 }   

			
		}
		else 
		{
			Duty.time_cycle = 0;
			Duty.time = 0;
			Fix_point_except.x  = 0;   //30
			Fix_point_except.y  = 0;  //30
			
			CCD_CTRL_PID.PID_out =0 ;
			CCD_CTRL_PID.shell_Pout = 0;
			CCD_CTRL_PID.merrer = 0;
			CCD_CTRL_PID_H.shell_Pout = 0;
			CCD_CTRL_PID_H.PID_out  = 0;
			CCD_CTRL_PID_H.merrer = 0;
			
			camera_Trance.merrer_H = 0;
			camera_Trance.merrer_V = 0;
			camera_Trance.PID_out_H = 0 ;
			camera_Trance.PID_out_V = 0 ;
  		}
	    
		
	}
	else 
	{
		Duty.time_cycle = 0;
			Duty.time = 0;
		Fix_point_except.x  = 0;   //30
		Fix_point_except.y  = 0;  //30


		CCD_CTRL_PID.PID_out =0 ;
		CCD_CTRL_PID.shell_Pout = 0;
	    CCD_CTRL_PID.merrer = 0;
		CCD_CTRL_PID_H.shell_Pout = 0;
		CCD_CTRL_PID_H.PID_out  = 0;
		CCD_CTRL_PID_H.merrer = 0;
		
		camera_Trance.merrer_H = 0;
		camera_Trance.merrer_V = 0;
		camera_Trance.PID_out_H = 0 ;
		camera_Trance.PID_out_V = 0 ;
        
        
	}
	//更好的飞行
    if(mode_state != mode_state_old)
    {
        ctrl_2.err_i.x = 0;
        ctrl_2.err_i.y = 0;
        ctrl_1.err_i.x = 0;
        ctrl_1.err_i.y = 0;
        
    }
    
    mode_state_old = mode_state;
}

void feed_error(int Ori_H_error,int Ori_V_error, int *H_error,int *V_error,float Hight)
{
	*H_error = Ori_H_error  - Hight * tan(Roll/57.3f) ;
}












