#include "msp430f5438a.h"
#include "lowpower.h"

/*************ʹ��ʵʱʱ�ӵ��ж���ʹϵͳ�Գ��͹���******************/

void Init_RTC(void)
{
  RTCCTL01=RTCTEV0+RTCTEVIE;
  //RTC Mode:32-bit counter mode / ACLK=32768Hz
  //RTCTEV=01:16-bit overflow, 65535/32768=2s
  //RTC Time Event Interrupt Enable
}

