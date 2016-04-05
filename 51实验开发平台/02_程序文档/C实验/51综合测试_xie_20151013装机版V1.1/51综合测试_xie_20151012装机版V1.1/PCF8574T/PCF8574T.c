
/*---------------------------------------------------------------------*/
/* --- STC MCU International Limited ----------------------------------*/
/* --- STC 1T Series MCU Demo Programme -------------------------------*/
/* --- Mobile: (86)13922805190 ----------------------------------------*/
/* --- Fax: 86-0513-55012956,55012947,55012969 ------------------------*/
/* --- Tel: 86-0513-55012928,55012929,55012966 ------------------------*/
/* --- Web: www.GXWMCU.com --------------------------------------------*/
/* --- QQ:  800003751 -------------------------------------------------*/
/* ���Ҫ�ڳ�����ʹ�ô˴���,���ڳ�����ע��ʹ���˺꾧�Ƽ������ϼ�����   */
/*---------------------------------------------------------------------*/


//��д Coody  2005-4-12

//#include	"config.h"
#define MAIN_Fosc		22118400UL	//
#include <PCF8574T\PCF8574T.h>

//PCF8574T ADDRESS
//A2 A1 A0 000  0X20
//A2 A1 A0 001  0X21
//A2 A1 A0 010  0X22  LED+KEY+BUZZER
//A2 A1 A0 011  0X23
//A2 A1 A0 100  0X24
//A2 A1 A0 101  0X25
//A2 A1 A0 110  0X26
//A2 A1 A0 111  0X27

/****************************/
void	I2C_Delay(void)	//for normal MCS51,	delay (2 * dly + 4) T, for STC12Cxxxx delay (4 * dly + 10) T
{
	/*u8	dly;
	dly = MAIN_Fosc / 2000000UL;		//��2us����
	//dly = MAIN_Fosc / 2000000;		//��2us����
	while(--dly)	;*/
	u16 i=80; //��������Ż��ٶ�	����������͵�5����д��
   while(i) 
   { 
     i--; 
   } 
 }

/****************************/
void I2C_Start(void)               //start the I2C, SDA High-to-low when SCL is high
{
	SDA = 1;
	I2C_Delay();
	SCL = 1;
	I2C_Delay();
	SDA = 0;
	I2C_Delay();
	SCL = 0;
	I2C_Delay();
}		


void I2C_Stop(void)					//STOP the I2C, SDA Low-to-high when SCL is high
{
	SDA = 0;
	I2C_Delay();
	SCL = 1;
	I2C_Delay();
	SDA = 1;
	I2C_Delay();
}

void S_ACK(void)              //Send ACK (LOW)
{
	SDA = 0;
	I2C_Delay();
	SCL = 1;
	I2C_Delay();
	SCL = 0;
	I2C_Delay();
}

void S_NoACK(void)           //Send No ACK (High)
{
	SDA = 1;
	I2C_Delay();
	SCL = 1;
	I2C_Delay();
	SCL = 0;
	I2C_Delay();
}
		
//void I2C_Check_ACK(void)         //Check ACK, If F0=0, then right, if F0=1, then error
void I2C_Check_ACK(char ack)         //Check ACK, If F0=0, then right, if F0=1, then error
{
if(ack == 1)
	SDA = 1;
else
	SDA = 0;
	I2C_Delay();
	SCL = 1;
	I2C_Delay();
	F0  = SDA;
	SCL = 0;
	I2C_Delay();
}

/****************************/
void I2C_WriteAbyte(u8 dat)		//write a byte to I2C
{
	u8 i;
	i = 8;
	do
	{
		if(dat & 0x80)	SDA = 1;
		else			SDA	= 0;
		dat <<= 1;
		I2C_Delay();
		SCL = 1;
		I2C_Delay();
		SCL = 0;
		I2C_Delay();
	}
	while(--i);
		I2C_Check_ACK(1);                //����Ӧ���ź�
}

/****************************/
u8 I2C_ReadAbyte(void)			//read A byte from I2C
{
	u8 i,dat;
	i = 8;
	SDA = 1;
	do
	{
		SCL = 1;
		I2C_Delay();
		dat <<= 1;
		if(SDA)		dat++;
		SCL  = 0;
		I2C_Delay();
	}
	while(--i);
	return(dat);
}

/****************************/
void WriteNbyte(u8 addr, u8 *p, u8 number)			/*	WordAddress,First Data Address,Byte lenth	*/
                         									//F0=0,right, F0=1,error
{
	I2C_Start();
	I2C_WriteAbyte(SLAW);
	I2C_Check_ACK(1);
	if(!F0)
	{
		I2C_WriteAbyte(addr);
		I2C_Check_ACK(1);
		if(!F0)
		{
			do
			{
				I2C_WriteAbyte(*p);		p++;
				I2C_Check_ACK(1);
				if(F0)	break;
			}
			while(--number);
		}
	}
	I2C_Stop();
}


/****************************/
void ReadNbyte(u8 addr, u8 *p, u8 number)				/*	WordAddress,First Data Address,Byte lenth	*/
                         									//F0=0,right, F0=1,error
{
	I2C_Start();
	I2C_WriteAbyte(SLAW);
	I2C_Check_ACK(1);
	if(!F0)
	{
		I2C_WriteAbyte(addr);
		I2C_Check_ACK(1);
		if(!F0)
		{
			I2C_Start();
			I2C_WriteAbyte(SLAR);
			I2C_Check_ACK(1);
			if(!F0)
			{
				do
				{
					*p = I2C_ReadAbyte();	p++;
					if(number != 1)		S_ACK();	//send ACK
				}
				while(--number);
				S_NoACK();			//send no ACK
			}
		}
	}
	I2C_Stop();
}

//*****************************************************************************************************
//��I2C�豸д��һ���ֽ�����
//*****************************************************************************************************

void PCF8574_Single_WriteI2C(u8 REG_Address,u8 REG_data)
{  u8 t;
	 t=(REG_Address << 1);
    I2C_Start();                  //��ʼ�ź�
	  I2C_WriteAbyte(t);   //�����豸��ַ+д�ź�
    I2C_WriteAbyte(REG_data);       //�ڲ��Ĵ������ݣ�
    I2C_Stop();                 //����ֹͣ�ź�
}

//*******************************************************************************************************
//��I2C�豸��ȡһ���ֽ�����
//*******************************************************************************************************
u8 PCF8574_Single_ReadI2C(u8 REG_Address)
{
	 u8 REG_data;
	 u8 t;
	// t=(IIC_WRITE<<1);
	//I2C_Start();                   //��ʼ�ź�
	//PCF8574_I2C_SendByte(PCF8574_SlaveAddress);    //�����豸��ַ+д�ź�
//	I2C_WriteAbyte(t);    //�����豸��ַ+д��
	//I2C_WriteAbyte(REG_Address);     //���ʹ洢��Ԫ��ַ����0��ʼ
	t=((REG_Address<<1)|0x01);	
	I2C_Start();                   //��ʼ�ź�
	//PCF8574_I2C_SendByte(PCF8574_SlaveAddress+1);  //�����豸��ַ+���ź�
	I2C_WriteAbyte(t);  //�����豸��ַ+���ź�
	REG_data=I2C_ReadAbyte();       //�����Ĵ�������
	I2C_Check_ACK(1);                //����Ӧ���ź�
	I2C_Stop();                       //ֹͣ�ź�
	return REG_data;
}					      