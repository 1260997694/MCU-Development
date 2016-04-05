#include "msp430f5438a.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "watchdog.h"
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

/**************������ʵ��Watchdog Timer��Interval Timer Mode����***************/

void main()
{
  __disable_interrupt();
  Init_CLK();//��ʼ��ϵͳʱ��
  P1DIR|=0x80;//LED4
  P1OUT|=0x80;
  WatchDog_init();
  __enable_interrupt();
  
  while(1)
  {
      __no_operation();
  }
}

#pragma vector=WDT_VECTOR
__interrupt void watchdog_timer(void)
{
    P1OUT^=0x80;
}