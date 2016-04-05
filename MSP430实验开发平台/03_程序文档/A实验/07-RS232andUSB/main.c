#include "msp430f5438a.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "RS232.h"
#include "delay.h"

void Init_CLK(void)
{
  WDTCTL     = WDTPW + WDTHOLD                            ; // �ؿ��Ź�
  P5SEL     |= 0x0C                                       ; // �˿ڹ���ѡ������
  UCSCTL6   &= ~XT2OFF                                    ; // ����ʹ��
  UCSCTL3   |= SELREF_2                                   ; // FLLref = REFO
  UCSCTL4   |= SELA__REFOCLK                                     ; // ACLK=REFO,SMCLK=DCO,MCLK=DCO
  do
  {
    UCSCTL7 &= ~(XT2OFFG + XT1LFOFFG + XT1HFOFFG + DCOFFG); // ��� XT2,XT1,DCO �����־                                                          
    SFRIFG1 &= ~OFIFG                                     ; 
  }while(SFRIFG1&OFIFG)                                   ; // ������������־
  UCSCTL6   |= XT2DRIVE0 + XT2DRIVE1                      ; // XT2 ����ģʽ 24~32MHz     
  UCSCTL4  = UCSCTL4-SELA__REFOCLK                     ;
  UCSCTL4   |= SELS_5 + SELM_5  + SELA__XT2CLK         ; // ACLK = SMCLK = MCLK = XT2
}

/**************������ʵ��Watchdog Timer��Interval Timer Mode����***************/

unsigned char RS1_RX;
unsigned char RS2_RX;
unsigned char USB_RX;

void main()
{
  __disable_interrupt();
  Init_CLK();//��ʼ��ϵͳʱ��
  P1DIR|=0xe0;//LED1~LED3
  P1OUT|=0xe0;//LED1~LED3Ϩ��
  Init_USB();
  Init_RS232_1();
  Init_RS232_2();
  
  RS232_1_TX("this is RS232_1");
  RS2_RX=0;RS232_2_TX("this is RS232_2");
  USB_TX("this is USB");
  
  __enable_interrupt();
  while(1)
  {
    if(RS1_RX=='1'){RS1_RX=0;RS232_1_TX("this is RS232_1");}
    if(RS2_RX=='2'){RS2_RX=0;RS232_2_TX("this is RS232_2");}
    if(USB_RX=='u'){USB_RX=0;USB_TX("this is USB");}
  }
}

#pragma vector=USCI_A1_VECTOR    //RS232_2
__interrupt void USCI_A1_ISR(void)
{
  switch(UCA1IV)
  {
    case 0:break;               // Vector 0 - no interrupt
    case 2:                     // Vector 2 - RXIFG
      {
         RS2_RX=UCA1RXBUF;
         if(RS2_RX=='2')
           P1OUT&=~BIT7;
         else
           P1OUT|=BIT7;
         break;
      }
    case 4:break;               // Vector 4 - TXIFG
    default: break;  
  }
}

#pragma vector=USCI_A2_VECTOR    //USB
__interrupt void USCI_A2_ISR(void)
{
  switch(UCA2IV)
  {
    case 0:break;               // Vector 0 - no interrupt
    case 2:                     // Vector 2 - RXIFG
      {
         USB_RX=UCA2RXBUF;
         if(USB_RX=='u')
           P1OUT&=~BIT6;
         else
           P1OUT|=BIT6;
         break;
      }
    case 4:break;               // Vector 4 - TXIFG
    default: break;  
  }
}

#pragma vector=USCI_A3_VECTOR    //RS232_1
__interrupt void USCI_A3_ISR(void)
{
  switch(UCA3IV)
  {
    case 0:break;               // Vector 0 - no interrupt
    case 2:                     // Vector 2 - RXIFG
      {
         RS1_RX=UCA3RXBUF;
         if(RS1_RX=='1')
           P1OUT&=~BIT5;
         else
           P1OUT|=BIT5;
         break;
      }
    case 4:break;               // Vector 4 - TXIFG
    default: break;  
  }
}