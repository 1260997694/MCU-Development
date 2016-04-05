#include "msp430f5438a.h"
#include <string.h>
#include "RS232.h"
#include "delay.h"

//void Init_USB(void)//UART_A2,BAUDRATE=38400 (16M/UCSRX=416/UCBRSX=6/UCBRFX=0)(UCOS16 = 0)
void Init_USB(void)  //UART_A2,BAUDRATE=9600 (32768/UCSRX=3/UCBRSX=3/UCBRFX=0)
{ 
  P9SEL |= BIT4+BIT5; // ѡ�����Ź���:P9.4=UCA2TXD,P9.5=UCA2RXD
  UCA2CTL1 = UCSWRST; // ״̬����λ
  //UCA2CTL0 = ;//LSB,8BIT,one stop bit,UART mode,Asynchronous mode
  UCA2CTL1 |= UCSSEL_0+UCSSEL_1; //UCSSEL=10: CLK = SMCLK = 16MHz
  //��֣�Ϊ�θı䲻��ʱ��Դ��������������������������������������������������������������������������
  
  UCA2BR0 = 0xa0; 
  UCA2BR1 = 0x01;
  UCA2MCTL = UCBRS_6 + UCBRF_0; // UCBRSx=6, UCBRFx=0
  UCA2IFG = 0;
  UCA2CTL1 &= ~UCSWRST; // ����״̬��
  UCA2IE = UCRXIE; // ��������ж�
}

//void Init_RS232_1(void)//UART_A3,BAUDRATE=9600 (16M/UCSRX=1666/UCBRSX=6/UCBRFX=0)(UCOS16 = 0)
void Init_RS232_1(void)  //UART_A3,BAUDRATE=9600 (32768/UCSRX=3/UCBRSX=3/UCBRFX=0)
{ 
  P10SEL |= BIT4+BIT5; // ѡ�����Ź���:P10.4=UCA3TXD,P10.5=UCA3RXD
  UCA3CTL1 = UCSWRST; // ״̬����λ
  UCA3CTL0 = UCPEN+UCPAR;//Even parity,LSB,8BIT,One stop bit,UART mode,Asynchronous mode
  
  UCA3CTL1 |= UCSSEL_0+UCSSEL_1; //UCSSEL=10: CLK = SMCLK = 16MHz
  //��֣�Ϊ�θı䲻��ʱ��Դ��������������������������������������������������������������������������
  
  UCA3BR0 = 3; 
  UCA3BR1 = 0; 
  UCA3MCTL = UCBRS_3 + UCBRF_0; // UCBRSx=3, UCBRFx=0
  UCA3CTL1 &= ~UCSWRST; // ����״̬��
  UCA3IE |= UCRXIE; // ��������ж�
}

//void Init_RS232_2(void)//UART_A1,BAUDRATE=19200 (16M/UCSRX=833/UCBRSX=2/UCBRFX=0)(UCOS16 = 0)
void Init_RS232_2(void)  //UART_A1,BAUDRATE=9600 (32768/UCSRX=3/UCBRSX=3/UCBRFX=0)
{ 
  P5SEL |= BIT6+BIT7; // ѡ�����Ź���:P5.6=UCA1TXD,P5.7=UCA1RXD
  UCA1CTL1 = UCSWRST; // ״̬����λ
  UCA1CTL0 = UCPEN+UCPAR;//Even parity,LSB,8BIT,One stop bit,UART mode,Asynchronous mode

  UCA1CTL1 |= UCSSEL_0+UCSSEL_1; //UCSSEL=10: CLK = SMCLK = 16MHz
  //��֣�Ϊ�θı䲻��ʱ��Դ��������������������������������������������������������������������������
  
  UCA1BR0 = 3; 
  UCA1BR1 = 0; 
  UCA1MCTL = UCBRS_3 + UCBRF_0; // UCBRSx=3, UCBRFx=0
  UCA1CTL1 &= ~UCSWRST; // ����״̬��
  UCA1IE |= UCRXIE; // ��������ж�
}

void USB_TX(char *tx_buf)
{
  unsigned char i,length;
  length = strlen(tx_buf);
  for(i=0;i<length;i++)
  {
    while (!(UCA2IFG&UCTXIFG));
    UCA2TXBUF = *tx_buf++; 
  }
}

void RS232_1_TX(char *tx_buf)
{
  unsigned char i,length;
  length = strlen(tx_buf);
  for(i=0;i<length;i++)
  {
    while (!(UCA3IFG&UCTXIFG)); 
    UCA3TXBUF = *tx_buf++; 
  }
}

void RS232_2_TX(char *tx_buf)
{
  unsigned char i,length;
  length = strlen(tx_buf);
  for(i=0;i<length;i++)
  {
    while (!(UCA1IFG&UCTXIFG)); 
    UCA1TXBUF = *tx_buf++; 
  }
}


