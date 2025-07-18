/*
 * state.h
 *
 *  Created on: Jun 24, 2025
 *      Author: vasanth
 */

#ifndef INC_STATE_H_
#define INC_STATE_H_

typedef enum operation {
	NORMAL,
	UPDATE,
}operation_t;

typedef enum passwordValidityState{
	INVALID,
	VALID,
}passwordValid_t;

typedef enum passwordUpdationState{
	UPDATION_SUCCESS,
	UPDATION_FAILED,
}passwordUpdation_t;

#endif /* INC_STATE_H_ */
