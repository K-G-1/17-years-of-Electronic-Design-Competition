/******************** (C) COPYRIGHT 2014 ANO Tech ********************************
  * 作者   ：匿名科创
 * 文件名  ：usart.c
 * 描述    ：串口驱动
 * 官网    ：www.anotc.com
 * 淘宝    ：anotc.taobao.com
 * 技术Q群 ：190169595
**********************************************************************************/
#include "PID.h"
#include "usart.h"
#include "data_transfer.h"
#include "ultrasonic.h"
#include "ano_of.h"


void Usart1_Init(u32 br_num)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE); //
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1,ENABLE);//
 
	
	//USART1_TX   GPIOA.9
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9; //PA.9
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;	//
  GPIO_Init(GPIOA, &GPIO_InitStructure);//
  
  //USART1_RX	  GPIOA.
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;//PA10
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;//
  GPIO_Init(GPIOA, &GPIO_InitStructure);//

   //USART1 
	USART_InitStructure.USART_BaudRate = br_num;//
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;//
	USART_InitStructure.USART_StopBits = USART_StopBits_1;//
	USART_InitStructure.USART_Parity = USART_Parity_No;//
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	//
  USART_Init(USART1, &USART_InitStructure); //
	
  USART_Cmd(USART1, ENABLE);  // 
	
	//USART_ClearFlag(USART1, USART_FLAG_TC);
	

	USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);//

	//Usart1 NVIC 
	NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;//
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=1;//
	NVIC_InitStructure.NVIC_IRQChannelSubPriority =1;		
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			
	NVIC_Init(&NVIC_InitStructure);	


}

u8 TxBuffer[256];
u8 TxCounter=0;
u8 count=0; 

u8 Rx_Buf[256];	//串口接收缓存

void Usart1_IRQ(void)
{
	u8 com_data;
	
	if(USART1->SR & USART_SR_ORE)//ORE中断
	{
		com_data = USART1->DR;
	}

  //接收中断
	if( USART_GetITStatus(USART1,USART_IT_RXNE) )
	{
		USART_ClearITPendingBit(USART1,USART_IT_RXNE);//清除中断标志

		com_data = USART1->DR;
		ANO_DT_Data_Receive_Prepare(com_data);
	}
	//发送（进入移位）中断
	if( USART_GetITStatus(USART1,USART_IT_TXE ) )
	{
				
		USART1->DR = TxBuffer[TxCounter++]; //写DR清除中断标志          
		if(TxCounter == count)
		{
			USART1->CR1 &= ~USART_CR1_TXEIE;		//关闭TXE（发送中断）中断
		}


		//USART_ClearITPendingBit(USART2,USART_IT_TXE);
	}



}

void Usart1_Send(unsigned char *DataToSend ,u8 data_num)
{
  u8 i;
	for(i=0;i<data_num;i++)
	{
		TxBuffer[count++] = *(DataToSend+i);
	}

	if(!(USART1->CR1 & USART_CR1_TXEIE))
	{
		USART_ITConfig(USART1, USART_IT_TXE, ENABLE); //打开发送中断
	}

}



void Uart2_Init(u32 br_num)
{
	USART_InitTypeDef USART_InitStructure;
	//USART_ClockInitTypeDef USART_ClockInitStruct;
	NVIC_InitTypeDef NVIC_InitStructure;
	GPIO_InitTypeDef GPIO_InitStructure;
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE); //开启USART2时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD,ENABLE);
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);  //Ê¹ÄÜAFIO¹¦ÄÜµÄÊ±ÖÓ
  GPIO_PinRemapConfig(GPIO_Remap_USART2 ,ENABLE);  //½øÐÐÖØÓ³Éä
	
	//串口中断优先级
	NVIC_InitStructure.NVIC_IRQChannel = USART2_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);	

	
	//配置PC12作为UART5　Tx
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5; 
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOD, &GPIO_InitStructure); 
	//配置PD2作为UART5　Rx
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6 ; 
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOD, &GPIO_InitStructure); 
	
	//配置UART5
	//中断被屏蔽了
	USART_InitStructure.USART_BaudRate = br_num;       //波特率可以通过地面站配置
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;  //8位数据
	USART_InitStructure.USART_StopBits = USART_StopBits_1;   //在帧结尾传输1个停止位
	USART_InitStructure.USART_Parity = USART_Parity_No;    //禁用奇偶校验
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None; //硬件流控制失能
	USART_InitStructure.USART_Mode = USART_Mode_Tx | USART_Mode_Rx;  //发送、接收使能
	USART_Init(USART2, &USART_InitStructure);
	


	//使能UART5接收中断
	USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);
	//使能USART5
	USART_Cmd(USART2, ENABLE); 
//	//使能发送（进入移位）中断
//	if(!(USART2->CR1 & USART_CR1_TXEIE))
//	{
//		USART_ITConfig(USART2, USART_IT_TXE, ENABLE); 
//	}

}
u8 Tx5Buffer[256];
u8 Tx5Counter=0;
u8 count5=0; 
u8 mid_line=0;
u8 CCD_OK_flag=0;
float CCD_ctrl_time;

