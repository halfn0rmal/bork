/*
 * adc.c
 *
 *  Created on: Oct 8, 2018
 *      Author: DEMO
 */

#include "adc.h"
#include <msp430.h>

void init_adc(void)
{
    // Configure ADC12
    ADC12CTL0 |= ADC12SHT0_2 | ADC12ON; // Cycle Sample Time, ADC On
    ADC12CTL1 |= ADC12SHP; // Source clock is sample timer
    ADC12CTL2 |= ADC12RES_2; // 12-bit conversion
    ADC12IE |= ADC12IE0; // Interrupt MEM0
    ADC12MCTL0 |= ADC12INCH_5;// | ADC12SREF0; // Select A4, Vref = 2.5V
}

void adc_sample(void)
{
    ADC12CTL0 |= ADC12ENC + ADC12SC; // Sampling and conversion start
    __bis_SR_register(LPM0_bits + GIE); // LPM0, ADC12_ISR will force exit
}

#pragma vector = ADC12_VECTOR
__interrupt void ADC12_ISR(void)
{
     ADC_value = ADC12MEM0; // Save MEM0
     //voltage = ADC_value*(3300/4096);
     __bic_SR_register_on_exit(LPM0_bits | GIE); // Exit CPU, clear interrupts
}
