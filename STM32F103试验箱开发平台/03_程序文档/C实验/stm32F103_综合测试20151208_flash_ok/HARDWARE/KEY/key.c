#include "key.h"
							   
 void Delay5ms(void)
{
		
   int i=50000;  
   while(i) 
   { 
     i--; 
   }  
}

//������ʼ������ PE1
void KEY_Init(void) //IO��ʼ��
{ 
 	GPIO_InitTypeDef GPIO_InitStructure;
	//��ʼ��KEY0-->GPIOA.13,KEY2-->GPIOA.15  ��������
 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOE | RCC_APB2Periph_GPIOA,ENABLE);//ʹ��PORTA,PORTEʱ��

	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_1;//PE2~4
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; //���ó���������
 	GPIO_Init(GPIOE, &GPIO_InitStructure);//��ʼ��GPIOE2,3,4
	
	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_0;//PE2~4
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; //���ó���������
 	GPIO_Init(GPIOA, &GPIO_InitStructure);//��ʼ��GPIOE2,3,4	
}

//����������
//���ذ���ֵ
//mode:0,��֧��������;1,֧��������;
//0��û���κΰ�������
//1��KEY0����
//2��KEY2����
//3��KEY2���� 
//4��KEY3���� WK_UP
//ע��˺�������Ӧ���ȼ�,KEY0>KEY2>KEY2>KEY3!!
u8 KEY_Scan(u8 mode)
{	 
	static u8 key_up=1;//�������ɿ���־
	
	if(mode)key_up=1;  //֧������		  
	//if(key_up&&(KEY0==0||KEY2==0||KEY2==0||KEY3==1))
	if(key_up&&(KEY2==0))
	{
		delay_ms(10);//ȥ���� 
		key_up=0;
		if(KEY4==0)return 1;
		else if(KEY2==0)return 2;
		else if(KEY2==0)return 3;
		else if(KEY3==1)return 4;
	}else if(KEY4==1&&KEY2==1&&KEY2==1&&KEY3==0)key_up=1; 	    
 	return 0;// �ް�������
}

static uint8_t key_flag = 0;
static uint8_t read_val = 0;

u8 play[4]  = {0x7E, 0x02, 0x0D, 0xEF};
u8 prev[4]  = {0x7E, 0x02, 0x02, 0xEF};
u8 next[4]  = {0x7E, 0x02, 0x01, 0xEF};
u8 pause[4] = {0x7E, 0x02, 0x0E, 0xEF};

u8 mode_U[5] = 			{0x7E, 0x03, 0x09, 0, 0xEF};
u8 mode_FLASH[5] =  {0x7E, 0x03, 0x09, 4, 0xEF}; 
u8 mode_TF[5] = 		{0x7E, 0x03, 0x09, 1, 0xEF};	

void KEY_Test(void)
{

	KEY_Init();
	PCF8574_I2C_GPIO_Config();	 
	
	PCF8574_Single_WriteI2C(PCF8574T_C, 0xF7);	//OUTC1	 close beep
	//beepms(200);	//OUTC3
	//LED0-2 : 		OUTC1 2 4
	while(key_flag != 0x0F)
	{
		
		if(strstr((const char*)gsm_ch, "OK"))
			LCD_ShowString(200, 100, "GSM_OK!"); 
		
		if(KEY1 == 0)
		{
			Delay5ms();
			if(KEY1 == 0)
			{
				key_flag |= 0x01;
				
				PCF8574_Single_WriteI2C(PCF8574T_C, 0xE7);	//OUTC4
				UART5_Send("AT\r\n",4);
				
				UART4_Send(mode_FLASH,5);			//MP3 TEST		
				Delay5ms();
				UART4_Send(play,4);			//MP3 TEST		
			}
		}
		if(KEY2 == 0)
		{
			key_flag |= 0x02;	
			
			UART4_Send(mode_TF,5);			//MP3 TEST
			Delay5ms();
			UART4_Send(play,4);			//MP3 TEST	
			
			if(key_flag & 0x01)
				PCF8574_Single_WriteI2C(PCF8574T_C, 0xE5);	//COUTC1
			else
				if(key_flag & 0x40)
					PCF8574_Single_WriteI2C(PCF8574T_C, 0xF1);	//COUTC1
			else
			PCF8574_Single_WriteI2C(PCF8574T_C, 0xF5);	//COUTC1
		}
		read_val = PCF8574_Single_ReadI2C((PCF8574T_C) | 0x01);
		if((read_val & 0x80) == 0)	//KEY3 : OUTC7
		{		
				key_flag |= 0x04;
			
				UART4_Send(mode_U,5);			//MP3 TEST
				Delay5ms();
				UART4_Send(play,4);			//MP3 TEST				
			
				if(key_flag & 0x03)
					PCF8574_Single_WriteI2C(PCF8574T_C, 0xE1);	//COUTC1
				else
					PCF8574_Single_WriteI2C(PCF8574T_C, 0xF3);	//COUTC2
		}
		
		if((read_val & 0x40) == 0)	//KEY4: OUTC6
		{
			
			key_flag |= 0x08;
			
			UART4_Send(next,4);			//MP3 TEST
			PCF8574_Single_WriteI2C(PCF8574T_C, 0xF7);	//OFF
		}		
}
}
