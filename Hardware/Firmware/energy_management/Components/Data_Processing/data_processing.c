/*
 * data_processing.c
 *
 *  Created on: Apr 25, 2025
 *      Author: Kaique
 */

#include "data_processing.h"
#include "log_debug.h"
#include <stdio.h>
#include <stdlib.h>


void data_processing(adc_data_t *adc_data, float *data)
{

	data[0] = adc_data->vAVG;
	data[1] = adc_data->iAVG;
	data[2] = adc_data->pAparente;
	data[3] = adc_data->pAtiva;
	data[4] = adc_data->pReativa;
	data[5] = adc_data->fatorPotencia;



	LOG_INFO("Tensão eficaz: %.2f V | Corrente eficaz: %.2f A | Potencia Aparente %.2f VA | Potencia Ativa: %.2f W | Potencia Reativa %.2f | Fator de Potencia %.2f",
			adc_data->vEficaz, adc_data->iEficaz, adc_data->pAparente, adc_data->pAtiva, adc_data->pReativa, adc_data->fatorPotencia);
}
