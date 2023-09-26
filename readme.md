# MSP_430_USART_Clock

This is CCS project for CC430F5137 controller by Texas Instruments.

Project exemplify how to communicate with MSP430 via USART bus.

## Behaviour

The board is idle in the message standby mode. After receiving any message via USART, board responds 
```
HELLO
```
## Connection

- Pin P2.6 - Rx
- Pin P2.7 - Tx
- Baud 115200
- Data bits - 8
- Parity - None
