/*
 * TIMER2_INT.h
 *
 * Created: 07/20/2024 11:55:09 ص
 *  Author: Mohamed Aias
 */ 


#ifndef TIMER2_INT_H_
#define TIMER2_INT_H_

#include "STD_TYPES.h"

//Timer/Counter Control Register
#define TCCR2 		*((volatile u8*)0x45)
#define FOC2		7
#define WGM20		6
#define COM21		5
#define COM20		4
#define WGM21		3
#define CS22		2
#define CS21		1
#define CS20		0

//Timer/Counter Register
#define TCNT2 		*((volatile u8*)0x44)

//Output Compare Register
#define OCR2 		*((volatile u8*)0x43)

//Timer/Counter Interrupt Mask
#define TIMSK 		*((volatile u8*)0x59)
#define OCIE2		1
#define TOIE2		0

#define TIFR				*((volatile u8*)0x58)
#define OCF2		7

#define TIMER2_DIV0			0
#define TIMER2_DIV8			1
#define TIMER2_DIV32    	2
#define TIMER2_DIV64		3
#define TIMER2_DIV128		4
#define TIMER2_DIV256		5
#define TIMER2_DIV1024		6

void TIMER2_initNormal();
void TIMER2_initCtc();
void TIMER2_start(u8 prescaler);
void TIMER2_stop(u8 prescaler);
void TIMER2_setPreload(u8 value);
void TIMER2_setOcr(u16 value); 
void TIMER2_setCallbackCtc(void (*func)());
u8 TIMER2_getCounts();





#endif /* TIMER2_INT_H_ */