#ifndef _USART_H
#define _USART_H
#define USART2_MAX_RECV_LEN		600					//最大接收缓存字节数
#define USART2_MAX_SEND_LEN		600					//最大发送缓存字节数
#define USART2_RX_EN 			1		

#include "stm32f10x.h"

extern u8 Rx_Buf[];
extern u8 mid_line;
void Usart1_Init(u32 br_num);
void Usart1_IRQ(void);
void Usart1_Send(unsigned char *DataToSend ,u8 data_num);


void Uart2_Init(u32 br_num);
void USART2_IRQHandler(void);
void Uart2_Send(unsigned char *DataToSend ,u8 data_num);

void Uart3_Init(u32 br_num);
void Uart3_Send(unsigned char *DataToSend ,u8 data_num);

#endif
