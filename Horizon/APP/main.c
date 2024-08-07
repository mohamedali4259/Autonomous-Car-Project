/*
 * Horizon.c
 *
 * Created: 04/03/2024 08:50:27 م
 * Author : Mohamed Aias
 */ 

#include "BIT_MATH.h"
#include "STD_TYPES.h"
# define F_CPU 16000000UL
#include <util/delay.h>
#include "DIO_INT.h"
#include "LCD_INT.h"
#include "EXT_INT.h"
#include "GI_INT.h"
#include "TIMER0_INT.h"
#include "TIMER1_INT.h"
#include "TIMER2_INT.h"
#include "ULTRASONIC_INT.h"
#include "SERVO_INT.h"

static s16 L_dis=0, R_dis=0, dis=0;
//f32 Ttick = (64.0/16000000)*1000; // 1000 to convert to ms
f32 Ttick = 0.004;  //ms
s32 ovCounter=0;
void overflowISR()
{
	ovCounter++;
}

void ultrasonicFunc()
{
	static u8 edge = 0;
	//rising
	if(edge == 0)
	{
		ovCounter = 0;
		TIMER0_initNormal(0);
		TIMER0_start(TIMER0_DIV64);
		edge=1;
	}
	//falling
	else if(edge == 1)
	{
		TIMER0_stop(TIMER0_DIV64);
		f32 time = ( TCNT0 + (ovCounter * 256) ) * Ttick;
		dis = 17*time;
		edge=0;
	}
	
}

void LCD_Car_Data_Display()
{
	LCD_clearDis();
	LCD_sendStr("d = ");
}


int main(void)
{
	GI_enable();
	S_init();
	US_init();
	LCD_init();
	M_init();
    TIMER0_setCallbackOv(overflowISR);
	EXT_int0Init(EXT_ANY_LOGICAL);
	EXT_setCallbackInt0(ultrasonicFunc);
	TIMER2_setCallbackCtc(ctcISR);
    
		
	while (1)
	{
	Trigger();
	Car_Go_Forward();
	LCD_Car_Data_Display();
	LCD_sendNum(dis);
	LCD_sendStr("cm");
	LCD_GoTo(0,1);
	LCD_sendStr("Car_Go_Forward");
	_delay_ms(1000);
	S_Check_Right_Obstacle();     // Servo Right Direction
	R_dis=dis;
	S_Check_Left_Obstacle();      // Servo Left Direction
	L_dis=dis;
	if(R_dis>35&&L_dis>35)
	{
		Car_Go_Forward();
		LCD_Car_Data_Display();
		LCD_sendNum(dis);
		LCD_sendStr("cm");
		LCD_GoTo(0,1);
		LCD_sendStr("Car_Go_Forward");
		_delay_ms(1000);
	}
	else if(L_dis>35&&R_dis<35)
	{
		Car_Stopping();
		Car_Turning_BackRight();
		LCD_Car_Data_Display();
		LCD_sendNum(R_dis);
		LCD_sendStr("cm");
		LCD_GoTo(0,1);
		LCD_sendStr("Turning_BackRight");
		_delay_ms(500);
		Car_Go_Forward();
		LCD_Car_Data_Display();
		LCD_sendNum(L_dis);
		LCD_sendStr("cm");
		LCD_GoTo(0,1);
		LCD_sendStr("Car_Go_Forward");
		_delay_ms(1000);
	}
	else if (L_dis<35&&R_dis>35)
	  {
			Car_Stopping();
			Car_Turning_Backleft();
			LCD_Car_Data_Display();
			LCD_sendNum(L_dis);
			LCD_sendStr("cm");
			LCD_GoTo(0,1);
			LCD_sendStr("Turning_Backleft");
			_delay_ms(500);
			Car_Go_Forward();
			LCD_Car_Data_Display();
			LCD_sendNum(R_dis);
			LCD_sendStr("cm");
			LCD_GoTo(0,1);
			LCD_sendStr("Car_Go_Forward");
			_delay_ms(1000);
	  }
	else
		{
			Car_Stopping();
			Car_Turnback();
		    Car_Go_Forward();
		    LCD_Car_Data_Display();
		    LCD_sendNum(dis);
		    LCD_sendStr("cm");
		    LCD_GoTo(0,1);
		    LCD_sendStr("Car_Go_Forward");
		    _delay_ms(1000);
		}
		
	dis=0; L_dis=0; R_dis=0;
	
	}
}
	