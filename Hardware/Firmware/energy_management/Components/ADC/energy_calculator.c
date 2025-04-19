// =============================================
// Módulo: energy_calculator.h
// Descrição: [Processar e Calcular dados de energia]
// =============================================


// ========== Includes ========== //

#include <hw_adc_reader.h>
#include "energy_calculator.h"
#include "math.h"
// ========== Variáveis Internas ========== //

extern uint8_t flag_time_out;
// ========== Funções Internas ========== //


// ========== Funções Públicas ========== //


void init_energy_engine(energy_engine_t *engine)
{
	adc_reader_init(engine->hadc);
}



void set_energy_calibration(adc_calibration_t *calc, float calI, float calV, float offsetI, float offsetV)
{
	calc->calI = calI;//	float calI = 11.5; //Calibração do sensor corrente
	calc->calV = calV;//	float calV = 460; //Calibração do sensor de tensão
	calc->offsetI = offsetI;//	float offsetI = 1.64; //Offset do sensor de corrente
	calc->offsetV = offsetV;//	float offsetV = 1.66; //Offset do sensor de tensão
}

void adc_buffer_separator(adc_data_t *data, adc_calibration_t *calc, uint16_t *buffer, uint16_t size)
{
	float v_data[512], i_data[512];
	for(int i = 0; i < size; i++)
	{

		v_data[i] = buffer[i * 2];
		i_data[i] = buffer[i * 2 + 1];

		data->vData[i] = v_data[i];
		data->vData[i] = (((v_data[i])*(3.3/4095.0)) - calc->offsetV) * calc->calV;

		data->iData[i] = i_data[i];
		data->iData[i] = ((i_data[i]*(3.3/4095.0))- calc->offsetI) * calc->calI;

	}

}

float rms_calculator(float *sinal, uint16_t size)
{
	float integral = 0;
	float rms = 0;

	int y;
	for(y = 0; y < size; y++)
	{
		integral += (sinal[y] * sinal[y]);
	}

	integral /= size;
	rms = sqrt(integral);
	return rms;
}

int state_adc_reader(energy_engine_t *data)
{

	adc_start_read_dma(data->hadc, (uint32_t*)data->buffer, data->size*2);
	//return IDLE;
	return 1;
}

int state_energy_calculator(adc_data_t *data, adc_calibration_t *calc, uint16_t size)
{	static uint16_t count = 1;
	float vEficaz = 0;
	float iEficaz = 0;
	data->pAparente = 0;
	data->pAtiva = 0;
	data->pReativa = 0;
	data->fatorPotencia = 0;


	vEficaz = rms_calculator(data->vData, 512);
	iEficaz = rms_calculator(data->iData, 512);

	if(iEficaz < 0.21)
		iEficaz = 0;

	if(count == 1){
		data->vEficaz = 0;
		data->iEficaz = 0;
		data->vMax = 0;
		data->vMin = 0;
		data->iMax = 0;
		data->iMin = 0;
	}

	data->vEficaz += vEficaz;
	data->iEficaz += iEficaz;



	if(data->vMax < vEficaz)
		data->vMax = vEficaz;
	if(data->vMin > vEficaz)
		data->vMin = vEficaz;

	if(data->iMax < iEficaz)
		data->iMax = iEficaz;
	if(data->iMin > iEficaz)
		data->iMin = iEficaz;


	count++;

	if(flag_time_out == 1)
	{
		data->vEficaz -= data->vMax;
		data->iEficaz -= data->iMax;
		data->vEficaz = data->vEficaz / (count - 2);
		data->iEficaz = data->iEficaz / (count - 2);


		data->pAparente = data->vEficaz * data->iEficaz;
		data->pAtiva = data->pAparente * data->fatorPotencia;
		data->pReativa = sqrt((data->pAparente * data->pAparente) - (data->pAtiva * data->pAtiva));
		count = 1;
		flag_time_out = 0;

		//return DATA_PROCESSING;
	}
	//return IDLE;
	return 1;
}
