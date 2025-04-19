/*
 * adc_reader.h
 *
 *  Created on: Apr 18, 2025
 *      Author: Kaique
 */

#ifndef ENERGY_ENGINE_ADC_READER_H_
#define ENERGY_ENGINE_ADC_READER_H_


// ======== Includes ======== //
#include "adc.h"


// ======== Configurações ======== //


// ======== Variáveis Externas ======== //

extern uint8_t flag_adc_complete;

// ======== Interface ======== //

void adc_reader_init(ADC_HandleTypeDef* hadc);
void adc_start_read_dma(ADC_HandleTypeDef* hadc, uint32_t* buffer, uint32_t size);



#endif /* ENERGY_ENGINE_ADC_READER_H_ */
