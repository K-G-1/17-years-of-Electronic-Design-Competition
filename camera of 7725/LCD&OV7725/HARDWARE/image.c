#include "image.h"
#include "ov7725.h"
#include "sys.h"
#include "sccb.h"
#include "lcd.h"
#include "oled.h"
#include "usart.h"
#include "PID_out.h"


struct _position position;
extern u8 mid_line[2][64] ;
u8 USART2_Tx_data[100];
u8 mid_data[4];
u8 mid_point;
u8 camera_width;
_mid_x_line mid_x_line;
u8 sound_flag =0;
u8 take_off_flag=0;

u8 deal_flag=0;

/**
  * @brief  设置显示位置
	* @param  sx:x起始显示位置
	* @param  sy:y起始显示位置
	* @param  width:显示窗口宽度,要求跟OV7725_Window_Set函数中的width一致
	* @param  height:显示窗口高度，要求跟OV7725_Window_Set函数中的height一致
  * @retval 无
  */
extern long int Camera_Data_Buff[2][100];
extern  uint16_t camera_dis_buf[100][100];
extern unsigned char tx_buff[4][260];
extern unsigned char Usart1_sand1_buff[19204];
unsigned  char deal_buff[4][128];
_camera_data camera_data;


void ImagDisp(uint16_t sx,uint16_t sy,uint16_t width,uint16_t height)
{
	uint16_t i, j ,buff=0; 
	int k=0,V_count=0;
	uint16_t Camera_Data,Camera_Data_old;
	

	u16 fiter_buff[4]={0};
	
//	LCD_Scan_Dir(L2R_U2D);		//从上到下,从左到右 
//	LCD_SetCursor(0x00,0x0000);	//设置光标位置 `
//	LCD_Set_Window(sx,sy,width,height);
//	LCD_WriteRAM_Prepare();     //开始写入GRAM	
	FIFO_PREPARE; 
	
	
	
	for(j =0; j < height; j++)
	{
		k=0;
		for(i = 0; i < width; i++)
		{
			
			READ_FIFO_PIXEL(Camera_Data);		/* 从FIFO读出一个rgb565像素到Camera_Data变量 */
//			Camera_Data_Buff[i*320+j]= Camera_Data ;
			
			if(Camera_Data> 0x3b55)
				Camera_Data=WHITE ;
			else Camera_Data=BLACK;

		
			
/**** 1*3 滤波****/
			
			if(j<3)
				fiter_buff[j]= Camera_Data;
			else
			{
				for(buff=0;buff<3;buff++)
				{
					fiter_buff[0]= fiter_buff[1];
					fiter_buff[1]= fiter_buff[2];
					fiter_buff[2]= Camera_Data;
				}
				
				if(fiter_buff[0]>fiter_buff[1])
				{
					fiter_buff[3]= fiter_buff[0];
					fiter_buff[0]= fiter_buff[1];
					fiter_buff[1]= fiter_buff[3];
					
					if(fiter_buff[1]>fiter_buff[2])
					{
						
						fiter_buff[1]= fiter_buff[2];
						fiter_buff[2]= fiter_buff[3];
					}
		
				}
			
			
				Camera_Data=fiter_buff[1];
					
				
			}
			
/*******************************************/
            if(Camera_Data <0xAAAA)
			{
				if(i<155&&i>5&&j>5&&j<155)
				 {
					 if(i >position.x_max)   position.x_max = i ; 
					 if(i <position.x_min)   position.x_min = i ;
					 
					 if(j >position.y_max)   position.y_max = j ; 
					 if(j <position.y_min)   position.y_min = j ; 
					 
				 }
			}
			
/******************************/
			
			
//			 if(j == 64)
//			 {
////				tx_buff[0][(i/2)] = Camera_Data; 
//				 deal_buff[0][(i/2)] = Camera_Data;
//			 }
//			 if(j == 32)
//			 {
////				tx_buff[0][(i/2)] = Camera_Data; 
//				 deal_buff[3][(i/2)] = Camera_Data;
//			 }
//			if(i == 172 )
//			{
////				tx_buff[1][j+130] = Camera_Data;
//				deal_buff[2][(j)] = Camera_Data;
//			}
//			
//			if(i == 64 )
//			{
////				tx_buff[1][j+2] = Camera_Data;
//				deal_buff[1][(j)] = Camera_Data;
//			}
			
/************************十字线********************************/			
//			if(j==120 && (i>=110&&i<210))
//			{
//				Camera_Data_Buff[1][i-110] = Camera_Data;
//			}
//			if(i==180 && (j>=70&&j<170))
//			{
//				Camera_Data_Buff[0][j-70] = Camera_Data;
//			}
/***********************************************/
//			LCD_WriteRAM(Camera_Data);

		}
	}
}


