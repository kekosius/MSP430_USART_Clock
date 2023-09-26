/*
 * tim_lib.c
 *
 *  Created on: 30 мар. 2023 г.
 *      Author: kinvl
 */

#include <msp430.h>
#include <stdint.h>

void TIM1_start(uint16_t);

void TIM1_init(){
    TA1CCTL0 = CCIE;                           // CCR0 interrupt enabled
    TA1CCR0 = 0;                               // TIM stop
    TA1CTL = TASSEL_1 + ID_3 + MC_1 + TACLR;   // ACLK for source, input divider 3 (/8), upmode, clear TAR
    TIM1_start(4096-1);                        // 32768Hz / (8 * 4096) = 1 trigger/sec; MAX - 65535
}

void TIM1_stop(){
    TA1CCR0 = 0;
}

void TIM1_start(uint16_t period){
    TA1CCR0 = period;
}
