/*****************************************************************************************************
*This file is a part of TM2 project which goal is to create a musical instrument.*
******************************************************************************************************/
/**
 * @file dac.h
 * @author Pawelec, Skomiał
 * @date Dec 2020
 * @brief File containing enums, structures and declarations for PIT timer
 * @ver 0.1
 */
 
 
 #include "dsp.h"
 
 #ifndef PIT_H
 #define PIT_H

 /**
 * @brief This function initalises PIT timer
 */
 void PIT_init(void);
 /**
 * @brief Prototype of interrupt request routine
 */
 void PIT_IRQHandler(void);
 
 
 #endif /* PIT_H */
