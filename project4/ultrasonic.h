 /******************************************************************************
 *
 * Module: Ultrasonic
 *
 * File Name: ultrasonic.c
 *
 * Description: Header file for the Ultrasonic HCSR04 driver
 *
 * Author: Mohamed Hossam
 *
 *******************************************************************************/

#ifndef ULTRASONIC_H_
#define ULTRASONIC_H_
#include"std_types.h"
/*******************************************************************************
 * 									Definitions
 *******************************************************************************/
#define ULTRASONIC_TRIGGER_PORT_ID  PORTB_ID
#define ULTRASONIC_TRIGGER_PIN_ID   PIN5_ID

#define TIMER_TICK_TIME_US		    1
/*******************************************************************************
 * 									Functions Prototypes
 *******************************************************************************/
/*
 * Description :
 * Initialize the ICU driver as required
 * Setup the ICU call back function
 * Setup the direction for the trigger pin as output pin
 */
void Ultrasonic_init(void);

/*
 * Description :
 * send trigger pulse
 * measure the distance
 * return the result
 */
uint16 Ultrasonic_readDistance(void);
#endif /* ULTRASONIC_H_ */
