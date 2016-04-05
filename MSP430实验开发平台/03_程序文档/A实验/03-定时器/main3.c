#include "msp430f5438a.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "timer2.h"
#include "delay2.h"

void Init_CLK(void)
{
  WDTCTL     = WDTPW + WDTHOLD                            ; // �ؿ��Ź�
  P5SEL     |= 0x0C                                       ; // �˿ڹ���ѡ������
  UCSCTL6   &= ~XT2OFF                                    ; // ����ʹ��
  UCSCTL3   |= SELREF_2                                   ; // FLLref = REFO
  UCSCTL4   |= SELA_2;//Ϊ�θþ�ز����٣�������������������������������������
  do
  {
    UCSCTL7 &= ~(XT2OFFG + XT1LFOFFG + XT1HFOFFG + DCOFFG); // ��� XT2,XT1,DCO �����־                                                          
    SFRIFG1 &= ~OFIFG                                     ; 
  }while(SFRIFG1&OFIFG)                                   ; // ������������־
  UCSCTL6   |= XT2DRIVE0 + XT2DRIVE1                      ; // XT2 ����ģʽ 24~32MHz                                            
  UCSCTL4   |= SELS_5 + SELM_5 + SELA_5                   ; // ACLK = SMCLK = MCLK = XT2
  UCSCTL5   |= DIVS2;                                     ; //SMCLK source divider,fACLK/16=1MHz
}

unsigned char count=0;

/************�ù���ʵ��TIMER��compare Output ��Toggle output mode ����**********/

void main()
{
  Init_CLK();//��ʼ��ϵͳʱ��
  Init_Timer0_A5();//��ʼ��Timer0_A5
  Timer0_A5_Start();//������ʱ���ȽϹ���
  
  while(1)
  {
    __no_operation();
  }
}