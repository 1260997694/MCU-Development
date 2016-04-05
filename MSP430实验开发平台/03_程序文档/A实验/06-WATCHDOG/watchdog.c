#include "msp430f5438a.h"
#include "watchdog.h"

void WatchDog_init(void)
{
  WDTCTL=WDTPW+WDTCNTCL+WDTTMSEL+WDTIS0;//ÿ��дWDTCTL�������WDTPW
                                        //WDTCNTCL��Watchdog timer counter clear.
                                        //WDTTMSEL��Interval timer mode
                                        //WDTIS0~2��Watchdog timer interval select.
  //001=Watchdog clock source /128M,SCLK/128M=16M/128M,��Ӧ128/16=8s
  WDT_INTENABLE;//ʹ��WDT�ж�
}

