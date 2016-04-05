#include "sys.h"
#include "usart.h"	
#include "lcd.h"

char Date_Buf[10];
char BufferA[50];
uint8_t DBufferFlag=0;
uint8_t mark = 0;
	static unsigned char BufferCount=0;
//////////////////////////////////////////////////////////////////
//�������´���,֧��printf����,������Ҫѡ��use MicroLIB	  
#if 1
#pragma import(__use_no_semihosting)    

void _ttywrch(int ch)  			//Ϊ��ʹ��malloc  xie 20150718
{ 
    while((USART1->SR&0X40)==0);//ѵ�����ͣ�ֱ���������  
    USART1->DR = (u8) ch;  
}

//��׼����Ҫ��֧�ֺ���                 
struct __FILE 
{ 
	int handle; 

}; 

FILE __stdout;       
//����_sys_exit()�Ա���ʹ�ð�����ģʽ    
_sys_exit(int x) 
{ 
	x = x; 
} 
//�ض���fputc���� 
int fputc(int ch, FILE *f)
{      
	while((USART1->SR&0X40)==0);//ѭ������,ֱ���������   
    USART1->DR = (u8) ch;      
	return ch;
}
#endif 

/*ʹ��microLib�ķ���*/
 /* 
int fputc(int ch, FILE *f)
{
	USART_SendData(USART1, (uint8_t) ch);

	while (USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET) {}	
   
    return ch;
}
int GetKey (void)  { 

    while (!(USART1->SR & USART_FLAG_RXNE));

    return ((int)(USART1->DR & 0x1FF));
}
*/
 
//����1�жϷ������
//ע��,��ȡUSARTx->SR�ܱ���Ī������Ĵ���   	
u8 USART_RX_BUF[USART_REC_LEN];     //���ջ���,���USART_REC_LEN���ֽ�.
//����״̬
//bit15��	������ɱ�־
//bit14��	���յ�0x0d
//bit13~0��	���յ�����Ч�ֽ���Ŀ
u16 USART_RX_STA=0;       //����״̬���	  

//��ʼ��IO ����1 
//bound:������
void Uart1_init(u32 bound){
    //GPIO�˿�����
    GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	 
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1|RCC_APB2Periph_GPIOA, ENABLE);	//ʹ��USART1��GPIOAʱ��
 	USART_DeInit(USART1);  //��λ����1
	 //USART1_TX   PA.9
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9; //PA.9
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;	//�����������
    GPIO_Init(GPIOA, &GPIO_InitStructure); //��ʼ��PA9
   
    //USART1_RX	  PA.10
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;//��������
    GPIO_Init(GPIOA, &GPIO_InitStructure);  //��ʼ��PA10
  
   //USART ��ʼ������

	USART_InitStructure.USART_BaudRate = bound;//һ������Ϊ9600;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;//�ֳ�Ϊ8λ���ݸ�ʽ
	USART_InitStructure.USART_StopBits = USART_StopBits_1;//һ��ֹͣλ
	USART_InitStructure.USART_Parity = USART_Parity_No;//����żУ��λ
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//��Ӳ������������
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	//�շ�ģʽ

    USART_Init(USART1, &USART_InitStructure); //��ʼ������
    USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);//�����ж�
    USART_Cmd(USART1, ENABLE);                    //ʹ�ܴ��� 

}


static u32 startadd = 0;
void USART1_IRQHandler(void)                	//����1�жϷ������
	{
	u8 Res;

	if(USART_GetITStatus(USART1, USART_IT_RXNE) != RESET)  //�����ж�(���յ������ݱ�����0x0d 0x0a��β)
		{
			Res =USART_ReceiveData(USART1);//(USART1->DR);	//��ȡ���յ�������
			if(Res == ',')
				Res = 0;
			else
			{
				SPI_FLASH_Write_Enable();                  //SET WEL 
				SPI_FLASH_PageWrite(&Res, startadd++, 1);
			}
/*		if((USART_RX_STA&0x8000)==0)//����δ���
			{
			if(USART_RX_STA&0x4000)//���յ���0x0d
				{
				if(Res!=0x0a)USART_RX_STA=0;//���մ���,���¿�ʼ
				else USART_RX_STA|=0x8000;	//��������� 
				}
			else //��û�յ�0X0D
				{	
				if(Res==0x0d)USART_RX_STA|=0x4000;
				else
					{
					USART_RX_BUF[USART_RX_STA&0X3FFF]=Res ;
					USART_RX_STA++;
					if(USART_RX_STA>(USART_REC_LEN-1))USART_RX_STA=0;//�������ݴ���,���¿�ʼ����	  
					}		 
				}  	
			}  
*/				 
     } 

#ifdef OS_TICKS_PER_SEC	 	//���ʱ�ӽ�����������,˵��Ҫʹ��ucosII��.
	OSIntExit();  											 
#endif
} 

