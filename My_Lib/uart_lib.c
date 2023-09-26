/*
 * tim_lib.c
 *
 *  Created on: 30 мар. 2023 г.
 *      Author: kinvl
 */

#include <msp430.h>
#include <stdint.h>

void UART_init(){

    PMAPPWD = 0x02D52;                        // Get write-access to port mapping regs
    P2MAP6 = PM_UCA0RXD;                      // Map UCA0RXD output to P2.6
    P2MAP7 = PM_UCA0TXD;                      // Map UCA0TXD output to P2.7
    PMAPPWD = 0;                              // Lock port mapping registers

    P2DIR |= BIT7;                            // Set P2.7 as TX output
    P2SEL |= BIT6 + BIT7;                     // Select P2.6 & P2.7 to UART function

    UCA0CTL1 |= UCSWRST;                      // **Put state machine in reset**
    UCA0CTL1 |= UCSSEL_2;                     // CLK = SMCLK
    UCA0BR0 = 0x04;                           // 115200 baud rate for 8.4 MHz (see user guide p.596)
    UCA0BR1 = 0x00;                           //
    UCA0MCTL = UCBRS_4 + UCBRF_7 + UCOS16;    // Modulation + UCOS16 enable
    UCA0CTL1 &= ~UCSWRST;                     // **Initialize USCI state machine**
    UCA0IE |= UCTXIE + UCRXIE;                // Enable USCI_A0 TX/RX interrupt

}

uint8_t UART_ReceiveChar(){
    return UCA0RXBUF;
}

void UART_TransmitChar(uint8_t data) {
    UCA0TXBUF = data;
    while((UCA0IFG & UCTXIFG) != UCTXIFG);    //USCI inactive (no transmitting or receiving)

}

void UART_Write(uint8_t *dat, uint32_t count) {
    while(count--)
    {
        UART_TransmitChar(*dat++);
    }
}

void UART_Tx_Number(uint32_t num) {
    uint32_t reverse = 0;
    uint8_t zero_trig = 0;

    while(num){
        reverse = reverse*10 + num%10;
        if (!(reverse || num%10)) zero_trig++; //check for amount of 0 digits in the end of number
        num /= 10;
    }

    while(reverse){
        UART_TransmitChar(reverse%10 + '0');
        reverse /= 10;
    }

    while (zero_trig) {
        UART_TransmitChar('0');
        zero_trig--;
    }

    UART_TransmitChar(' ');
}
