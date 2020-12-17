/*****************************************************************************************************
*This file is a part of TM2 project which goal is to create a musical instrument.*
******************************************************************************************************/
/**
 * @file const_dat_file.h
 * @author Pawelec, Skomiał
 * @date Dec 2020
 * @brief File containing constant data for read only.
 * @ver 0.1
 */
 
 #include "MKL05Z4.h"
 #define NR_OF_KEYS 49
 
 #ifndef CONST_DAT_FILE_H
 #define CONST_DAT_FILE_H
 static const uint8_t make_codes[NR_OF_KEYS] = 
 {0x76, // ESC
	 0x05, // F1
	 0x06, // F2
	 0x04, // F3
	 0x0C, // F4
	 0x03, // F5
	 0x0B, // F6
	 0x83, // F7
	 0x0A, // F8
	 0x01, // F9
	 0x09, // F10
	 0x78, // F11
	 0x07, // F12
	 0x0E, // `
	 0x16, // 1
	 0x1E, // 2
	 0x26, // 3
	 0x25, // 4
	 0x2E, // 5
	 0x36, // 6
	 0x3D, // 7
	 0x3E, // 8
	 0x46, // 9
	 0x45, // 0
	 0x4E, // -
	 0x55, // =
	 0x66, // Backspace
	 0x0D, // Tab
	 0x15, // Q
	 0x1D, // W
	 0x24, // E
	 0x2D, // R
	 0x2C, // T
	 0x35, // Y
	 0x3C, // U
	 0x43, // I
	 0x44, // O
	 0x4D, // P
	 0x54, // [
	 0x5B, // ]
	 0x5D, // \*
   0x58, // Caps Lock
	 0x1C, // A
   0x1B, // S
   0x23, // D
   0x2B, // F
   0x34, // G
   0x33, // H
   0x3B // J
 };
 // Other keys will be added, the order of the make codes should be adjusted so that the most used keys are first
 #endif /* CONST_DAT_FILE_H */
 