#include "msp430f5438a.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "RTC.h"
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

/**************������ʵ��RTC��Calendar���ܣ�������ѵ�ķ�ʽ��дRTC�Ĵ���***************/

CALENDAR_n CalendarSET={0x2014,0x07,0x08,0x02,0x18,0x30,0x00};
CALENDAR_n CalendarGET[2];

void main()
{
  //__disable_interrupt();
  Init_CLK();//��ʼ��ϵͳʱ��
  Init_RTC_Calendar();
  //__enable_interrupt();
  
  CalendarGET[0] = GetTime();
  delay_s(10);
  SET_Time(CalendarSET);
  delay_s(10);
  CalendarGET[1] = GetTime();
  delay_s(1);
}

