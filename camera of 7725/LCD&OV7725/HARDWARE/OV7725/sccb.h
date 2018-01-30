#ifndef __SCCB_H
#define __SCCB_H

#include "sys.h"

/************************** OV7725 �������Ŷ���********************************/
#define      OV7725_SIO_C_SCK_AHBxClock_FUN              RCC_AHB1PeriphClockCmd
#define      OV7725_SIO_C_GPIO_CLK                       RCC_AHB1Periph_GPIOD
#define      OV7725_SIO_C_GPIO_PORT                      GPIOD
#define      OV7725_SIO_C_GPIO_PIN                       GPIO_Pin_6

#define      OV7725_SIO_D_SCK_AHBxClock_FUN              RCC_AHB1PeriphClockCmd
#define      OV7725_SIO_D_GPIO_CLK                       RCC_AHB1Periph_GPIOD
#define      OV7725_SIO_D_GPIO_PORT                      GPIOD
#define      OV7725_SIO_D_GPIO_PIN                       GPIO_Pin_7

#define SCL_H         GPIO_SetBits(OV7725_SIO_C_GPIO_PORT , OV7725_SIO_C_GPIO_PIN) 
#define SCL_L         GPIO_ResetBits(OV7725_SIO_C_GPIO_PORT , OV7725_SIO_C_GPIO_PIN) 
   
#define SDA_H         GPIO_SetBits(OV7725_SIO_D_GPIO_PORT , OV7725_SIO_D_GPIO_PIN) 
#define SDA_L         GPIO_ResetBits(OV7725_SIO_D_GPIO_PORT , OV7725_SIO_D_GPIO_PIN) 

#define SCL_read      GPIO_ReadInputDataBit(OV7725_SIO_C_GPIO_PORT , OV7725_SIO_C_GPIO_PIN) 
#define SDA_read      GPIO_ReadInputDataBit(OV7725_SIO_D_GPIO_PORT , OV7725_SIO_D_GPIO_PIN) 

#define ADDR_OV7725   0x42

void SCCB_GPIO_Config(void);
int SCCB_WriteByte( u16 WriteAddress , u8 SendByte);
int SCCB_ReadByte(u8* pBuffer,   u16 length,   u8 ReadAddress);

#endif 
