/*
 * TIMER_PROG.c
 *
 * Created: 05/01/2024 07:55:19 م
 *  Author: Mohamed Aias
 */ 

#include "BIT_MATH.h"
#include "STD_TYPES.h"
#include "TIMER0_INT.h"

void TIMER0_initNormal()
{
	//select normal mode
	CLEAR_BIT(TCCR0,WGM00);
	CLEAR_BIT(TCCR0,WGM01);
	
	//enable
	SET_BIT(TIMSK,TOIE0);
}

void TIMER0_start(u8 prescaler)
{
	if(prescaler == TIMER0_DIV0)
	{
		SET_BIT(TCCR0,CS00);
		CLEAR_BIT(TCCR0,CS01);
		CLEAR_BIT(TCCR0,CS02);
	}
	else if(prescaler == TIMER0_DIV8)
	{
		CLEAR_BIT(TCCR0,CS00);
		SET_BIT(TCCR0,CS01);
		CLEAR_BIT(TCCR0,CS02);
	}
	else if(prescaler == TIMER0_DIV64)
	{
		SET_BIT(TCCR0,CS00);
		SET_BIT(TCCR0,CS01);
		CLEAR_BIT(TCCR0,CS02);
	}
	else if(prescaler == TIMER0_DIV256)
	{
		CLEAR_BIT(TCCR0,CS00);
		CLEAR_BIT(TCCR0,CS01);
		SET_BIT(TCCR0,CS02);
	}
	else if(prescaler == TIMER0_DIV1024)
	{
		SET_BIT(TCCR0,CS00);
		CLEAR_BIT(TCCR0,CS01);
		SET_BIT(TCCR0,CS02);
	}
	
	else if(prescaler == TIMER0_EXT_RISING)
	{
		SET_BIT(TCCR0,CS00);
		SET_BIT(TCCR0,CS01);
		SET_BIT(TCCR0,CS02);
	}
	
}

void TIMER0_stop(u8 prescaler)
{
	CLEAR_BIT(TCCR0,CS00);
	CLEAR_BIT(TCCR0,CS01);
	CLEAR_BIT(TCCR0,CS02);
}

void TIMER0_setPreload(u8 value)
{
	TCNT0 = value;
}

u8 TIMER0_getCounts()
{
	return TCNT0;
}

void (*TIMER0_ovFunc)();

void TIMER0_setCallbackOv(void (*func)())
{
	TIMER0_ovFunc = func;
}

//num(in vector table)-1
void __vector_11() __attribute__((signal));
void __vector_11()
{
	TIMER0_ovFunc();
}