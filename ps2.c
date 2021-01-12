/*****************************************************************************************************
*This file is a part of TM2 project which goal is to create a musical instrument.*
******************************************************************************************************/
/**
 * @file ps2.c
 * @author Pawelec, Skomial
 * @date Dec 2020
 * @brief File containing definitions for ps2 keyboard.
 * @ver 0.1
 */
 
 
#include "ps2.h"

#define CLK_PIN 6
#define DATA_LINE 7
#define DATA_FRAME_SIZE 11
#define PARITY_BIT_POS 9
#define DATA_BUFFER_SIZE 10

static uint8_t data_frame[DATA_FRAME_SIZE]; // #TODO: Try to enclose this in a structure for readability
static uint8_t data;
static uint8_t bit_idx; // For monitoring current bit of data frame
static uint8_t data_ready; // Marker indicating that whole data frame has been received and data got decoded
static uint8_t data_buffer[DATA_BUFFER_SIZE]; // Buffer for data
static uint8_t data_buffer_offset = 0; // For indexing data buffer

// Data buffer is "round". Because of this, in data preprocessing we have to check special clauses
void dat_buff_handler(void)
{
	if(data_buffer_offset == 0) // Make sure that previously received data is different
	{
		if(*(data_buffer+DATA_BUFFER_SIZE-1) != data) 
		{
			*(data_buffer) = data;
			data_buffer_offset++;
		}
	}
	else
	{
		if(data_buffer_offset<DATA_BUFFER_SIZE)
		{
			if(data != *(data_buffer+data_buffer_offset-1))
			{
			*(data_buffer + data_buffer_offset) = data;
			data_buffer_offset++;
			}
		}
		else data_buffer_offset = 0;
	}
}

uint8_t pow2(uint8_t pow)
{
	if(pow == 0) return 1;
	volatile uint8_t i = 1;
	volatile uint8_t ans = 1;
	for(i; i <= pow; i++)
	{
		ans *= 2;
	}
	return ans;
}

uint8_t chck_if_dat_rdy(void)
{
	return data_ready;
}

uint8_t get_data(void)
{
	return data;
}

void Ps2_comm_init(void)
	{
	SIM->SCGC5 |= SIM_SCGC5_PORTB_MASK; // Connecting clock to PORTB
	// Valid signal on data line occurs on low level of CLK, that's why interrupt is also set to logic zero
	PORTB->PCR[CLK_PIN] |= PORT_PCR_MUX(1) | PORT_PCR_IRQC(8) | PORT_PCR_PE_MASK | PORT_PCR_PS_MASK; // Selecting appropriate pin function, interrupts on logic zero and pullup
	PORTB->PCR[DATA_LINE] |= PORT_PCR_MUX(1) | PORT_PCR_PE_MASK | PORT_PCR_PS_MASK; // Selecting appropriate pin function and pullup
	PORTB->PCR[CLK_PIN] |= PORT_PCR_ISF_MASK; // Resetting interrupt flag
	NVIC_ClearPendingIRQ(PORTB_IRQn);
	NVIC_SetPriority(PORTB_IRQn, 0); // Setting interrupt priority level #TODO - check if priority is correct (should be highest priority)
	NVIC_EnableIRQ(PORTB_IRQn); // Enabling interrupts from PORTB
 }
 
 
void PORTB_IRQHandler(void)
	{
	if(bit_idx == DATA_FRAME_SIZE) // If received whole data frame
	{
		data = 0;
		volatile uint8_t i = 1;
		for (i; i < PARITY_BIT_POS; i++)
		{
			data += data_frame[i] * pow2(i-1); // Decode received data
		}
		dat_buff_handler(); // Save accordingly to buffer
		bit_idx = 0;
		data_ready = 1;
	}
	else // Save incoming bits of transmission
	{
		data_frame[bit_idx] = ((PTB->PDIR) & (1<<DATA_LINE))>>DATA_LINE;
		bit_idx++;
		data_ready = 0;
	}
	PORTB->PCR[CLK_PIN] |= PORT_PCR_ISF_MASK;
 }
uint8_t * get_dat_buff(void)
 {
	 return data_buffer;
 }

 
