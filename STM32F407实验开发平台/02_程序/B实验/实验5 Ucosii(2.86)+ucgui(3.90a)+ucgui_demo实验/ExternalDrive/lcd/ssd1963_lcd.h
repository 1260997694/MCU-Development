

#ifndef __LCD_H__
#define __LCD_H__	1
//#include "main.h"
#include "stm32f4xx.h"


#define  HDP  479  //Horizontal Display Period
#define  HT   531  //Horizontal Total
#define  HPS  43   //LLINE Pulse Start Position
#define  LPS  8    //	Horizontal Display Period Start Position
#define  HPW  10   //	LLINE Pulse Width


#define  VDP  271	//Vertical Display Period
#define  VT   288	//Vertical Total
#define  VPS  12	//	LFRAME Pulse Start Position
#define  FPS  4	    //Vertical Display Period Start Positio
#define  VPW  10 	// LFRAME Pulse Width


/***********************************************************************************
������ɫ�궨��
***********************************************************************************/
#define   Black        0x0000                    // ��ɫ�� 0, 0, 0              
#define   Navy         0x000F                    // ����ɫ�� 0, 0, 128          
#define   Dgreen       0x03E0                    // ����ɫ�� 0, 128, 0          
#define   Dcyan        0x03EF                    // ����ɫ�� 0, 128, 128        
#define   Marooon       0x7800                    // ���ɫ��128, 0, 0           
#define   Purple       0x780F                    // ��ɫ�� 128, 0, 128          
#define   Olive        0x7BE0                    // ����̣�128, 128, 0         
#define   Lgray        0xC618                    // �Ұ�ɫ��192, 192, 192        
#define   Dgray        0x7BEF                    // ���ɫ��128, 128, 128        
#define   Blue         0x001F                    // ��ɫ�� 0, 0, 255            
#define   Green        0x07E0                 	 // ��ɫ�� 0, 255, 0             
#define   Cyan         0x07FF                    // ��ɫ�� 0, 255, 255           
#define   Red          0xF800                    // ��ɫ�� 255, 0, 0             
#define   Magenta      0xF81F                    // Ʒ�죺 255, 0, 255          
#define   Yellow       0xFFE0                    // ��ɫ�� 255, 255, 0           
#define   White        0xFFFF                    // ��ɫ�� 255, 255, 255   

#define LCD_RAM    *(__IO uint16_t *) (0x6C000002)    	//��ַ�Ĵ���
#define LCD_REG    *(__IO uint16_t *) (0x6C000000)	 	//ָ��Ĵ���

//��������
void lcd_clear(u16 Color);
void lcd_init(void);
void write_data_Prepare(void);
void LCD_ShowString(u16 x0, u16 y0, u8 *pcStr, u16 PenColor, u16 BackColor);
void LCD_Fill(uint8_t xsta, uint16_t ysta, uint8_t xend, uint16_t yend, uint16_t colour);
void LCD_DrawLine(uint16_t xsta, uint16_t ysta, uint16_t xend, uint16_t yend, uint16_t color);
unsigned short lcd_read_gram(unsigned int x,unsigned int y);
void LCD_DrawPoint(uint16_t xsta, uint16_t ysta, uint16_t color);

#endif