void USART2_IRQHandler(void)
{
	u8 com_data;

//    if(USART_GetFlagStatus(USART2, USART_FLAG_ORE) != RESET)
//    {
//    USART_ClearFlag(USART2, USART_FLAG_ORE); //清除溢出中断
//    }

  //接收中断
	if( USART_GetITStatus(USART2,USART_IT_RXNE) )
	{
		USART_ClearITPendingBit(USART2,USART_IT_RXNE);//清除中断标志
		CCD_ctrl_time = Get_Cycle_T(3)/1000000.0f;
		com_data = USART2->DR;
//		mid_line = USART2->DR;
//		CCD_OK_flag =1;
//		My_Data_Receive_Prepare(com_data);
        AnoOF_GetOneByte(com_data);
	}

	//发送（进入移位）中断
	if( USART_GetITStatus(USART2,USART_IT_TXE ) )
	{
				
		USART2->DR = Tx5Buffer[Tx5Counter++]; //写DR清除中断标志
          
		if(Tx5Counter == count5)
		{
			USART2->CR1 &= ~USART_CR1_TXEIE;		//关闭TXE（发送中断）中断
		}


		//USART_ClearITPendingBit(USART2,USART_IT_TXE);
	}

}

void Uart2_Send(unsigned char *DataToSend ,u8 data_num)
{
	u8 i;
	for(i=0;i<data_num;i++)
	{
		Tx5Buffer[count5++] = *(DataToSend+i);
	}

	if(!(USART2->CR1 & USART_CR1_TXEIE))
	{
		USART_ITConfig(USART2, USART_IT_TXE, ENABLE); //打开发送中断
	}

}


void Uart3_Init(u32 br_num)
{
	USART_InitTypeDef USART_InitStructure;
	//USART_ClockInitTypeDef USART_ClockInitStruct;
	NVIC_InitTypeDef NVIC_InitStructure;
	GPIO_InitTypeDef GPIO_InitStructure;
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3, ENABLE); //开启USART2时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD,ENABLE);
	
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);  //Ê¹ÄÜAFIO¹¦ÄÜµÄÊ±ÖÓ
  GPIO_PinRemapConfig(GPIO_FullRemap_USART3 ,ENABLE);  //½øÐÐÖØÓ³Éä
	//串口中断优先级
	NVIC_InitStructure.NVIC_IRQChannel = USART3_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 4;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);	


	
	//配置PC12作为UART5　Tx
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8; 
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOB, &GPIO_InitStructure); 
	//配置PD2作为UART5　Rx
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9 ; 
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOB, &GPIO_InitStructure); 
	
	//配置UART5
	//中断被屏蔽了
	USART_InitStructure.USART_BaudRate = br_num;       //波特率可以通过地面站配置
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;  //8位数据
	USART_InitStructure.USART_StopBits = USART_StopBits_1;   //在帧结尾传输1个停止位
	USART_InitStructure.USART_Parity = USART_Parity_No;    //禁用奇偶校验
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None; //硬件流控制失能
	USART_InitStructure.USART_Mode = USART_Mode_Tx | USART_Mode_Rx;  //发送、接收使能
	USART_Init(USART3, &USART_InitStructure);
	


	//使能UART5接收中断
	USART_ITConfig(USART3, USART_IT_RXNE, ENABLE);
	//使能USART5
	USART_Cmd(USART3, ENABLE); 
//	//使能发送（进入移位）中断
//	if(!(USART2->CR1 & USART_CR1_TXEIE))
//	{
//		USART_ITConfig(USART2, USART_IT_TXE, ENABLE); 
//	}

}

u8 Tx3Buffer[256];
u8 Tx3Counter=0;
u8 count3=0; 
void USART3_IRQHandler(void)
{
	u8 com_data;

    if(USART_GetFlagStatus(USART3, USART_FLAG_ORE) != RESET)
    {
    USART_ClearFlag(USART3, USART_FLAG_ORE); //清除溢出中断
    }
  //接收中断
	if( USART_GetITStatus(USART3,USART_IT_RXNE) != RESET )
	{
		USART_ClearITPendingBit(USART3,USART_IT_RXNE);//清除中断标志

		com_data = USART3->DR;
        Openmv_Data_Receive_Prepare(com_data);

	}

//	//发送（进入移位）中断
	if( USART_GetITStatus(USART3,USART_IT_TXE ) )
	{
				
		USART3->DR = Tx3Buffer[Tx3Counter++]; //写DR清除中断标志
          
		if(Tx3Counter == count3)
		{
			USART3->CR1 &= ~USART_CR1_TXEIE;		//关闭TXE（发送中断）中断
		}


		USART_ClearITPendingBit(USART2,USART_IT_TXE);
	}

}

void Uart3_Send(unsigned char *DataToSend ,u8 data_num)
{
	u8 i;
	for(i=0;i<data_num;i++)
	{
		Tx3Buffer[count3++] = *(DataToSend+i);
	}

	if(!(USART3->CR1 & USART_CR1_TXEIE))
	{
		USART_ITConfig(USART3, USART_IT_TXE, ENABLE); //打开发送中断
	}

}


/******************* (C) COPYRIGHT 2014 ANO TECH *****END OF FILE************/

