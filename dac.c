/*****************************************************************************************************
*This file is a part of TM2 project which goal is to create a musical instrument.*
******************************************************************************************************/
/**
 * @file dac.c
 * @author Pawelec, Skomiał
 * @date Dec 2020
 * @brief File containing enums, structures and declarations for DAC module.
 * @ver 0.1
 */
 
 
 #include "dac.h"
 
 #define DAC_OUT_PIN 1
 
 void Init_DAC(void)
 {
	 SIM->SCGC5 |= SIM_SCGC5_PORTB_MASK; // Connecting clock to PORTB
	 SIM->SCGC6 |= SIM_SCGC6_DAC0_MASK; // Connecting clock to DAC
	 PORTB->PCR[DAC_OUT_PIN] |= PORT_PCR_MUX(0); // Selecting PTB1 as DAC0 output
	 DAC0->C0 &= (uint8_t)~DAC_C0_DACRFS_MASK ; // Selecting DACREF_1 as ref voltage
	 // Not utilising data buffer
	 DAC0->C0 |= (uint8_t)DAC_C0_DACEN_MASK; // Enabling DAC module
 }
 
 void convert(uint8_t datl, uint8_t dath)
 {
	 DAC0->DAT[0].DATL = datl;
	 DAC0->DAT[0].DATH = dath;
 }
 
