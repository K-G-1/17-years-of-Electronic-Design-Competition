/******************** (C) COPYRIGHT 2014 ANO Tech ********************************
  * 作者   ：匿名科创
 * 文件名  ：main.c
 * 描述    ：主循环
 * 官网    ：www.anotc.com
 * 淘宝    ：anotc.taobao.com
 * 技术Q群 ：190169595
**********************************************************************************/
#include "include.h"
#include "time.h"
#include "mpu6050.h"
#include "mpu9250.h"
#include "ak8975.h"
#include "led.h"
#include "rc.h"
#include "imu.h"
#include "pwm_in.h"
#include "ctrl.h"
#include "ms5611.h"
#include "parameter.h"
#include "ultrasonic.h"
#include "height_ctrl.h"
#include "fly_mode.h"
#ifdef  USE_FULL_ASSERT
void assert_failed(uint8_t* file, uint32_t line)
{ 
  while (1)
  {
		
  }
}
#endif
//=======================================================================================


//=======================================================================================
u8 Init_Finish = 0;
int main(void)
{

	Init_Finish = All_Init();	
	while(1)
	{
		Duty_Loop();
//		float inner_loop_time;
//		
//		inner_loop_time = Get_Cycle_T(0)/1000000.0f; 						//获取内环准确的执行周期
//		
//		test[0] = GetSysTime_us()/1000000.0f;
//		
//	//	MPU6050_Read(); 															//读取mpu6轴传感器

//	//	MPU6050_Data_Prepare( inner_loop_time );			//mpu6轴传感器数据处理
//		
//		MPU6500_Read();
//		MPU6500_Data_Prepare(inner_loop_time);
//		
//		READ_MPU9250_ACCEL();
//		READ_MPU9250_GYRO();
//		READ_MPU9250_MAG();
	}
}
/******************* (C) COPYRIGHT 2014 ANO TECH *****END OF FILE************/

