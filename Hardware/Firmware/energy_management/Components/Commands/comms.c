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
        HW_COMMS_Transmit((uint8_t *)"OK\r\n", 4);
        result = COMMS_CMD_RELE_ON;

    }
    else if (strstr(buffer, "AT+RELE_OFF") != NULL)
    {
        HW_COMMS_Transmit((uint8_t *)"OK\r\n", 4);
        result = COMMS_CMD_RELE_OFF;
    }
    else if (strstr(buffer, "OK\r\n") != NULL)
    {
        result = COMMS_CMD_OK;
    }

    flag_receive = 0;
    //memset(buffer, 0, sizeof(buffer));
    return result;
}

// ========== Funções Públicas ========== //
void COMMS_Init(COMMS_State_t *state)
{
	HW_COMMS_Transmit((uint8_t*)"AT+INIT\r\n", 9);
	while(1)
	{
		HAL_UART_Receive_DMA(&huart1, (uint8_t*)buffer, 12);
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
	static uint8_t flag_send = 0;
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
			flag_send = 1;
			break;
		}
		if(parsed == COMMS_CMD_OK){
			COMMS_SendData();
			*command = AT_STATUS;
			flag_send = 0;
			return true;
		}
		if(HW_COMMS_TimeoutExpired())
		{
			flag_send = 1;
			break;
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
		data = ptr_data;
		size = ptr_size;
		break;

	default:
		break;
	}
}

