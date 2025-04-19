/*
 * adc_reader.c
 *
 *  Created on: Apr 18, 2025
 *      Author: Kaique
 */
#include <hw_adc_reader.h>

void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef *hadc)
{
    if (hadc->Instance == ADC1)
    {
    	HAL_ADC_Stop_DMA(hadc);
    	flag_adc_complete = 1;
    }
}


void adc_reader_init(ADC_HandleTypeDef* hadc)
{
	HAL_ADC_Stop(hadc);
	HAL_ADCEx_Calibration_Start(hadc);
	HAL_ADC_Start(hadc);
}

void adc_start_read_dma(ADC_HandleTypeDef* hadc, uint32_t* buffer, uint32_t size)
{

	HAL_ADC_Start_DMA(hadc, buffer, size);
}


//Analisar ir para o
