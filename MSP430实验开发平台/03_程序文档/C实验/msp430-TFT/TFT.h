#ifndef _TFT_H
#define _TFT_H

#include "delay.h"

//����LCD�ĳߴ�
#define LCD_W 480
#define LCD_H 272

//������ɫ
#define WHITE  0xFFFF
#define BLACK  0x0000	  
#define BLUE   0x001F  
#define BRED   0XF81F
#define GRED   0XFFE0
#define GBLUE  0X07FF
#define RED    0xF800
#define MAGENTA   0xF81F
#define GREEN  0x07E0
#define CYAN   0x7FFF
#define YELLOW    0xFFE0
#define BROWN  0XBC40 //��ɫ
#define BRRED  0XFC07 //�غ�ɫ
#define GRAY   0X8430 //��ɫ

//GUI��ɫ��ǰ������ɫΪPANEL����ɫ��
#define DARKBLUE   0X01CF //����ɫ
#define LIGHTBLUE  0X7D7C //ǳ��ɫ
#define GRAYBLUE   0X5458 //����ɫ
#define LIGHTGREEN  0X841F //ǳ��ɫ
#define LGRAY 	    0XC618 //ǳ��ɫ(PANNEL),���屳��ɫ
#define LGRAYBLUE   0XA651 //ǳ����ɫ(�м����ɫ)
#define LBBLUE      0X2B12 //ǳ����ɫ(ѡ����Ŀ�ķ�ɫ)

//16λ����ģʽ�����ʹ��8λ����ģʽ����ע�͵������
#define Bus_16

//IO������
#define RD_LCD_DataPortH  P4IN//����8λ���ݿڣ�8λģʽ��ֻʹ�ø�8λ
#define WT_LCD_DataPortH  P4OUT//д��8λ���ݿڣ�8λģʽ��ֻʹ�ø�8λ

#define RD_LCD_DataPortL  P2IN//����8λ���ݿڣ�8λģʽ�µ�8λ���Բ����ߣ���ȷ�ϵ�8λ�Ѿ�����10K����
#define WT_LCD_DataPortL  P2OUT//д��8λ���ݿڣ�8λģʽ�µ�8λ���Բ����ߣ���ȷ�ϵ�8λ�Ѿ�����10K����

#define SET_LCD_RS  P3OUT|=BIT2//��λ���������л�����
#define CLR_LCD_RS  P3OUT&=~BIT2//��λ���������л�����
#define GET_LCD_RS  P3IN&BIT2//�����������л�����״̬��1Ϊ�ߣ�0Ϊ�ͣ�

#define SET_LCD_WR  P3OUT|=BIT3//��λд��������
#define CLR_LCD_WR  P3OUT&=~BIT3//��λд��������
#define GET_LCD_WR  P3OUT&BIT3//��д��������״̬��1Ϊ�ߣ�0Ϊ�ͣ�

#define SET_LCD_RD  P3OUT|=BIT1//��λ����������
#define CLR_LCD_RD  P3OUT&=~BIT1//��λ����������
#define GET_LCD_RD  P3OUT&BIT1//������������״̬��1Ϊ�ߣ�0Ϊ�ͣ�

#define SET_LCD_CS  P3OUT|=BIT6//��λƬѡ����
#define CLR_LCD_CS  P3OUT&=~BIT6//��λƬѡ����
#define GET_LCD_CS  P3OUT&BIT6//��Ƭѡ����״̬��1Ϊ�ߣ�0Ϊ�ͣ�

#define SET_LCD_REST  P3OUT|=BIT7//��λ��λ����
#define CLR_LCD_REST  P3OUT&=~BIT7//��λ��λ����
#define GET_LCD_REST  P3OUT&BIT7//����λ����״̬��1Ϊ�ߣ�0Ϊ�ͣ�

extern uint BACK_COLOR, POINT_COLOR;   //����ɫ������ɫ

void LCD_Init(void);
void LCD_Clear(uint);
void LCD_Address_set(uint,uint,uint,uint);
void LCD_WR_DATA8(char VH,char VL); //�������ݣ�8λ����
void LCD_WR_DATA(int);
void LCD_WR_REG(int);
void LCD_DrawPoint(uint,uint);//����
void LCD_DrawPoint_big(uint,uint);//��һ�����
uint LCD_ReadPoint(uint,uint); //����
void LCD_Draw_Circle(uint ,uint,uchar);
void LCD_DrawLine(uint, uint, uint, uint);
void LCD_DrawRectangle(uint, uint, uint, uint);		   
void LCD_Fill(uint,uint,uint,uint,uint);
void LCD_ShowChar(uint x,uint y,uchar num,uchar mode);//��ʾһ���ַ�
void LCD_ShowNum(uint x,uint y,ulong num,uchar len);//��ʾ����
void LCD_Show2Num(uint x,uint y,uint num,uchar len);//��ʾ2������
void LCD_ShowString(uint x,uint y,const uchar *p);//��ʾһ���ַ���
void LCD_showhanzi(uint x,uint y,uchar index);

void showimage(void);

#endif