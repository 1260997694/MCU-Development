#ifndef _DDPLAY_H
#define _DDPLAY_H

//��������ʹ��
#define KEY1_PULLUP do{P6REN|=BIT3;}while(0)
#define KEY1_OUT_H do{P6OUT|=BIT3;}while(0)
#define KEY1_IN     (P6IN&BIT3)
#define KEY1_INPUT do{P6DIR&=~BIT3;}while(0)
#define IS_KEY1_DOWN ((P6IN&BIT3)==0)

#define KEY2_PULLUP do{P6REN|=BIT5;}while(0)
#define KEY2_OUT_H do{P6OUT|=BIT5;}while(0)
#define KEY2_IN (P6IN&BIT5)
#define KEY2_INPUT do{P6DIR&=~BIT5;}while(0)
#define IS_KEY2_DOWN ((P6IN&BIT5)==0)

#define KEY3_PULLUP do{P6REN|=BIT6;}while(0)
#define KEY3_OUT_H do{P6OUT|=BIT6;}while(0)
#define KEY3_IN (P6IN&BIT6)
#define KEY3_INPUT do{P6DIR&=~BIT6;}while(0)
#define IS_KEY3_DOWN ((P6IN&BIT6)==0)

#define KEY4_PULLUP do{P6REN|=BIT7;}while(0)
#define KEY4_OUT_H do{P6OUT|=BIT7;}while(0)
#define KEY4_IN (P6IN&BIT7)
#define KEY4_INPUT do{P6DIR&=~BIT7;}while(0)
#define IS_KEY4_DOWN ((P6IN&BIT7)==0)

#define KEY5_PULLUP do{P7REN|=BIT7;}while(0)
#define KEY5_OUT_H do{P7OUT|=BIT7;}while(0)
#define KEY5_IN (P7IN&BIT7)
#define KEY5_INPUT do{P7DIR&=~BIT7;}while(0)
#define IS_KEY5_DOWN ((P7IN&BIT7)==0)

#define LED1_DIROUT do{P1DIR|=BIT4;}while(0)
#define LED2_DIROUT do{P1DIR|=BIT5;}while(0)
#define LED3_DIROUT do{P1DIR|=BIT6;}while(0)
#define LED4_DIROUT do{P1DIR|=BIT7;}while(0)

#define LED1_ON do{P1OUT&=~BIT4;}while(0)
#define LED1_OFF do{P1OUT|=BIT4;}while(0)
#define LED2_ON do{P1OUT&=~BIT5;}while(0)
#define LED2_OFF do{P1OUT|=BIT5;}while(0)
#define LED3_ON do{P1OUT&=~BIT6;}while(0)
#define LED3_OFF do{P1OUT|=BIT6;}while(0)
#define LED4_ON do{P1OUT&=~BIT7;}while(0)
#define LED4_OFF do{P1OUT|=BIT7;}while(0)

#define BUZZER_DIROUT do{P11DIR|=BIT2;}while(0)
#define BUZZER_ON do{P11OUT|=BIT2;}while(0)
#define BUZZER_OFF do{P11OUT&=~BIT2;}while(0)

extern void Init_GPIO(void);

void init_keypad();

#endif