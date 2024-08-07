/*
 * TIMER2_PROG.c
 *
 * Created: 07/20/2024 11:55:37 ص
 *  Author: Mohamed Aias
 */ 

#include "BIT_MATH.h"
#include "STD_TYPES.h"
#include "TIMER2_INT.h"

void TIMER2_initNormal()
{
	//select normal mode
	CLEAR_BIT(TCCR2,WGM20);
	CLEAR_BIT(TCCR2,WGM21);
	
	//enable
	SET_BIT(TIMSK,TOIE2);
}

void TIMER2_initCtc()
{
	//select ctc mode
	CLEAR_BIT(TCCR2,WGM20);
	SET_BIT(TCCR2,WGM21);
	
	//enable
	SET_BIT(TIMSK,OCIE2);
	
	// Toggle OC2 on compare match
	SET_BIT(TCCR2,COM20);
	CLEAR_BIT(TCCR2,COM21);

}

void TIMER2_start(u8 prescaler)
{
	if(prescaler == TIMER2_DIV0)
	{
		SET_BIT(TCCR2,CS20);
		CLEAR_BIT(TCCR2,CS21);
		CLEAR_BIT(TCCR2,CS22);
	}
	else if(prescaler == TIMER2_DIV8)
	{
		CLEAR_BIT(TCCR2,CS20);
		SET_BIT(TCCR2,CS21);
		CLEAR_BIT(TCCR2,CS22);
	}
	else if(prescaler == TIMER2_DIV32)
	{
		SET_BIT(TCCR2,CS20);
		SET_BIT(TCCR2,CS21);
		CLEAR_BIT(TCCR2,CS22);
	}
	else if(prescaler == TIMER2_DIV64)
	{
		CLEAR_BIT(TCCR2,CS20);
		CLEAR_BIT(TCCR2,CS21);
		SET_BIT(TCCR2,CS22);
	}
	else if(prescaler == TIMER2_DIV128)
	{
		SET_BIT(TCCR2,CS20);
		CLEAR_BIT(TCCR2,CS21);
		SET_BIT(TCCR2,CS22);
	}
	else if(prescaler == TIMER2_DIV256)
	{
		CLEAR_BIT(TCCR2,CS20);
		SET_BIT(TCCR2,CS21);
		SET_BIT(TCCR2,CS22);
	}
	else if(prescaler == TIMER2_DIV1024)
	{
		SET_BIT(TCCR2,CS20);
		SET_BIT(TCCR2,CS21);
		SET_BIT(TCCR2,CS22);
	}
	
}

void TIMER2_stop(u8 prescaler)
{
	CLEAR_BIT(TCCR2,CS20);
	CLEAR_BIT(TCCR2,CS21);
	CLEAR_BIT(TCCR2,CS22);
}

void TIMER2_setPreload(u8 value)
{
	TCNT2 = value;
}

void TIMER2_setOcr(u16 value)       
{
	OCR2 = value;
}

u8 TIMER2_getCounts()
{
	return TCNT2;
}

void (*TIMER2_ctcFunc)();

void TIMER2_setCallbackCtc(void (*func)())
{
	TIMER2_ctcFunc = func;
}

//num(in vector table)-1
void __vector_4() __attribute__((signal));
void __vector_4()
{
	TIMER2_ctcFunc();
}