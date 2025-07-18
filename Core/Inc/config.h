/*
 * config.h
 *
 *  Created on: Jul 17, 2025
 *      Author: vasanth
 */

#ifndef INC_CONFIG_H_
#define INC_CONFIG_H_

#define PASS_LENGTH 8
#define FLASH_STORAGE_ADDR 	0x080E0000

#define RESET_PASS_BUFFER(buffer) \
    do { passPointer = 0; memset(buffer, 0, sizeof(buffer)); } while (0)

#define RESET_PASSPOINTER() \
    do { passPointer = 0; } while (0)


#endif /* INC_CONFIG_H_ */
