/*
 * hw_log_debug.h
 *
 *  Created on: Apr 17, 2025
 *      Author: Kaique
 */

#ifndef HW_LOG_DEBUG_H_
#define HW_LOG_DEBUG_H_

#ifdef __cplusplus
extern "C" {
#endif

void hw_log_init(void);
int hw_log_putchar(int ch);  // usado internamente pelo printf

#ifdef __cplusplus
}
#endif



#endif /* HW_LOG_DEBUG_H_ */
