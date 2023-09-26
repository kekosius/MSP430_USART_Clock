#include <msp430.h>
#include <stdint.h>
#include <My_Lib/led_lib.h>
#include <My_Lib/uart_lib.h>
#include <My_Lib/setup.h>
#include <My_Lib/tim_lib.h>

uint8_t tx_char = 0;
uint32_t time_count = 0;

uint8_t message[7] = {13, 'H', 'E', 'L', 'L', 'O', 13};

int main(void)
{
    WDT_stop();

    LED_init();                               // P1.0 for LED output

    MCLK_setup_8388608Hz();

    XT1_oscillator_init();                    // ACLK source setup

    UART_init();                              // 115200 baud, 8N1, P2.6 - RX, P2.7 - TX

    TIM1_init();                              // 1 interrupt/sec

    __bis_SR_register(GIE);                   // Enter interrupts enabled
    __no_operation();                         // For debugger

    while(1)
    {
        __bis_SR_register(GIE);
    }
}

// UART_A0 interrupt service routine
#if defined(__TI_COMPILER_VERSION__) || defined(__IAR_SYSTEMS_ICC__)
#pragma vector=USCI_A0_VECTOR
__interrupt void USCI_A0_ISR(void)
#elif defined(__GNUC__)
void __attribute__ ((interrupt(USCI_A0_VECTOR))) USCI_A0_ISR (void)
#else
#error Compiler not supported!
#endif
{

    switch(__even_in_range(UCA0IV,4))
  {
    case 0: break;                          // Vector 0 - no interrupt
    case 2:                                 // Vector 2 - RXIFG
        tx_char = UART_ReceiveChar();
        LED_On();
        UART_Write(message, 7);
        time_count = 0;
      break;
    case 4:                                 // Vector 4 - TXIFG
        LED_Off();
      break;
    default: break;
  }
}

// Timer A0 interrupt service routine
#if defined(__TI_COMPILER_VERSION__) || defined(__IAR_SYSTEMS_ICC__)
#pragma vector=TIMER1_A0_VECTOR
__interrupt void TIMER1_A0_ISR(void)
#elif defined(__GNUC__)
void __attribute__ ((interrupt(TIMER1_A0_VECTOR))) TIMER1_A0_ISR (void)
#else
#error Compiler not supported!
#endif
{
    time_count++;
    UART_Tx_Number(time_count);
}




