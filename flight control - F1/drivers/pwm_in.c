/******************** (C) COPYRIGHT 2014 ANO Tech ********************************
  * 作者   ：匿名科创
 * 文件名  ：pwm_in.c
 * 描述    ：PWM输入捕获
 * 官网    ：www.anotc.com
 * 淘宝    ：anotc.taobao.com
 * 技术Q群 ：190169595
**********************************************************************************/
#include "pwm_in.h"
#include "rc.h"
#include "include.h"

u16 Rc_Pwm_In[8];


void PWM_IN_Init(void)
{
	
		GPIO_InitTypeDef GPIO_InitStructure;
		TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
		TIM_ICInitTypeDef  TIM_ICInitStructure;
		NVIC_InitTypeDef NVIC_InitStructure;
		TIM_ICInitTypeDef  TIM4_ICInitStructure;
    
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);	 
 	  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD, ENABLE);  
	  RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);  
    GPIO_PinRemapConfig(GPIO_Remap_TIM4, ENABLE);  
	
		NVIC_InitStructure.NVIC_IRQChannel = TIM8_CC_IRQn;
		NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = NVIC_PWMIN_P;
		NVIC_InitStructure.NVIC_IRQChannelSubPriority = NVIC_PWMIN_S;
		NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
		NVIC_Init(&NVIC_InitStructure);
		NVIC_InitStructure.NVIC_IRQChannel = TIM4_IRQn;
		NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = NVIC_PWMIN_P;
		NVIC_InitStructure.NVIC_IRQChannelSubPriority = NVIC_PWMIN_S;
		NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
		NVIC_Init(&NVIC_InitStructure);	 
	
//////////////////////////////////////////////////////////////////////////////////////////////	
	
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM8,ENABLE);
   RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;
   GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
   GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
   GPIO_Init(GPIOC, &GPIO_InitStructure);
  
	 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7;
   GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
   GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
   GPIO_Init(GPIOC, &GPIO_InitStructure);
	
	 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;
   GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
   GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
   GPIO_Init(GPIOC, &GPIO_InitStructure);
	
	
   GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
   GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
   GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
   GPIO_Init(GPIOC, &GPIO_InitStructure);
	
	TIM_TimeBaseStructure.TIM_Period = 0XFFFF;                      //Éè¶¨¼ÆÊýÆ÷×Ô¶¯ÖØ×°Öµ 
	TIM_TimeBaseStructure.TIM_Prescaler =71; 	                 //Ô¤·ÖÆµÆ÷   
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;      //ÉèÖÃÊ±ÖÓ·Ö¸î:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIMÏòÉÏ¼ÆÊýÄ£Ê½
	TIM_TimeBaseInit(TIM8, &TIM_TimeBaseStructure);              //¸ù¾ÝTIM_TimeBaseInitStructÖÐÖ¸¶¨µÄ²ÎÊý³õÊ¼»¯TIMxµÄÊ±¼ä»ùÊýµ¥Î»
  

	TIM_ICInitStructure.TIM_Channel = TIM_Channel_1;
	TIM_ICInitStructure.TIM_ICPolarity = TIM_ICPolarity_Rising;
	TIM_ICInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI;
	TIM_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1;
	TIM_ICInitStructure.TIM_ICFilter = 0x0;
	TIM_ICInit(TIM8, &TIM_ICInitStructure);
	TIM_ICInitStructure.TIM_Channel = TIM_Channel_2;
	TIM_ICInitStructure.TIM_ICPolarity = TIM_ICPolarity_Rising;
	TIM_ICInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI;
	TIM_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1;
	TIM_ICInitStructure.TIM_ICFilter = 0x0;
	TIM_ICInit(TIM8, &TIM_ICInitStructure);
	TIM_ICInitStructure.TIM_Channel = TIM_Channel_3;
	TIM_ICInitStructure.TIM_ICPolarity = TIM_ICPolarity_Rising;
	TIM_ICInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI;
	TIM_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1;
	TIM_ICInitStructure.TIM_ICFilter = 0x0;
	TIM_ICInit(TIM8, &TIM_ICInitStructure);
	TIM_ICInitStructure.TIM_Channel = TIM_Channel_4;
	TIM_ICInitStructure.TIM_ICPolarity = TIM_ICPolarity_Rising;
	TIM_ICInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI;
	TIM_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1;
	TIM_ICInitStructure.TIM_ICFilter = 0x0;
	TIM_ICInit(TIM8, &TIM_ICInitStructure);
  
  /* TIM enable counter */
  TIM_Cmd(TIM8, ENABLE);

  /* Enable the CC2 Interrupt Request */
  TIM_ITConfig(TIM8, TIM_IT_CC1, ENABLE);
	TIM_ITConfig(TIM8, TIM_IT_CC2, ENABLE);
	TIM_ITConfig(TIM8, TIM_IT_CC3, ENABLE);
	TIM_ITConfig(TIM8, TIM_IT_CC4, ENABLE);
