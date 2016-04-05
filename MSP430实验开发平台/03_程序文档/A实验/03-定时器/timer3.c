#include "msp430f5438a.h"
#include "timer2.h"

void Init_Timer0_A5(void)
{
  TA0CTL&=~(MC0+MC1);//stop mode
  TA0CTL=TASSEL1+ID1+ID0;//SMCLK=1MHz,IDx=8
  TA0EX0=TAIDEX2;//IDEx=5,��TCLK=SMCK/8/5=25000Hz
  TA0CCR0=50000; // 50000/25000=2S���ü��������ʱ��Ϊ100ms��������������������
  TA0CCR3=25000; // 1s
  TA0R=0;//���������
  
  P1DIR|=BIT4;//����Ϊ�����IMP������������������������������
  P1SEL|=BIT4;//P1.1ѡ��ڶ����ܣ�TA0.3��IMP������������������������������������
  
}

void Timer0_A5_Start(void)
{
  TA0CTL|=MC0;//Up mode��50000/25000=2s����������������������������
  TA0CCTL3|=OUTMOD2;//Toggle output mode����ģʽ��2S�����ڣ�������������������������
}

void Timer0_A5_Stop(void)
{
  TA0R=0;//���������
  TA0CTL|=TACLR;//Timer_A clear. Setting this bit resets TAR, the TACLK divider, and the count direction.
  TA0CTL&=~(MC0+MC1);//stop mode
}

