/*****************************************************************************************************
*This file is a part of TM2 project which goal is to create a musical instrument.*
******************************************************************************************************/
/**
 * @file main.c
 * @author Pawelec, Skomial
 * @date Jan 2021
 * @brief File containing the main function.
 * @ver 0.1
 */


#include "pit.h"
#include "adc.h"


 int main (void) {
	 Init_DAC(); // Initialise DAC
	 init_array(); // Initialise arrays in dat_prep file
	 Ps2_comm_init(); // Initalise receive from PS/2 keyboard
	 volatile uint8_t cal;
	 cal = init_ADC();
	 if(cal) while(1); // If callibration failed, do not proceed
	 
	 
	 PIT_init();
	 while(1)
	 {
		 if(chck_if_dat_rdy())
		 {
			decode_keys();
		 }
	 }
 }

