/*****************************************************************************************************
*This file is a part of TM2 project which goal is to create a musical instrument.*
******************************************************************************************************/
/**
 * @file dat_prep.h
 * @author Pawelec, Skomiał
 * @date Dec 2020
 * @brief File containing declarations of functions, structures and enums for decoding data from keyboard.
 * @ver 0.1
 */
 

 #ifndef DAT_PREP_H
 #define DAT_PREP_H
 #include "const_dat_file.h"
 #include "ps2.h"
 /**
	* @brief This function decodes data stored in data buffer
 */
 void decode_keys(void);
 
 /**
 * @brief This function initialises heather file specific arrays, to be used once
 */
 void init_array(void);
 /**
 * @brief This function returns available array idx from stack
 */
 uint8_t get_idx_from_stack(void);
 /**
 * @brief This function pushes released idx to stack
 */
 void push_idx_to_stack(uint8_t);
 /**
 * @brief This function returns pointer to array containing tune idx
 */
 uint8_t * get_tune_idx_arr(void);
 
 #endif /* DAT_PREP_H */
