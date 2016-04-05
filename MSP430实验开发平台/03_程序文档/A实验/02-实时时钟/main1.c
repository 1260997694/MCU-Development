#include "msp430f5438a.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
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

/**************������ʵ��RTC��Calendar���ܣ������жϵķ�ʽ��дRTC�Ĵ���***************/

CALENDAR_n CalendarSET={0x2014,0x07,0x08,0x02,0x18,0x30,0x00};
CALENDAR_n CalendarGET;

bool SETCalendar_sign = false;
bool GETCalendar_sign = false;
bool SETAlarm_sign = false;

void main()
{
  __disable_interrupt();
  Init_CLK();//��ʼ��ϵͳʱ��
  Init_RTC_Calendar();
  __enable_interrupt();
  
  SETCalendar_sign = true;
  SETAlarm_sign = true;
  
  while(1)
  {
    delay_s(10);
    GETCalendar_sign = true;
  }
}



#pragma vector=RTC_VECTOR
__interrupt void RTC_ISR(void)
{
  if(RTCIV&RTC_RTCRDYIFG)
  {
    if(SETCalendar_sign){SET_Time(CalendarSET);SETCalendar_sign = false;}
    if(GETCalendar_sign){CalendarGET=GetTime();GETCalendar_sign = false;}
    if(SETAlarm_sign){SET_Alarmtime(0,0,0x08,0x30);SETAlarm_sign = false;}
  }
  RTCCTL01  &=~(RTCRDYIFG + RTCTEVIFG);
}