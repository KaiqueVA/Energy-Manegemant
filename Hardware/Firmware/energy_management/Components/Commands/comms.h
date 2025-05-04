#ifndef COMMS_H
#define COMMS_H

// =============================================
// Módulo: comms.h
// Descrição: Comunicação genérica com suporte a comandos AT
// =============================================


// ========== Includes ========== //
#include <stdint.h>
#include <stdbool.h>


// ========== Configurações ========== //



// ========== Enumerações ========== //
typedef enum {
    COMMS_STATE_IDLE,
    COMMS_STATE_SENDING,
    COMMS_STATE_WAITING_RESPONSE,
    COMMS_STATE_SUCCESS,
    COMMS_STATE_ERROR
} COMMS_State_t;

typedef enum
{
	AT_INIT,
	AT_SEND,
	AT_STATUS,
	AT_RESET,
} COMMS_AT_Command_t;


// ========== Estruturas ========== //



// ========== Interface Pública ========== //
void COMMS_Init(COMMS_State_t *state);
bool COMMS_Process(COMMS_AT_Command_t *command, COMMS_State_t *state);

bool COMMS_SendCommand(COMMS_AT_Command_t *command, float *ptr_data, uint16_t ptr_size);
bool COMMS_SendCommandAndGetResponse(const char *command, char *response_buffer, uint16_t response_size);


#endif // COMMS_H
