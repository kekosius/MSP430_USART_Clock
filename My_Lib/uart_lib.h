/*
 * uart_lib.h
 *
 *  Created on: 30 мар. 2023 г.
 *      Author: kinvl
 */

#ifndef MY_LIB_UART_LIB_H_
#define MY_LIB_UART_LIB_H_

void UART_init(void);

uint8_t UART_ReceiveChar(void);

void UART_TransmitChar(uint8_t);

void UART_Write(uint8_t *, uint32_t);

void UART_Tx_Number(uint32_t);

#endif /* MY_LIB_UART_LIB_H_ */
