// =============================================
// Módulo: comms.c
// Descrição: Implementação da comunicação genérica com suporte a comandos AT
// =============================================


// ========== Includes ========== //

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "comms.h"
#include "hw_comms.h"
#include "usart.h"



// ========== Configurações ========== //



// ========== Variáveis Internas ========== //

float *data = NULL;
uint16_t size = 0;
char buffer[4] = "";
uint8_t flag_receive = 0;

// ========== Funções Internas ========== //

bool COMMS_SendData()
{

		for(uint16_t i = 0; i < 6; i++)
		{
			uint8_t str_size = snprintf(NULL, 0, "AT+DATA_%i=%.2f\r\n", i, data[i]);
			char *str = (char*)malloc(str_size + 1);
			if(str == NULL)
			{
				return false;
			}
			snprintf(str, str_size + 1, "AT+DATA_%i=%.2f\r\n", i, data[i]);
			HW_COMMS_Transmit((uint8_t*)str, str_size);
			HAL_Delay(10);
			free(str);
		}
		return true;
}

// ========== Funções Públicas ========== //
void COMMS_Init(COMMS_State_t *state)
{
	HW_COMMS_Transmit("AT+INIT\r\n", 9);
	while(1)
	{
		HAL_UART_Receive_DMA(&huart1, (uint8_t*)buffer, 4);
		if(strstr((char*)buffer, "OK") != NULL)
		{
			break;
		}
	}
	*state = COMMS_STATE_IDLE;
}

uint8_t test = 10;

bool COMMS_Process(COMMS_AT_Command_t *command, COMMS_State_t *state)
{
	static uint8_t flag_send = 0;
	*state = COMMS_STATE_IDLE;
	switch(*command)
	{
	case AT_INIT:
		//HW_COMMS_Transmit("AT+INIT\r\n", 9);
		break;
	case AT_SEND:
		if(flag_send == 0)
		{

			HAL_UART_Receive_DMA(&huart1, (uint8_t*)buffer, size);
			HW_COMMS_Transmit("AT+SEND\r\n", 9);



			flag_send = 1;
			break;
		}
		if(strstr((char*)buffer, "OK") != NULL){
			COMMS_SendData();
			*command = AT_STATUS;
			flag_send = 0;
			return true;
		}


		break;
	default:
		return false;
		break;
	}
}


bool COMMS_SendCommand(COMMS_AT_Command_t *command, float *ptr_data, uint16_t ptr_size)
{
	switch(*command)
	{
	case AT_SEND:
		data = ptr_data;
		size = ptr_size;
		break;

	default:
		break;
	}
}

