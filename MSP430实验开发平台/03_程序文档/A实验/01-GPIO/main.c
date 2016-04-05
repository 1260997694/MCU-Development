#include "msp430f5438a.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "GPIO.h"
#include "delay.h"

void Init_CLK(void)
{
  WDTCTL     = WDTPW + WDTHOLD                            ; // �ؿ��Ź�
  P5SEL     |= 0x0C                                       ; // �˿ڹ���ѡ������
  UCSCTL6   &= ~XT2OFF                                    ; // ����ʹ��
  UCSCTL3   |= SELREF_2                                   ; // FLLref = REFO
  UCSCTL4   |= SELA_2                                     ; // ACLK=REFO,SMCLK=DCO,MCLK=DCO
  do
  {
    UCSCTL7 &= ~(XT2OFFG + XT1LFOFFG + XT1HFOFFG + DCOFFG); // ��� XT2,XT1,DCO �����־                                                          
    SFRIFG1 &= ~OFIFG                                     ; 
  }while(SFRIFG1&OFIFG)                                   ; // ������������־
  UCSCTL6   |= XT2DRIVE0 + XT2DRIVE1                      ; // XT2 ����ģʽ 24~32MHz                                            
  UCSCTL4   |= SELS_5 + SELM_5                            ; // SMCLK = MCLK = XT2
}


void main()
{
  Init_CLK();//��ʼ��ϵͳʱ��
  Init_GPIO();//��ʼ��������LED
  while(1)
  {
    //test qin 
   /* while(1)
   {
      LED1_ON;
       LED2_ON;
        LED3_ON;
        LED4_ON;
      delay_s(1);
      LED1_OFF;
      LED2_OFF;
      LED3_OFF;
      LED4_OFF;
      delay_s(1);
    
    }
    */
    
    //test over
    
    
    
    
    
    if(KEY2_IN==0)//��KEY2���²���ɨ�赽ʱ������LED1����ʱ1��Ϩ��LED1
    {
      BUZZER_ON;
      LED1_ON;
      delay_s(1);
      BUZZER_OFF;
      LED1_OFF;
    }
    if(KEY3_IN==0)//��KEY3���²���ɨ�赽ʱ������LED2����ʱ1��Ϩ��LED2
    {
      BUZZER_ON;
      LED2_ON;
      delay_s(1);
      BUZZER_OFF;
      LED2_OFF;
    }
    if(KEY4_IN==0)//��KEY4���²���ɨ�赽ʱ������LED3����ʱ1��Ϩ��LED3
    {
      BUZZER_ON;
      LED3_ON;
      delay_s(1);
      BUZZER_OFF;
      LED3_OFF;
    }
    if(KEY5_IN==0)//��KEY5���²���ɨ�赽ʱ������LED4����ʱ1��Ϩ��LED4
    {
      BUZZER_ON;
      LED4_ON;
      delay_s(1);
      BUZZER_OFF;
      LED4_OFF;
    }
    if(KEY1_IN==0)//��KEY1���²���ɨ�赽ʱ������LED1~LED4����ʱ1��Ϩ��LED1~LED4
    {BUZZER_ON;LED1_ON;LED2_ON;LED3_ON;LED4_ON;delay_s(1);BUZZER_OFF;LED1_OFF;LED2_OFF;LED3_OFF;LED4_OFF;}
  }
}