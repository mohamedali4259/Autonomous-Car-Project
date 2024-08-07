/*
 * GI_PROG.c
 *
 * Created: 04/24/2024 08:38:22 م
 *  Author: Mohamed Aias
 */ 


#include "BIT_MATH.h"
#include "GI_INT.h"

void GI_enable()
{
	SET_BIT(SREG, I);
}

void GI_disable()
{
	CLEAR_BIT(SREG, I);
}