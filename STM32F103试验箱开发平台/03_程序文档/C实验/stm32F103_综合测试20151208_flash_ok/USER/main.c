#include "stm32f10x.h"
#include "stm32f10x_conf.h"
#include "led.h"
#include "delay.h"
#include "key.h"
#include "sys.h"
#include "usart.h"	 
#include "24cxx.h"
#include "touch.h"	
#include "keypad.h"
#include "relay.h"
#include "dht11.h"
#include "DC_motor.h"
#include "step_motor.h"
#include "bmp085.h"
#include "MMA7455.h"
#include "flash.h"
#include "lcd.h"
#include "PCF8574.h"
#include "enc28j60.h"
#include "Dot_Matrix.h"

  
u8 state=0;	   
void beepms(u16 va);  
void refshow(void);//ˢ����ʾ	
 


void Load_Drow_Dialog(void)
{
	LCD_Clear(WHITE);//����   
 	POINT_COLOR=BLUE;//��������Ϊ��ɫ 
	LCD_ShowString(lcddev.width-24,0,"RST");//��ʾ��������
  	POINT_COLOR=RED;//���û�����ɫ 
}

void xianshi()//��ʾ��Ϣ
{    
	u8 idstr[5];
	BACK_COLOR=WHITE;
	POINT_COLOR=RED;	
	LCD_ShowString(0,2,"ID:");	    
	inttohex(lcddev.id,idstr);	  
	LCD_ShowString(100,2,idstr);
}

void refshow(void)	 //ˢ����ʾ
{
	switch(state)
	{
		case 0:
		LCD_Clear(WHITE);
	    xianshi();
    	//showqq();
		break;
		case 1:
		LCD_Clear(BLACK); 
		break;
		case 2:
		LCD_Clear(RED);
		break;
		case 3:
		LCD_Clear(GREEN);
		break;
		case 4:
		LCD_Clear(BLUE);
		break;
	}	
}
void jiance(u8 key) //��ⰴ��
{
	if(key==1)	//KEY_RIGHT����,��ִ��У׼����
	{
		LCD_Clear(WHITE);//����
	    TP_Adjust();  //��ĻУ׼ 
		TP_Save_Adjdata();	 
		Load_Drow_Dialog();
	}
	if(key==2)
	{
		state++;
		 if(state==5)
		 {
		 	state=0;
			abx=1;
			LCD_Init();	

		 }
		refshow();//ˢ����ʾ
	}

}	 

void beepms(u16 va)
{
	beep=1;
	delay_ms(va);
	beep=0;
}				

uint32_t address = 0;

