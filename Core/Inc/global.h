/*
 * global.h
 *
 *  Created on: Jul 17, 2025
 *      Author: vasanth
 */

#ifndef INC_GLOBAL_H_
#define INC_GLOBAL_H_

#include "main.h"
#include "state.h"
#include "config.h"


extern char passBuffer[PASS_LENGTH + 1];
extern char flashPassBuffer[PASS_LENGTH + 1];
extern uint8_t passPointer;
extern operation_t mode;

// Queues
extern QueueHandle_t sendDisplayQueue;
extern QueueHandle_t sendValidatorQueue;
extern QueueHandle_t validatorQueue;
extern QueueHandle_t sendUpdationQueue;
extern QueueHandle_t updatorQueue;
extern QueueSetHandle_t xQueueSet;


#endif /* INC_GLOBAL_H_ */
