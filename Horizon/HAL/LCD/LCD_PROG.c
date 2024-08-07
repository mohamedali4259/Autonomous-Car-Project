/*
 * LCD_PROG.c
 *
 * Created: 04/17/2024 06:14:27 م
 *  Author: Mohamed Aias
 */ 

#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "DIO_INT.h"
#include "LCD_INT.h"

#define F_CPU 16000000UL
#include <util/delay.h>

void LCD_init()
{
	DIO_setPinDir(LCD_D4, DIO_OUTPUT);
	DIO_setPinDir(LCD_D5, DIO_OUTPUT);
	DIO_setPinDir(LCD_D6, DIO_OUTPUT);
	DIO_setPinDir(LCD_D7, DIO_OUTPUT);
	
	DIO_setPinDir(LCD_RS, DIO_OUTPUT);
	DIO_setPinDir(LCD_RW, DIO_OUTPUT);
	DIO_setPinDir(LCD_E, DIO_OUTPUT);
	
	_delay_ms(30);
	LCD_sendCmd(0b00000010);
	LCD_sendCmd(0b00101000);
	_delay_ms(1);
	LCD_sendCmd(0b00001111);
	_delay_ms(1);
	LCD_sendCmd(0b00000001);
	_delay_ms(2);
	LCD_sendCmd(0b00000110);
}

void LCD_sendData(u8 data)
{
	DIO_setPinValue(LCD_RW, DIO_LOW);
	DIO_setPinValue(LCD_RS,DIO_HIGH);
	
	DIO_setPinValue(LCD_D4, GET_BIT(data,4));
	DIO_setPinValue(LCD_D5, GET_BIT(data,5));
	DIO_setPinValue(LCD_D6, GET_BIT(data,6));
	DIO_setPinValue(LCD_D7, GET_BIT(data,7));
	
	LCD_pulse();
	////////////
	DIO_setPinValue(LCD_D4, GET_BIT(data,0));
	DIO_setPinValue(LCD_D5, GET_BIT(data,1));
	DIO_setPinValue(LCD_D6, GET_BIT(data,2));
	DIO_setPinValue(LCD_D7, GET_BIT(data,3));
	
	LCD_pulse();
	

}

void LCD_sendCmd(u8 cmd)
{
	DIO_setPinValue(LCD_RW, DIO_LOW);
	DIO_setPinValue(LCD_RS,DIO_LOW);
	
	DIO_setPinValue(LCD_D4, GET_BIT(cmd,4));
	DIO_setPinValue(LCD_D5, GET_BIT(cmd,5));
	DIO_setPinValue(LCD_D6, GET_BIT(cmd,6));
	DIO_setPinValue(LCD_D7, GET_BIT(cmd,7));
	
	LCD_pulse();
	////////////
	DIO_setPinValue(LCD_D4, GET_BIT(cmd,0));
	DIO_setPinValue(LCD_D5, GET_BIT(cmd,1));
	DIO_setPinValue(LCD_D6, GET_BIT(cmd,2));
	DIO_setPinValue(LCD_D7, GET_BIT(cmd,3));
	
	LCD_pulse();
}

void LCD_clearDis()
{
	LCD_sendCmd(0b00000001);
}

void LCD_pulse()
{
	DIO_setPinValue(LCD_E, DIO_HIGH);
	_delay_ms(1);
	DIO_setPinValue(LCD_E, DIO_LOW);
}


void LCD_sendStr(u8* str)
{
	u8 i=0;
	while(str[i]!='\0')
	{
		LCD_sendData(str[i]);
		i++;
	}
}

void LCD_sendNum(s32 num)
{
	u8 arr[5];
	s8 counter=0;
	
	if (num==0)
	{
		LCD_sendData('0');
		return;
	}
	
	if (num<0)
	{
		LCD_sendData('-');
	}
	
	while (num>0)
	{
		arr[counter]=((num%10)+48);
		num=num/10;
		counter++;
	}
	
	while (counter>=0)
	{
		LCD_sendData(arr[counter--]);
	}
	
}

void LCD_sendfloatNum(f32 num)
{
	LCD_sendNum((s32)num);
	LCD_sendData('.');
	f32 no = num - (s32)num;
	no = no * 1000;
	LCD_sendNum((s32)no);
}

void LCD_GoTo(u8 x, u8 line)
{
	if (line==0)
	{
		LCD_sendCmd(0b10000000+x);
	}
	else if (line==1)
	{
		LCD_sendCmd(0b11000000+x);
	}
}