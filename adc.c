/*****************************************************************************************************
*This file is a part of TM2 project which goal is to create a musical instrument.*
******************************************************************************************************/
/**
 * @file adc.h
 * @author Pawelec, Skomiał
 * @date Dec 2020
 * @brief File containing declarations of functions, structures and enums for ADC module
 * @ver 0.1
 */
 
 #include "adc.h"
 
 uint8_t init_ADC(void)
 {
	uint16_t callibration;
	SIM->SCGC6 |= SIM_SCGC6_ADC0_MASK;          // Dołączenie sygnału zegara do ADC0
	SIM->SCGC5 |= SIM_SCGC5_PORTB_MASK;					// Dołączenie sygnału zegara do portu B
	PORTB->PCR[2] &= ~(uint32_t)(1<<2);										//PTB2 - wejście analogowe, kanał 4
	//ADC0->CFG1 = ADC_CFG1_ADICLK(ADICLK_BUS_2) | ADC_CFG1_ADIV(ADIV_4) | ADC_CFG1_ADLSMP_MASK;	// Zegar wejściowy BUS/2=10.49MHz, zegar ADCK równy 2.62MHz (2621440Hz), długi czas prókowania. Dokumentacja strona 432
	ADC0->CFG2 = ADC_CFG2_ADHSC_MASK;										// Włącz wspomaganie zegara o dużej częstotliwości. Dokumentacja strona 433
	ADC0->SC3  = ADC_SC3_AVGE_MASK | ADC_SC3_AVGS(3);		// Włącz uśrednianie na 32 próbki. Dokumentacja strona 438
	ADC0->SC3 |= ADC_SC3_CAL_MASK;											// Rozpoczęcie kalibracji
	while(ADC0->SC3 & ADC_SC3_CAL_MASK);								// Czekaj na koniec kalibracji
	
	if(ADC0->SC3 & ADC_SC3_CALF_MASK)
	{
	  ADC0->SC3 |= ADC_SC3_CALF_MASK;
	  return(1);																				// Wróć, jeśli błąd kalibracji
	}
	
	callibration = 0x00;
	callibration += ADC0->CLP0;
	callibration += ADC0->CLP1;
	callibration += ADC0->CLP2;
	callibration += ADC0->CLP3;
	callibration += ADC0->CLP4;
	callibration += ADC0->CLPS;
	callibration += ADC0->CLPD;
	callibration = callibration >> 1;
	callibration |= 1<<16;                       // Ustaw najbardziej znaczący bit na 1
	ADC0->PG = ADC_PG_PG(callibration);           // Zapisz w  "plus-side gain calibration register"
	//ADC0->OFS = 0;														// Klaibracja przesunięcia zera (z pomiaru swojego punktu odniesienia - masy)
	ADC0->SC1[0] = ADC_SC1_ADCH(31);						// Zablokuj przetwornik ADC0
	ADC0->CFG2 |= ADC_CFG2_ADHSC_MASK;					// Włącz tryb szybkiej konwersji
	//ADC0->CFG1 = ADC_CFG1_ADICLK(ADICLK_BUS_2) | ADC_CFG1_ADIV(ADIV_1) | ADC_CFG1_ADLSMP_MASK | ADC_CFG1_MODE(MODE_12);	// Zegar ADCK równy 10.49MHz, rozdzielczość 12 bitów, długi czas próbkowania
	ADC0->SC2 &= ~ADC_SC2_ADTRG_MASK; // Upewnienie, że wybrane jest wyzwalanie sprzętowe
	NVIC_ClearPendingIRQ(ADC0_IRQn);
	NVIC_EnableIRQ(ADC0_IRQn);
	return(0);																	// Wróć, jeśli wszystko w porządku

 }
