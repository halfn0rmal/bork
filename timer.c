/*
 * timer.c
 *
 *  Created on: Oct 8, 2018
 *      Author: Adam Grant
 */

#include "timer.h"
#include <msp430.h>

uint8_t tock;

void timer_A_Init(void)
{
    TA0CCTL0 = CCIE;                          // CCR0 interrupt enabled
    TA0CCR0 =  62500;                           // 2 Hz
    TA0CTL = TASSEL_2 + MC_1 + ID_3 + TACLR;         // SMCLK, upmode, clear TAR
}

// Timer A0 interrupt service routine
#pragma vector=TIMER0_A0_VECTOR
__interrupt void TIMER0_A0_ISR(void)
{

  if(seconds>0)
  {
      P4OUT |= 1<<7;                            // Toggle P4.7

      if(tock==0)
      {
          seconds--;
          tock=1;
      }
      else
      {
          tock=0;
      }
  }
  else
  {
      P4OUT &= ~1<<7;
  }

}

