/*
 * log_debug.h
 *
 *  Created on: Apr 17, 2025
 *      Author: Kaique
 */

#ifndef LOG_DEBUG_H_
#define LOG_DEBUG_H_

#include <stdio.h>

// ======== Configurações ======== //
#define LOG_ENABLE       1
#define LOG_USE_PREFIX   1
#define LOG_COLOR_ENABLE 1

// ======== Interface ======== //
void log_printf(const char *prefix, const char *fmt, ...);

// ======== Macros de uso ======== //
#if LOG_ENABLE

#define LOG_INFO(fmt, ...)   log_printf("INFO", fmt, ##__VA_ARGS__)
#define LOG_WARN(fmt, ...)   log_printf("WARN", fmt, ##__VA_ARGS__)
#define LOG_ERROR(fmt, ...)  log_printf("ERROR", fmt, ##__VA_ARGS__)
#define LOG_RAW(fmt, ...)    log_printf(NULL, fmt, ##__VA_ARGS__)

#else

#define LOG_INFO(fmt, ...)
#define LOG_WARN(fmt, ...)
#define LOG_ERROR(fmt, ...)
#define LOG_RAW(fmt, ...)

#endif


#endif /* LOG_DEBUG_H_ */
