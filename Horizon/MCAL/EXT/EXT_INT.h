/*
 * EXT_INT.h
 *
 * Created: 04/24/2024 07:44:45 م
 *  Author: Mohamed Aias
 */ 


#ifndef EXT_INT_H_
#define EXT_INT_H_

#include "STD_TYPES.h"


#define MCUCR  (*(volatile u8*)0x55)
#define ISC00	0
#define ISC01	1

#define ISC10	2
#define ISC11	3

#define ISC2	6

#define MCUCSR  (*(volatile u8*)0x54)


#define GICR  (*(volatile u8*)0x5B)
#define  INT0 6
#define  INT1 7
#define  INT2 5

#define EXT_FALLING		0
#define EXT_RISING		1
#define EXT_ANY_LOGICAL	2


void EXT_int0Init(u8 trigger);
void EXT_int1Init(u8 trigger);
void EXT_int2Init(u8 trigger);
void EXT_setCallbackInt0(void (*func)());


#endif /* EXT_INT_H_ */