/////////////////////////////////////////////////////////////////////////////////////////////

  GPIO_PinRemapConfig(GPIO_Remap_TIM4, ENABLE);  //
	GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_12|GPIO_Pin_13|GPIO_Pin_14|GPIO_Pin_15;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD;
  GPIO_Init(GPIOD, &GPIO_InitStructure);

  
	TIM_TimeBaseStructure.TIM_Period = 0XFFFF;                      //Éè¶¨¼ÆÊýÆ÷×Ô¶¯ÖØ×°Öµ 
	TIM_TimeBaseStructure.TIM_Prescaler =71; 	                 //Ô¤·ÖÆµÆ÷   
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;      //ÉèÖÃÊ±ÖÓ·Ö¸î:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIMÏòÉÏ¼ÆÊýÄ£Ê½
	TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStructure);  
	
	  TIM4_ICInitStructure.TIM_Channel = TIM_Channel_1;                //CC1S=01 	Ñ¡ÔñÊäÈë¶Ë IC1Ó³Éäµ½TI1ÉÏ
  	TIM4_ICInitStructure.TIM_ICPolarity =TIM_ICPolarity_Rising;	   //ÉÏÉýÑØ²¶»ñ
  	TIM4_ICInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI; //Ó³Éäµ½TI1ÉÏ
  	TIM4_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1;	         //ÅäÖÃÊäÈë·ÖÆµ,²»·ÖÆµ 
  	TIM4_ICInitStructure.TIM_ICFilter = 0x00;                        //IC1F=0000 ÅäÖÃÊäÈëÂË²¨Æ÷ ²»ÂË²¨
  	TIM_ICInit(TIM4, &TIM4_ICInitStructure);
	
	  TIM4_ICInitStructure.TIM_Channel = TIM_Channel_2;                //CC1S=01 	Ñ¡ÔñÊäÈë¶Ë IC1Ó³Éäµ½TI1ÉÏ
  	TIM4_ICInitStructure.TIM_ICPolarity = TIM_ICPolarity_Rising;	   //ÉÏÉýÑØ²¶»ñ
  	TIM4_ICInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI; //Ó³Éäµ½TI1ÉÏ
  	TIM4_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1;	         //ÅäÖÃÊäÈë·ÖÆµ,²»·ÖÆµ 
  	TIM4_ICInitStructure.TIM_ICFilter = 0x00;                        //IC1F=0000 ÅäÖÃÊäÈëÂË²¨Æ÷ ²»ÂË²¨
  	TIM_ICInit(TIM4, &TIM4_ICInitStructure);
		
		TIM4_ICInitStructure.TIM_Channel = TIM_Channel_3;                //CC1S=01 	Ñ¡ÔñÊäÈë¶Ë IC1Ó³Éäµ½TI1ÉÏ
  	TIM4_ICInitStructure.TIM_ICPolarity = TIM_ICPolarity_Rising;	   //ÉÏÉýÑØ²¶»ñ
  	TIM4_ICInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI; //Ó³Éäµ½TI1ÉÏ
  	TIM4_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1;	         //ÅäÖÃÊäÈë·ÖÆµ,²»·ÖÆµ 
  	TIM4_ICInitStructure.TIM_ICFilter = 0x00;                        //IC1F=0000 ÅäÖÃÊäÈëÂË²¨Æ÷ ²»ÂË²¨
  	TIM_ICInit(TIM4, &TIM4_ICInitStructure);
		
		TIM4_ICInitStructure.TIM_Channel = TIM_Channel_4;                //CC1S=01 	Ñ¡ÔñÊäÈë¶Ë IC1Ó³Éäµ½TI1ÉÏ
  	TIM4_ICInitStructure.TIM_ICPolarity = TIM_ICPolarity_Rising;	   //ÉÏÉýÑØ²¶»ñ
  	TIM4_ICInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI; //Ó³Éäµ½TI1ÉÏ
  	TIM4_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1;	         //ÅäÖÃÊäÈë·ÖÆµ,²»·ÖÆµ 
  	TIM4_ICInitStructure.TIM_ICFilter = 0x00;                        //IC1F=0000 ÅäÖÃÊäÈëÂË²¨Æ÷ ²»ÂË²¨
  	TIM_ICInit(TIM4, &TIM4_ICInitStructure);
	
	  TIM_Cmd(TIM4,ENABLE ); 
		
	  TIM_ITConfig(TIM4, TIM_IT_CC1, ENABLE);        //ÔÊÐí¸üÐÂÖÐ¶Ï ,ÔÊÐíCC1IE²¶»ñÖÐ¶Ï	
	  TIM_ITConfig(TIM4, TIM_IT_CC2, ENABLE);
	  TIM_ITConfig(TIM4, TIM_IT_CC3, ENABLE);
	  TIM_ITConfig(TIM4, TIM_IT_CC4, ENABLE);
}

