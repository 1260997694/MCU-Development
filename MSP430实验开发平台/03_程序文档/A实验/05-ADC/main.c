#include "msp430f5438a.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "ADC.h"
#include "delay.h"

void Init_CLK(void)
{
  WDTCTL     = WDTPW + WDTHOLD                            ; // �ؿ��Ź�
  P5SEL     |= 0x0C                                       ; // �˿ڹ���ѡ������
  UCSCTL6   &= ~XT2OFF                                    ; // ����ʹ��
  UCSCTL3   |= SELREF_2                                   ; // FLLref = REFO
  UCSCTL4   |= SELA_2                                     ; // ACLK=REFO,SMCLK=DCO,MCLK=DCO
  //REFOCLK: Internal, trimmed, low frequency oscillator with 32768 Hz typical frequency, with the ability 
  //to be used as a clock reference into the FLL.
  do
  {
    UCSCTL7 &= ~(XT2OFFG + XT1LFOFFG + XT1HFOFFG + DCOFFG); // ��� XT2,XT1,DCO �����־                                                          
    SFRIFG1 &= ~OFIFG                                     ; 
  }while(SFRIFG1&OFIFG)                                   ; // ������������־
  UCSCTL6   |= XT2DRIVE0 + XT2DRIVE1                      ; // XT2 ����ģʽ 24~32MHz                                            
  UCSCTL4   |= SELS_5 + SELM_5                            ; // SMCLK = MCLK = XT2
}

/**************������ʵ��ADC single-conversion�ɼ�Temperature diode��ѹֵ�Ĺ���***************/

unsigned int ADC_value=0;
void main()
{
  //__disable_interrupt();
  Init_CLK();//��ʼ��ϵͳʱ��
  Init_ADC();
  P1DIR|=BIT7;
  P1OUT|=BIT7;
  //__enable_interrupt();
  while(1)
  {
    ADC12_START;
    while (!(ADC12IFG & BITA));
    P1OUT&=~BIT7;
    ADC_value=ADC12MEM10; 
    delay_ms(500);
    P1OUT|=BIT7;
    delay_ms(500);
  }
}

