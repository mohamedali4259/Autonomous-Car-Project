/*
 * LCD_INT.h
 *
 * Created: 04/17/2024 06:13:39 م
 *  Author: Mohamed Aias
 */ 


#ifndef LCD_INT_H_
#define LCD_INT_H_

#include "STD_TYPES.h"
#include "DIO_INT.h"

//config
#define LCD_D4	DIO_PINA4
#define LCD_D5	DIO_PINA5
#define LCD_D6	DIO_PINA6
#define LCD_D7	DIO_PINA7

#define LCD_E	DIO_PINB3
#define LCD_RS	DIO_PINB1
#define LCD_RW	DIO_PINB2
//////////////////////////////////////

#define LCD_CLEAR_DIS	0b
#define LCD_SHIFT_DIS	0b

void LCD_init();
void LCD_sendData(u8 data);
void LCD_sendCmd(u8 cmd);
void LCD_clearDis();
void LCD_pulse();
void LCD_sendStr(u8* str);
void LCD_sendNum(s32 num);
void LCD_sendfloatNum(f32 num);
void LCD_GoTo(u8 x, u8 line);
void LCD_Car_Data_Display();




#endif /* LCD_INT_H_ */