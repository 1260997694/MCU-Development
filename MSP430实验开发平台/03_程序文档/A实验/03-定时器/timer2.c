#include "msp430f5438a.h"
#include "timer2.h"

void Init_Timer0_A5(void)
{
  TA0CTL&=~(MC0+MC1);//stop mode
  TA0CTL=TASSEL1+ID1+ID0;//SMCLK=16MHz,IDx=8
  TA0EX0=TAIDEX2;//IDEx=5,��TCLK=SMCK/8/5=400000Hz
  TA0CCR0=40000; // 40000/400000=0.1S=100ms���ü��������ʱ��Ϊ100ms
  TA0R=0;//���������
}

void Timer0_A5_Start(void)
{
  TA0CTL|=MC0;//Up mode��40000/400000=100ms
  TA0CCTL0|=CCIE;//Capture/compare interrupt enable
}

void Timer0_A5_Stop(void)
{
  TA0R=0;//���������
  TA0CTL|=TACLR;//Timer_A clear. Setting this bit resets TAR, the TACLK divider, and the count direction.
  TA0CTL&=~(MC0+MC1);//stop mode
}

unsigned char Timercounter=0,sign=0;

#pragma vector=TIMER0_A0_VECTOR                             
__interrupt void Timer0_A0(void)
{
   TA0CCTL0&=~CCIFG;//���жϱ�־λ����ֹ���Ͻ����жϺ���
   Timercounter++;//100ms������жϣ�Timercounter��1
   if(Timercounter==20)//20x100ms=2s
   {
     Timercounter=0;//����Timercounter
     sign=1;//��λȫ�ֱ���sign
   }
}