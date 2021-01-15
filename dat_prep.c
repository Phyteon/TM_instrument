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
 #define BASE_SHIFT (uint8_t)0x15
 
 static uint8_t idx_of_track_arr[DAT_BUFF_SIZE];
 static uint8_t key_make_code[DAT_BUFF_SIZE];
 static uint8_t stack_ptr; // Used for idx stack operation
 static uint8_t track_available_idx_stack[DAT_BUFF_SIZE]; // Used for storing index of recently released key in idx_of_track array
 
 // #TODO: make sure that make and break codes of unused keys do not interfere with the rest of the keys
 // #TODO: delete break code data from array => Done
 
 void init_array(void)
 {
	 volatile uint8_t i = 0;
	 for(i; i< DAT_BUFF_SIZE; i++)
	 {
		 idx_of_track_arr[i] = 0xFF; // 0xFF indicates that given array position is not used
		 key_make_code[i] = 0xFF; // Same as above (make codes equal or above 0x60 are not used)
		 track_available_idx_stack[i] = i; // Pushing available spots of array on stack
	 }
	 stack_ptr = DAT_BUFF_SIZE - 1; // pesudo pointer to stack top
 }
 
 uint8_t get_idx_from_stack(void)
 {
	 volatile uint8_t temp = track_available_idx_stack[stack_ptr];
	 if(stack_ptr > 0) stack_ptr--; // Point to next available index
	 return temp;
 }
 
 void push_idx_to_stack(uint8_t index)
 {
	 if(stack_ptr<(DAT_BUFF_SIZE))
	 stack_ptr++;
	 track_available_idx_stack[stack_ptr] = index;
 }
 
 uint8_t *get_tune_idx_arr(void)
 {
	 return idx_of_track_arr;
 }
 
 void decode_keys(void)
 {
	 reset_data_rdy();
	 uint8_t * buff = get_dat_buff(); // Getting pointer to data buffer
	 volatile uint8_t idx = 0;
	 for (idx; idx<DAT_BUFF_SIZE; idx++) // Iterating over data buffer
	 {
		 volatile uint8_t buf_read_val = *(buff + idx); // Is it possible that during this function buff array changes? !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
		 if((buf_read_val > 0x0F) && (buf_read_val < 0x60)) // Checking if received make code is in designated scope
				{
					volatile uint8_t idx_of_track = 0xFF; // Can't show up on watch 1. Too many volatile variables?
					volatile uint8_t shift = buf_read_val & 0xF0; // Zeroing lower nibble
					shift = shift >> 4; // Shifting older nibble to younger nibble
					shift -= 1;
					shift *= 2; // Final shift coefficient for array idx
					idx_of_track = buf_read_val - BASE_SHIFT - shift; // Calculate the final idx
					if(idx+1 < DAT_BUFF_SIZE) // For ensuring correct scope of indices in array
					{
						if(buff[idx + 1] != 0xF0) // Check if read data is not break code
						{
							volatile uint8_t temp = get_idx_from_stack(); // Get available idx of idx_trac_arr from stack
							idx_of_track_arr[temp] = idx_of_track; // Save idx of related music
							key_make_code[temp] = buf_read_val; // Copying make code for reference for quick delete of related music idx
							//buff[idx] = 0; // Deleting data from data buffer - Cant do that beacuse break code won't be read correctly !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
						}
						else // If read data is break code
						{
							buff[idx] = 0; // Deleting data from data buffer
							buff[idx + 1]= 0; // Deleting brake code identifier
							volatile uint8_t k = 0;
							for(k; k<DAT_BUFF_SIZE; k++) // Iterating over quick reference make code array
							{
								if(key_make_code[k] == buf_read_val)
								{
									idx_of_track_arr[k] = 0xFF; // Writing 255 to indicate that idx related key was released
									key_make_code[k] = 0xFF; // Deleting associated make code from quick reference make code array
									push_idx_to_stack(k);
									break; // Not iterating further through quick reference make code array
								}
							}
						}
					}
					else // For ensuring correct scope of indices in array
					{
						if(*(buff) != 0xF0) //  Check if read data is not break code
						{
							volatile uint8_t temp = get_idx_from_stack();
							idx_of_track_arr[temp] = idx_of_track; // Save idx of related music
							key_make_code[temp] = buf_read_val; // Copying make code for reference for quick delete of related music idx
							buff[idx] = 0; // Deleting data from data buffer
						}
						else if(*(buff) == 0xF0) // Check if read data is break code
						{
							buff[idx] = 0; // Deleting data from data buffer
							buff[idx + 1]= 0; // Deleting brake code identifier
							volatile uint8_t k = 0;
							for(k; k<DAT_BUFF_SIZE; k++) // Iterating over quick reference make code array
							{
								if(key_make_code[k] == buf_read_val)
								{
									idx_of_track_arr[k] = 0xFF; // Writing 255 to indicate that idx related key was released
									key_make_code[k] = 0xFF; // Deleting associated make code from quick reference make code array
									push_idx_to_stack(k);
									break; // Not iterating further through quick reference make code array
								}
							}
						}
					}
				}
		}
 }

