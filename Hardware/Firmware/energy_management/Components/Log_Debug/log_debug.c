/*
 * log_debug.c
 *
 *  Created on: Apr 17, 2025
 *      Author: Kaique
 */
#include "log_debug.h"
#include <stdarg.h>
#include <string.h>

#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_YELLOW  "\x1b[33m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_RESET   "\x1b[0m"

void log_printf(const char *prefix, const char *fmt, ...) {
    const char *color = "";

#if LOG_COLOR_ENABLE
    if (prefix) {
        if (strcmp(prefix, "INFO") == 0)      color = ANSI_COLOR_GREEN;
        else if (strcmp(prefix, "WARN") == 0) color = ANSI_COLOR_YELLOW;
        else if (strcmp(prefix, "ERROR") == 0) color = ANSI_COLOR_RED;
    }
#endif

    char buffer[256];
    int len = 0;

#if LOG_COLOR_ENABLE
    len += snprintf(buffer + len, sizeof(buffer) - len, "%s", color);
#endif

    if (prefix && LOG_USE_PREFIX) {
        len += snprintf(buffer + len, sizeof(buffer) - len, "[%s] ", prefix);
    }

    va_list args;
    va_start(args, fmt);
    len += vsnprintf(buffer + len, sizeof(buffer) - len, fmt, args);
    va_end(args);

#if LOG_COLOR_ENABLE
    len += snprintf(buffer + len, sizeof(buffer) - len, ANSI_COLOR_RESET);
#endif

    // Garante quebra de linha se faltar
    if (len > 0 && buffer[len - 1] != '\n') {
        len += snprintf(buffer + len, sizeof(buffer) - len, "\r\n");
    }

    printf("%s", buffer);
}
