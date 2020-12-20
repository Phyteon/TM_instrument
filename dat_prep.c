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
 static uint8_t key_make_code[DAT_BUFF_SIZE];
 static uint8_t array_idx = 0;
 static uint8_t recently_released; // Used for storing index of recently released key in idx_of_track array ?????
 
 // #TODO: make sure that make and break codes of unused keys do not interfere with the rest of the keys
 // #TODO: fix indexing of idx_of_track array !!!!!!!!!!!!!
 // #TODO: delete break code data from array => Done
 
 uint8_t *decode_keys(void)
 {
	 uint8_t * buff = get_dat_buff(); // Getting pointer to data buffer
	 volatile uint8_t idx = 0;
	 for (idx; idx<DAT_BUFF_SIZE; idx++) // Iterating over data buffer
	 {
			volatile uint8_t i = 0;
			for(i; i < NR_OF_KEYS; i++) // Iterating over saved make codes of keys
			{
				if(idx+1 < DAT_BUFF_SIZE) // For ensuring correct scope of indices in array
				{
					if((*(make_codes + i) == *(buff + idx)) && (*(buff + idx + 1) != 0xF0)) // Check if read data is not break code
					{
						*(idx_of_track + array_idx) = i; // Save idx of related music
						*(key_make_code + array_idx) = *(buff + idx); // Copying make code for reference for quick delete of related music idx
						array_idx++;
						*(buff + idx) = 0; // Deleting data from data buffer
						break; // Not iterating further through key make codes
					}
					else if((*(make_codes + i) == *(buff + idx)) && (*(buff + idx + 1) == 0xF0)) // Check if read data is break code
					{
						*(buff + idx) = 0; // Deleting data from data buffer
						*(buff + idx + 1) = 0; // Deleting brake code identifier
						volatile uint8_t k = 0;
						for(k; k<DAT_BUFF_SIZE; k++) // Iterating over quick reference make code array
						{
							if(*(key_make_code+k) == *(make_codes + i))
							{
								*(idx_of_track + k) = 0xFF; // Writing 255 to indicate that idx related key was released
								*(key_make_code + k) = 0; // Deleting associated make code from quick reference make code array
								//recently_released = k;
								break; // Not iterating further through quick reference make code array
							}
						}
					}
				}
				else // For ensuring correct scope of indices in array
				{
					if((*(make_codes + i) == *(buff + idx)) && (*(buff) != 0xF0)) //  Check if read data is not break code
					{
						*(idx_of_track + array_idx) = i; // Save idx of related music
						*(key_make_code + array_idx) = *(buff + idx); // Copying make code for reference for quick delete of related music idx
						array_idx++;
						*(buff + idx) = 0; // Deleting data from data buffer
						break; // Not iterating further through key make codes
					}
					else if((*(make_codes + i) == *(buff + idx)) && (*(buff) == 0xF0)) // Check if read data is break code
					{
						*(buff + idx) = 0; // Deleting data from data buffer
						*(buff) = 0; // Deleting brake code identifier
						volatile uint8_t k = 0;
						for(k; k<DAT_BUFF_SIZE; k++) // Iterating over quick reference make code array
						{
							if(*(key_make_code+k) == *(make_codes + i))
							{
								*(idx_of_track + k) = 0xFF; // Writing 255 to indicate that idx related key was released
								*(key_make_code + k) = 0; // Deleting associated make code from quick reference make code array
								//recently_released = k;
								break; // Not iterating further through quick reference make code array
							}
						}
					}
				}
			}
	}
	 return idx_of_track;
 }
