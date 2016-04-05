#include "msp430f5438a.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "timer.h"
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

unsigned char count=0;

/************�ù���ʵ��TIMER�Ķ�ʱ��up mode�Ĺ���**********/

void main()
{
  __disable_interrupt();//����ȫ���ж�
  Init_CLK();//��ʼ��ϵͳʱ��
  P1DIR|=BIT4+BIT5+BIT6+BIT7;//LED1~LED4��ʼ������Ϊ���
  Init_Timer0_A5();//��ʼ��Timer0_A5
  Timer0_A5_Start();//������ʱ������
  __enable_interrupt();//ʹ��ȫ���ж�
  while(1)
  {
     if(sign)//��1S��ʱ���timer���жϳ�����λsign
     {
       sign=0;//����ȴ���һ��1S��ʱ�жϺ���ִ��ʱ����λsign
       count++;
       switch(count)
       {
         case 1:{P1OUT&=~BIT4;break;}//����LED1
         case 2:{P1OUT&=~BIT5;break;}//����LED2
         case 3:{P1OUT&=~BIT6;break;}//����LED3
         case 4:{P1OUT&=~BIT7;break;}//����LED4
         case 5:{P1OUT|=BIT4;break;}//Ϩ��LED1
         case 6:{P1OUT|=BIT5;break;}//Ϩ��LED2
         case 7:{P1OUT|=BIT6;break;}//Ϩ��LED3
         case 8:{P1OUT|=BIT7;count=0;break;}//Ϩ��LED4��ͬʱ����count�������Ϳ���ѭ������Ϩ��LED����
         default:break;
       }
     }
  }
}