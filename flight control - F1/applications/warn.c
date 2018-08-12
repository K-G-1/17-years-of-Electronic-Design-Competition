#include "warn.h"
#include "time.h"
#include "mpu6050.h"

void switch_init(void)
{
	GPIO_InitTypeDef  GPIO_InitStructure;
	NVIC_InitTypeDef   NVIC_InitStructure;
	EXTI_InitTypeDef   EXTI_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);//ʹ��GPIOAʱ��
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOE, ENABLE);//ʹ��GPIOAʱ��

	GPIO_EXTILineConfig(GPIO_PortSourceGPIOE,GPIO_PinSource14);
    GPIO_EXTILineConfig(GPIO_PortSourceGPIOA,GPIO_PinSource4);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_14;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;//100MHz
	GPIO_Init(GPIOE, &GPIO_InitStructure);//��ʼ�� 
	
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;//100MHz
	GPIO_Init(GPIOA, &GPIO_InitStructure);//��ʼ�� 


	/* ����EXTI_Line2,3,4 */
	EXTI_InitStructure.EXTI_Line = EXTI_Line14;
	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;//�ж��¼�
	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling; //�½��ش���
	EXTI_InitStructure.EXTI_LineCmd = ENABLE;//�ж���ʹ��
	EXTI_Init(&EXTI_InitStructure);//����

    
    /* ����EXTI_Line2,3,4 */
	EXTI_InitStructure.EXTI_Line = EXTI_Line4;
	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;//�ж��¼�
	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising_Falling; //�½��ش���
	EXTI_InitStructure.EXTI_LineCmd = ENABLE;//�ж���ʹ��
	EXTI_Init(&EXTI_InitStructure);//����
    
    NVIC_InitStructure.NVIC_IRQChannel = EXTI15_10_IRQn;			//ʹ�ܰ���KEY2���ڵ��ⲿ�ж�ͨ��
  	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x03;	//��ռ���ȼ�2�� 
  	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x01;					//�����ȼ�2
  	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;								//ʹ���ⲿ�ж�ͨ��
  	NVIC_Init(&NVIC_InitStructure);
    
    NVIC_InitStructure.NVIC_IRQChannel = EXTI4_IRQn;			//ʹ�ܰ���KEY2���ڵ��ⲿ�ж�ͨ��
  	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x03;	//��ռ���ȼ�2�� 
  	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x01;					//�����ȼ�2
  	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;								//ʹ���ⲿ�ж�ͨ��
  	NVIC_Init(&NVIC_InitStructure);
    

}

void light_sound_init(void)
{
	GPIO_InitTypeDef  GPIO_InitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);//ʹ��GPIOAʱ��
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;//��ͨ���ģʽ
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;//100MHz
	GPIO_Init(GPIOB, &GPIO_InitStructure);//��ʼ�� 
	
	GPIO_ResetBits(GPIOB,GPIO_Pin_8);
	
	
	
}


void set_light_sound(u8 mode)
{
	static int T_count;
	if(mode == 1)
	{
		T_count ++;
		if(T_count /20 %2 ==0)
		{
			GPIO_SetBits(GPIOB,GPIO_Pin_8);
		}
		else 
			GPIO_ResetBits(GPIOB,GPIO_Pin_8);
	}
	else 
	{
		GPIO_ResetBits(GPIOB,GPIO_Pin_8);
		T_count = 0;
	}
}




struct _Switch Switch;
struct _Switch Switch2;
struct _Switch Switch3;
struct _Switch Mode3_Switch;

//�ⲿ�ж�2�������
//��������ѡ��
//void EXTI2_IRQHandler(void)
//{
//	Delay_ms(5);
//	if(KEY0==0)	  
//	{				 
//       Switch.count_mode ++;
//		if(Switch.count_mode >=4)
//			Switch.count_mode =0;
//		if(Switch.count_mode == 2)
//		{
//			Duty.mode = 1;
//		}
//		else
//			Duty.mode = Switch.count_mode ;
////		Uart2_Send(&Switch.count_mode,1);
//	}		 
//	 EXTI_ClearITPendingBit(EXTI_Line2);//���LINE2�ϵ��жϱ�־λ 
//}
//�ⲿ�ж�3�������
void EXTI15_10_IRQHandler(void)
{
	Delay_ms(10);
	if(GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_14)==0)	 
	{
       
       Switch2.count_unlock ++;
		if(Switch2.count_unlock == 1)
		{
			Switch2.count_mode = 1;
			Switch2.flag = 1 ;
		}
		else if(Switch2.count_unlock == 2)
		{
			 Switch2.count_mode =0;
			Switch2.count_unlock = 0;
		}
	}		 
	 EXTI_ClearITPendingBit(EXTI_Line14);  //���LINE3�ϵ��жϱ�־λ  
}
//�ⲿ�ж�4�������

void EXTI4_IRQHandler(void)
{
	static u8 flag;
	Delay_ms(10);
	if(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_4)==0)	 
	{	
        Mode3_Switch.mode ++;
        if(Mode3_Switch.mode >=2)
            Mode3_Switch.mode = 0;
	}	
    else 
    {

    }        
	 EXTI_ClearITPendingBit(EXTI_Line4);//���LINE4�ϵ��жϱ�־λ  
}




extern u8 change_CCD_data,mode_state,change_Hight_data,fly_ready;
extern float CH_filter[CH_NUM];

/*******************************
 һ������
�ı��־λ ����ң��������ͨ�� ��һ��ʧ�ر���ͨ��

ǰ8�뱨��
0.5�����
֮������Զ�ģʽ

T:	������������
************************/
void   Auto_switch_2(float T)
{
	static float T_count= 0;
	static u8 falg =0 ;
	if( Switch2.count_mode == 1)
	{
		falg = 1 ;
		T_count += T;
		if(T_count < 8)
		{
			camera_Trance.sound = 1;
		}	
		else  if(T_count >= 8.0f&& T_count < 8.5f)
		{
//			CH_filter[ROL]= 0;
//			CH_filter[PIT]= 0;
//			CH_filter[THR]= 380;
//			CH_filter[YAW]= 0;
			Mode3_Switch.mode = 1;
			camera_Trance.sound = 0;
			change_Hight_data = 1 ;
			mode_state = 2 ;
			change_CCD_data = 1;
			fly_ready = 1 ;
			
			
		}
		else 
		{
//			CH_filter[ROL]= 0;
//			CH_filter[PIT]= 0;
			CH_filter[THR]= -350;
//			CH_filter[YAW]= 0;
//			CH_filter[AUX2] = 300 ;
		}
		
	}
	else 
	{
		T_count = 0;
		if(falg ==  1)
		{
			falg = 0 ;
			T_count = 0;
			camera_Trance.sound = 0;
			change_Hight_data = 0 ;
			mode_state = 2 ;
			change_CCD_data = 0;
		}
	}		
	
	
}



//һ��У׼
void CALIBRATE_duty(float T)
{
	  
	 if(Switch3.flag >=1)
	 {
		Switch3.time += T; 
		 if(Switch3.time >=2.0f)
		 {
			Switch3.flag =0 ; 
			mpu6050.Acc_CALIBRATE = 1;		
			mpu6050.Gyro_CALIBRATE = 1; 
		 }
		 
	 }	

}

