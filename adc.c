/*****************************************************************************************************
*This file is a part of TM2 project which goal is to create a musical instrument.*
******************************************************************************************************/
/**
 * @file adc.h
 * @author Pawelec, Skomiał
 * @date Dec 2020
 * @brief File containing declarations of functions, structures and enums for ADC module
 * @ver 0.1
 */
 #define ANALOG_IN 2
 #define CONV_INIT 0xFF
 #include "adc.h"
 
 uint8_t init_ADC(void)
 {
	uint16_t callibration;
	SIM->SCGC6 |= SIM_SCGC6_ADC0_MASK; // Connecting clock to ADC0
	SIM->SCGC5 |= SIM_SCGC5_PORTB_MASK; // Connecting clock to PORTB
	PORTB->PCR[ANALOG_IN] = PORT_PCR_MUX(0);	// Fourth channel of ADC0
	ADC0->CFG1 = (ADC_CFG1_ADICLK(1) | ADC_CFG1_ADIV(2) | ADC_CFG1_MODE(0)) & (~ADC_CFG1_ADLSMP_MASK);	// Bus CLK/8, to achieve best callibration results. Single-ended 8-bit conversion, short sample time
	ADC0->CFG2 = ADC_CFG2_ADHSC_MASK;	// Configure ADC for high-speed conversion
	ADC0->SC3  = ADC_SC3_AVGE_MASK | ADC_SC3_AVGS(3);	// Hardware averaging of 32 samples (for callibration)
	ADC0->SC3 |= ADC_SC3_CAL_MASK; // Start callibration
	while(ADC0->SC3 & ADC_SC3_CAL_MASK); // Wait for end of conversion
	
	if(ADC0->SC3 & ADC_SC3_CALF_MASK)
	{
	  ADC0->SC3 |= ADC_SC3_CALF_MASK;
	  return(1);	// Return nonzero value if callibration failed
	}
	
	callibration = 0x00;
	callibration += ADC0->CLP0;
	callibration += ADC0->CLP1;
	callibration += ADC0->CLP2;
	callibration += ADC0->CLP3;
	callibration += ADC0->CLP4;
	callibration += ADC0->CLPS;
	callibration += ADC0->CLPD;
	callibration = callibration >> 1; // Divide the outcome by 2
	callibration |= 1<<16; // Set the MSB
	ADC0->PG = ADC_PG_PG(callibration); // Save outcome accordingly
	ADC0->SC3 &= ~(ADC_SC3_AVGE_MASK | ADC_SC3_AVGS(3)); // Disable hardware averaging
	ADC0->SC1[0] = ADC_SC1_ADCH(4); // Select channel 4 as input
	ADC0->CFG1 = (ADC_CFG1_ADICLK(0) | ADC_CFG1_ADIV(0) | ADC_CFG1_MODE(0)) & ~ADC_CFG1_ADLSMP_MASK;	// Bus CLK, single-ended 8-bit conversion, short conversion time
	ADC0->SC2 &= ~ADC_SC2_ADTRG_MASK; // Make sure that software trigger is selected
	return(0);	// Return 0 if init completed succesfully

 }
 
 void trigger_measure(void)
 {
	 ADC0->SC1[0] &= CONV_INIT;
 }
 
 uint8_t return_measurement(void)
 {
	 if((ADC0->SC1[0] & ADC_SC1_COCO_MASK) == ADC_SC1_COCO_MASK) // Check the COCO flag
	 {
		 return (uint8_t)ADC0->R[0];
	 }
	 else return 0;
 }
