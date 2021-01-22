/*****************************************************************************************************
*This file is a part of TM2 project which goal is to create a musical instrument.*
******************************************************************************************************/
/**
 * @file dac.h
 * @author Pawelec, Skomiał
 * @date Dec 2020
 * @brief File containing enums, structures and declarations for DAC module.
 * @ver 0.1
 */
 
 
#include "MKL05Z4.h"

#ifndef DAC_H
#define DAC_H


/**
 * @brief Setup operation of 12-bit DAC converter
 */
void Init_DAC(void);

/**
 * @brief Load data to be converted to DAC register
 */
void convert(uint8_t, uint8_t);



#endif /* DAC_H */
