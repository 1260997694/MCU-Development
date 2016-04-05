#include "PCF8574.h"
#include  <math.h>    //Keil library

//PA0(23) - SCL
//PA1(24) - SDA

/*******************************************************************************
* Function Name  : I2C_GPIO_Config
* Description    : Configration Simulation IIC GPIO
* Input          : None 
* Output         : None
* Return         : None
****************************************************************************** */
void PCF8574_I2C_GPIO_Config(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	
	PCF8574_I2C_Stop();
}

void PCF8574_i2c_SDA_input(void)
{
   GPIO_InitTypeDef GPIO_InitStructure;
   GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7 ;
   //GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;	
	 //GPIO_InitStructure.GPIO_OType = GPIO_OType_OD;
   //GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN; 
	 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
   GPIO_Init(GPIOB, &GPIO_InitStructure);
}

void PCF8574_i2c_SDA_output(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7; 
	//GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	//GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	//GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT; 
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed= GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
}
/*******************************************************************************
* Function Name  : PCF8574_I2C_delay
* Description    : Simulation IIC Timing series delay
* Input          : None
* Output         : None
* Return         : None
****************************************************************************** */
void PCF8574_I2C_delay(void)
{
		
   u16 i=5000; //��������Ż��ٶ�	����������͵�5����д��
   while(i) 
   { 
     i--; 
   }  
}

void PCF8574_delay5ms(void)
{
		
   int i=50000;  
   while(i) 
   { 
     i--; 
   }  
}

void PCF8574_delay50us(void)
{
		
   int i=500;  
   while(i) 
   { 
     i--; 
   }  
}
//*************************************************************************************************
//I2C��ʼ�ź�
//*************************************************************************************************
void PCF8574_I2C_Start(void)
{
    SDA_H;                    //����������
    SCL_H;                    //����ʱ����
    PCF8574_I2C_delay();                 //��ʱ
    SDA_L;                    //�����½���
    PCF8574_I2C_delay();                 //��ʱ
    SCL_L;                    //����ʱ����
    PCF8574_I2C_delay();                 //���	
}
//*************************************************************************************************
//I2Cֹͣ�ź�
//*************************************************************************************************
void PCF8574_I2C_Stop(void)
{
	  SCL_L;                    //����ʱ����
    SDA_L;                    //����������
    PCF8574_I2C_delay();                 //��ʱ	
    SCL_H;                    //����ʱ����
    PCF8574_I2C_delay();                 //��ʱ
    SDA_H;                    //����������
    PCF8574_I2C_delay();                 //��ʱ
}
//**************************************************************************************************
//I2C����Ӧ���ź�
//��ڲ���:ack (0:ACK 1:NAK)
//**************************************************************************************************
void PCF8574_I2C_SendACK(char ack)
{
	if(ack == 1)
	  SDA_H;
	else
    SDA_L;                  //дӦ���ź�
	SCL_H;                    //����ʱ����
	PCF8574_I2C_delay();                 //��ʱ
	SCL_L;                    //����ʱ����
	PCF8574_I2C_delay();                 //��ʱ
}
//****************************************************************************************************
//I2C����Ӧ���ź�
//****************************************************************************************************
char PCF8574_I2C_RecvACK(void)
{
	char CY;
	PCF8574_i2c_SDA_input();
	PCF8574_I2C_delay();                 //��ʱ	
	SCL_H;                    //����ʱ����
	PCF8574_I2C_delay();                 //��ʱ
	if(SDA_read)
    CY = 1;                   //��Ӧ���ź�
	else
		CY = 0;
	SCL_L;                    //����ʱ����
	PCF8574_i2c_SDA_output();
	PCF8574_I2C_delay();                 //��ʱ
	return CY;
}
//*****************************************************************************************************
//��I2C���߷���һ���ֽ�����
//*****************************************************************************************************
void PCF8574_I2C_SendByte(uchar dat)
{
    uchar i;
    for (i=0; i<8; i++)         //8λ������
    {
			  if(dat&0x80)
          SDA_H;               //�����ݿ�
			  else
					SDA_L;
				
        dat <<= 1;              //�Ƴ����ݵ����λ			
        SCL_H;                //����ʱ����
        PCF8574_I2C_delay();             //��ʱ
        SCL_L;                //����ʱ����
        PCF8574_I2C_delay();             //��ʱ
    }
    PCF8574_I2C_RecvACK();
}
//*****************************************************************************************************
//��I2C���߽���һ���ֽ�����
//******************************************************************************************************
uchar PCF8574_I2C_RecvByte(void)
{
    uchar i;
    uchar dat = 0;
		PCF8574_i2c_SDA_input();
    for (i=0; i<8; i++)         //8λ������
    {
        SCL_L;                //����ʱ����
        PCF8574_I2C_delay();             //��ʱ 
        SCL_H;                //����ʱ����
        PCF8574_I2C_delay();             //��ʱ
  			dat <<= 1;			
			  if(SDA_read)
					dat |= 1;             //������               

    }
	  PCF8574_i2c_SDA_output();		
    return dat;
}

//*****************************************************************************************************
//��I2C�豸д��һ���ֽ�����
//*****************************************************************************************************

//REG_Address : SALVE ADDRESS
//REG_data    : data
void PCF8574_Single_WriteI2C(uchar REG_Address,uchar REG_data)
{  uchar t;
	 t=(REG_Address<<1);
	
    PCF8574_I2C_Start();       //��ʼ�ź�
	  PCF8574_I2C_SendByte(t);   //�����豸��ַ+д�ź�
    PCF8574_I2C_SendByte(REG_data);   //�ڲ��Ĵ�����ַ
    PCF8574_I2C_Stop();        //����ֹͣ�ź�
}

//*******************************************************************************************************
//��I2C�豸��ȡһ���ֽ�����
//*******************************************************************************************************
uchar PCF8574_Single_ReadI2C(uchar REG_Address)
{
	uchar REG_data;
	 uchar t;
	t=((REG_Address<<1)|0x01);	
	
	PCF8574_I2C_Start();                   //��ʼ�ź�
	PCF8574_I2C_SendByte(t);  //�����豸��ַ+���ź�
	REG_data=PCF8574_I2C_RecvByte();       //�����Ĵ�������
	PCF8574_I2C_SendACK(1);                //����Ӧ���ź�
	PCF8574_I2C_Stop();                    //ֹͣ�ź�
	return REG_data;
}					      

