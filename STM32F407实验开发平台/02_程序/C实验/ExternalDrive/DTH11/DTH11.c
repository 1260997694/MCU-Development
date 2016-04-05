//#include "stm32f10x.h"
#include "dth11.h"
#include "delay.h"
#include "gpio.h"
#include "uart.h"
#include "lcd.h"

typedef unsigned char  U8;       //defined for unsigned 8-bits integer variable 	  �޷���8λ���ͱ���  
typedef unsigned int   U16;      // defined for unsigned 16-bits integer variable 	  �޷���16λ���ͱ��� 
unsigned char  U8FLAG,k;
unsigned char  U8count,U8temp;
unsigned char  U8T_data_H,U8T_data_L,U8RH_data_H,U8RH_data_L,U8checkdata;
unsigned char  U8T_data_H_temp,U8T_data_L_temp,U8RH_data_H_temp,U8RH_data_L_temp,U8checkdata_temp;
unsigned char  U8comdata;
//unsigned char  outdata[5];  //���巢�͵��ֽ���	   
unsigned char  indata[5];
unsigned char  count, count_r=0;
unsigned char  str[5]={"RS232"};
unsigned char  U16temp1,U16temp2;
u8 tdata[4]={0x00,0x00,0x00,0x00};
u8 sbuf;
////////////////////////////////////////////////////////////
void DTH11_OUT() //����TM1638DIO����Ϊ�������
{
   GPIO_InitTypeDef GPIO_InitStructure;
	 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3; 
   GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT; 
   GPIO_InitStructure.GPIO_Speed= GPIO_Speed_50MHz;
   GPIO_Init(GPIOC, &GPIO_InitStructure);
}
////////////////////////////////////////////////////////////
void DTH11_IN()  //����TM1638DIO����Ϊ��������
{
   GPIO_InitTypeDef GPIO_InitStructure;
   GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3 ; 
   GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN; 
   GPIO_Init(GPIOC, &GPIO_InitStructure);
}
////////////////////////////////////////////////////////////
  void DTH11_Delay(U16 j)
    {     
			U8 i;
	    for(;j>0;j--)
	  { 	
		//for(i=0;i<27;i++);
			for(i=0;i<250;i++);

	  }
    } 
////////////////////////////////////////////////////////////
		
void  Delay_10us(void)
      {
        unsigned char i;
        i--;
        i--;
        i--;
        i--;
        i--;
        i--;
       }
////////////////////////////////////////////////////////////
      void  DTH11_COM(void)
      {
     
	      unsigned char count,i;
		/*		U8comdata=0;
      for(i=8;i>0;i--)	   
	    {
				U8comdata<<=1;
				count=0;
				DTH11_IN();	
			  while((GPIO_ReadInputDataBit(GPIOF,GPIO_Pin_6)==0)&&count++<20);
				if(count>=20) return ;
			  DTH11_Delay(4);
				if(GPIO_ReadInputDataBit(GPIOF,GPIO_Pin_6)!=0)
				{
					U8comdata++;
					while((GPIO_ReadInputDataBit(GPIOF,GPIO_Pin_6)!=0)&&count++<20)
					{
						DTH11_OUT();	
						GPIO_SetBits(GPIOF,GPIO_Pin_6);
					}
					if(count>=20)
					{
						return ;
					}
				
				}
				
			}*/
			U8comdata=0;
      for(i=0;i<8;i++)	   
	    {
		
	   //	U8FLAG=2;
			DTH11_IN();	
			//while((!GPIO_ReadInputDataBit(GPIOF,GPIO_Pin_6))&&U8FLAG++);
	   	//while((!P2_0)&&U8FLAG++);
			while(!GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_3));
			DTH11_Delay(4);
	  	U8temp=0;
			if(GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_3))U8temp=1;
	    // if(P2_0)U8temp=1;
		    //U8FLAG=2;
				//while((GPIO_ReadInputDataBit(GPIOF,GPIO_Pin_6))&&U8FLAG++);
			while(GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_3));
		// while((P2_0)&&U8FLAG++);
	   	//��ʱ������forѭ��		  
	   //	 if(U8FLAG==1)break;
	   	//�ж�����λ��0����1	 
	   	   
		// ����ߵ�ƽ�߹�Ԥ��0�ߵ�ƽֵ������λΪ 1 
	   	 
		   U8comdata<<=1;
	   	   U8comdata|=U8temp;        //0
	     }//rof
	   //U8comdata=9;
	}
