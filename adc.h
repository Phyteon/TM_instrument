/*****************************************************************************************************
*This file is a part of TM2 project which goal is to create a musical instrument.*
******************************************************************************************************/
/**
 * @file adc.c
 * @author Pawelec, Skomiał
 * @date Dec 2020
 * @brief File containing declarations of functions, structures and enums for ADC module
 * @ver 0.1
 */
 #include "MKL05Z4.h"
 #ifndef ADC_H
 #define ADC_H
 /**
 * @brief This function initialises ADC module, returns non zero value if init failed
 */
 uint8_t init_ADC(void);
 
 /**
 * @brief This function serves the purpose of a software trigger
 */
 void trigger_measure(void);
 
  /**
 * @brief This function returns measured value if the conversion was completed
 */
 uint8_t return_measurement(void);
 
 #endif /* ADC_H */
