#include "step_motor.h"

//MOTOR0-3 : PE6 PD12 PD6 PE5

u8 F_Rotation[8]={0x08,0x0C,0x04,0x06,0x02,0x03,0x01,0x09};		//


void STEP_Motor_delay(u32 tim)
{
	unsigned char i;
	for(;tim>0;tim--)
	 for(i=0;i<180;i++);
}

void STEP_Motor_GPIO_Init(void)
{
	 GPIO_InitTypeDef  GPIO_InitStructure;
		
	 RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD | RCC_APB2Periph_GPIOE, ENABLE);	 //ʹ��PB,PE�˿�ʱ��
		
	 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5 | GPIO_Pin_6;				
	 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //�������
	 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO���ٶ�Ϊ50MHz
		
	 GPIO_Init(GPIOE, &GPIO_InitStructure);	  				 //������� ��IO���ٶ�Ϊ50MHz
	 GPIO_SetBits(GPIOE,GPIO_Pin_5 | GPIO_Pin_6); 						 //PE.5 ����� 
		
	 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12 | GPIO_Pin_6;				
	 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //�������
	 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO���ٶ�Ϊ50MHz
		
	 GPIO_Init(GPIOD, &GPIO_InitStructure);	  				 //������� ��IO���ٶ�Ϊ50MHz
	 GPIO_SetBits(GPIOD,GPIO_Pin_12 | GPIO_Pin_6); 						 //PE.5 ����� 
}

void BUJIN_port(u8 dat)
{
	//unsigned char dat=0x09;
		if((dat&0x08)==0x00)
		IN2_ONOFF(Bit_RESET);
	else IN2_ONOFF(Bit_SET);
		
		if((dat&0x04)==0x00)
		IN4_ONOFF(Bit_RESET);
	else IN4_ONOFF(Bit_SET);		
		
			if((dat&0x02)==0x00)
		IN3_ONOFF(Bit_RESET);
	else IN3_ONOFF(Bit_SET);
		
		if((dat&0x01)==0x00)
		IN1_ONOFF(Bit_RESET);
	else IN1_ONOFF(Bit_SET);
}

void STEP_Motor_test(void)
{
	u8 i,j;

	STEP_Motor_GPIO_Init();	

   for(j=0;j<90;j++)
		for(i = 0; i < 8; i ++)
		{
			BUJIN_port(F_Rotation[i]);
			STEP_Motor_delay(100);		//1ms
		}
		BUJIN_port(0x00); //        8214
}
