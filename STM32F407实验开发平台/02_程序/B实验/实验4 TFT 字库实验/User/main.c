/****************************************Copyright (c)***************************************
/**-------------------------------------------------------------------------------------------
** Created by:          qinyx
** Last modified Date:  2014-02-28
** Last Version:        V1.00
** Descriptions:        STM32F407Ƕ��ʽʵ����
**-------------------------------------------------------------------------------------------*/
//********************************************************************************************/
#include "stm32f4xx.h"
#include "SysTick.h"
#include "lcd.h"
//#include "sddriver.h"
//#include "ff.h"
//#include "w25q16.h"
//#include "tm1638.h"
#include "delay.h"



void GPIO_Configuration(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;        //����GPIO��ʼ���ṹ��
  RCC_APB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);  //����GPIOBʱ��
  //RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO , ENABLE);  //ʹ��GPIOa����ģ��ʱ��ʹ�� ,PA6���Ÿ���ΪPWMģ��
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4|GPIO_Pin_8|GPIO_Pin_9;; //����PB13 PB14�ֱ�ΪTM1638 STB CLK���ţ����ó��������
	    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_Init(GPIOB, &GPIO_InitStructure);
	
}



int main(void)
{
  		u8 i,j;  
	SysTick_Init();
    lcd_init();
	/*--------��ʾ���� ���ֿ�----------*/
  lcd_clear(Black);
	LCD_DrawRectangle(0,0, 479, 271, Green);
	LCD_DrawRectangle(5,5, 474, 266, Green);
  LCD_ShowString(150,30, "**  STM32F407ʵ�鿪��ƽ̨ **", Red, Black);
	LCD_ShowString(60,60, " ʵ��1�����ڲ���ʵ�� ", White, Black);		
	LCD_ShowString(60, 90, "��ʵ���Ǵ��ڲ���ʵ��", White, Black);	
  LCD_ShowString(60, 120, "1����������", White, Black);	
	LCD_ShowString(60, 150, "2����������", White, Black);	
	LCD_ShowString(30, 180, "ʵ���������ڴ��ڵ�������п���������Ϣ\"hh\"", White, Black);	
	///////////////////////////////////////////////
	while(1);
}

