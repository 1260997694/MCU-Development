#include "msp430f5438a.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "SPI.h"
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
unsigned char SD_sendbuffer[512];
unsigned char SD_Receivebuffer[512];

void main()
{
  unsigned int i=0;
  Init_CLK();//��ʼ��ϵͳʱ��
  
  for(;i<512;i++)
  {
    if(i<256)SD_sendbuffer[i]=i;
    else SD_sendbuffer[i]=511-i;
  }
  
  SPI_Init();
  while(SD_Init()==false);
  
  SD_Block_W(SD_sendbuffer,0);
  SD_Block_R(SD_Receivebuffer,0);
  
  while(1)
  {
     __no_operation();
  }
}

