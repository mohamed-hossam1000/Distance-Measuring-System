 /******************************************************************************
 *
 * Module: ICU
 *
 * File Name: icu.c
 *
 * Description: Source file for the LCD driver
 *
 * Author: Mohamed Hossam
 *
 *******************************************************************************/
#include"icu.h"
#include"gpio.h"
#include<avr/interrupt.h>
#include<avr/io.h>

/* global variable to hold the call back function address */
static volatile void (*g_callBack)(void) = NULL_PTR;
/*******************************************************************************
 * 								Functions Definitions
*******************************************************************************/
/**
 * Description :
 * Interrupt Service Routine for the ICU interrupt
 */
ISR(TIMER1_CAPT_vect)
{
	if(g_callBack!=NULL_PTR)
	{
		/* call the call back function */
		(*g_callBack)();
	}
}

/*
 * Description :
 * initialize the ICU with the required frequency and edge detection
 */
void ICU_init(const ICU_configType* config)
{
	/* configure ICP1 as input pin */
	GPIO_setupPinDirection(PORTD_ID, PIN6_ID, PIN_INPUT);
	/* bits required for non-PWM modes  */
	TCCR1A=(1<<FOC1A) | (1<<FOC1A);
	/* set the clock prescaler and choose edge detection type */
	TCCR1B=config->clk | (config->edge << ICES1);
	/* enable the ICU interrupts */
	TIMSK|=(1<<TICIE1);
	/* initialize the registers */
	TCNT1=0;
	ICR1=0;
}

/*
 * Description :
 * change the type of edge the ICU detects
 */
void ICU_selectEdgeDetectionType(ICU_edgeType edge)
{
	TCCR1B=(TCCR1B&0xBF) | (edge<<6);
}

/*
 * Description :
 * set call back address
 */
void ICU_setCallBack(void (*func_ptr)(void))
{
	g_callBack=func_ptr;
}

/*
 * Description :
 * Function to clear timer value
 */
void ICU_cleaTimerValue()
{
	TCNT1=0;
}

/*
 * Description :
 * get the TIMER1 value when the input is captured
 */
uint16 ICU_getCapturedValue(void)
{
	return ICR1;
}

/*
 * Description :
 * function to disable Timer1 and the ICU
 */
void ICU_deinit()
{
	/* clear the registers */
	TCCR1A=0;
	TCCR1B=0;
	TCNT1=0;
	ICR1=0;
	/* disable the ICU interrupts */
	TIMSK&=~(1<<TICIE1);
}
