/*****************************************************************************************************
*This file is a part of TM2 project which goal is to create a musical instrument.*
******************************************************************************************************/
/**
 * @file ftfa.c
 * @author Pawelec, Skomial
 * @date Dec 2020
 * @brief File containing definitions for FTFA.
 * @ver 0.1
 */
 
#include "ftfa.h"
 
void Read_tone(void){

	FTFA->FSTAT |= FTFA_FSTAT_CCIF(0);	// Flash command in progress
		
	if (FTFA->FSTAT != 0){			// Access error or protection detected from previous commands
		FTFA->FSTAT = 0x30;	
	}
	
	// Todo: FCCOB registers communication (as suggested in 27.4.10)
	
	
	FTFA->FSTAT = 0x80;		// Flash command is completed, set no errors
	
}
 
 
 
 
 