void camera_sand_data(struct _position camera_data,float T,u8 Tx_data[100])
{
	int temp=0;
	u8 _cnt=0;
	u8 sum = 0;
	u8 i=0;

	
	
	
	Tx_data[_cnt++] = 0x02;
	Tx_data[_cnt++] = 0xfe;
	Tx_data[_cnt++] = 0x01;
	Tx_data[_cnt++] = 0;
	temp = (camera_data.position_x);
	Tx_data[_cnt++] =BYTE1(temp);
	Tx_data[_cnt++] =BYTE0(temp);
	
	temp = (int)(camera_data.position_y);
	Tx_data[_cnt++] =  BYTE1(temp);
	Tx_data[_cnt++] =  BYTE0(temp);
//	
	temp = (camera_data.dri_flag);
	Tx_data[_cnt++] =  BYTE0(temp);
	
	temp = (camera_data.sound_flag);
	Tx_data[_cnt++] =  BYTE0(temp);
	
	temp = (camera_data.take_off_flag);
	Tx_data[_cnt++] =  BYTE0(temp);
	
	
	 Tx_data[3] = _cnt-4;
	
	
	for(i=0;i<_cnt;i++)
		sum += Tx_data[i];
	Tx_data[_cnt++]=sum;
	
	Uart2_Send(Tx_data,_cnt);
}



int flight_data(float T)
{
	if(position.x_max != 0 &&position.x_min != 160)
	{

		position.H_x_max = position.x_max ;
		position.H_x_min = position.x_min ;	
	}
	if(position.y_max != 0 && position.y_min!= 160)
	{

		 position.V_y_max = position.y_max ;
		 position.V_y_min = position.y_min;
	}
	

    
	
	position.x_max = 0 ;                //方便计算下一次的数据
	position.x_min = 160;
	position.y_max = 0;
	position.y_min = 160;
	
	
	
	position.position_x = 75 - (position.H_x_max + position.H_x_min)/2   ;
	position.position_y = (position.V_y_max + position.V_y_min)/2 -75 ;
	
//	if(deal_flag >=1 && position.dri_flag ==0)
//	{
//		if(position.position_x > position.position_x_old + 40 ||position.position_x< position.position_x_old -40)
//		{
//            position.position_x = position.position_x_old ;
//		}	
//		if(position.position_y > position.position_y_old + 40 ||position.position_y< position.position_y_old -40)
//		{
//            position.position_y = position.position_y_old ;
//		}
//		
//	}
//	else if(deal_flag ==0)
//	{
//		if(position.position_x > position.position_x_old + 40 ||position.position_x< position.position_x_old -40)
//		{
//            position.position_x = position.position_x_old ;
//		}
//		if(position.position_y > position.position_y_old + 40 ||position.position_y< position.position_y_old -40)
//		{
//            position.position_y = position.position_y_old ;
//		}
//	}

	
	
	
	if(position.Y_old >50 && position.position_y <-40)
		position.dri_flag =0 ;
	position.Y_old = position.position_y ;
	
	OLED_P6x8data( 30, 0 ,position.position_x );
	  OLED_P6x8data( 60, 0 ,position.position_y );
	camera_sand_data(position,T,USART2_Tx_data);
	
	position.position_x_old =  position.position_x;
	position.position_y_old = position.position_y ;
}
//int flight_data(float T)
//{
//    static  u8 mid =64;
//	static  int mid_L;
//	static  int direction;
//	mid_x_line.horizontal_64 = mid_line_deal(deal_buff[0],mid_x_line.horizontal_64_old);
//	mid_x_line.horizontal_64_old = mid_x_line.horizontal_64;
//	CCD_PID_data(mid_x_line.horizontal_64,T);
//	

