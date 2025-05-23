/*
 * hw_comms.h
 *
 *  Created on: Apr 26, 2025
 *      Author: Kaique
 */

#ifndef CHW_COMMS_H_
#define HW_COMMS_H_

#include <stdint.h>
#include <stdbool.h>


extern uint8_t flag_timeout;
extern uint8_t flag_receive;

bool HW_COMMS_Transmit(uint8_t *data, uint16_t length);
bool HW_COMMS_Receive(uint8_t *buffer, uint16_t length);

void HW_COMMS_StartTimeout(uint32_t timeout_ms);
void HW_COMMS_StopTimeout(void);
bool HW_COMMS_TimeoutExpired(void);

#endif /* HW_COMMS_H_ */
