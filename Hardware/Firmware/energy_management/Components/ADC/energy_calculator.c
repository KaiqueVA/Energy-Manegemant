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

#define NCoef 2
float iir(float NewSample) {
    float ACoef[NCoef+1] = {
        0.09024282337497788200,
        0.18048564674995576000,
        0.09024282337497788200
    };

    float BCoef[NCoef+1] = {
        1.00000000000000000000,
        -0.98923277241909324000,
        0.35020406031482593000
    };

    static float y[NCoef+1]; //output samples
    static float x[NCoef+1]; //input samples
    int n;

    //shift the old samples
    for(n=NCoef; n>0; n--) {
       x[n] = x[n-1];
       y[n] = y[n-1];
    }

    //Calculate the new output
    x[0] = NewSample;
    y[0] = ACoef[0] * x[0];
    for(n=1; n<=NCoef; n++)
        y[0] += ACoef[n] * x[n] - BCoef[n] * y[n];

    return y[0];
}



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

	for(int j = 0; j < 8; j++)
	{

	}


	for(int i = 0; i < size; i++)
	{

		v_data[i] = buffer[i * 2];
		i_data[i] = buffer[i * 2 + 1];
		//i_data[i] = iir(i_data[i]); // IIR filter temporarily disabled for testing raw ADC data processing.

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

	data->vEficaz = rms_calculator(data->vData, 512);
	data->iEficaz = rms_calculator(data->iData, 512);

	if(data->iEficaz < 0.21)
		data->iEficaz = 0.0;

	if(count == 1){
		data->vAVG = 0;
		data->iAVG = 0;
		data->vMax = 0;
		data->vMin = data->vEficaz;
		data->iMax = 0;
		data->iMin = data->iEficaz;
		data->pAparente = 0;
		data->pAtiva = 0;
		data->pReativa = 0;
		data->fatorPotencia = 0;
	}

	data->vAVG += data->vEficaz;
	data->iAVG += data->iEficaz;



	if(data->vMax < data->vEficaz)
		data->vMax = data->vEficaz;
	if(data->vMin > data->vEficaz)
		data->vMin = data->vEficaz;

	if(data->iMax < data->iEficaz)
		data->iMax = data->iEficaz;
	if(data->iMin > data->iEficaz)
		data->iMin = data->iEficaz;


	count++;

	if(flag_time_out == 1)
	{
		data->vAVG -= data->vMax;
		data->iAVG -= data->iMax;
		data->vAVG = data->vAVG / (count - 2);
		data->iAVG = data->iAVG / (count - 2);


		data->pAparente = data->vAVG * data->iAVG;
		data->fatorPotencia = 0.9;
		data->pAtiva = data->pAparente * data->fatorPotencia;
		data->pReativa = sqrt((data->pAparente * data->pAparente) - (data->pAtiva * data->pAtiva));
		count = 1;
		flag_time_out = 0;

		//return DATA_PROCESSING;
	}
	//return IDLE;
	return 1;
}


