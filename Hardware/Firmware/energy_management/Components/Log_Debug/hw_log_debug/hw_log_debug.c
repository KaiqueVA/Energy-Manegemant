/*
 * hw_log_debug.c
 *
 *  Created on: Apr 17, 2025
 *      Author: Kaique
 */
#include "hw_log_debug.h"
#include "usart.h"


//Configure a UART
extern UART_HandleTypeDef huart1;

void hw_log_init(void) {
    // void
}

int __io_putchar(int ch) {
    return hw_log_putchar(ch);
}


int hw_log_putchar(int ch) {
    uint8_t c = ch;
    HAL_UART_Transmit(&huart1, &c, 1, 10);
    return ch;
}
