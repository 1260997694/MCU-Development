#include "msp430f5438a.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "watchdog1.h"
#include "delay1.h"

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

/**************������ʵ��Watchdog Timer��Interval Timer Mode����***************/

void main()
{
  Init_CLK();//��ʼ��ϵͳʱ��
  P1DIR|=0xC0;//LED4��LED3
  P1OUT|=0xC0;
  WatchDog_init1();
  unsigned char i=0;
  while(1)
  {   
      P1OUT&=~BIT6;//����LED3
      for(i=0;i<5;i++)
      {
          delay_ms(500);
          WDT_CLEAR;//ι��
          P1OUT&=~BIT7;//����LED4
          delay_ms(500);
          WDT_CLEAR;//ι��
          P1OUT|=BIT7;//Ϩ��LED4
      }
      delay_ms(520);
      P1OUT&=~BIT7;//����LED4
  }
}

