/*****************************************************************************************************
*This file is a part of TM2 project which goal is to create a musical instrument.*
******************************************************************************************************/
/**
 * @file main.c
 * @author Pawelec, Skomial
 * @date Dec 2020
 * @brief File containing the main function.
 * @ver 0.1
 */


#include "ps2.h"
#include "dac.h"



 int main (void) { 
	uint8_t data_buffer;
	Init_DAC();
	Ps2_comm_init();
	while(1)
	{
		if(chck_if_dat_rdy())
		{
			data_buffer = get_data(); // Store current stable data independently in case interrupt arrives early
			// Here decode key and action
		}
	}
	 
	 
	 
 }

