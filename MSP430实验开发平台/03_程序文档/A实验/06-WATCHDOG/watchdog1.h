#ifndef _WATCHDOG1_H
#define _WATCHDOG1_H

#define WDT_STOP  do{WDTCTL = WDTPW+WDTHOLD;}while(0)
#define WDT_CLEAR  do{WDTCTL|= WDTPW+WDTCNTCL;}while(0)
#define WDT_INTENABLE  do{SFRIE1|=WDTIE;}while(0) // ʹ��WDT�ж�
#define WDT_INTDISABLE  do{SFRIE1&=~WDTIE;}while(0) // ����WDT�ж�

extern void WatchDog_init1(void);

#endif