//UART3 -> RFID
void Uart3_init(u32 bound)
{
	USART_InitTypeDef USART_InitStructure;
	GPIO_InitTypeDef GPIO_InitStructure;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);	;
	/* ��������3��ʱ�� */
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3, ENABLE);	//ʹ��USART3��GPIOAʱ��
//USART3_TX PB10
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_10;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
//USART3_RX PB11
	
	GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_11;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;//��������	
	GPIO_Init(GPIOB, &GPIO_InitStructure);

	USART_InitStructure.USART_BaudRate   = 115200; //115200;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	USART_InitStructure.USART_StopBits   = USART_StopBits_1;
	USART_InitStructure.USART_Parity     = USART_Parity_No;
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode                = USART_Mode_Tx | USART_Mode_Rx;

	USART_Init(USART3, &USART_InitStructure);
	USART_ITConfig(USART3, USART_IT_RXNE, ENABLE);
	USART_Cmd(USART3, ENABLE);
}

void USART3_IRQHandler(void)    //RFID     
{
	uint8_t ch;
	if(USART_GetFlagStatus(USART3,USART_FLAG_RXNE))
	{
		ch = USART_ReceiveData(USART3);  //ȡ�����ڵõ�������
	//	USART_SendData(USART3, ch);
		BufferA[BufferCount++]=ch;
		if(BufferCount>48)
		{
      DBufferFlag=1;
			BufferCount=0;
    }
		else
		{
			DBufferFlag=0;
		}
	}
} 

void Uart5_init(u32 bound)
{
GPIO_InitTypeDef GPIO_InitStructure; 
  	USART_InitTypeDef USART_InitStructure;   


   
RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC |RCC_APB2Periph_GPIOD|RCC_APB2Periph_AFIO, ENABLE);  //??UART5??GPIOC???  
  	RCC_APB1PeriphClockCmd(RCC_APB1Periph_UART5, ENABLE);  //????5?? 

  	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12;	         	//USART5 TX 
  	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 
  	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;    	//?????? 
  	GPIO_Init(GPIOC, &GPIO_InitStructure);	    	 //c??  

  	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;	         	 //USART5 RX 
  	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;    //?????? 
  	GPIO_Init(GPIOD, &GPIO_InitStructure);	         	 //D??  
   
  	USART_InitStructure.USART_BaudRate   = bound; 
  	USART_InitStructure.USART_WordLength = USART_WordLength_8b;	//???8? 
  	USART_InitStructure.USART_StopBits   = USART_StopBits_1;	//???1? 
  	USART_InitStructure.USART_Parity     = USART_Parity_No;	//???? 
  	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None; //????? 
  	USART_InitStructure.USART_Mode       = USART_Mode_Rx | USART_Mode_Tx;	//???? 
   
  	/* Configure USART3 */ 
  	USART_Init(UART5, &USART_InitStructure);	//????????  
   
  	/*USART3 receive data register is not empty */ 
  	USART_ITConfig(UART5, USART_IT_RXNE, ENABLE);   
  	/* Enable the USART3 */ 
  	USART_Cmd(UART5, ENABLE);		
	
/*	
		USART_InitTypeDef USART_InitStructure; 
		GPIO_InitTypeDef GPIO_InitStructure;
	
	 RCC_APB1PeriphClockCmd(RCC_APB1Periph_UART5, ENABLE);
   RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC | RCC_APB2Periph_AFIO | RCC_APB2Periph_GPIOD , ENABLE);	
	
   GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12;
   GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
   GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;  
   GPIO_Init(GPIOC, &GPIO_InitStructure);
	
   GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;
   GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
   GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
   GPIO_Init(GPIOD, &GPIO_InitStructure);	
	
		USART_DeInit(UART5);
		USART_InitStructure.USART_BaudRate = bound;
		USART_InitStructure.USART_WordLength = USART_WordLength_8b;
		USART_InitStructure.USART_StopBits = USART_StopBits_1;
		USART_InitStructure.USART_Parity = USART_Parity_No ;
		USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
		USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
		USART_Init(UART5,&USART_InitStructure);
		USART_ITConfig(UART5, USART_IT_RXNE, ENABLE);
    USART_Cmd(UART5, ENABLE);
*/
}

