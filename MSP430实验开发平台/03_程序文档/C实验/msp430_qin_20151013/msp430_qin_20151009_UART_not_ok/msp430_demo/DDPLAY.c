#include "msp430f5438a.h"
#include "DDPLAY.h"
#include "macro.h"

void init_keypad(){
  KEY1_INPUT;
  KEY1_PULLUP;//����ʹ��
  KEY1_OUT_H;//����ߣ�ʹ��KEY1~KEY5������������ʹ��
}

void Init_GPIO(void)
{
  init_keypad();
  
  LED1_DIROUT;//LED1~LED4����Ϊ���
  LED2_DIROUT;
  LED3_DIROUT;
  LED4_DIROUT;
   
  LED1_ON;//��ʼ��LED1~LED4Ϩ��
  LED2_ON;
  LED3_ON;
  LED4_ON;
  
  BUZZER_DIROUT;//��ʼ��BUZZERλ���
  BUZZER_ON;
  
  delay_ms(500);//delay_s(1);
  LED1_OFF;//��ʼ��LED1~LED4Ϩ��
  LED2_OFF;
  LED3_OFF;
  LED4_OFF;
  
  delay_ms(500);//delay_s(1);
  LED1_ON;//��ʼ��LED1~LED4Ϩ��
  LED2_ON;
  LED3_ON;
  LED4_ON;
  BUZZER_OFF;
}