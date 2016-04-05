#include "stm32f4xx.h"
#include "ucos_ii.h"
#include "GUI.h"
#include "Panel.h"
#include "Gpio.h"
#include "progbar.h"

/********************************************************************************************
*�������ƣ�void Panel(void)
*
*��ڲ�������
*
*���ڲ�������
*
*����˵����������ʾ��
*******************************************************************************************/
void Panel(void)
{
    int i = 0;
    PROGBAR_Handle ahProgBar;

	GUI_SetBkColor(GUI_BLACK);   //���ñ�����ɫ
	GUI_SetColor(GUI_RED);       //����ǰ����ɫ��������ͻ�ͼ����ɫ
    GUI_Clear();                 //��ָ����ɫ����
    GUI_SetFont(&GUI_Font8x16);
    GUI_DispStringAt("www.openmcu.com",50,10); //��ʾ�ַ�

    ahProgBar = PROGBAR_Create(  60, 180, 100,20,WM_CF_SHOW );    //����һ��������
    PROGBAR_SetBarColor(ahProgBar,0,GUI_GREEN);                   //���ý��������󲿷�ɫֵ
    PROGBAR_SetBarColor(ahProgBar,1,GUI_RED);                     //���ý��������Ҳ���ɫֵ
    PROGBAR_SetTextColor(ahProgBar,0,GUI_BLUE);                   //���ý�����������Ҳ���ɫֵ
    PROGBAR_SetTextColor(ahProgBar,1,GUI_BLACK);                  //���ý�����������Ҳ���ɫֵ

    while(1)
    {
        LED3_ONOFF(Bit_RESET);        //�򿪵�LED3

        for(i = 0; i < 100 ; i++)
        {
            PROGBAR_SetValue(ahProgBar,i);       //���ý�������ֵ
            OSTimeDly(50);
        }

        LED3_ONOFF(Bit_SET);       //�رյ�LED3

        for(i = 100; i >0 ; i--)
        {
            PROGBAR_SetValue(ahProgBar,i);       //���ý�������ֵ
            OSTimeDly(50);
        }

    }
}