u8  TIM8CH1_CAPTURE_STA=0;	//	
u8  TIM8CH2_CAPTURE_STA=0;
u8  TIM8CH3_CAPTURE_STA=0;
u8  TIM8CH4_CAPTURE_STA=0;

void _TIM8_CC_IRQHandler(void)	
{
	static u16 temp_cnt1,temp_cnt1_2,temp_cnt2,temp_cnt2_2,temp_cnt3,temp_cnt3_2,temp_cnt4,temp_cnt4_2;
	
	Feed_Rc_Dog(1);//RC
	
	if(TIM8->SR & TIM_IT_CC1) 
	{
		TIM8->SR = ~TIM_IT_CC1;//TIM_ClearITPendingBit(TIM3, TIM_IT_CC1);

		if(TIM8CH1_CAPTURE_STA & 0x40)
		{
			TIM8CH1_CAPTURE_STA = 0x80;
			temp_cnt1 = TIM_GetCapture1(TIM8);
			TIM_OC1PolarityConfig(TIM8,TIM_ICPolarity_Falling);
		}
		else
		{
			TIM8CH1_CAPTURE_STA = 0;
			TIM8CH1_CAPTURE_STA |= 0x40;
			TIM_OC1PolarityConfig(TIM8,TIM_ICPolarity_Rising);
			
			temp_cnt1_2 = TIM_GetCapture1(TIM8);
			if(temp_cnt1_2>=temp_cnt1)
				Rc_Pwm_In[7] = temp_cnt1_2-temp_cnt1;
			else
				Rc_Pwm_In[7] = 0xffff-temp_cnt1+temp_cnt1_2+1;
		}
	}
	if(TIM8->SR & TIM_IT_CC2) 
	{
		TIM8->SR = ~TIM_IT_CC2;
		TIM8->SR = ~TIM_FLAG_CC2OF;
		if(TIM8CH2_CAPTURE_STA & 0x40)
		{
			TIM8CH2_CAPTURE_STA = 0x80;
			temp_cnt2 = TIM_GetCapture2(TIM8);
			TIM_OC2PolarityConfig(TIM8,TIM_ICPolarity_Falling);
		}
		else
		{
			TIM8CH2_CAPTURE_STA = 0;
			TIM8CH2_CAPTURE_STA |= 0x40;
			TIM_OC2PolarityConfig(TIM8,TIM_ICPolarity_Rising);
			
			temp_cnt2_2 = TIM_GetCapture2(TIM8);
			if(temp_cnt2_2>=temp_cnt2)
				Rc_Pwm_In[6] = temp_cnt2_2-temp_cnt2;
			else
				Rc_Pwm_In[6] = 0xffff-temp_cnt2+temp_cnt2_2+1;
		}
	}
	if(TIM8->SR & TIM_IT_CC3) 
	{
		TIM8->SR = ~TIM_IT_CC3;
		TIM8->SR = ~TIM_FLAG_CC3OF;
		if(TIM8CH3_CAPTURE_STA & 0x40)
		{
			TIM8CH3_CAPTURE_STA = 0x80;
			temp_cnt3 = TIM_GetCapture3(TIM8);
			TIM_OC3PolarityConfig(TIM8,TIM_ICPolarity_Falling);
		}
		else
		{
			TIM8CH3_CAPTURE_STA = 0;
			TIM8CH3_CAPTURE_STA |= 0x40;
			TIM_OC3PolarityConfig(TIM8,TIM_ICPolarity_Rising);
			temp_cnt3_2 = TIM_GetCapture3(TIM8);
			if(temp_cnt3_2>=temp_cnt3)
				Rc_Pwm_In[5] = temp_cnt3_2-temp_cnt3;
			else
				Rc_Pwm_In[5] = 0xffff-temp_cnt3+temp_cnt3_2+1;
		}
	}
	if(TIM8->SR & TIM_IT_CC4) 
	{
		TIM8->SR = ~TIM_IT_CC4;
		TIM8->SR = ~TIM_FLAG_CC4OF;
		if(TIM8CH4_CAPTURE_STA & 0x40)
		{
			TIM8CH4_CAPTURE_STA = 0x80;
			temp_cnt4 = TIM_GetCapture4(TIM8);
			TIM_OC4PolarityConfig(TIM8,TIM_ICPolarity_Falling);
		}
		else
		{
			TIM8CH4_CAPTURE_STA = 0;
			TIM8CH4_CAPTURE_STA |= 0x40;
			TIM_OC4PolarityConfig(TIM8,TIM_ICPolarity_Rising);
			
			temp_cnt4_2 = TIM_GetCapture4(TIM8);
			if(temp_cnt4_2>=temp_cnt4)
				Rc_Pwm_In[4] = temp_cnt4_2-temp_cnt4;
			else
				Rc_Pwm_In[4] = 0xffff-temp_cnt4+temp_cnt4_2+1;
		}
	}
}


