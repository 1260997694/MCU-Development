

//#include "stm32f10x.h"
#include "tm1638.h"
#include "delay.h"
#include "gpio.h"

//TM1638 STB��PB9  CLK��PB4    DIO��PB8
void delay_tim(unsigned char tim)
{
	unsigned char i;
	for(;tim>0;tim--)
	 for(i=0;i<250;i++)
	{;}
}
//��������ʱ����
static Delay_1us(int counter)
{
	int i,j;
	for(i=0;i<counter;i++)
	  for(j=0;j<33;j++);
}


void DIO_OUT() //����TM1638DIO����Ϊ�������
{
   GPIO_InitTypeDef GPIO_InitStructure;
   //GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8 ; 
	/*
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2; 
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	 GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
   GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT; 
   GPIO_InitStructure.GPIO_Speed= GPIO_Speed_50MHz;
   GPIO_Init(GPIOB, &GPIO_InitStructure);
	*/
	    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;

    //for(i=0;i<LED_NUMBER;i++)
    {
        RCC_AHB1PeriphClockCmd( RCC_AHB1Periph_GPIOB , ENABLE); 
        GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;
        GPIO_Init(GPIOB, &GPIO_InitStructure);
        GPIO_WriteBit(GPIOB,GPIO_Pin_2,Bit_SET);
    }	
}
void DIO_IN()  //����TM1638DIO����Ϊ��������
{
   GPIO_InitTypeDef GPIO_InitStructure;
   GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2 ;
GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;	
	 GPIO_InitStructure.GPIO_OType = GPIO_OType_OD;
   GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN; 
   GPIO_Init(GPIOB, &GPIO_InitStructure);
}
void TM1638_Write(unsigned char	DATA)			//д���ݺ���
{
   unsigned char i;
   DIO_OUT();
				
   for(i=0;i<8;i++)
   {
   	GPIO_ResetBits(GPIOF,GPIO_Pin_13);
	  if(DATA&0X01)
		{
	    GPIO_SetBits(GPIOB,GPIO_Pin_2);
		}
	  else 
		{
	    GPIO_ResetBits(GPIOB,GPIO_Pin_2);
		}
	  DATA>>=1;
	  GPIO_SetBits(GPIOF,GPIO_Pin_13);
	  delay_tim(1);
   }
	 
}
unsigned char TM1638_Read(void)					//�����ݺ���
{
	unsigned char i;
	unsigned char temp=0;
	DIO_IN();
	delay_tim(1);
	for(i=0;i<8;i++)
	{
	  temp>>=1;
	  GPIO_ResetBits(GPIOF,GPIO_Pin_13);
		delay_tim(10);
		if(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_2) == Bit_SET)
	    temp|=0x80;
	  GPIO_SetBits(GPIOF,GPIO_Pin_13);
		
		delay_tim(1);
	}
	return temp;
}
void Write_COM(unsigned char cmd)		//����������
{
  GPIO_ResetBits(GPIOF,GPIO_Pin_15);
	TM1638_Write(cmd);
	GPIO_SetBits(GPIOF,GPIO_Pin_15);
}

unsigned char c[4];
unsigned char Read_key(void)
{
	unsigned char i,key_value=0;
	unsigned char tmp_num[4]={0,0,0,0};
	int* key;
   GPIO_ResetBits(GPIOF,GPIO_Pin_15);
	TM1638_Write(0x42);
	Delay(1);
	/*for(i=0;i<200;i++)
	delay_tim(200);*/
	for(i=0;i<4;i++)
	{
		c[i]=TM1638_Read();
		//delay_tim(10);
	}
	GPIO_SetBits(GPIOF,GPIO_Pin_15);				//4���ֽ����ݺϳ�һ���ֽ�
	for(i=0;i<4;i++)
		{
			if(c[i]!=0)
				switch(c[i])
			{
				case 0x01:tmp_num[i]=i*8+1; break;
				case 0x10:tmp_num[i]=i*8+2; break;
				case 0x02:tmp_num[i]=i*8+3; break;
				case 0x20:tmp_num[i]=i*8+4; break;
				case 0x04:tmp_num[i]=i*8+5; break;
				case 0x40:tmp_num[i]=i*8+6; break;
				case 0x08:tmp_num[i]=i*8+7; break;
				case 0x80:tmp_num[i]=i*8+8; break;
				default : tmp_num[i]=0;break;
			}
		}
		key_value=tmp_num[0]+tmp_num[1]+tmp_num[2]+tmp_num[3];
///////		
		/*key = (int *)&c[0];
	switch(*key)
	{
	  case 0x00000002:
		  key_value = 1;
	    break;
	  case 0x00000020:
		  key_value = 2;
	    break;
	  case 0x00000200:
		  key_value = 3;
	    break;
	  case 0x00002000:
		  key_value = 4;
	    break;
	  case 0x00020000:
		  key_value = 5;
	    break;
	  case 0x00200000:
		  key_value = 6;
	    break;
	  case 0x02000000:
		  key_value = 7;
	    break;
	  case 0x20000000:
		  key_value = 8;
	    break;
		case 0x00000001:
		  key_value = 9;
	    break;
	  case 0x00000010:
		  key_value = 10;
	    break;
	  case 0x00000100:
		  key_value = 11;
	    break;
	  case 0x00001000:
		  key_value = 12;
	    break;
	  case 0x00010000:
		  key_value = 13;
	    break;
	  case 0x00100000:
		  key_value = 14;
	    break;
	  case 0x01000000:
		  key_value = 15;
	    break;
	  case 0x10000000:
		  key_value = 16;
	    break;
		default :
			key_value = 0xff;
			break;
  }*/
   
  return (key_value);
}


