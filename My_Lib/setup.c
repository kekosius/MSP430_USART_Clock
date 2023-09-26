/*
 * setup.c
 *
 *  Created on: 30 мар. 2023 г.
 *      Author: kinvl
 */

#include <msp430.h>
#include <stdint.h>

void XT1_oscillator_init(){                   // 32768 Hz oscillator for ACLK source

    P5SEL |= 0x03;                            // Enable XT1 pins
    do
    {
      UCSCTL7 &= ~(XT1LFOFFG + DCOFFG);       // Clear XT2,XT1,DCO fault flags
      SFRIFG1 &= ~OFIFG;                      // Clear fault flags
      __delay_cycles(100000);                 // Delay for Osc to stabilize
    }while (SFRIFG1&OFIFG);                   // Test oscillator fault flag
}

void MCLK_setup_8388608Hz(){

    UCSCTL3 |= SELREF_2;                      // Set DCO FLL reference = REFO
    UCSCTL4 |= SELA_2;                        // Set ACLK = REFO

    __bis_SR_register(SCG0);                  // Disable the FLL control loop
    UCSCTL0 = 0x0000;                         // Set lowest possible DCOx, MODx
    UCSCTL1 = DCORSEL_5;                      // Select DCO range 24MHz operation
    UCSCTL2 = FLLD_1 + 255;                   // Set DCO Multiplier for 12MHz
                                              // (N + 1) * FLLRef = Fdco
                                              // (254 + 1) * 32768 = 8388608Hz
                                              // Set FLL Div = fDCOCLK/2
    __bic_SR_register(SCG0);                  // Enable the FLL control loop

    // Worst-case settling time for the DCO when the DCO range bits have been
    // changed is n x 32 x 32 x f_MCLK / f_FLL_reference. See UCS chapter in 5xx
    // UG for optimization.
    // 32 x 32 x 8388608Hz / 32,768 Hz = 262144 = MCLK cycles for DCO to settle
    __delay_cycles(262144);

    // Loop until XT1,XT2 & DCO fault flag is cleared
    do
    {
      UCSCTL7 &= ~(XT2OFFG + XT1LFOFFG + XT1HFOFFG + DCOFFG);
                                              // Clear XT2,XT1,DCO fault flags
      SFRIFG1 &= ~OFIFG;                      // Clear fault flags
    }while (SFRIFG1&OFIFG);                   // Test oscillator fault flag
}

void WDT_stop(){
    WDTCTL = WDTPW+WDTHOLD;                   // Stop watchdog timer
}
