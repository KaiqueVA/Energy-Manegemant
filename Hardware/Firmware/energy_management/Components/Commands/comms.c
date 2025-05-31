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
char buffer[12] = "";
uint8_t flag_receive = 0;
uint8_t flag_send = 0;

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

COMMS_ParsedCmd_t COMMS_ParseReceivedBuffer(void)
{
    COMMS_ParsedCmd_t result = COMMS_CMD_NONE;

    if (strstr(buffer, "AT+RELE_ON") != NULL)
    {
    	memset(buffer, 0, sizeof(buffer));
        HW_COMMS_Transmit((uint8_t *)"OK\r\n", 4);
        result = COMMS_CMD_RELE_ON;
        memset(buffer, 0, sizeof(buffer));

    }
    else if (strstr(buffer, "AT+RELE_OFF") != NULL)
    {
    	memset(buffer, 0, sizeof(buffer));
        HW_COMMS_Transmit((uint8_t *)"OK\r\n", 4);
        result = COMMS_CMD_RELE_OFF;

    }
    else if (strstr(buffer, "OK\r\n") != NULL)
    {
        result = COMMS_CMD_OK;
        memset(buffer, 0, sizeof(buffer));
    }

    flag_receive = 0;
    return result;
}

// ========== Funções Públicas ========== //
void COMMS_Init(COMMS_State_t *state)
{
	uint16_t prev_tick = HAL_GetTick();
	HW_COMMS_Transmit((uint8_t*)"AT+INIT\r\n", 9);
	HAL_UART_Receive_DMA(&huart3, (uint8_t*)buffer, 12);
	while(1)
	{
		if(HAL_GetTick() - prev_tick > 1000)
		{
			HW_COMMS_Transmit((uint8_t*)"AT+INIT\r\n", 9);
			prev_tick = HAL_GetTick();
		}
		if(strstr((char*)buffer, "OK") != NULL)
		{
			memset(buffer, 0, sizeof(buffer));
			break;
		}
	}
	*state = COMMS_STATE_IDLE;
}


bool COMMS_Process(COMMS_AT_Command_t *command, COMMS_State_t *state)
{
	static COMMS_ParsedCmd_t parsed = COMMS_CMD_NONE;
	*state = COMMS_STATE_IDLE;

	if(flag_receive == 1)
	{
		parsed = COMMS_ParseReceivedBuffer();

	}


	switch(*command)
	{
	case AT_SEND:
		if(flag_send == 0)
		{
			HW_COMMS_Transmit((uint8_t*)"AT+SEND\r\n", 9);
			HW_COMMS_StartTimeout(250);
			flag_send = 1;
			break;
		}
		if(parsed == COMMS_CMD_OK){
			HW_COMMS_StopTimeout();
			COMMS_SendData();
			*command = AT_STATUS;
			flag_send = 0;
			return true;
		}
		if(HW_COMMS_TimeoutExpired())
		{
			flag_send = 1;
			return false;

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
		flag_send = 0;
		data = ptr_data;
		size = ptr_size;
		break;

	default:
		break;
	}
}

