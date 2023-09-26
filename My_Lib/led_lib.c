/*
 * tim_lib.c
 *
 *  Created on: 30 мар. 2023 г.
 *      Author: kinvl
 */

#include <msp430.h>
#include <stdint.h>

void LED_init(){
    P1OUT = 0x00;                            // P1.0 setup for LED output
    P1DIR |= BIT0;
}

void LED_On(){
    P1OUT = 1;
}

void LED_Off(){
    P1OUT = 0;
}

void LED_Toggle(){
    P1OUT ^= BIT0;
}