uint8_t gsm_ch[GSM_length] = {0};

void UART5_IRQHandler(void)   	//GSM      
{	
  uint8_t ch;
	//static uint8_t count = 0, temp[5] = {0};
	//uint8_t a[1] = {'A'};
	
	static uint8_t gsm_count = 0;

	if(USART_GetFlagStatus(UART5,USART_FLAG_RXNE))
	{
		ch = USART_ReceiveData(UART5);  //ȡ�����ڵõ�������
		
		USART_SendData(UART4, ch);
		while (USART_GetFlagStatus(UART4, USART_FLAG_TC) == RESET);
		
			gsm_ch[gsm_count] = ch;
			gsm_count ++; 
			
			if(gsm_count  > GSM_length)
				gsm_count = 0;	
		
/*		
		temp[count] = ch;
		if(temp[count] == 0x0D)
		{
			temp[count] = ' ';
			LCD_ShowString(142, 160,a);
			LCD_ShowString(150, 160,temp);
			count = 0;	
		}
		if(temp[count] == 0x0A)
			temp[count] = ' ';
		
			
		count ++;
*/
		}	
} 

void UART5_Send(uint8_t *str,uint32_t num)
{
	while(num!=0)
	{
    UART5->DR = (*str++ & (uint16_t)0x01FF);
		while (USART_GetFlagStatus(UART5, USART_FLAG_TC) == RESET);
		num--;
	}
}

void Uart4_init(u32 bound)
{
   USART_InitTypeDef USART_InitStructure;
   GPIO_InitTypeDef GPIO_InitStructure;
	
	 RCC_APB1PeriphClockCmd(RCC_APB1Periph_UART4, ENABLE);                                                                                
   RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC | RCC_APB2Periph_AFIO, ENABLE);	

   GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
   GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
   GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;  
   GPIO_Init(GPIOC, &GPIO_InitStructure);

   GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;
   GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
   GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
   GPIO_Init(GPIOC, &GPIO_InitStructure);	
	
	USART_DeInit(UART4);                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                              
	USART_InitStructure.USART_BaudRate = bound;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	USART_InitStructure.USART_Parity = USART_Parity_No ;
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
	USART_Init(UART4,&USART_InitStructure);
	USART_ITConfig(UART4, USART_IT_RXNE, ENABLE);
  USART_Cmd(UART4, ENABLE);
}

void UART4_IRQHandler(void)         
{
	uint8_t ch;
	if(USART_GetFlagStatus(UART4, USART_FLAG_RXNE))
	{
		ch = USART_ReceiveData(UART4);  //ȡ�����ڵõ�������
		
		USART_SendData(UART5, ch);
		while (USART_GetFlagStatus(UART5, USART_FLAG_TC) == RESET);		
		
	//	USART_SendData(USART3, ch);
		BufferA[BufferCount++]=ch;
		if(BufferCount>48)
		{
      DBufferFlag=1;
			BufferCount=0;
    }
		else
		{
			DBufferFlag=0;
		}
	}
} 

void UART4_Send(uint8_t *str,uint32_t num)
{
	while(num!=0)
	{
    UART4->DR = (*str++ & (uint16_t)0x01FF);
		while (USART_GetFlagStatus(UART4, USART_FLAG_TC) == RESET);
		num--;
	}
}


void RFID_Test()
{
	unsigned char i;	
	char Rfid_Id[9];
	char Rfid_Value[35];
	
	while(BufferCount<48);
		for(i=0;i<9;i++)
			Rfid_Id[i]=BufferA[i+1];
		LCD_ShowString(50, 180, "RFID_ID:");
		LCD_ShowString(114, 180, Rfid_Id);

		for(i=0;i<35;i++)
			Rfid_Value[i]=BufferA[i+12];
		LCD_ShowString(50, 200, "RFID_Value:");
		LCD_ShowString(138, 200, Rfid_Value);

	for(i=0;i<BufferCount;i++)
					 BufferA[i]=0x00;
			 BufferCount=0;
			 DBufferFlag=0;
}

