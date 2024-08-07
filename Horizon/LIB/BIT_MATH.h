﻿/*
 * BIT_MATH.h
 *
 * Created: 04/03/2024 09:06:02 م
 *  Author: Mohamed Aias
 */ 


#ifndef BIT_MATH_H_
#define BIT_MATH_H_
#define SET_BIT(x,n)        x=x|(1<<n)
#define TOGGLE_BIT(x,n)     x=x^(1<<n)
#define CLEAR_BIT(x,n)      x=x&(~(1<<n))
#define GET_BIT(x,n)        ((x&(1<<n))>>n)
// #define GET_BIT(x,n)        ((x>>n)&1)




#endif /* BIT_MATH_H_ */