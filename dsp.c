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
 
 double floor(double x);
 
 static uint16_t sample_counter = 0;
 void assemble_samples(uint8_t* idx_array)
 {
	 volatile uint16_t final_samp = 0;
	 volatile uint8_t i = 0;
	 volatile uint8_t nr_of_keys = 0;
	 volatile uint8_t final_samp_l;
	 volatile uint8_t final_samp_h;
	 for(i; i < DAT_BUFF_SIZE; i++)
	 {
		 if(idx_array[i] != 0xFF) // Check if index is valid
		 {
			 final_samp += sounds[idx_array[i]][sample_counter]; // Add corresponding samples
			 nr_of_keys += 1;
		 }
	 }
	 // Dividing outcome sample into younger and older byte, beacuse DAC module does not support 16-bit access
	 if(nr_of_keys)
	 final_samp = normalise(final_samp, nr_of_keys);
	 final_samp_l = (uint8_t)(final_samp & 0xFF);
	 final_samp_h = (uint8_t)((final_samp & 0xFF00)>>8);
	 if(sample_counter == NR_OF_SAMPLES - 1) sample_counter = 0;
	 else sample_counter++; // Incrementing sample counter
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
 
 uint16_t normalise(uint16_t sample, uint8_t nr_of_keys)
 {
	 volatile double percentage;
	 volatile uint16_t final;
	 percentage = (double)sample/((double)nr_of_keys*255.0);
	 final = (uint16_t)(floor(percentage*4095.0));
	 return final;
 }
