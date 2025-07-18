/*
 * log.h
 *
 *  Created on: Jul 8, 2025
 *      Author: vasanth
 */

#ifndef INC_LOG_H_
#define INC_LOG_H_

#define INFO "INFO"
#define ERROR "ERROR"
#include "main.h"

extern UART_HandleTypeDef huart4;


#define EVENT_LOG(level,fmt, ...)                             \
    do {                                                \
        char logBuffer[128];                            \
        snprintf(logBuffer, sizeof(logBuffer),          \
            "%s: " fmt "\n",level, ##__VA_ARGS__);        \
        HAL_UART_Transmit(&huart4, (uint8_t*)logBuffer, \
                          strlen(logBuffer), HAL_MAX_DELAY); \
    } while(0)

#endif /* INC_LOG_H_ */
