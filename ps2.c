/*****************************************************************************************************
*This file is a part of TM2 project which goal is to create a musical instrument.*
******************************************************************************************************/
/**
 * @file ps2.h
 * @author Pawelec, Skomial
 * @date Dec 2020
 * @brief File containing definitions for ps2 keyboard.
 * @ver 0.1
 */
 
 
 #include "MKL05Z4.h"
 #include "ps2.h"

#define CLK_PIN 6
#define DATA_LINE 7
 
 void Ps2_comm_init(void){
	SIM->SCGC5 |= SIM_SCGC5_PORTB_MASK; // Connecting clock to PORTB
	// Valid signal on data line occurs on low level of CLK, that's why interrupt is also set to logic zero
	PORTB->PCR[CLK_PIN] |= PORT_PCR_MUX(1) | PORT_PCR_IRQC(8) | PORT_PCR_PE_MASK | PORT_PCR_PS_MASK; // Selecting appropriate pin function, interrupts on logic zero and pullup
	PORTB->PCR[DATA_LINE] |= PORT_PCR_MUX(1) | PORT_PCR_PE_MASK | PORT_PCR_PS_MASK; // Selecting appropriate pin function and pullup
	
	NVIC_ClearPendingIRQ(PORTB_IRQn);
	NVIC_SetPriority(PORTB_IRQn, 3); // Setting interrupt priority level #TODO - check if priority is correct (should be highest priority)
	NVIC_EnableIRQ(PORTB_IRQn); // Enabling interrupts from PORTB
 }
 
 void PORTB_IRQHandler(void){
	
	 
	 
 }

 
