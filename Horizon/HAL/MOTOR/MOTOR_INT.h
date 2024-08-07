/*
 * MOTOR_INT.h
 *
 * Created: 06/20/2024 02:34:33 ص
 *  Author: Mohamed Aias
 */ 


#ifndef MOTOR_INT_H_
#define MOTOR_INT_H_

#define M1_IN1          DIO_PINC3
#define M1_IN2          DIO_PINC4
#define M1_EN1          DIO_PIND4
#define M2_IN3          DIO_PINC5
#define M2_IN4          DIO_PINC6
#define M2_EN2          DIO_PIND5

void M_init();
void M1_clockwise();
void M1_anticlockwise();
void M2_clockwise();
void M2_anticlockwise();
void M1_stop();
void M2_stop();
void Car_Go_Forward();
void Car_Go_Backward();
void Car_Stopping();
void Car_Turning_Backleft();
void Car_Turning_BackRight();
void Car_Turnback();

#endif /* MOTOR_INT_H_ */