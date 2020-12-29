/*****************************************************************************************************
*This file is a part of TM2 project which goal is to create a musical instrument.*
******************************************************************************************************/
/**
 * @file dsp.c
 * @author Pawelec, Skomiał
 * @date Dec 2020
 * @brief File containing definitions of functions, structures and enums for final data prep for DAC
 * @ver 0.1
 */
 #include "dsp.h"
 #define DAT_BUFF_SIZE 10
 static uint16_t sample_counter = 0;
 void assemble_samples(uint8_t* idx_array)
 {
	 volatile uint16_t final_samp = 0;
	 volatile uint8_t i = 0;
	 volatile uint8_t final_samp_l;
	 volatile uint8_t final_samp_h;
	 for(i; i < DAT_BUFF_SIZE; i++)
	 {
		 if(idx_array[i] != 0xFF)
		 {
			 final_samp += sounds[idx_array[i]][sample_counter];
		 }
	 }
	 final_samp_l = (uint8_t)(final_samp & 0xFF);
	 final_samp_h = (uint8_t)((final_samp & 0xFF00)/0x0F);
	 if(sample_counter == NR_OF_SAMPLES - 1) sample_counter = 0;
	 else sample_counter++;
	 convert(final_samp_l, final_samp_h);
 }

 uint16_t get_sample_counter(void)
 {
	 return sample_counter;
 }
 
 void set_sample_counter(uint16_t var)
 {
	 sample_counter = var;
 }
