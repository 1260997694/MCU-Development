#include "msp430f5438a.h"
#include "GPIO.h"

void Init_GPIO(void)
{
  KEY1_PULLUP;//����ʹ��
  KEY2_PULLUP;
  KEY3_PULLUP;
  KEY4_PULLUP;
  KEY5_PULLUP;
  
  KEY1_OUT_H;//����ߣ�ʹ��KEY1~KEY5������������ʹ��
  KEY2_OUT_H;
  KEY3_OUT_H;
  KEY4_OUT_H;
  KEY5_OUT_H;
  
  LED1_DIROUT;//LED1~LED4����Ϊ���
  LED2_DIROUT;
  LED3_DIROUT;
  LED4_DIROUT;
  LED1_OFF;//��ʼ��LED1~LED4Ϩ��
  LED2_OFF;
  LED3_OFF;
  LED4_OFF;
  
  BUZZER_DIROUT;//��ʼ��BUZZERλ���
}