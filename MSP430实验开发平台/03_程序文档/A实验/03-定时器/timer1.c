#include "msp430f5438a.h"
#include "timer1.h"

unsigned char sign=0;

void Init_Timer0_A5(void)
{
  TA0CTL=TASSEL1+ID1+ID0;//SMCLK=16MHz,IDx=8
  TA0EX0=TAIDEX2;//IDEx=5,��TCLK=SMCK/8/5=400000Hz
  TA0R=0;//���������
  TA0CTL&=~(MC0+MC1);//stop mode
  
}

unsigned char timercount=0;
void Timer0_A5_Start(void)
{
  TA0CTL|=MC1;//Continuous mode��65535/400000=164ms
  while(!(TA0CTL&TAIFG));//�ȴ�164ms��ʱ��������λ�жϱ�־λ
  TA0CTL&=~TAIFG;//���жϱ�־λ
  timercount++;
  if(timercount==30)//4.92S����ʱ
  {
    timercount=0;sign=1;//��λsign
  }
}

void Timer0_A5_Stop(void)
{
  TA0R=0;//���������
  TA0CTL|=TACLR;//Timer_A clear. Setting this bit resets TAR, the TACLK divider, and the count direction.
  TA0CTL&=~(MC0+MC1);//stop mode
}
