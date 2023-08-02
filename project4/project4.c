 /******************************************************************************
 *
 * Project : Distance measuring System
 *
 * File Name: project3.c
 *
 * Description: measure the distance using Ultrasonic sensor HC-SR04 and display
 * 				it on the LCD
 *
 * Author: Mohamed Hossam
 *
 *******************************************************************************/
#include"ultrasonic.h"
#include"lcd.h"
#include<avr/io.h>
#include<util/delay.h>

int main()
{
	uint16 distance;

	/* set global interrupt enable */
	SREG|=(1<<7);

	/* initiate Ultrasonic and LCD modules */
	LCD_init();
	Ultrasonic_init();


	LCD_displayString("Distance=    cm");
	for(;;)
	{
		/* get the distance from the  Ultrasonic */
		distance=Ultrasonic_readDistance();
		/* display the distance */
		LCD_moveCursor(0,10);
		if(distance < 10)
		{
			LCD_integerToString(distance);
			LCD_displayString("  ");
		}
		else if(distance < 100)
		{
			LCD_integerToString(distance);
			LCD_displayCharacter(' ');
		}
		else if(distance <= 400)
		{
			LCD_integerToString(distance);
		}
		else
		{
			/* Ultrasonic_readDistance function returns approximately 655 if
			 * there is no object in range */
			/* display --- to indicate that there is no object in range */
			LCD_displayString("---");
		}
		/* wait measurement cycle period as instructed in data sheet */
		_delay_ms(60);
	}
}