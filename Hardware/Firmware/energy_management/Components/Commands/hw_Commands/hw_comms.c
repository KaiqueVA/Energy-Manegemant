#include "hw_comms.h"
#include "stm32f1xx_hal.h"
#include "usart.h" // UART handle (ex: huart1)
#include "tim.h"   // TIM4 handle (ex: htim4)

static volatile bool hw_timeout_flag = false;



//HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart) {
//	if (huart->Instance == USART1) {
//		flag_receive = 1;
//	}
//}

bool HW_COMMS_Transmit(uint8_t *data, uint16_t length) {
    return (HAL_UART_Transmit(&huart1, data, length, 1000) == HAL_OK);
}

bool HW_COMMS_Receive(uint8_t *buffer, uint16_t length) {
    return (HAL_UART_Receive(&huart1, buffer, length, 1000) == HAL_OK);

}

void HW_COMMS_Delay(uint32_t ms) {
    HAL_Delay(ms);
}

void HW_COMMS_StartTimeout(uint32_t timeout_ms) {
    hw_timeout_flag = false;
    __HAL_TIM_SET_COUNTER(&htim4, 0);
    __HAL_TIM_SET_AUTORELOAD(&htim4, timeout_ms);
    HAL_TIM_Base_Start_IT(&htim4);
}

bool HW_COMMS_TimeoutExpired(void) {
    return hw_timeout_flag;
}

void HW_COMMS_TimerIRQHandler(void) {
    hw_timeout_flag = true;
    HAL_TIM_Base_Stop_IT(&htim4);
}
