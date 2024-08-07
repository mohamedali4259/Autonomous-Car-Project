/*
 * SERVO_PROG.c
 *
 * Created: 06/21/2024 07:41:48 ص
 *  Author: Mohamed Aias
 */ 
#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "DIO_INT.h"
#include "SERVO_INT.h"
#include "TIMER2_INT.h"

#define F_CPU 16000000UL
#include <util/delay.h>

u16 Counter=0;

void S_init()
{
	DIO_setPinDir(S_ENABLE,DIO_OUTPUT);
}

void ctcISR()
{
	Counter++;
}

void S_0_degree()
{
	TIMER2_initCtc();
	TIMER2_setOcr(249);
	static u8 flag=0;
	//rising
	if (flag==0)
	{
		Counter=0;
		TIMER2_setPreload(0);
		TIMER2_start(TIMER2_DIV64);
		DIO_setPinValue(S_ENABLE,DIO_LOW);
		flag=1;
	}
	//falling
	else if (flag==1)
	{
		if(Counter==1)    // Td=1ms
		{
			DIO_setPinValue(S_ENABLE,DIO_HIGH);
			flag=2;
		}
	}
	else if (flag==2)
	{
		if(Counter==2)   // Td=2ms
		{
			DIO_setPinValue(S_ENABLE,DIO_LOW);
			// Clear OC2 on Compare Match
			CLEAR_BIT(TCCR2,COM20);
			SET_BIT(TCCR2,COM21);
		
			flag=3;
		}
	}
	else if (flag==3)
	{
		if(Counter==20)    // Td=20ms
		{
			TIMER2_stop(TIMER2_DIV64);	
			flag=0;
		}
	}
}

void S_180_degree()
{
	TIMER2_initCtc();
	TIMER2_setOcr(249);
	static u8 flag=0;
	//rising
	if (flag==0)
	{
		Counter=0;
		TIMER2_setPreload(0);
		TIMER2_start(TIMER2_DIV128);
		DIO_setPinValue(S_ENABLE,DIO_LOW);
		flag=1;
	}
	//falling
	else if (flag==1)
	{
		if(Counter==1)    // Td=2ms
		{
			DIO_setPinValue(S_ENABLE,DIO_HIGH);
			flag=2;
		}
	}
	else if (flag==2)
	{
		if(Counter==2)   //Td=4ms
		{
		    DIO_setPinValue(S_ENABLE,DIO_LOW);
			// Clear OC2 on Compare Match
			CLEAR_BIT(TCCR2,COM20);
			SET_BIT(TCCR2,COM21);
		flag=3;	
		}
	}
	else if (flag==3)
	{
		if(Counter==10)
		{
			TIMER2_stop(TIMER2_DIV128);
			flag=0;
		}
	}
}

void S_Check_Right_Obstacle()
{
	S_init();
	S_180_degree();
	Trigger();
	_delay_ms(1000);	
}

void S_Check_Left_Obstacle()
{
	S_init();
	S_0_degree();
	Trigger();
	_delay_ms(1000);
}

