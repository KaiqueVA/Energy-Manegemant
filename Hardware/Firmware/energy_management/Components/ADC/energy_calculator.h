#ifndef ENERGY_CALCULATOR_H_
#define ENERGY_CALCULATOR_H_

// =============================================
// Módulo: energy_calculator.h
// Descrição: [Processar e Calcular dados de energia]
// =============================================


// ========== Includes ========== //

// ========== Configurações ========== //


// ========== Enumerações ========== //


// ========== Estruturas ========== //

typedef struct
{
	ADC_HandleTypeDef* hadc;
	uint16_t *buffer;
	uint32_t size;

} energy_engine_t;

typedef struct
{
	float calI; //Calibração do sensor corrente
	float calV; //Calibração do sensor de tensão

	float offsetI; //Offset do sensor de corrente
	float offsetV; //Offset do sensor de tensão

} adc_calibration_t;

typedef struct
{
	float vData[512];
	float iData[512];

	float vEficaz;
	float vMax;
	float vMin;

	float iEficaz;
	float iMax;
	float iMin;

	float pAparente;
	float pAtiva;
	float pReativa;
	float fatorPotencia;

} adc_data_t;

// ========== Interface Pública ========== //


void init_energy_engine(energy_engine_t *engine);

void set_energy_calibration(adc_calibration_t *calc, float calI, float calV, float offsetI, float offsetV);

void adc_buffer_separator(adc_data_t *data, adc_calibration_t *calc, uint16_t *buffer, uint16_t size);

float rms_calculator(float *sinal, uint16_t size);

//mudar para a pasta da maquina de estados
int state_energy_calculator(adc_data_t *data, adc_calibration_t *calc, uint16_t size);

//mudar para a pasta da maquina de estados
int state_adc_reader(energy_engine_t *data);



#endif /* ENERGY_CALCULATOR_H_ */
