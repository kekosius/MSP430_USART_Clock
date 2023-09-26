/*
 * setup.h
 *
 *  Created on: 30 мар. 2023 г.
 *      Author: kinvl
 */

#ifndef MY_LIB_SETUP_H_
#define MY_LIB_SETUP_H_

void MCLK_setup_8388608Hz(void);

void WDT_stop(void);

void XT1_oscillator_init(void);

#endif /* MY_LIB_SETUP_H_ */
