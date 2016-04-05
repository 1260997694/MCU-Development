#include "msp430f5438a.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "sys_clock.h"
#include "delay.h"


//***************************************************************************//
//                                                                           //
//                 ������: ����ʱ�Ӳ������P11.0~2                           //
//                                                                           //
//***************************************************************************//

int main( void )
{
  WDTCTL = WDTPW + WDTHOLD                                ; // �رտ��Ź�
  Init_CLK();                                             ;
  P11DS  = BIT0 + BIT1 + BIT2                            ; // ACK��MCK��SMCK�����P11.0/1/2
  P11SEL = BIT0 + BIT1 + BIT2                            ;
  P11DIR = BIT0 + BIT1 + BIT2                            ;
  P1DIR|=0xf0;
  while(1)  
  {
    P1OUT=0x00;
    delay_s(2);
    P1OUT=0xf0;
    delay_s(2);
  }
}