//	return 1;
//}

int mid_line_deal(unsigned char data[128],u8 mid_old)
{
	static u8 j=0;
	static int A,B;
	u8 left,right;
	u8 left_flag=0,right_flag=0;
	u8 left_count,right_count;	 
	u8 error_count=0;
	u8 mid_point;
	
	if(data[mid_old] ==0)                                     //判断跳变是不是过大
	{
		  //在上一次中线附近
		for(left = mid_old;left>0;left--)                      //从中左找 跳变   下降沿
		{
			if(data[left-2]> data[left] +10)
			{
				left_count = left;
				break;
			}
			if(left <=11)                                      //没有找到 ，代表全黑
			{
				 left_count = 11;
				error_count++;
				break;
			}
		}
		for (right = mid_old;right<128;right++)               //从中向右找  跳变  上升沿
		{
			if(data[right]+10< data[right+2] )
			{
				right_count = right;
				break;
			}
			if(right >=114)                                  // 没有找到 ，代表全黑
			{
				right_count = 114;
				error_count++;
				break;
			}
		}
        mid_point = (left_count+ right_count )/2;
//		camera_data.width = right_count - left_count; 
			
		
	}
	else 
	{
		
		for(left = mid_old;left>0;left--)                      //从中右找 不同
		{
			 if(data[left-2] +10< data[left] )
			{                                                  //下降沿
				 A = left;
				left_count = left;
				break;
			}
			else
				A = 0;
			if(left <= 11)
			{                                                    //代表全白
				 A = 1;
				error_count++;
				break;
			}
		}
		for(right = mid_old;right<128;right++)                      //从中左找 不同
		{
			if(data[right]> data[right+2] +10)
			{                                                  //下降沿
				 B = right;
				right_count = right;
				break;
			}
			else
				B = 0;
			if(right >= 114)
			{                                                       //代表全白
				 B=1;
				error_count++;
				break;
			}
		}
		if(A ==1 && B ==1)
		{
			  return mid_point = mid_old;
		}
		else if(A==1)                                              //在右边找到了下降沿 
		{
			for(right = B+2;right<128;right++)
			{
				if(data[right]< data[right+2] )
				{                                                  //下降沿
					 right_count = right;
					break;
				}
				if(right >=114)
				{
					right_count = 114;
					break;
				}
			}
			  mid_point = (B+ right_count )/2;
		}
		else if(B==1)                                            //在zuo边找到了下降沿 
		{
			  for(left = A;left>0;left--)
			{
				if(data[left-2]> data[left] )
				{                                                  //上升沿
					 left_count = left;
					break;
				}
				if(left <=11)
				{
					left_count = 11;
					break;
				}
			}
			  mid_point = (A+ left_count )/2;
		}
		else 
		{
//			return mid_point = mid_old;
			 if((64-A)>=(B-64)) 						//右边的更靠近
			 {
				 for(right = B+2;right<128;right++)
				{
					if(data[right]< data[right+2] )
					{                                                  //下降沿
						 right_count = right;
						break;
					}
					if(right >=114)
					{
						right_count = 114;
						break;
					}
				}
				  mid_point = (B+ right_count )/2;
			 }
			 else
			 {
				 for(left = A;left>0;left--)
				{
					if(data[left-2]> data[left] )
					{                                                  //上升沿
						 left_count = left;
						break;
					}
					if(left <=11)
					{
						left_count = 11;
						break;
					}
				}
				  mid_point = (A+ left_count )/2;
			 }
		}
			
	}
	if(error_count ==0)
	{
		camera_data.width = right_count - left_count; 
	}
	if((mid_point>mid_old+40)||(mid_point<  mid_old-40))
		mid_point = mid_old;
	
  return mid_point;
}

void DT_usart1(u8 com_data)
{
		static u8 flag_status=0;
	 if(com_data == 0xfe && flag_status == 0)
	 {
		flag_status ++;
		 
	 }
	else if(flag_status == 1)
	{
		position.sound_flag = com_data ;
		OLED_P6x8data(30,1,com_data);
		flag_status ++;
	}
	else if(flag_status ==2)
	{
		position.take_off_flag = com_data;
		OLED_P6x8data(60,1,com_data);
		flag_status = 0;
	}
	
	
}




