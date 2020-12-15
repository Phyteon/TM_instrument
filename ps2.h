/*****************************************************************************************************
*This file is a part of TM2 project which goal is to create a musical instrument.*
******************************************************************************************************/
/**
 * @file ps2.h
 * @author Pawelec, Skomiał
 * @date Dec 2020
 * @brief File containing enums, structures and declarations for ps2 keyboard.
 * @ver 0.1
 */
 
 
#include "MKL05Z4.h"

#ifndef PS2_H
#define PS2_H


/**
 * @brief Initialise communication with PS/2 keyboard
 */
void Ps2_comm_init(void);

/**
	* @brief Interrupt handler for communication - Utilising PTB6 for CLK line, PTB7 for data line 
	*/
void PORTB_IRQHandler(void);

/**
	* @brief Function for converting incoming transmission data bits into 8 bit unsigned integer 
	*/
uint8_t pow2(uint8_t);


#endif /* PS2_H */
