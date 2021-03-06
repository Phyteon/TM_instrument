/*****************************************************************************************************
*This file is a part of TM2 project which goal is to create a musical instrument.*
******************************************************************************************************/
/**
 * @file dsp.h
 * @author Pawelec, Skomiał
 * @date Dec 2020
 * @brief File containing declarations of functions, structures and enums for final data prep for DAC
 * @ver 0.1
 */
 
 
 #include "dat_prep.h"
 #include "dac.h"

 #ifndef DSP_H
 #define DSP_H

 /**
 * @brief This function adds samples before sending them to DAC
 */
 void assemble_samples(uint8_t*);
  /**
 * @brief This function returns value of the sample_counter
 */
 uint16_t get_sample_counter(void);
  /**
 * @brief This function sets the value of sample_counter
 */
 void set_sample_counter(uint16_t);
  /**
 * @brief This function normalises sound level to a 12-bit unsigned int
 */
 uint16_t normalise(uint16_t, uint8_t);
 
#endif /* DSP_H */
