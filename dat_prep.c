/*****************************************************************************************************
*This file is a part of TM2 project which goal is to create a musical instrument.*
******************************************************************************************************/
/**
 * @file dat_prep.c
 * @author Pawelec, Skomiał
 * @date Dec 2020
 * @brief File containing declarations of functions, structures and enums for decoding data from keyboard.
 * @ver 0.1
 */
 
 #include "dat_prep.h"
 #define DAT_BUFF_SIZE 10
 static uint8_t idx_of_track[DAT_BUFF_SIZE];
 
 uint8_t decode_keys(void)
 {
	 uint8_t * buff = get_dat_buff();
	 volatile uint8_t idx = 0;
	 for (idx; idx<DAT_BUFF_SIZE; idx++)
	 {
		 if(*(buff + idx) == 0xF0)
		 {
			 
		 }
	 }
	 
 }