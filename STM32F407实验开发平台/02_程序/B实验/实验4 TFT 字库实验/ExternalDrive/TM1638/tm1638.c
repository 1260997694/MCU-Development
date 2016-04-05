

//#include "stm32f10x.h"
#include "tm1638.h"
#include "delay.h"
//TM1638 STB?PB13  CLK?PB14    DIO?PB15  old
//TM1638 STB��PB9  CLK��PB4    DIO��PB8
void DIO_OUT() //����TM1638DIO����Ϊ�������
{
   GPIO_InitTypeDef GPIO_InitStructure;
   //GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8 ; 
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4|GPIO_Pin_8|GPIO_Pin_9; 
   GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT; 
   GPIO_InitStructure.GPIO_Speed= GPIO_Speed_50MHz;
   GPIO_Init(GPIOB, &GPIO_InitStructure);
}
void DIO_IN()  //����TM1638DIO����Ϊ��������
{
   GPIO_InitTypeDef GPIO_InitStructure;
   GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8 ; 
   GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN; 
   GPIO_Init(GPIOB, &GPIO_InitStructure);
}
void TM1638_Write(unsigned char	DATA)			//д���ݺ���
{
   unsigned char i;
   DIO_OUT();
   for(i=0;i<8;i++)
   {
   	GPIO_ResetBits(GPIOB,GPIO_Pin_4);
	  if(DATA&0X01)
	  GPIO_SetBits(GPIOB,GPIO_Pin_8);
	  else 
	  GPIO_ResetBits(GPIOB,GPIO_Pin_8);
	  DATA>>=1;
	  GPIO_SetBits(GPIOB,GPIO_Pin_4);
	  delay_us(1);
   }
}
unsigned char TM1638_Read(void)					//�����ݺ���
{
	unsigned char i;
	unsigned char temp=0;
	DIO_IN();
	delay_us(1);
	for(i=0;i<8;i++)
	{
	  temp>>=1;
	  GPIO_ResetBits(GPIOB,GPIO_Pin_4);
	  delay_ms(1);
	  if(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_8)==1)
	  temp|=0x80;
	  GPIO_SetBits(GPIOB,GPIO_Pin_4);
	  delay_us(1);
	}
	return temp;
}
void Write_COM(unsigned char cmd)		//����������
{
	DIO_OUT();//qinyx
    GPIO_ResetBits(GPIOB,GPIO_Pin_9);
	TM1638_Write(cmd);
	GPIO_SetBits(GPIOB,GPIO_Pin_9);
}
unsigned char Read_key(void)
{
   unsigned char c[4],i,key_value=0;
   GPIO_ResetBits(GPIOB,GPIO_Pin_9);
   TM1638_Write(0x42);//��ʼ��ȡ��ֵ
   delay_us(1);
   for(i=0;i<4;i++)
   {c[i]=TM1638_Read();delay_us(1);}
   GPIO_SetBits(GPIOB,GPIO_Pin_9);
   for(i=0;i<4;i++)
   key_value|=c[i]<<i;
   for(i=0;i<8;i++)
   if((0x01<<i)==key_value)break;
   return i;
}
void Write_DATA(unsigned char add,unsigned char DATA)
{
    Write_COM(0x44);
    GPIO_ResetBits(GPIOB,GPIO_Pin_9);
	TM1638_Write(0xc0|add);
	TM1638_Write(DATA);
	GPIO_SetBits(GPIOB,GPIO_Pin_9);
}
void Write_oneLED(unsigned char num,unsigned char flag)	//��������һ��LED������numΪ��Ҫ���Ƶ�led��ţ�flagΪ0ʱϨ�𣬲�Ϊ0ʱ����
{
	Write_DATA(num,flag);
}
void init_TM1638(void)
{
	unsigned char i;
	Write_COM(0x8a);//������Ϊȫ���ȵ�4/16
	Write_COM(0x40);
	GPIO_ResetBits(GPIOB,GPIO_Pin_9);
	TM1638_Write(0xc0);
	for(i=0;i<16;i++)
	TM1638_Write(0x00);
	GPIO_SetBits(GPIOB,GPIO_Pin_9);

}