////////////////////////////////////////////////////////////
void DTH11_RH(void)
	{
		/*while(1)//4  30US  6  50US   3200 24MS
		{
		DTH11_OUT();
		GPIO_ResetBits(GPIOF,GPIO_Pin_6);
		DTH11_Delay(3200);
		GPIO_SetBits(GPIOF,GPIO_Pin_6);
		DTH11_Delay(3200);
		}*/

	  //��������18ms 
		DTH11_OUT();
		GPIO_ResetBits(GPIOC,GPIO_Pin_3);
       //P2_0=0;
		DTH11_Delay(2600);
		//DTH11_Delay(200);
		//DTH11_Delay(200);
	//	DTH11_Delay(200);
		GPIO_SetBits(GPIOC,GPIO_Pin_3);
	  // P2_0=1;
	 //������������������ ������ʱ20us
		DTH11_Delay(3);
	 //������Ϊ���� �жϴӻ���Ӧ�ź� 
		GPIO_SetBits(GPIOC,GPIO_Pin_3);
	   //P2_0=1;
	 //�жϴӻ��Ƿ��е͵�ƽ��Ӧ�ź� �粻��Ӧ����������Ӧ����������	
			DTH11_IN();
		if(!GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_3))
	   //if(!P2_0)		 //T !	  
	   {
	   U8FLAG=2;
	 //�жϴӻ��Ƿ񷢳� 80us �ĵ͵�ƽ��Ӧ�ź��Ƿ����	 
			 //while((!GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_3))&&U8FLAG++);
			 while(!GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_3));  //xie
	   U8FLAG=2;
	 //�жϴӻ��Ƿ񷢳� 80us �ĸߵ�ƽ���緢����������ݽ���״̬

			//while((GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_3))&&U8FLAG++);	
			while(GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_3));		//xie			 
			//while((P2_0)&&U8FLAG++);
	 //���ݽ���״̬		 
	   DTH11_COM();
	   U8RH_data_H_temp=U8comdata;
	   DTH11_COM();
	   U8RH_data_L_temp=U8comdata;
	   DTH11_COM();
	   U8T_data_H_temp=U8comdata;
	   DTH11_COM();
	   U8T_data_L_temp=U8comdata;
	   DTH11_COM();
	   U8checkdata_temp=U8comdata;
			 DTH11_OUT();
			 GPIO_SetBits(GPIOC,GPIO_Pin_3);
	  // P2_0=1;
	 //����У�� 
	 
	   U8temp=(U8T_data_H_temp+U8T_data_L_temp+U8RH_data_H_temp+U8RH_data_L_temp);
	  if(U8temp==U8checkdata_temp)
	   {
	   	  U8RH_data_H=U8RH_data_H_temp;
	   	  U8RH_data_L=U8RH_data_L_temp;
		  U8T_data_H=U8T_data_H_temp;
	   	  U8T_data_L=U8T_data_L_temp;
	   	  U8checkdata=U8checkdata_temp;
	   }//fi
	   }//fi

	}
	
void Send_DTH11(void)
	{
		  u8 DHT11_temp[17]={"temp_value:00.0 C"};
      u8 DHT11_humi[17]={"humi_value:00.0RH"};
		 str[0]=U8RH_data_H;
	   str[1]=U8RH_data_L;
	   str[2]=U8T_data_H;
	   str[3]=U8T_data_L;
	   str[4]=U8checkdata;

	//	printf("Temperature=%d%d%d%d%d",str[0],str[1],str[2],str[3],str[4]);
	//	LCD_ShowString(150, 100, "�¶�ֵΪ��", Red, Black);
	//	LCD_ShowString(150, 100, "�¶�ֵΪ��", Red, Black);


//	LCD_ShowString(200, 18, bmp_tmp, White, Black);
	DHT11_temp[11]=(str[2]%100)/10+'0';  // ȡʮλ 
	DHT11_temp[12]=str[2]%10+'0';        // ȡ��λ
	LCD_ShowString(150, 140,DHT11_temp, White, Black);
	
			
	DHT11_humi[11]=(str[0]%100)/10+'0';  // ȡʮλ 
	DHT11_humi[12]=str[0]%10+'0';        // ȡ��λ
	LCD_ShowString(150, 160,DHT11_humi, White, Black);		
	/*
	outdata[3] =str[0]/1000+'0';      // ȡǧλ 
  outdata[2] =(str[0]%1000)/100+'0'; //ȡ��λ 
  outdata[11] =(str[0]%100)/10+'0';  // ȡʮλ 
  outdata[0] =str[0]%10+'0';        // ȡ��λ
	
  bmp_tmp[11]=outdata[2];
	bmp_tmp[12]=outdata[1];
	bmp_tmp[14]=outdata[0];
//	LCD_ShowString(200, 18, bmp_tmp, White, Black);
	//LCD_ShowString(150, 60, bmp_tmp, White, Black);
  LCD_ShowString(150, 60,"temperture", Red, Black); */

		
		
		
		printf("humi_value =%d %%RH \r\n",str[0]);
		printf("temp_value =%d C \r\n",str[2]);

  }
/*void conversion(long temp_data)  
{     
    shiwan=temp_data/100000+0x30 ;
    temp_data=temp_data%100000;   //ȡ������ 
    wan=temp_data/10000+0x30 ;
    temp_data=temp_data%10000;   //ȡ������
	qian=temp_data/1000+0x30 ;
    temp_data=temp_data%1000;    //ȡ������
    bai=temp_data/100+0x30   ;
    temp_data=temp_data%100;     //ȡ������
    shi=temp_data/10+0x30    ;
    temp_data=temp_data%10;      //ȡ������
    ge=temp_data+0x30; 	
}*/

