/*
 * servo.h
 *
 *  Created on: Jul 17, 2025
 *      Author: vasanth
 */

#ifndef INC_SERVO_H_
#define INC_SERVO_H_

#include "stm32f4xx_hal.h"
#include <stdint.h>




void rotateServoMotor(uint16_t angle);
void lock();
void unlock();


#endif /* INC_SERVO_H_ */
