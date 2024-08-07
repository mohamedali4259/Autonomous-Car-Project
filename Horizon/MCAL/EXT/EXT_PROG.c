/*
 * EXT_PROG.c
 *
 * Created: 04/24/2024 07:45:37 م
 *  Author: Mohamed Aias
 */ 

#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "EXT_INT.h"
#include "DIO_INT.h"

void EXT_int0Init(u8 trigger)
{
	if(trigger == EXT_RISING)
	{
		SET_BIT(MCUCR, ISC00);
		SET_BIT(MCUCR, ISC01);
	}
	else if(trigger == EXT_FALLING)
	{
		CLEAR_BIT(MCUCR, ISC00);
		SET_BIT(MCUCR, ISC01);
	}
	else if(trigger == EXT_ANY_LOGICAL)
	{
		SET_BIT(MCUCR, ISC00);
		CLEAR_BIT(MCUCR, ISC01);
	}
	
	//enable
	SET_BIT(GICR,INT0);
	
}

void (*EXT_int0Func)();

//EXT_int0Func = toggleLed;

void EXT_setCallbackInt0(void (*func)())
{
	EXT_int0Func = func;
}

//num(in vector table)-1
void __vector_1() __attribute__((signal));
void __vector_1()
{
	EXT_int0Func();
	//DIO_togglePinValue(DIO_PINC2);
}



void EXT_int1Init(u8 trigger)
{
	if(trigger == EXT_RISING)
	{
		SET_BIT(MCUCR, ISC10);
		SET_BIT(MCUCR, ISC11);
	}
	else if(trigger == EXT_FALLING)
	{
		CLEAR_BIT(MCUCR, ISC10);
		SET_BIT(MCUCR, ISC11);
	}
	else if(trigger == EXT_ANY_LOGICAL)
	{
		SET_BIT(MCUCR, ISC10);
		CLEAR_BIT(MCUCR, ISC11);
	}
	
	//enable
	SET_BIT(GICR,INT1);
}

void (*EXT_int1Func)();

//EXT_int1Func = toggleLed;

void EXT_setCallbackInt1(void (*func)())
{
	EXT_int1Func = func;
}

//num(in vector table)-1
void __vector_2() __attribute__((signal));
void __vector_2()
{
	EXT_int1Func();
	//DIO_togglePinValue(DIO_PINC2);
}

void EXT_int2Init(u8 trigger)
{
		if(trigger == EXT_RISING)
		{
			SET_BIT(MCUCR, ISC2);
		}
		else if(trigger == EXT_FALLING)
		{
			CLEAR_BIT(MCUCR, ISC2);
		}
	
		
		//enable
		SET_BIT(GICR,INT2);
}

void (*EXT_int2Func)();

//EXT_int2Func = toggleLed;

void EXT_setCallbackInt2(void (*func)())
{
	EXT_int2Func = func;
}

//num(in vector table)-1
void __vector_3() __attribute__((signal));
void __vector_3()
{
	EXT_int2Func();
	//DIO_togglePinValue(DIO_PINC2);
}
