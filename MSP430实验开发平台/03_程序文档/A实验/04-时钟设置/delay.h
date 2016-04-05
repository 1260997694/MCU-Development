#ifndef _DELAY_H
#define _DELAY_H

#include <intrinsics.h>
#define  INTERNAL_HF_OSC
//#define  EXTERNAL_HF_OSC
#define  FLL_FACTOR     610   // FLL_FACTOR: DCO��Ƶϵ��    

#ifdef EXTERNAL_HF_OSC
  #define   XTAL   16   //�ɶ���Ϊ���õľ���Ƶ�ʣ���λMhz��
  #define   delay(x)      __delay_cycles ( (unsigned long )x )
  #define   delay_us(x)   __delay_cycles ( (unsigned long )x * XTAL) 
  #define   delay_ms(x)   __delay_cycles ( (unsigned long )x * XTAL*1000) 
  #define   delay_s(x)    __delay_cycles ( (unsigned long )x * XTAL*1000000)
#endif

#ifdef INTERNAL_HF_OSC
  #define   XTAL   20  
  #define   delay(x)      __delay_cycles ( (unsigned long )x )
  #define   delay_us(x)   __delay_cycles ( (unsigned long )x * XTAL) 
  #define   delay_ms(x)   __delay_cycles ( (unsigned long )x * XTAL*1000) 
  #define   delay_s(x)    __delay_cycles ( (unsigned long )x * XTAL*1000000)
#endif

typedef unsigned char uchar;
typedef unsigned int uint;
typedef unsigned long ulong;

#endif