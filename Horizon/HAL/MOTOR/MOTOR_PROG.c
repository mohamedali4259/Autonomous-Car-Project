/*
 * MOTOR_PROG.c
 *
 * Created: 06/20/2024 02:35:01 ص
 *  Author: Mohamed Aias
 */ 

#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "DIO_INT.h"
#include "MOTOR_INT.h"

#define F_CPU 16000000UL
#include <util/delay.h>

void M_init()
{
	DIO_setPinDir(M1_IN1,DIO_OUTPUT);
	DIO_setPinDir(M1_IN2,DIO_OUTPUT);
	DIO_setPinDir(M1_EN1,DIO_OUTPUT);
	DIO_setPinDir(M2_IN3,DIO_OUTPUT);
	DIO_setPinDir(M2_IN4,DIO_OUTPUT);
	DIO_setPinDir(M2_EN2,DIO_OUTPUT);
	TIMER1_initPhaseCorrectMod9();
	TIMER1_setPCFrequency(25);
}

void M1_clockwise()            /// Forward 
{
	DIO_setPinValue(M1_IN1,DIO_LOW);
	DIO_setPinValue(M1_IN2,DIO_HIGH);
	DIO_setPinValue(M1_EN1,DIO_HIGH);
	TIMER1_setOcr(500);             /// Duty=10%
}

void M1_anticlockwise()        /// Backward
{
	DIO_setPinValue(M1_IN1,DIO_HIGH);
	DIO_setPinValue(M1_IN2,DIO_LOW);
	DIO_setPinValue(M1_EN1,DIO_HIGH);
	TIMER1_setOcr(250);             /// Duty=5%
}

void M2_clockwise()                /// Forward
{
	DIO_setPinValue(M2_IN3,DIO_HIGH);
	DIO_setPinValue(M2_IN4,DIO_LOW);
	DIO_setPinValue(M2_EN2,DIO_HIGH);
	TIMER1_setOcr(500);             /// Duty=10%
}

void M2_anticlockwise()           /// Backward
{
	DIO_setPinValue(M2_IN3,DIO_LOW);
	DIO_setPinValue(M2_IN4,DIO_HIGH);
	DIO_setPinValue(M2_EN2,DIO_HIGH);
	TIMER1_setOcr(250);             /// Duty=5%
}

void M1_stop()
{
	DIO_setPinValue(M1_IN1,DIO_LOW);
	DIO_setPinValue(M1_IN2,DIO_LOW);
	DIO_setPinValue(M1_EN1,DIO_LOW);
}

void M2_stop()
{
	DIO_setPinValue(M2_IN3,DIO_LOW);
	DIO_setPinValue(M2_IN4,DIO_LOW);
	DIO_setPinValue(M2_EN2,DIO_LOW);
}

void Car_Go_Forward()
{
	M1_clockwise();
	M2_clockwise();
}

void Car_Go_Backward()
{
	M1_anticlockwise();
	M2_anticlockwise();
	_delay_ms(500);
}

void Car_Stopping()
{
	M1_stop();
	M2_stop();
	_delay_ms(1000);
}

void Car_Turning_Backleft()
{
	M1_stop();
	M2_anticlockwise();    
	_delay_ms(500);
}

void Car_Turning_BackRight()
{
	M2_stop();
	M1_anticlockwise();     
	_delay_ms(500);
}

void Car_Turnback()
{
	Car_Go_Backward();
	M1_clockwise();
	M2_anticlockwise();
	_delay_ms(500);
}