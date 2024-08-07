/*
 * ULTRASONIC_PROG.c
 *
 * Created: 06/21/2024 09:09:41 ص
 *  Author: Mohamed Aias
 */ 
#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "DIO_INT.h"
#include "MOTOR_INT.h"
#include "ULTRASONIC_INT.h"
#include "TIMER0_INT.h"
#include "EXT_INT.h"

#define F_CPU 16000000UL
#include <util/delay.h>
	
void US_init()
{
	///TIMER0_initNormal();
	///EXT_int0Init(EXT_ANY_LOGICAL);
	DIO_setPinDir(DIO_PIND1,DIO_OUTPUT);      // Go to Ultrasonic Trigger
	DIO_setPinDir(DIO_PIND2,DIO_INPUT);       // Return from Ultrasonic Echo 
}

void Trigger()
{
	// send 10 us pulse to Ultrasonic
		DIO_setPinValue(DIO_PIND1,DIO_HIGH);
		_delay_us(10);
		DIO_setPinValue(DIO_PIND1,DIO_LOW);
		_delay_us(1000);
}


