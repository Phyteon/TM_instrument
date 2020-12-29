/*****************************************************************************************************
*This file is a part of TM2 project which goal is to create a musical instrument.*
******************************************************************************************************/
/**
 * @file dsp.c
 * @author Pawelec, Skomiał
 * @date Dec 2020
 * @brief File containing definitions of functions, structures and enums for PIT timer
 * @ver 0.1
 */
 
 #include "pit.h"
 #define COUNTER_CONST_VAL 10331
 static uint8_t * tune_idx_arr;
 void PIT_init(void)
 {
	 SIM->SCGC6 |= SIM_SCGC6_PIT_MASK;
	 PIT->MCR |= PIT_MCR_MDIS_MASK | PIT_MCR_FRZ_MASK; // Disabling module before further setup and allowing freezing of timers in debug mode (docs page 536)
	 PIT->CHANNEL[0].LDVAL |= COUNTER_CONST_VAL; // Loading pre-calculated value to LDVAL to obtain 4060 Hz interrupt frequency (for playing sounds)
	 PIT->CHANNEL[0].TCTRL |= PIT_TCTRL_TIE_MASK | PIT_TCTRL_TEN_MASK; // Allowing generation of interrupts and enabling individual counter
	 NVIC_ClearPendingIRQ(PIT_IRQn);
	 NVIC_SetPriority(PIT_IRQn, 1); // Setting interrupt priority level #TODO - check if priority is correct (should be lower priority than PORTB)
	 NVIC_EnableIRQ(PIT_IRQn);
	 tune_idx_arr = get_tune_idx_arr(); // Getting pointer to array
	 PIT->MCR &= ~PIT_MCR_MDIS_MASK; // Enabling whole module
 }
 
 void PIT_IRQHandler(void)
 {
	 assemble_samples(tune_idx_arr);
	 PIT->CHANNEL[0].TFLG |= PIT_TFLG_TIF_MASK; // Clear interrupt
 }