u8  TIM4CH1_CAPTURE_STA=0;	//	
u8  TIM4CH2_CAPTURE_STA=0;
u8  TIM4CH3_CAPTURE_STA=0;
u8  TIM4CH4_CAPTURE_STA=0;


void _TIM4_IRQHandler(void)		
{
	static u16 temp_cnt1,temp_cnt1_2,temp_cnt2,temp_cnt2_2,temp_cnt3,temp_cnt3_2,temp_cnt4,temp_cnt4_2;
	
	Feed_Rc_Dog(1);//RC
	
	if(TIM4->SR & TIM_IT_CC1) 
	{
		TIM4->SR = ~TIM_IT_CC1;//TIM_ClearITPendingBit(TIM3, TIM_IT_CC1);

		if(TIM4CH1_CAPTURE_STA & 0x40)
		{
			TIM4CH1_CAPTURE_STA = 0x80;
			temp_cnt1 = TIM_GetCapture1(TIM4);
			TIM_OC1PolarityConfig(TIM4,TIM_ICPolarity_Falling);
		}
		else
		{
			TIM4CH1_CAPTURE_STA = 0;
			TIM4CH1_CAPTURE_STA |= 0x40;
			TIM_OC1PolarityConfig(TIM4,TIM_ICPolarity_Rising);
			
			temp_cnt1_2 = TIM_GetCapture1(TIM4);
			if(temp_cnt1_2>=temp_cnt1)
				Rc_Pwm_In[3] = temp_cnt1_2-temp_cnt1;
			else
				Rc_Pwm_In[3] = 0xffff-temp_cnt1+temp_cnt1_2+1;
		}
	}
	if(TIM4->SR & TIM_IT_CC2) 
	{
		TIM4->SR = ~TIM_IT_CC2;
		TIM4->SR = ~TIM_FLAG_CC2OF;
		if(TIM4CH2_CAPTURE_STA & 0x40)
		{
			TIM4CH2_CAPTURE_STA = 0x80;
			temp_cnt2 = TIM_GetCapture2(TIM4);
			TIM_OC2PolarityConfig(TIM4,TIM_ICPolarity_Falling);
		}
		else
		{
			TIM4CH2_CAPTURE_STA = 0;
			TIM4CH2_CAPTURE_STA |= 0x40;
			TIM_OC2PolarityConfig(TIM4,TIM_ICPolarity_Rising);
			
			temp_cnt2_2 = TIM_GetCapture2(TIM4);
			if(temp_cnt2_2>=temp_cnt2)
				Rc_Pwm_In[2] = temp_cnt2_2-temp_cnt2;
			else
				Rc_Pwm_In[2] = 0xffff-temp_cnt2+temp_cnt2_2+1;
		}
	}
	if(TIM4->SR & TIM_IT_CC3) 
	{
		TIM4->SR = ~TIM_IT_CC3;
		TIM4->SR = ~TIM_FLAG_CC3OF;
		if(TIM4CH3_CAPTURE_STA & 0x40)
		{
			TIM4CH3_CAPTURE_STA = 0x80;
			temp_cnt3 = TIM_GetCapture3(TIM4);
			TIM_OC3PolarityConfig(TIM4,TIM_ICPolarity_Falling);
		}
		else
		{
			TIM4CH3_CAPTURE_STA = 0;
			TIM4CH3_CAPTURE_STA |= 0x40;
			TIM_OC3PolarityConfig(TIM4,TIM_ICPolarity_Rising);
			temp_cnt3_2 = TIM_GetCapture3(TIM4);
			if(temp_cnt3_2>=temp_cnt3)
				Rc_Pwm_In[1] = temp_cnt3_2-temp_cnt3;
			else
				Rc_Pwm_In[1] = 0xffff-temp_cnt3+temp_cnt3_2+1;
		}
	}
	if(TIM4->SR & TIM_IT_CC4) 
	{
		TIM4->SR = ~TIM_IT_CC4;
		TIM4->SR = ~TIM_FLAG_CC4OF;
		if(TIM4CH4_CAPTURE_STA & 0x40)
		{
			TIM4CH4_CAPTURE_STA = 0x80;
			temp_cnt4 = TIM_GetCapture4(TIM4);
			TIM_OC4PolarityConfig(TIM4,TIM_ICPolarity_Falling);
		}
		else
		{
			TIM4CH4_CAPTURE_STA = 0;
			TIM4CH4_CAPTURE_STA |= 0x40;
			TIM_OC4PolarityConfig(TIM4,TIM_ICPolarity_Rising);
			
			temp_cnt4_2 = TIM_GetCapture4(TIM4);
			if(temp_cnt4_2>=temp_cnt4)
				Rc_Pwm_In[0] = temp_cnt4_2-temp_cnt4;
			else
				Rc_Pwm_In[0] = 0xffff-temp_cnt4+temp_cnt4_2+1;
		}
	}
}

/******************* (C) COPYRIGHT 2014 ANO TECH *****END OF FILE************/