void Write_DATA(unsigned char add,unsigned char DATA)
{
    Write_COM(0x44);
    GPIO_ResetBits(GPIOF,GPIO_Pin_15);
	TM1638_Write(0xc0|add);
	TM1638_Write(DATA);
	GPIO_SetBits(GPIOF,GPIO_Pin_15);
}
void Write_oneLED(unsigned char num,unsigned char flag)	//��������һ��LED������numΪ��Ҫ���Ƶ�led��ţ�flagΪ0ʱϨ�𣬲�Ϊ0ʱ����
{
	Write_DATA(num,flag);
}
void init_TM1638(void)
{	
	unsigned char i;
	
	TM1638_GPIO_Configuration();   //IO�ڳ�ʼ��

	Write_COM(0x8a);//������Ϊȫ���ȵ�4/16
	Write_COM(0x40);
	GPIO_ResetBits(GPIOF,GPIO_Pin_15);
	TM1638_Write(0xc0);
	for(i=0;i<16;i++)
	TM1638_Write(0x00);
	GPIO_SetBits(GPIOF,GPIO_Pin_15);

	DIO_OUT();
}

void TM1638_GPIO_Configuration(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;        //����GPIO��ʼ���ṹ��

/*
  RCC_APB1PeriphClockCmd(RCC_AHB1Periph_GPIOF, ENABLE);  //����GPIOFʱ��
  //RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO , ENABLE);  //ʹ��GPIOa����ģ��ʱ��ʹ�� ,PA6���Ÿ���ΪPWMģ��
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_15|GPIO_Pin_13; //����PF15 PF13�ֱ�ΪTM1638 STB CLK���ţ����ó��������
	//GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13; //����PF15 PF13�ֱ�ΪTM1638 STB CLK���ţ����ó��������
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
  GPIO_Init(GPIOF, &GPIO_InitStructure);
		
	//GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13; //����PF15 PF13�ֱ�ΪTM1638 STB CLK���ţ����ó��������
//	GPIO_Init(GPIOF, &GPIO_InitStructure);
	
  RCC_APB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE); 
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2; 
	    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
//	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
  GPIO_Init(GPIOB, &GPIO_InitStructure);	
*/

    //GPIO_InitTypeDef  GPIO_InitStructure;
//f13
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;

    //for(i=0;i<LED_NUMBER;i++)
    {
        RCC_AHB1PeriphClockCmd( RCC_AHB1Periph_GPIOF , ENABLE); 
        GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13;
        GPIO_Init(GPIOF, &GPIO_InitStructure);
        GPIO_WriteBit(GPIOF,GPIO_Pin_13,Bit_SET);
    }

		//f15
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;

    //for(i=0;i<LED_NUMBER;i++)
    {
        RCC_AHB1PeriphClockCmd( RCC_AHB1Periph_GPIOF , ENABLE); 
        GPIO_InitStructure.GPIO_Pin = GPIO_Pin_15;
        GPIO_Init(GPIOF, &GPIO_InitStructure);
        GPIO_WriteBit(GPIOF,GPIO_Pin_15,Bit_SET);
    }		
	
}

