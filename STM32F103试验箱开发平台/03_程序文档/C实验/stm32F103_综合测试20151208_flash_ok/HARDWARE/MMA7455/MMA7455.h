#ifndef _MMA7455_H_
#define _MMA7455_H_

#include  <math.h>    //Keil library
#include <stm32f10x.h>
#include <stm32f10x_gpio.h>
#include "lcd.h"

#define   uchar unsigned char
#define   uint unsigned int	

#define	MMA7455_SlaveAddress	0x1D	//IICд��ʱ�ĵ�ַ 
#define MMA7455_IIC_READ  						((0x1D << 1) | 0x01)  //�����ָ��
#define MMA7455_IIC_WRITE 						(0x1D << 1)  //����дָ��
//************************************
/*ģ��IIC�˿�������붨��*/
#define SCL_H         GPIO_SetBits(GPIOB,GPIO_Pin_6) 
#define SCL_L         GPIO_ResetBits(GPIOB,GPIO_Pin_6) 
   
#define SDA_H         GPIO_SetBits(GPIOB,GPIO_Pin_7)
#define SDA_L         GPIO_ResetBits(GPIOB,GPIO_Pin_7)

#define SCL_read      GPIOB->IDR  & GPIO_Pin_6
#define SDA_read      GPIOB->IDR  & GPIO_Pin_7

void MMA7455_delay50us(void);
void MMA7455_data_init(void);
uint8_t MMA7455_self_test7455(void);
void MMA7455_sendxyz(void);
void MMA7455_Test(void);









#endif
