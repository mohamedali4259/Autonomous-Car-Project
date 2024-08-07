/*
 * SERVO_INT.h
 *
 * Created: 06/21/2024 07:41:18 ص
 *  Author: Mohamed Aias
 */ 


#ifndef SERVO_INT_H_
#define SERVO_INT_H_

#define S_ENABLE      DIO_PIND7

void S_init();
void S_0_degree();
void S_180_degree();
void S_Check_Right_Obstacle();
void S_Check_Left_Obstacle();
void ctcISR();



#endif /* SERVO_INT_H_ */