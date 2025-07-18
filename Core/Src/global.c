/*
 * global.c
 *
 *  Created on: Jul 17, 2025
 *      Author: vasanth
 */
#include "global.h"

char passBuffer[PASS_LENGTH + 1] = {0};
char flashPassBuffer[PASS_LENGTH + 1] = "12345678";
uint8_t passPointer = 0;
operation_t mode = NORMAL;

// Queue handles
QueueHandle_t sendDisplayQueue;
QueueHandle_t sendValidatorQueue;
QueueHandle_t validatorQueue;
QueueHandle_t sendUpdationQueue;
QueueHandle_t updatorQueue;
QueueSetHandle_t xQueueSet = NULL;
