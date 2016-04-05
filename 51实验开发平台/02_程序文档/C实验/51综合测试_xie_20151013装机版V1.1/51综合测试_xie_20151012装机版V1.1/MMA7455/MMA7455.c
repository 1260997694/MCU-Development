#include "MMA7455.h"

//    MMA7455
uchar table4[10]="0123456789";

uchar xposivalue;			//x?y��??��?��????��?g?��
uchar xnegavalue;			//x���䡤??��?��????��?g?��
uchar yposivalue;			//y?y��??��?��????��?g?��
uchar ynegavalue;			//y���䡤??��?��????��?g?��

/**************************************************************************/
/************                  ����ʱ����                    **************/
/**************************************************************************/

void delay5ms()
{ 
	idata int i; 

	i=500;
	while(i--);
	
}


void MMA7455_delay50us(void)
{
		
   int i=500;  
   while(i) 
   { 
     i--; 
   }  
}

//*****************************************************************************************************
//?��I2C������?D�䨨?��???��??����y?Y
//*****************************************************************************************************
void Single_WriteI2C(uchar SlaveAddress, uchar REG_Address,uchar REG_data)
{
    I2C_Start();                  //?e��?D?o?
    I2C_WriteAbyte(SlaveAddress);   //����?��������?��??��+D��D?o?
    I2C_WriteAbyte(REG_Address);    //?��2???��??�¦�??����?
    I2C_WriteAbyte(REG_data);       //?��2???��??�¨�y?Y��?
    I2C_Stop();                   //����?������?1D?o?
}
//*******************************************************************************************************
//�䨮I2C������??����?��???��??����y?Y
//*******************************************************************************************************
uchar Single_ReadI2C(uchar SlaveAddress, uchar REG_Address)
{
	uchar REG_data;
	I2C_Start();                   //?e��?D?o?
	I2C_WriteAbyte(SlaveAddress - 1);    //����?��������?��??��+D��D?o?
	I2C_WriteAbyte(REG_Address);     //����?����?���̣�?a��??����?�䨮0?a��?	
	I2C_Start();                   //?e��?D?o?
	I2C_WriteAbyte(SlaveAddress);  //����?��������?��??��+?��D?o?
	REG_data=I2C_ReadAbyte();       //?��3???��??�¨�y?Y
	//I2C_SendACK(1);                //?����?��|��eD?o?
   	S_NoACK();
	I2C_Stop();                    //����?1D?o?
	return REG_data;
}	

//******************************************************************************************************
//3?��??��MMA7455
//******************************************************************************************************
void MMA7455_data_init(void)
{
	xposivalue=50;
	xnegavalue=50;
	yposivalue=50;
	ynegavalue=50;
}

u8 MMA7455_self_test(void)					 //o����y1|?����o?��2a7455��D??��D2?o?
{										 											 //          ��?1???��D2?o?��?1602???��??��?
	uchar j;							 								   //			 ?��No acceleration!"
	char t, status, name;

	MMA7455_delay50us();
  	Single_WriteI2C(MMA7455_IIC_WRITE, 0x16,0x15);
	status = Single_ReadI2C(MMA7455_IIC_READ, 0x09);
	name = Single_ReadI2C(MMA7455_IIC_READ, 0x0f); //whoami
	MMA7455_delay50us();
	t = Single_ReadI2C(MMA7455_IIC_READ, 0x16);

	Single_WriteI2C(MMA7455_IIC_WRITE, 0x10,0x15);
	Single_WriteI2C(MMA7455_IIC_WRITE, 0x12,0x25);	
	Single_WriteI2C(MMA7455_IIC_WRITE, 0x14,0x10);	
	
	if(t!=0x15)
	{
		//printf("No acceleration!");	
		//LCD_ShowString(150, 30, "Not found!");
		return 0;
	}
	else
	{
		//LCD_ShowString(150, 30, "found!");
		//printf("X= 0.00,Y= 0.00, Z= 0.00,t=%c\n",t);
		return 1;
	}
}




////////////////////////////////////////////////////////////////////////////////////////
void MMA7455_sendxyz(void)				
{
	u16 x1,x2,x3,xsign;
	uchar x_data[4], status;
	u16 x,y,z;
	u8 X_Angle[] = {"X:000"}, Y_Angle[] = {"Y:000"}, Z_Angle[] = {"Z:000"}; 

	x =Single_ReadI2C(MMA7455_IIC_READ, 0x06);
	y =Single_ReadI2C(MMA7455_IIC_READ, 0x07);
	z =Single_ReadI2C(MMA7455_IIC_READ, 0x08);

	X_Angle[2]=(x/63)+'0';
	X_Angle[3]=((x*100/63)%100)/10+'0';
	X_Angle[4]=(x*100/63)%10+'0';		
	//printf("X_angle %c%c%c ", X_Angle[2], X_Angle[3], X_Angle[4]);	
	LCD_ShowString(150, 190,X_Angle);		

	Y_Angle[2]=(y/63)+'0';
	Y_Angle[3]=((y*100/63)%100)/10+'0';
	Y_Angle[4]=(y*100/63)%10+'0';		
	//printf("Y_angle %c%c%c ", Y_Angle[2], Y_Angle[3], Y_Angle[4]);
	LCD_ShowString(200, 190,Y_Angle);	
	
	Z_Angle[2] = (z/63)+'0';
	Z_Angle[3] = ((z*100/63)%100)/10+'0';
	Z_Angle[4] =( z*100/63)%10+'0';			
	//printf("Z_angle %c%c%c\n", Z_Angle[2], Z_Angle[2], Z_Angle[2]);
	LCD_ShowString(250, 190,Z_Angle);	
}



void MMA7455_Test(void)
{
	//MMA7455_self_test7455();	
	if(MMA7455_self_test())	
	{					
		MMA7455_sendxyz();
		delay5ms();	
	}
}
