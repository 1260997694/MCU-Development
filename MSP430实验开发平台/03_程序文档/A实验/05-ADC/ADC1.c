#include "msp430f5438a.h"
#include "ADC.h"

void Init_ADC(void)
{  
  __disable_interrupt();
  ADC12CTL0=ADC12ON+ADC12SHT02+ADC12REFON+ADC12REF2_5V; // ��ADC12, sample-and-hold time 64cycle.����ʱ��ԴΪ�ڲ����������ο�ԴΪ�ڲ�2.5V
  ADC12CTL1=ADC12SHP+ADC12CSTARTADD3+ADC12CSTARTADD1; // ���ڲ�����ʱ��
  ADC12CTL2=ADC12RES1;//ADC12RES=10:12-bit (13 clock cycle conversion time)
  ADC12MCTL0=ADC12SREF_1+ ADC12INCH_10; // Vr+=Vref+ and Vr-=AVss,input channel:Temperature diode
  ADC12_EN;//ADCʹ��
  ADC12IE|=ADC12IE10;//ʹ���ж�
}

