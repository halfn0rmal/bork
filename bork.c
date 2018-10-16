/*
 * Bork - A program to train my dog "Wall-E"
 *
 * */
#include <msp430.h>				
#include "adc.h"
#include "timer.h"

void main(void)
{
	WDTCTL = WDTPW | WDTHOLD;		// stop watchdog timer
	P4DIR |= 1<<7;                  //P4.7 Output
	P1DIR |= 0x01;					// configure P1.0 as output
	P6SEL |= 1<<5;                  //P6.5 set as ADC A5
	timer_A_Init();
	init_adc();

	P4OUT &= ~1<<7;                 //Turn off P4.7

	while(1)
	{
	    adc_sample();
		if(ADC_value>3000)
		{
		    seconds=10;  //Start the runtime for X seconds
		    P1OUT |= 0x01;  //Flash P1.0 when ADC goes above volume threshold
		}
		else
		{
		   P1OUT &= ~0x01;
		}
	}
}