int main(void)
{	 
	delay_init();	    	 		//��ʱ������ʼ��	 
	PCF8574_I2C_GPIO_Config();	 
			
	lcddev.bus16=1;//���߽ӿڣ�0-8λ���ߣ�1-16λ���ߣ��޸�8λ����֮ǰ��ȷ������������Ƿ���8λ�ӿڣ�Ŀǰֻ��2.4��2.8�����֧��8λ�İ汾��3.2�����Ͼ���֧��8λ���� 
	lcddev.id=0x1943;//ָ��ID,0x1234Ϊ�Զ���ID,�м�ע�ⲻ�����е������ܶ���ID,ֻ���ٲ�������IC�ܶ�ID,����4.3���Լ�4.3�����ϵĶ����ܶ�ID.

	delay_init();	    	 		//��ʱ������ʼ��	  
	NVIC_Configuration(); 	//����NVIC�жϷ���2:2λ��ռ���ȼ���2λ��Ӧ���ȼ�
	Uart1_init(9600);	 			//���ڳ�ʼ��Ϊ9600
	Uart3_init(115200);			//RFID
	Uart4_init(9600);				//MP3  
	Uart5_init(9600);				//GSM

	LCD_Init();	
	
  SPI_Flash_Init();			  //��ʼ��Flash;	
	GPIO_SetBits(GPIOC, GPIO_Pin_0);	
	GPIO_SetBits(GPIOD, GPIO_Pin_7);	
	
		while(1)
	{
		ziku_test();
	}
	
	
	//tp_dev.init();					//������ʼ��
	
	//enc28j60_Test();			//�W�ڜyԇ

#if 1	                                       
	LCD_Clear(BLACK);
	LCD_DrawRectangle(0,5, 479, 271);
	LCD_DrawRectangle(5,18, 474, 266);
	LCD_ShowString(150, 6, "--STM32F103VCT6 Platform--");  // ʵ�鿪��ƽ̨	
	LCD_ShowString(150,60, "STEP1: KEY and GSM testing");
	LCD_ShowString(10, 200, "Press K1,K2,K3,K4, observe LED1,LED2,LED3 and information"); 		
	KEY_Test();						//STEP1: KEY test
	
		
	LCD_Clear(BLACK);
	LCD_DrawRectangle(0,5, 479, 271);
	LCD_DrawRectangle(5,18, 474, 266);
	LCD_ShowString(150, 6, "--STM32F103VCT6 Platform--");  // ʵ�鿪��ƽ̨	
	LCD_ShowString(150,60, "STEP2: RELAY testing");
	LCD_ShowString(150, 200, "Tips: observe the RELAY"); 		
	Relay_test();					//STEP2: RELAY test
		
#endif
		//Delay5ms();
		LCD_Clear(BLACK);
		LCD_DrawRectangle(0,5, 479, 271);
		LCD_DrawRectangle(5,18, 474, 266);
		LCD_ShowString(150, 6, "--STM32F103VCT6 Platform--");  // ʵ�鿪��ƽ̨
		LCD_ShowString(30,60, "STEP3: Temperature, humidity and smoke Sensor testing");	//
		//LCD_ShowString(150, 200, ""); 
		LCD_ShowString(50, 220, "Tips: Note of the information on the screen"); 		
	while(KEY1 == 1)
	{	
		DHT11_Test();					//STEP3: DHT11 test	
		GAS_Test();
		HUMAN_Test();		
	}
		//delay_ms(500);
	LCD_Clear(BLACK);
	LCD_DrawRectangle(0,5, 479, 271);
	LCD_DrawRectangle(5,18, 474, 266);
	LCD_ShowString(150, 6, "--STM32F103VCT6 Platform--");  // ʵ�鿪��ƽ̨
	LCD_ShowString(180,60, "STEP4: RFID testing");
	LCD_ShowString(100, 100, "Tips: Note of the information on the screen"); 	
	RFID_Test();				  //STEP4: RFID test			
	delay_ms(500);
	
	LCD_Clear(BLACK);
	LCD_DrawRectangle(0,5, 479, 271);
	LCD_DrawRectangle(5,18, 474, 266);
	LCD_ShowString(150, 6, "--STM32F103VCT6 Platform--");  // ʵ�鿪��ƽ̨
	LCD_ShowString(100,60, "STEP5: DC motor testing");
	LCD_ShowString(100, 100, "Tips: Observe the DC motor"); 
	while(KEY1 == 1)
	{	
		DC_Motor_test();			//STEP5: DC motor test	
	}		
		delay_ms(500);
	LCD_Clear(BLACK);
	LCD_DrawRectangle(0,5, 479, 271);
	LCD_DrawRectangle(5,18, 474, 266);
	LCD_ShowString(150, 6, "--STM32F103VCT6 Platform--");  // ʵ�鿪��ƽ̨
	LCD_ShowString(100,60, "STEP6: STEP motor testing");
	LCD_ShowString(100, 100, "Tips: Observe the STEP motor"); 	
	while(KEY1 == 1)
	{	
		STEP_Motor_test();		//STEP6: step_motor test	
	}
		delay_ms(500);
	LCD_Clear(BLACK);
	LCD_DrawRectangle(0,5, 479, 271);
	LCD_DrawRectangle(5,18, 474, 266);
	LCD_ShowString(150, 6, "--STM32F103VCT6 Platform--");  // ʵ�鿪��ƽ̨
	LCD_ShowString(100,60, "STEP7: Dot matrix testing");
	LCD_ShowString(100, 100, "Tips: Observe the Dot matrix");	
	while(KEY1 == 1)
	{	
		Dot_Matrix_test();		//STEP9: Dot_Matrix test
	}
	G_ONOFF(Bit_SET);
	delay_ms(500);
	LCD_Clear(BLACK);
	LCD_DrawRectangle(0,5, 479, 271);
	LCD_DrawRectangle(5,18, 474, 266);
	LCD_ShowString(150, 6, "--STM32F103VCT6 Platform--");  // ʵ�鿪��ƽ̨	
	LCD_ShowString(100,60, "STEP8: Presure and temperature testing");
	LCD_ShowString(50, 100, "Tips: Note of the information on the screen");
	while(KEY1 == 1)
	{	
		BMP085_Test();
	}
		delay_ms(500);	
	LCD_Clear(BLACK);
	LCD_DrawRectangle(0,5, 479, 271);
	LCD_DrawRectangle(5,18, 474, 266);
	LCD_ShowString(150, 6, "--STM32F103VCT6 Platform--");  // ʵ�鿪��ƽ̨	
	LCD_ShowString(100,60, "STEP9: Acceleration testing");
	LCD_ShowString(50, 100, "Tips: Note of the information on the screen");
	while(KEY1 == 1)
	{	
		MMA7455_Test();
	}
	
	LCD_Clear(BLACK);
	LCD_DrawRectangle(0,5, 479, 271);
	LCD_DrawRectangle(5,18, 474, 266);
	LCD_ShowString(150, 6, "--STM32F103VCT6 Platform--");  // ʵ�鿪��ƽ̨	
	LCD_ShowString(150,60, "Test complete!");
		//init_TM1638();			//keypad
		//TM1638Test();	

	while(1)
	{	

			//PCF8574_Single_WriteI2C(PCF8574_SlaveAddress, 0xFF);
			//Delay5ms();
			//PCF8574_Single_WriteI2C(PCF8574_SlaveAddress, 0);
			//Delay5ms();Delay5ms();Delay5ms();Delay5ms();Delay5ms();
			//Delay5ms();Delay5ms();Delay5ms();Delay5ms();		
			//Delay5ms();	
	}
}
		/*
	while(1)
	{ 
	   key=KEY_Scan(0);//ɨ�谴��		   
	   tp_dev.scan(0); //ɨ�败��		   	
			
		if(tp_dev.sta&TP_PRES_DOWN)			//������������
		{
			if(state!=1)
			{
				LCD_Clear(WHITE);
			}
			while(key==0)
			{	
			
				key=KEY_Scan(0);//ɨ�谴��
		    	tp_dev.scan(0);	
				if(tp_dev.sta&TP_PRES_DOWN)			//������������
				{			
				 	if(tp_dev.x<lcddev.width&&tp_dev.y<lcddev.height)
					{	
						if(tp_dev.x>(lcddev.width-24)&&tp_dev.y<16)Load_Drow_Dialog();//���
						else TP_Draw_Big_Point(tp_dev.x,tp_dev.y,RED);		//��ͼ	  			   
					}
				}
							
			} 			
		}	   	    
	   jiance(key);//��ⰴ��	 
		i++;
		if(i==65000)
		{
			i=0;
			LED0=!LED0;
		}
	}
	*/
